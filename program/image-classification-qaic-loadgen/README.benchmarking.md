# Benchmarking

## Run Options

* `--power` adds power measurement to the experiment run
* `--group.edge` runs two scenarios: `--scenario=offline` and `--scenario=singlestream`
* `--group.datacenter` runs two scenarios: `--scenario=offline` and `--scenario=server`
* `--group.open` runs the following modes: `--mode=accuracy` and `--mode=performance`
* `--group.closed` runs the modes for `--group.open` and in addition the following compliance tests: `--compilance,=TEST01,TEST04-A,TEST04-B,TEST05`
* `--pre_fan=150 --post_fan=50` - sets [fan speed](https://github.com/krai/ck-qaic/blob/main/docker/README.md#set-the-fan-speed) before and after the benchmark.
* `--vc=12` - sets [device frequency](https://github.com/krai/ck-qaic/blob/main/docker/README.md#device-frequency). If the `vc_value_default` is included in cmdgen metadata it is enough to do `--vc` and the value will be fetched from cmdgen. Without `--vc` the device will operate at max frequency 1450 MHz corresponding to `--vc=17`.
* `--timestamp` - adds timestamp to the filename in the format `%Y%m%dT%H%M%S`.
  
**We can run individual experiments by using the individual scenario/mode instead of the `group` option**

## Edge Category
### R282_Z93_Q1

#### Quick Accuracy Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q1 --sdk=1.7.1.12 --model=resnet50 \
--mode=accuracy --scenario=offline 
```
#### Full Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q1 --sdk=1.7.1.12 --model=resnet50 \
--group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
```

### R282_Z93_Q5 
#### Quick Accuracy Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q5 --sdk=1.7.1.12 --model=resnet50 \
--mode=accuracy --scenario=offline
```
#### Full Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q5 --sdk=1.7.1.12 --model=resnet50 \
--group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
```

### AEDK_15W
#### Quick Accuracy Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=aedk_15w --sdk=1.7.1.12 --model=resnet50 \
--mode=accuracy --scenario=offline 
```
#### Full Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=aedk_15w --sdk=1.7.1.12 --model=resnet50 \
--group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
```

### AEDK_20W
#### Quick Accuracy Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=aedk_20w --sdk=1.7.1.12 --model=resnet50 \
--mode=accuracy --scenario=offline
```
#### Full Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=aedk_20w --sdk=1.7.1.12 --model=resnet50 \
--group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
```

## Datacenter Category
### R282_Z93_Q8
#### Quick Accuracy Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q8 --sdk=1.7.1.12 --model=resnet50 \
--mode=accuracy --scenario=offline
```
#### Full Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q8 --sdk=1.7.1.12 --model=resnet50 \
--group.edge --group.closed --offline_target_qps=1 \ --server_target_qps=1
```

### G292_Z43_Q16
#### Quick Accuracy Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=g292_z43_q16 --sdk=1.7.1.12 --model=resnet50 \
--mode=accuracy --scenario=offline 
```
#### Full Run
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=g292_z43_q16 --sdk=1.7.1.12 --model=resnet50 \
--group.edge --group.closed --offline_target_qps=1 \ --server_target_qps=1
```

## Docker option

### Launch a reusable Docker container
```
CONTAINER_ID=`ck run cmdgen:benchmark.image-classification.qaic-loadgen  --docker=container_only --out=none \ 
--sdk=1.7.1.12 --model_name=resnet50 --experiment_dir`
```

#### Test
```
docker container ps
```
<details><pre>
CONTAINER ID   IMAGE                              COMMAND               CREATED          STATUS          PORTS     NAMES
1970b84476cc   krai/mlperf.resnet50.full:ubuntu_1.7.1.12   "/bin/bash -c bash"   4 seconds ago   Up 2 seconds             eager_germain
</pre></details>

When `--docker=container_only` or `--docker` are set the following optional parameters can be used:


`--experiment_dir` - directory with experimental data (`${CK_EXPERIMENT_DIR}`by default)

`--volume <experiment_dir_default>:<docker_experiment_dir_default>` - map directory in docker to directory in local machine

`--docker_experiment_dir_default`  - `/home/krai/CK_REPOS/local/experiment` by default

` --experiment_dir_default`  - `${CK_EXPERIMENT_DIR}` by default
 
`--docker_image`   - `krai/mlperf.<model_name>:ubuntu_<sdk>` by default

`<model_name>` - `resnet50`      

`<sdk>` - for example, `1.7.1.12`

`--shared_group_name` - `qaic` by default


### Quick Accuracy Check

```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q1 --sdk=1.7.1.12 --model=resnet50 \
--mode=accuracy --scenario=offline --target_qps=1 \
--container=$CONTAINER_ID
```

## SUTs

### `r282_z93_q1`

```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q1 --sdk=1.7.1.12 --model=resnet50 \
--group.edge --group.closed --target_qps=1 --target_latency=1000 \
--container=$CONTAINER_ID
```

### `r282_z93_q5`

```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q5 --sdk=1.7.1.12 --model=resnet50 \
--group.edge --group.closed --target_qps=1 --target_latency=1000 \
--container=$CONTAINER_ID
```

### `r282_z93_q8`

```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=r282_z93_q8 --sdk=1.7.1.12 --model=resnet50 \
--group.datacenter --group.closed --target_qps=1 --server_target_qps=1 \
--container=$CONTAINER_ID
```

### `g292_z43_q16`

```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--sut=g292_z43_q16 --sdk=1.7.1.12 --model=resnet50 \
--group.datacenter --group.closed --target_qps=1 --server_target_qps=1 \
--container=$CONTAINER_ID
```

## Miscellaneous useful commands

### Useful `ipmitool` commands

#### Read the fan speed

##### Gigabyte R282-Z93
```
sudo ipmitool sensor get BPB_FAN_1A
```
<details><pre>
Locating sensor record...
Sensor ID              : BPB_FAN_1A (0xa0)
 Entity ID             : 29.1
 Sensor Type (Threshold)  : Fan
<b> Sensor Reading        : 8100 (+/- 0) RPM</b>
 Status                : ok
 Lower Non-Recoverable : na
 Lower Critical        : 1200.000
 Lower Non-Critical    : 1500.000
 Upper Non-Critical    : na
 Upper Critical        : na
 Upper Non-Recoverable : na
 Positive Hysteresis   : Unspecified
 Negative Hysteresis   : 150.000
 Assertion Events      :
 Assertions Enabled    : lnc- lcr-
 Deassertions Enabled  : lnc- lcr-
</pre></details>

##### Gigabyte G292-Z43
```
sudo ipmitool sensor get SYS_FAN2
```
<details><pre>
Locating sensor record...
Sensor ID              : SYS_FAN2 (0xa3)
 Entity ID             : 29.4
 Sensor Type (Threshold)  : Fan
 <b>Sensor Reading        : 10800 (+/- 0) RPM</b>
 Status                : ok
 Lower Non-Recoverable : 0.000
 Lower Critical        : 1200.000
 Lower Non-Critical    : 1500.000
 Upper Non-Critical    : 38250.000
 Upper Critical        : 38250.000
 Upper Non-Recoverable : 38250.000
 Positive Hysteresis   : Unspecified
 Negative Hysteresis   : 150.000
 Assertion Events      :
 Assertions Enabled    : lnc- lnc+ lcr- lcr+ lnr- lnr+ unc- unc+ ucr- ucr+ unr- unr+
 Deassertions Enabled  : lnc- lnc+ lcr- lcr+ lnr- lnr+ unc- unc+ ucr- ucr+ unr- unr+
</pre></details>

#### Set the fan speed

##### Gigabyte R282-Z93, G292-Z43

Value | Speed, RPM
-|-
0     | 3,000
25    | 4,200
50    | 5,550
75    | 6,750
100   | 8,100
125   | 9,450
150   | 10,800
200   | 13,350
250   | 15,900

For example, to set the fan speed to 8,100 RPM, use <b>100</b>:

<pre>
sudo ipmitool raw 0x2e 0x10 0x0a 0x3c 0 64 1 <b>100</b> 0xFF
</pre>

### Useful `watch` commands
{%
    include-markdown "../shared_docs/watch.md"
%}