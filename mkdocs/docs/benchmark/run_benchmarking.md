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
