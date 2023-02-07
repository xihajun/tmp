
## Edge Category

<div class="result" markdown>

=== "r282_z93_q1"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q1 --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline 
    ```

=== "r282_z93_q5"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q5 --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline
    ```

=== "aedk_15w"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=aedk_15w --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline 
    ```

=== "aedk_20w"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=aedk_20w --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline
    ```

</div>

<div class="result" markdown>

=== "r282_z93_q1"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q5 --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
    ```

=== "r282_z93_q5"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q5 --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
    ```

=== "aedk_15w"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=aedk_15w --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
    ```

=== "aedk_20w"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=aedk_20w --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --offline_target_qps=1 \ --singlestream_target_latency=1000 --multistream_target_latency=1000
    ```

</div>

## Datacenter Category

### Quick Accuracy Run


<div class="result" markdown>

=== "r282_z93_q8"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q8 --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline
    ```

=== "g292_z43_q16"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=g292_z43_q16 --sdk=1.7.1.12 --model=resnet50 \
    --mode=accuracy --scenario=offline 
    ```

</div>

!!! Note
    
    For those `_qx` SUTs, we will require the access from qualcomm.

### Full Run

<div class="result" markdown>

=== "r282_z93_q8"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q8 --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --offline_target_qps=1 \ --server_target_qps=1
    ```

=== "g292_z43_q16"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=g292_z43_q16 --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --offline_target_qps=1 \ --server_target_qps=1
    ```

</div>
