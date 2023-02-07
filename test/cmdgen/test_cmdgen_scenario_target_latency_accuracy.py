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
# A selection of edge  target_latency and scenarios.
scenario_target1_target2 = [
    ('singlestream', 'singlestream_target_latency', 'target_latency'),
    ('multistream',  'multistream_target_latency', 'target_latency'),
]

scenario_target = [
    ( 'singlestream', 'target_latency'),
    ( 'singlestream', 'singlestream_target_latency'),
    ( 'multistream',  'target_latency'),
    ( 'multistream',  'multistream_target_latency'),
]
# A selection of sut
sut = [ 'q1_std_edge', 'q4_std_edge' ]

scenario = [ ['singlestream'], ['multistream'] ]

# A selection of integer or floating-point values.
value = [ '123', '0.123', '456.', '123.456' ]

value1_value2 = [ ('123', '234'), ('0.123', '0.234') ]

@pytest.mark.parametrize("sdk", sdk)
@pytest.mark.parametrize("implementation,model", implementation_model)
@pytest.mark.parametrize("sut", sut)
@pytest.mark.parametrize("scenario", scenario)

def test_cmdgen_target_sut(sdk, implementation, model, sut, scenario):
    cmdgen_target_value(sdk, implementation, model, sut, scenario, value1=None, value2=None)

@pytest.mark.parametrize("sdk", sdk)
@pytest.mark.parametrize("implementation,model", implementation_model)
@pytest.mark.parametrize("sut", sut)
@pytest.mark.parametrize("scenario_target", scenario_target)
@pytest.mark.parametrize("value", value)

def test_cmdgen_target_sut_value1(sdk, implementation, model, sut, scenario_target, value):
    cmdgen_target_value(sdk, implementation, model, sut, scenario_target, value1=value)

@pytest.mark.parametrize("sdk", sdk)
@pytest.mark.parametrize("implementation,model", implementation_model)
@pytest.mark.parametrize("sut", sut)
@pytest.mark.parametrize("scenario_target1_target2", scenario_target1_target2)
@pytest.mark.parametrize("value1,value2", value1_value2)

def test_cmdgen_target_sut_value12(sdk, implementation, model, sut, scenario_target1_target2, value1, value2):
    cmdgen_target_value(sdk, implementation, model, sut, scenario_target1_target2, value1, value2)

def cmdgen_target_value(sdk, implementation, model, sut, scenario_target, value1=None, value2=None):
    # No multistream for bert-99.
    if model == 'bert-99' and scenario_target[0] == 'multistream': return

    # No bert-99.9 for edge.
    if model == 'bert-99.9'and 'edge' in sut: return

    # Access.
    i={'action':'gen', 'module_uoa':'cmdgen', 'mode':'accuracy', 'sdk':sdk}
    i.update({'data_uoa':implementation, 'model':model})

    if value1 == None and value2 == None:
        i.update({'sut':sut, 'scenario':scenario_target[0]})
    elif (value1 != None and value2 == None ):
        i.update({'sut':sut, 'scenario':scenario_target[0], scenario_target[1]:value1})
    elif (value1 != None and value2 != None):
        i.update({'sut':sut, 'scenario':scenario_target[0], scenario_target[1]:value1, scenario_target[2]:value2})

    r=ck.access(i)
    print(r)
    return_code = r['return']
    assert return_code == 0
    cmds = r.get('cmds')
    assert len(cmds) == 1
    cmd = cmds[0]
    match = re.search(r'-target_latency.(\d*\.?\d*)', cmd)
    match_loadgen = re.search(r'--env.CK_LOADGEN_TARGET_LATENCY=(\d*\.?\d*)', cmd)

    assert match == None
    assert match_loadgen == None
