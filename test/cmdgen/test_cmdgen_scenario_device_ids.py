#!/usr/bin/python3

import pytest,re
import ck.kernel as ck


# A selection of SDK versions.
sdk = [ '1.7.1.12', '1.8.0' ]

# A selection of implementations and models.
implementation_model = [
    ('benchmark.image-classification.qaic-loadgen',   'resnet50'),
    ('benchmark.packed-bert.qaic-loadgen',            'bert-99'),
    ('benchmark.packed-bert.qaic-loadgen',            'bert-99.9'),
    ('benchmark.object-detection.qaic-loadgen',       'retinanet'),
    ('benchmark.object-detection-large.qaic-loadgen', 'ssd_resnet34'),
    ('benchmark.object-detection-small.qaic-loadgen', 'ssd_mobilenet'),
]
scenario_device_ids = [
    ( 'singlestream', 'device_ids'),
    ( 'multistream',  'device_ids'),
    ( 'offline',      'device_ids'),
]
# A selection of sut
sut = [ 'q1_std_edge', 'q4_std_edge' ]

mode=[ 'accuracy' ]

# A selection of integer or floating-point values.
value = [ '0' ]

@pytest.mark.parametrize("sdk", sdk)
@pytest.mark.parametrize("implementation,model", implementation_model)
@pytest.mark.parametrize("sut", sut)
@pytest.mark.parametrize("mode", mode)
@pytest.mark.parametrize("scenario_device_ids", scenario_device_ids)


def test_cmdgen_device_ids(sdk, implementation, model, sut, mode, scenario_device_ids):
    cmdgen_device_ids_value(sdk, implementation, model, sut, mode, scenario_device_ids)

@pytest.mark.parametrize("sdk", sdk)
@pytest.mark.parametrize("implementation,model", implementation_model)
@pytest.mark.parametrize("sut", sut)
@pytest.mark.parametrize("mode", mode)
@pytest.mark.parametrize("scenario_device_ids", scenario_device_ids)
@pytest.mark.parametrize("value", value)

def test_cmdgen_device_ids_value(sdk, implementation, model, sut, mode, scenario_device_ids, value):
    cmdgen_device_ids_value(sdk, implementation, model, sut, mode, scenario_device_ids, value)

def cmdgen_device_ids_value(sdk, implementation, model, sut, mode, scenario_device_ids, value=None):
    # No multistream for bert-99.
    if model == 'bert-99' and scenario_device_ids[0] == 'multistream': return

    # No bert-99.9 for edge.
    if model == 'bert-99.9'and 'edge' in sut: return

    # Access.
    i={'action':'gen', 'module_uoa':'cmdgen', 'mode':mode, 'sdk':sdk}
    i.update({'data_uoa':implementation, 'model':model})

    if value == None:
        i.update({'sut':sut, 'scenario':scenario_device_ids[0]})
    elif (value != None ):
        i.update({'sut':sut, 'scenario':scenario_device_ids[0], scenario_device_ids[1]:value})

    r=ck.access(i)
    return_code = r['return']
    assert return_code == 0
    cmds = r.get('cmds')
    assert len(cmds) == 1
    cmd = cmds[0]
    match_loadgen = re.search(r'--env.CK_ENV_QAIC_DEVICE_IDS=(\d*\.?\d*)', cmd)
    print("match_loadgen=",match_loadgen)

    if value != None:
        assert match_loadgen.group(1) == value 
    else:
        assert match_loadgen.group(1) != None 

