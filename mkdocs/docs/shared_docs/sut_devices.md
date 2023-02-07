
<div class="result" markdown>

=== "r282_z93_q1"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q1 --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --target_qps=1 --target_latency=1000 \
    --container=$CONTAINER_ID
    ```

=== "r282_z93_q5"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q5 --sdk=1.7.1.12 --model=resnet50 \
    --group.edge --group.closed --target_qps=1 --target_latency=1000 \
    --container=$CONTAINER_ID
    ```

=== "r282_z93_q8"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=r282_z93_q8 --sdk=1.7.1.12 --model=resnet50 \
    --group.datacenter --group.closed --target_qps=1 --server_target_qps=1 \
    --container=$CONTAINER_ID
    ```

=== "g292_z43_q16"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --sut=g292_z43_q16 --sdk=1.7.1.12 --model=resnet50 \
    --group.datacenter --group.closed --target_qps=1 --server_target_qps=1 \
    --container=$CONTAINER_ID
    ```

</div>