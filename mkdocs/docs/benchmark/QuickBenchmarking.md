# Benchmarking

!!! note "Have you used CK before?"
    If not, please check out the [Quick CK Guide](QuickCKGuide.md) first.

!!! note "Which command variant should I use?"
    - Dockerless: Recommended for general use on Edge appliances.
    - Recordless: Recommended for one-off checks on servers.
    - Stateless: Recommended for general use on servers.
    - Stateful: Recommended for debugging on servers.

## Image Classification - ResNet50

### [CmdGen](https://github.com/ctuning/ck-ml/tree/c84964bb019fe1b12ba952fafd92274ecdc64380/cmdgen)

!!! note "About CmdGen"
    CmdGen\[[1]\] is a command-line generator that generates a command-line for a given MLPerf benchmark, model, and scenario. It is a part of the [CK-ML](https://github.com/ctuning/ck-ml/tree/c84964bb019fe1b12ba952fafd92274ecdc64380/cmdgen).
    [1]: https://cknowledge.io/c/module/cmdgen/

#### Offline

##### Accuracy

<div class="result" markdown>
=== "Dockerless"
    ```
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 \
    --sdk=1.8.3.7 --sut=q4_std_edge --mode=accuracy --scenario=offline \
    --verbose
    ```

=== "Recordless"
     ```
     ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 \
     --sdk=1.8.3.7 --sut=q4_std_edge --mode=accuracy --scenario=offline \
     --verbose --docker
     ```

=== "Stateless"
     ```
     ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 \
     --sdk=1.8.3.7 --sut=q4_std_edge --mode=accuracy --scenario=offline \
     --verbose --docker --experiment_dir
     ```

=== "Stateful"
     ```
     ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 \
     --sdk=1.8.3.7 --sut=q4_std_edge --mode=accuracy --scenario=offline \
     --verbose --container=$CONTAINER_ID_RESNET50
     ```

</div>

##### Performance

<div class="result" markdown>
=== "Dockerless"
    ```
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 \
    --sdk=1.8.3.7 --sut=q4_std_edge --mode=performance --scenario=offline \
    --target_qps=1 --verbose
    ```

=== "Recordless"
     ```
     ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 \
     --sdk=1.8.3.7 --sut=q4_std_edge --mode=performance --scenario=offline \
     --target_qps=1 --verbose --docker
     ```

=== "Stateless"
     ```
     ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 \
     --sdk=1.8.3.7 --sut=q4_std_edge --mode=performance --scenario=offline \
     --target_qps=1 --verbose --docker --experiment_dir
     ```

=== "Stateful"
     ```
     ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 \
     --sdk=1.8.3.7 --sut=q4_std_edge --mode=performance --scenario=offline \
     --target_qps=1 --verbose --container=$CONTAINER_ID_RESNET50
     ```

     where a container with a hash `CONTAINER_ID_RESNET50` is created as follows:
     ```
     CONTAINER_ID_RESNET50=$(ck run --docker=container_only --docker_os=ubuntu \
     cmdgen:benchmark.image-classification.qaic-loadgen --model_name=resnet50 \
     --sdk=1.8.3.7 --experiment_dir --out=none)
     ```
     and can be interactively modified as follows:
     ```
     docker exec -it $CONTAINER_ID_RESNET50 /bin/bash
     ```


## Quick run `on Device` (<2 minutes per performance run)

<div class="result" markdown>

=== "Image Classification: resnet50"

    ``` bash
    ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
    --model=resnet50 --sdk=1.8.2.10 --sut=eb6 --group.edge --group.open \
    --offline_target_qps=1 --singlestream_target_latency=1000 \
    --multistream_target_latency=1000 --multistream_query_count=660
    ```

=== "Language Processing: bert99"

    ``` bash
    ck run cmdgen:benchmark.packed-bert.qaic-loadgen --verbose \
    --model=bert-99 --sdk=1.8.2.10 --sut=eb6 --group.edge --group.open \
    --offline_target_qps=1 --singlestream_target_latency=1000 \
    --multistream_target_latency=1000 --multistream_query_count=666
    ```

</div>

<div class="result" markdown>

## Quick Accuracy Run `on Device`

=== "Object Detection: SSD Small"

    ``` bash
    ck run cmdgen:benchmark.object-detection-large.qaic-loadgen --verbose \
    --sut=r282_z93_q1 --sdk=1.6.80 --model=ssd_resnet34 \
    --mode=accuracy --scenario=offline
    ```

=== "Object Detection: RetinaNet"

    ``` bash
    ck run cmdgen:benchmark.object-detection.qaic-loadgen --verbose \
    --sut=r282_z93_q2_prev --sdk=1.8.0.73 --model=retinanet \
    --mode=accuracy --scenario=offline
    ```

=== "Object Detection: SSD Large"

    ``` bash
    ck run cmdgen:benchmark.object-detection-large.qaic-loadgen --verbose \
    --sut=r282_z93_q1 --sdk=1.6.80 --model=ssd_resnet34 \
    --mode=accuracy --scenario=offline
    ```

</div>


## Quick Run With Script for different devices
```
cd $(ck find repo:ck-qaic)/script/run
```
<div class="result" markdown>

=== "Q18"

    ``` bash
    SUT=g292_z43_q18 SDK_VER=1.6.80 POWER=no DOCKER=yes ./run_datacenter.sh
    ```

=== "Q18e"

    ``` bash
    SUT=g292_z43_q18e SDK_VER=1.6.80 POWER=yes DOCKER=yes ./run_datacenter.sh
    ```

=== "Q16"

    ``` bash
    SUT=g292_z43_q16 SDK_VER=1.6.80 POWER=no DOCKER=yes ./run_datacenter.sh
    ```

=== "Q16e"

    ``` bash
    SUT=g292_z43_q16e SDK_VER=1.6.80 POWER=yes DOCKER=yes ./run_datacenter.sh
    ```

=== "Q8"

    ``` bash
    SUT=r282_z93_q8 SDK_VER=1.6.80 POWER=no DOCKER=yes ./run_datacenter.sh
    ```

=== "Q8e"

    ``` bash
    SUT=r282_z93_q8e SDK_VER=1.6.80 POWER=yes DOCKER=yes ./run_datacenter.sh
    ```

=== "Q5"

    ``` bash
    SUT=r282_z93_q5 SDK_VER=1.6.80 POWER=no DOCKER=yes ./run_edge.sh
    ```

=== "Q5e"

    ``` bash
    SUT=r282_z93_q5e SDK_VER=1.6.80 POWER=yes DOCKER=yes ./run_edge.sh
    ```

=== "Q2"

    ``` bash
    SUT=r282_z93_q2 SDK_VER=1.6.80 POWER=no DOCKER=yes ./run_edge.sh
    ```

=== "Q1"

    ``` bash
    SUT=r282_z93_q1 SDK_VER=1.6.80 POWER=no DOCKER=yes ./run_edge.sh
    ```

=== "PowerEdge R7515 Pro"

    ``` bash
    SUT=q4_pro_dc SDK_VER=1.7.1.12 ./run_datacenter.sh
    ```

=== "EL8000 / PowerEdge R7515 Std"

    ``` bash
    SUT=q4_std_edge SDK_VER=1.7.1.12 ./run_edge.sh
    ```

=== "SE350"

    ``` bash
    SUT=q1_pro_edge SDK_VER=1.7.1.12 ./run_edge.sh
    ```

=== "Gloria "Highend""

    ``` bash
    SUT=gloria1 SDK_VER=1.7.1.12 ./run_edge.sh
    ```

=== "AEDK @ 15W TDP"

    ``` bash
    SUT=aedk_15w SDK_VER=1.6.80 POWER=yes ./run_edge.sh
    ```

=== "AEDK @ 20W TDP"

    ``` bash
    SUT=aedk_20w SDK_VER=1.6.80 POWER=yes ./run_edge.sh
    ```

=== "AEDK @ 25W TDP"

    ``` bash
    SUT=aedk_25w SDK_VER=1.6.80 POWER=yes ./run_edge.sh
    ```

=== "Haishen"

    ``` bash
    SUT=haishen SDK_VER=1.6.80 ./run_edge.sh
    ```

=== "Gloria"

    ``` bash
    SUT=gloria SDK_VER=1.7.1.12 ./run_edge.sh
    ```

=== "Heimdall"

    ``` bash
    SUT=heimdall SDK_VER=1.7.1.12 ./run_edge.sh
    ```

=== "EB6"

    ``` bash
    SUT=eb6 SDK_VER=1.7.1.12 ./run_edge.sh
    ```

!!! Note
    
    For those `_qx` SUTs, we will require the access from qualcomm.

</div>

??? example "Check the experiments"
    <pre><code>krai@eb6:~&dollar; ck list local:experiment:* | sort
    mlperf_v2.1-closed-eb6-qaic-v<a vartag='SDK_VER'>1.8.2.10</a>-aic100-resnet50-multistream-accuracy-dataset_size.50000-preprocessed_using.opencv
    mlperf_v2.1-closed-eb6-qaic-v<a vartag='SDK_VER'>1.8.2.10</a>-aic100-resnet50-multistream-performance-target_latency.1000
    mlperf_v2.1-closed-eb6-qaic-v<a vartag='SDK_VER'>1.8.2.10</a>-aic100-resnet50-offline-accuracy-dataset_size.50000-preprocessed_using.opencv
    mlperf_v2.1-closed-eb6-qaic-v<a vartag='SDK_VER'>1.8.2.10</a>-aic100-resnet50-offline-performance-target_qps.1
    mlperf_v2.1-closed-eb6-qaic-v<a vartag='SDK_VER'>1.8.2.10</a>-aic100-resnet50-singlestream-accuracy-dataset_size.50000-preprocessed_using.opencv
    mlperf_v2.1-closed-eb6-qaic-v<a vartag='SDK_VER'>1.8.2.10</a>-aic100-resnet50-singlestream-performance-target_latency.1000</code></pre>


<div class="result" markdown>

=== "Datacenter and Edge servers"

    ```
    QUICK_RUN=yes OFFLINE_ONLY=yes WORKLOADS=resnet50 SDK_VER=1.8.2.10 SUT=eb6 ./run_edge.sh
    ```
=== "Image Classification: resnet50"

    ```
    QUICK_RUN=yes OFFLINE_ONLY=yes WORKLOADS=resnet50 SDK_VER=1.8.2.10 SUT=eb6 ./run_edge.sh
    ```
</div>

## Short run `on Device` (2 minutes per performance run)

```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--model=resnet50 --sdk=1.8.2.10 --sut=eb6 --group.edge --group.open \
--offline_target_qps=1380 --singlestream_target_latency=5 \
--multistream_target_latency=10.5 --multistream_query_count=62857
```

??? example "Check the experiments"
    <pre><code>krai@eb6:~&dollar; ck list experiment:* | grep -v latency.1000  | sort
    mlperf_v2.1-closed-eb6-qaic-v1.8.2.10-aic100-resnet50-multistream-accuracy-dataset_size.50000-preprocessed_using.opencv
    mlperf_v2.1-closed-eb6-qaic-v1.8.2.10-aic100-resnet50-multistream-performance-target_latency.10.5
    mlperf_v2.1-closed-eb6-qaic-v1.8.2.10-aic100-resnet50-offline-accuracy-dataset_size.50000-preprocessed_using.opencv
    mlperf_v2.1-closed-eb6-qaic-v1.8.2.10-aic100-resnet50-offline-performance-target_qps.1
    mlperf_v2.1-closed-eb6-qaic-v1.8.2.10-aic100-resnet50-offline-performance-target_qps.1380
    mlperf_v2.1-closed-eb6-qaic-v1.8.2.10-aic100-resnet50-singlestream-accuracy-dataset_size.50000-preprocessed_using.opencv
    mlperf_v2.1-closed-eb6-qaic-v1.8.2.10-aic100-resnet50-singlestream-performance-target_latency.5
    </code></pre>


## Full run `on Device` (10 minutes per performance run)

```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --verbose \
--model=resnet50 --sdk=1.8.2.10 --sut=eb6 --group.edge --group.open \
--offline_target_qps=6900 --singlestream_target_latency=1 \
--multistream_target_latency=2.1 --multistream_query_count=314285
```

## Inspecting the results

Expand Details after individual [Accuracy/Performance commands](https://gist.github.com/sahelib25/89100fc07091c5c41e619205338ebd94) to see `grep` commands that can be used to quickly inspect the obtained results.

## Further info

Please contact <a vartag='ANTON_EMAIL'>anton@krai.ai</a> if you have any problems or questions.
