# A Slow Setup of required Docker images

How does the docker dependency looks like?

<div class="result" markdown>

=== "Setup Resnet50"

    ``` mermaid
    graph TD
        base[<a href='#build-base'>Base</a>] --> krai/qaic[krai/qaic: SDK dependent]
        base[<a href='#build-base'>Base</a>]  --> krai/ck.common
        krai/qaic[krai/qaic: SDK dependent] --> krai/mlperf.resnet50
        krai/ck.common --> |<a href='#build-ckresnet50'>Step1</a>|krai/ck.resnet50
        krai/ck.resnet50 --> |<a href='#build-mlperfresnet50'>Step2</a>|krai/mlperf.resnet50
        Imagenet[(<a href='#install-coco-dataset'>Imagenet</a>)] -.-> |<a href='#build-ckresnet50'>Step1|krai/ck.resnet50
    ```

=== "Setup ssd-mobilenet"

    ``` mermaid
    graph TD
        base[<a href='#build-base'>Base</a>] --> krai/qaic[krai/qaic: SDK dependent]
        base[<a href='#build-base'>Base</a>]  --> krai/ck.common
        krai/qaic --> krai/mlperf.ssd-mobilenet
        krai/ck.common --> krai/ck.ssd-mobilenet
        krai/ck.ssd-mobilenet --> |<a href='#build-mlperfssd-mobilenet'>Build mlperf.ssd-mobilenet</a>|krai/mlperf.ssd-mobilenet
        COCO -.-> |<a href='#build-ckssd-mobilenet'>Build ck.ssd-mobilenet</a>|krai/ck.ssd-mobilenet
        krai/ck.common --> |<a href='#build-coco-image'>Download COCO Dataset</a>|COCO[(COCO)]
    ```
=== "Docker Dependency"

    ``` mermaid
    graph TD
        base[<a href='#build-base'>Base</a>] --> krai/qaic[krai/qaic: SDK dependent]
        base[<a href='#build-base'>Base</a>]  --> krai/ck.common
        krai/qaic --> krai/mlperf.ssd-mobilenet
        krai/qaic --> krai/mlperf.resnet50
        krai/ck.common --> krai/ck.resnet50
        krai/ck.resnet50 --> krai/mlperf.resnet50
        krai/ck.common --> krai/ck.ssd-mobilenet
        krai/ck.ssd-mobilenet --> krai/mlperf.ssd-mobilenet
        krai/ck.common --> COCO
        COCO -.-> |<a href='#build-ckssd-mobilenet'>Build ck.ssd-mobilenet</a>|krai/ck.ssd-mobilenet
        Imagenet[(Imagenet Dataset)]
        Imagenet --> krai/ck.resnet50
        krai/ck.common --> COCO[(COCO Dataset)]
        Imagenet[(<a href='#build-imagenet'>ImageNet</a>)] -.-> |<a href='#build-ckresnet50'>Step1|krai/ck.resnet50
    ```

</div>

<div class="result" markdown>

[Run][Demo]{ .md-button }

</div>

  [primary color]: ../setup/changing-the-colors.md#primary-color
  [accent color]: ../setup/changing-the-colors.md#accent-color 
  [Demo]: javascript:alert$.next("Demo")


## Build Base


```
$(ck find ck-qaic:docker:base)/build.base.sh
```

??? example "Parameters"
    - DOCKER_OS=ubuntu: only ubuntu (Ubuntu 20.04) and centos (CentOS 7) are supported.
    - PYTHON_VER=3.9.14.
    - GCC_MAJOR_VER=11.
    - TIMEZONE=US/Central (Austin)
??? example "Shell"
    <iframe width=1200px, height=500 frameBorder=0 src="https://tmate.io/t/rqKXPvqzHNMrYYH8QCLrRhHed"></iframe>


## Build SSD-MobileNet

### Build COCO Image

```
cd $(ck find repo:ck-qaic)/docker

time CK_QAIC_REPO=ck-qaic-dev-krai CK_QAIC_CHECKOUT=main CK_QAIC_PAT=$CK_QAIC_PAT WORKSPACE_DIR=/workspace ./build_ck.sh coco
```

<!-- <iframe width=1200px, height=500 frameBorder=0 src="https://tmate.io/t/rqKXPvqzHNMrYYH8QCLrRhHed"></iframe> -->

<!-- <iframe width=1200px, height=500 frameBorder=0 src="https://fake-terminal.glitch.me"></iframe> -->
??? example "Shell"
    <iframe width=1200px, height=500 frameBorder=0 src="https://tmate.io/t/rqKXPvqzHNMrYYH8QCLrRhHed"></iframe>


### Build `ck.ssd-mobilenet`
```
cd $(ck find repo:ck-qaic)/docker

time CK_QAIC_REPO=ck-qaic-dev-krai CK_QAIC_CHECKOUT=main CK_QAIC_PAT=$CK_QAIC_PAT WORKSPACE_DIR=/workspace ./build_ck.sh ssd-mobilenet
```

??? example "Shell"
    <iframe width=1200px, height=500 frameBorder=0 src="https://tmate.io/t/rqKXPvqzHNMrYYH8QCLrRhHed"></iframe>

### Build `mlperf.ssd-mobilenet`
```
cd $(ck find repo:ck-qaic)/docker

time CK_QAIC_REPO=ck-qaic-dev-krai CK_QAIC_CHECKOUT=fix_build_vars CK_QAIC_PAT=$CK_QAIC_PAT WORKSPACE_DIR=/workspace SDK_VER=1.8.2.10 COMPILE_PRO=no COMPILE_STD=yes USE_PRECALIBRATED_PROFILE=yes ./build.sh ssd-mobilenet
```

??? example "Shell"
    <iframe width=1200px, height=500 frameBorder=0 src="https://tmate.io/t/rqKXPvqzHNMrYYH8QCLrRhHed"></iframe>

## Build resnet50


### Build ImageNet

```
$(ck find ck-qaic:docker:imagenet)/build.sh
```

### Build `ck.resnet50`
```
cd $(ck find repo:ck-qaic)/docker

time CK_QAIC_REPO=ck-qaic-dev-krai CK_QAIC_CHECKOUT=main CK_QAIC_PAT=$CK_QAIC_PAT WORKSPACE_DIR=/workspace ./build_ck.sh resnet50
```

??? example "Shell"
    <iframe width=1200px, height=500 frameBorder=0 src="https://tmate.io/t/rqKXPvqzHNMrYYH8QCLrRhHed"></iframe>

### Build `mlperf.resnet50`
```
cd $(ck find repo:ck-qaic)/docker

time CK_QAIC_REPO=ck-qaic-dev-krai CK_QAIC_CHECKOUT=fix_build_vars CK_QAIC_PAT=$CK_QAIC_PAT WORKSPACE_DIR=/workspace SDK_VER=1.8.2.10 COMPILE_PRO=no COMPILE_STD=yes USE_PRECALIBRATED_PROFILE=yes ./build.sh ssd-resnet50
```

??? example "Shell"
    <iframe width=1200px, height=500 frameBorder=0 src="https://tmate.io/t/rqKXPvqzHNMrYYH8QCLrRhHed"></iframe>