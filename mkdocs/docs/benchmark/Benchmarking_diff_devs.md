# Benchmarking on Different Device

This page will show example of `sdk = `<a vartag='SDK_EXAMPLE'>1.7.1.12</a>

??? example "Show me the Run Options"

    - `--power` adds power measurement to the experiment run
    - `--group.edge` runs two scenarios: `--scenario=offline` and `--scenario=singlestream`
    - `--group.datacenter` runs two scenarios: `--scenario=offline` and `--scenario=server`
    - `--group.open` runs the following modes: `--mode=accuracy` and `--mode=performance`
    - `--group.closed` runs the modes for `--group.open` and in addition the following compliance tests: `--compilance,=TEST01,TEST04-A,TEST04-B,TEST05`
    - `--pre_fan=150 --post_fan=50` - sets [fan speed](https://github.com/krai/ck-qaic/blob/main/docker/README.md#set-the-fan-speed) before and after the benchmark.
    - `--vc=12` - sets [device frequency](https://github.com/krai/ck-qaic/blob/main/docker/README.md#device-frequency). If the `vc_value_default` is included in cmdgen metadata it is enough to do `--vc` and the value will be fetched from cmdgen. Without `--vc` the device will operate at max frequency 1450 MHz corresponding to `--vc=17`.
    - `--timestamp` - adds timestamp to the filename in the format `%Y%m%dT%H%M%S`.
    
    **We can run individual experiments by using the individual scenario/mode instead of the `group` option**


## Quick Accuracy Run


<div class="result" markdown>
=== "Edge Category"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q1 --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline 
    ```

=== "Datacenter Category"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q8 --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline
    ```


=== "Docker Option"
    ``` bash
    # Launch a reusable Docker container
    CONTAINER_ID=`ck run cmdgen:benchmark.image-classification.qaic-loadgen  --docker=container_only --out=none \ 
    --sdk=1.7.1.12 --model_name=resnet50 --experiment_dir`

    # Test Docker
    docker container ps

    # Quick Accuracy Check
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q1 --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline --target_qps=1 \
    --container=$CONTAINER_ID
    ```
</div>

## Full Run


<div class="result" markdown>

=== "Edge Category"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q5 --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
    ```
=== "Data Center Category"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q8 --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --offline_target_qps=1 \ --server_target_qps=1
    ```

</div>


??? example "Docker"

    When `--docker=container_only` or `--docker` are set the following optional parameters can be used:

    - `--experiment_dir` - directory with experimental data (`${CK_EXPERIMENT_DIR}`by default)

    - `--volume <experiment_dir_default>:<docker_experiment_dir_default>` - map directory in docker to directory in local machine

    - `--docker_experiment_dir_default`  - `/home/krai/CK_REPOS/local/experiment` by default

    - ` --experiment_dir_default`  - `${CK_EXPERIMENT_DIR}` by default
    
    - `--docker_image`   - `krai/mlperf.<model_name>:ubuntu_<sdk>` by default

    - `<model_name>` - `resnet50`      

    - `<sdk>` - for example, <a vartag='SDK_EXAMPLE'>1.7.1.12</a>

    - `--shared_group_name` - `qaic` by default

