Submitter | System | Workloads | Deliverables
-|-|-|-
HPE | EL8000 e920d<br>Q4 PCIe Std | ResNet50, RetinaNet,<br>BERT-99 | Peak Performance w/ Power:<br> tuning & submission.

## Results

`Check more [here](../Result-v2.0.md)

Round | ResNet50 Single Stream | ResNet50 Multi Stream | ResNet50 Offline | RetinaNet Single Stream | RetinaNet Multi Stream | RetinaNet Offline | BERT-99 Single Stream | BERT-99 Offline
-|-|-|-|-|-|-|-|-
v2.1 | 0.62 | 0.66 | 77,652.40 | 25.39 | 63.67 | 660.94 | 7.31 | 2,863.30
v3.0 | 0.54 | 0.66 |79,205.10 | 15.20 | 27.52 | 1,102.85 | | 2,920.46
Delta | -12.9% | 0% | +2.0% | -40.13% | -56.78% | +66.8% | | +2.0%

## Device Details

=== "aedkr_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_aedkr_prev.sh"
    %}
    ```
=== "q1_std_edge_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_q1_std_edge_prev.sh"
    %}
    ```
=== "r282_z93_q5"
    ```
    {%
    include-markdown "../defs-v2.1/def_r282_z93_q5.sh"
    %}
    ```
=== "r282_z93_q5_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_r282_z93_q5_prev.sh"
    %}
    ```
=== "aedke"
    ```
    {%
    include-markdown "../defs-v2.1/def_aedke.sh"
    %}
    ```
=== "g292_z43_q16"
    ```
    {%
    include-markdown "../defs-v2.1/def_g292_z43_q16.sh"
    %}
    ```
=== "gloria"
    ```
    {%
    include-markdown "../defs-v2.1/def_gloria.sh"
    %}
    ```
=== "q4_pro_dc"
    ```
    {%
    include-markdown "../defs-v2.1/def_q4_pro_dc.sh"
    %}
    ```
=== "r282_z93_q5e"
    ```
    {%
    include-markdown "../defs-v2.1/def_r282_z93_q5e.sh"
    %}
    ```
=== "aedke_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_aedke_prev.sh"
    %}
    ```
=== "g292_z43_q16_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_g292_z43_q16_prev.sh"
    %}
    ```
=== "gloria1"
    ```
    {%
    include-markdown "../defs-v2.1/def_gloria1.sh"
    %}
    ```
=== "q4_pro_dc_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_q4_pro_dc_prev.sh"
    %}
    ```
=== "r282_z93_q5e_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_r282_z93_q5e_prev.sh"
    %}
    ```
=== "aedkh"
    ```
    {%
    include-markdown "../defs-v2.1/def_aedkh.sh"
    %}
    ```
=== "g292_z43_q16e"
    ```
    {%
    include-markdown "../defs-v2.1/def_g292_z43_q16e.sh"
    %}
    ```
=== "gloria1_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_gloria1_prev.sh"
    %}
    ```
=== "q4_std_edge"
    ```
    {%
    include-markdown "../defs-v2.1/def_q4_std_edge.sh"
    %}
    ```
=== "r282_z93_q8"
    ```
    {%
    include-markdown "../defs-v2.1/def_r282_z93_q8.sh"
    %}
    ```
=== "g292_z43_q18"
    ```
    {%
    include-markdown "../defs-v2.1/def_g292_z43_q18.sh"
    %}
    ```
=== "g292_z43_q18_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_g292_z43_q18_prev.sh"
    %}
    ```
=== "q1_std"
    ```
    {%
    include-markdown "../defs-v2.1/def_q1_std.sh"
    %}
    ```
=== "r282_z93_q8e"
    ```
    {%
    include-markdown "../defs-v2.1/def_r282_z93_q8e.sh"
    %}
    ```
=== "g292_z43_q18e"
    ```
    {%
    include-markdown "../defs-v2.1/def_g292_z43_q18e.sh"
    %}
    ```
=== "g292_z43_q18e_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_g292_z43_q18e_prev.sh"
    %}
    ```
=== "q1_std_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_q1_std_prev.sh"
    %}
    ```
=== "r282_z93_q8e_prev"
    ```
    {%
    include-markdown "../defs-v2.1/def_r282_z93_q8e_prev.sh"
    %}
    ```
=== "aedkr"
    ```
    {%
    include-markdown "../defs-v2.1/def_aedkr.sh"
    %}
    ```
=== "q1_std_edge"
    ```
    {%
    include-markdown "../defs-v2.1/def_q1_std_edge.sh"
    %}
    ```

## Benchmarking Scripts

Please use the scripts below for benchmarking 3 different models (Bert, ResNet, and RetinaNet) with 3 different scenarios: Offline, SingleStream on different devices.

=== "BERT-99"
    === "Offline"
        === "Performance"
            <pre><code>## BERT-99 Offline Performance</code></pre>
            <pre><code>time ck run cmdgen:benchmark.packed-bert.qaic-loadgen --model=bert-99 --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=offline --mode=performance --sut=q4_std_edge --target_qps=3000</code></pre> 
    === "SingleStream"
        === "Performance (+ Accuracy)"
            <pre><code>## BERT-99 SingleStream Performance (+ Accuracy)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time SHORT_RUN=no POWER=no UPDATE_CK_QAIC=no WORKLOADS=bert SDK_VER=1.8.3.7 SINGLESTREAM_ONLY=yes \ 
            DEFS_DIR=$CK_REPOS/ck-qaic-scripts/defs-v3.0 SUT=q4_std_edge DOCKER=yes ./run_edge.sh</code></pre> 
             
            ??? example "Results" 
                {"exact_match": 82.45979186376537, "f1": 90.06234274518785} 
                ... 
                ================================================ 
                MLPerf Results Summary 
                ================================================ 
                SUT name : QAIC_SUT 
                Scenario : SingleStream 
                Mode     : PerformanceOnly 
                90th percentile latency (ns) : 7428935 
                Result is : VALID 
                Min duration satisfied : Yes 
                Min queries satisfied : Yes 
                Early stopping satisfied: Yes 
                Early Stopping Result: 
                * Processed at least 64 queries (79944). 
                * Would discard 7796 highest latency queries. 
                * Early stopping 90th percentile estimate: 7429380 
                * Early stopping 99th percentile estimate: 7469961 
                ================================================ 
                Additional Stats 
                ================================================ 
                QPS w/ loadgen overhead         : 133.24 
                QPS w/o loadgen overhead        : 135.22 
                Min latency (ns)                : 7231162 
                Max latency (ns)                : 20808418 
                Mean latency (ns)               : 7395465 
                50.00 percentile latency (ns)   : 7393786 
                90.00 percentile latency (ns)   : 7428935 
                95.00 percentile latency (ns)   : 7440266 
                97.00 percentile latency (ns)   : 7447604 
                99.00 percentile latency (ns)   : 7467881 
                99.90 percentile latency (ns)   : 7676371 
                ================================================ 
                Test Parameters Used 
                ================================================ 
                samples_per_query : 1 
                target_qps : 136.986 
                target_latency (ns): 0 
                max_async_queries : 1 
                min_duration (ms): 600000 
                max_duration (ms): 0 
                min_query_count : 1024 
                max_query_count : 0 
                qsl_rng_seed : 14284205019438841327 
                sample_index_rng_seed : 4163916728725999944 
                schedule_rng_seed : 299063814864929621 
                accuracy_log_rng_seed : 0 
                accuracy_log_probability : 0 
                accuracy_log_sampling_target : 0 
                print_timestamps : 0 
                performance_issue_unique : 0 
                performance_issue_same : 0 
                performance_issue_same_index : 0 
                performance_sample_count : 10833 
        === "Performance"
            <pre><code>## BERT-99 SingleStream Performance</code></pre>
            <pre><code>ck run cmdgen:benchmark.packed-bert.qaic-loadgen --verbose --sut=q4_std_edge --sdk=1.8.3.7 \ 
            --docker --experiment_dir --model=bert-99 --mode=performance --scenario=singlestream --singlestream_target_latency=7 \ 
            --vc=16 --sleep_before_ck_benchmark_sec=60</code></pre> 
=== "RetinaNet"
    === "Offline"
        === "Performance"
            <pre><code>## RetinaNet Offline Performance</code></pre>
            <pre><code>time ck run cmdgen:benchmark.object-detection.qaic-loadgen --model=retinanet --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=offline --mode=performance --sut=q4_std_edge --target_qps=1100</code></pre> 
    === "SingleStream"
        === "Accuracy (single device) `OK`"
            <pre><code>## RetinaNet SingleStream Accuracy (single device) `OK`</code></pre>
            <pre><code>time ck run cmdgen:benchmark.object-detection.qaic-loadgen --model=retinanet --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=singlestream --mode=accuracy --sut=q4_std_edge --device_ids=0</code></pre> 
        === "Accuracy (multiple devices) `OK`"
            <pre><code>## RetinaNet SingleStream Accuracy (multiple devices) `OK`</code></pre>
            <pre><code>time ck run cmdgen:benchmark.object-detection.qaic-loadgen --model=retinanet --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=singlestream --mode=accuracy --sut=q4_std_edge --device_ids=0,1</code></pre> 
        === "Performance (+ Accuracy)"
            <pre><code>## RetinaNet SingleStream Performance (+ Accuracy)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time SHORT_RUN=no POWER=no UPDATE_CK_QAIC=no WORKLOADS=retinanet SDK_VER=1.8.3.7 SINGLESTREAM_ONLY=yes \ 
            DEFS_DIR=$CK_REPOS/ck-qaic-scripts/defs-v3.0 SUT=q4_std_edge DOCKER=yes ./run_edge.sh</code></pre> 
        === "Performance"
            <pre><code>## RetinaNet SingleStream Performance</code></pre>
            <pre><code>ck run cmdgen:benchmark.object-detection.qaic-loadgen --verbose --sut=q4_std_edge --sdk=1.8.3.7 \ 
            --docker --experiment_dir --model=retinanet --mode=performance --scenario=singlestream --singlestream_target_latency=15 \ 
            --vc=17 --sleep_before_ck_benchmark_sec=60</code></pre> 
    === "MultiStream"
        === "Performance (+ Accuracy)"
            <pre><code>## RetinaNet MultiStream Performance (+ Accuracy)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time SHORT_RUN=no POWER=no UPDATE_CK_QAIC=no WORKLOADS=retinanet SDK_VER=1.8.3.7 MULTISTREAM_ONLY=yes \ 
            DEFS_DIR=$CK_REPOS/ck-qaic-scripts/defs-v3.0 SUT=q4_std_edge DOCKER=yes ./run_edge.sh</code></pre> 
        === "Performance"
            <pre><code>## RetinaNet MultiStream Performance</code></pre>
            <pre><code>ck run cmdgen:benchmark.object-detection.qaic-loadgen --verbose --sut=q4_std_edge --sdk=1.8.3.7 \ 
            --docker --experiment_dir --model=retinanet --mode=performance --scenario=multistream --multistream_target_latency=27 \ 
            --multistream_query_count=24444 --vc=17 --sleep_before_ck_benchmark_sec=60</code></pre> 
=== "ResNet50"
    === "Offline"
        === "Performance"
            <pre><code>## ResNet50 Offline Performance</code></pre>
            <pre><code>time ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=offline --mode=performance --sut=q4_std_edge --target_qps=80000</code></pre> 
        === "Accuracy (+ Quick Performance)"
            <pre><code>## ResNet50 Offline Accuracy (+ Quick Performance)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time QUICK_RUN=yes POWER=no UPDATE_CK_QAIC=no DOCKER=yes OFFLINE_ONLY=yes SDK_VER=1.8.3.7 \ 
            WORKLOADS=resnet50 SUT=q4_std_edge ./run_edge.sh</code></pre> 
        === "Short Performance (~2 minutes)"
            <pre><code>## ResNet50 Offline Short Performance (~2 minutes)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time SHORT_RUN=yes POWER=no UPDATE_CK_QAIC=no DOCKER=yes OFFLINE_ONLY=yes SDK_VER=1.8.3.7 \ 
            WORKLOADS=resnet50 SUT=q4_std_edge DEFS_DIR=$CK_REPOS/ck-qaic-scripts/defs-v3.0 ./run_edge.sh</code></pre> 
        === "Full Performance (~12 minutes)"
            <pre><code>## ResNet50 Offline Full Performance (~12 minutes)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time SHORT_RUN=no POWER=no UPDATE_CK_QAIC=no DOCKER=yes OFFLINE_ONLY=yes SDK_VER=1.8.3.7 \ 
            WORKLOADS=resnet50 SUT=q4_std_edge DEFS_DIR=$CK_REPOS/ck-qaic-scripts/defs-v3.0 ./run_edge.sh 
            </code></pre> 
        === "Full Performance with Power (~25 minutes)"
            <pre><code>## ResNet50 Offline Full Performance with Power (~25 minutes)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time SHORT_RUN=no POWER=yes UPDATE_CK_QAIC=no DOCKER=yes OFFLINE_ONLY=yes SDK_VER=1.8.3.7 \ 
            WORKLOADS=resnet50 SUT=q4_std_edge DEFS_DIR=$CK_REPOS/ck-qaic-scripts/defs-v3.0 ./run_edge.sh</code></pre> 
    === "SingleStream"
        === "Accuracy (single device) `OK`"
            <pre><code>## ResNet50 SingleStream Accuracy (single device) `OK`</code></pre>
            <pre><code>time ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=singlestream --mode=accuracy --sut=q4_std_edge --device_ids=0</code></pre> 
            <pre> 
            accuracy=75.992%, good=37996, total=50000 
            </pre> 
        === "Accuracy (multiple devices) `HANGS`"
            <pre><code>## ResNet50 SingleStream Accuracy (multiple devices) `HANGS`</code></pre>
            <pre><code>time ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=singlestream --mode=accuracy --sut=q4_std_edge --device_ids=0,1</code></pre> 
        === "Performance (+ Accuracy)"
            <pre><code>## ResNet50 SingleStream Performance (+ Accuracy)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time SHORT_RUN=no POWER=no UPDATE_CK_QAIC=no \ 
            WORKLOADS=resnet50 SDK_VER=1.8.3.7 SINGLESTREAM_ONLY=yes \ 
            DEFS_DIR=$CK_REPOS/ck-qaic-scripts/defs-v3.0 SUT=q4_std_edge \ 
            DOCKER=yes ./run_edge.sh</code></pre> 
        === "Performance"
            <pre><code>## ResNet50 SingleStream Performance</code></pre>
            <pre><code>time ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=singlestream --mode=performance --sut=q4_std_edge --device_ids=0 \ 
            --verbose --singlestream_target_latency=.60</code></pre> 
    === "MultiStream"
        === "Performance (+ Accuracy)"
            <pre><code>## ResNet50 MultiStream Performance (+ Accuracy)</code></pre>
            <pre><code>cd $(ck find ck-qaic:script:run) 
            time SHORT_RUN=no POWER=no UPDATE_CK_QAIC=no \ 
            WORKLOADS=resnet50 SDK_VER=1.8.3.7 MULTISTREAM_ONLY=yes \ 
            DEFS_DIR=$CK_REPOS/ck-qaic-scripts/defs-v3.0 SUT=q4_std_edge \ 
            DOCKER=yes ./run_edge.sh</code></pre> 
        === "Performance"
            <pre><code>## ResNet50 MultiStream Performance</code></pre>
            <pre><code>time ck run cmdgen:benchmark.image-classification.qaic-loadgen --model=resnet50 --docker --experiment_dir \ 
            --sdk=1.8.3.7 --scenario=multistream --mode=performance --sut=q4_std_edge \ 
            --verbose --multistream_target_latency=.65 --multistream_query_count=1015384</code></pre> 