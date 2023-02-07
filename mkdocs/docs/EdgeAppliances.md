# Setting up Edge appliances with Qualcomm Cloud AI 100

<!-- markdown="1" is required for GitHub Pages to render the TOC properly. -->

<details markdown="1">
  <summary>Table of Contents</summary>
- [With Docker Setup](#with-docker-setup)
  * [A. Host setup](#a-host-setup)
    + [Prerequisites](#prerequisites)
      - [50G Space](#50g-space)
      - [Copy the QAIC Apps/Platform SDKs](#copy-the-qaic-apps-platform-sdks)
      - [Copy the ImageNet validation dataset](#copy-the-imagenet-validation-dataset)
    + [`[H1]` Common host setup](#--h1---common-host-setup)
      - [Clone the repository with setup scripts](#clone-the-repository-with-setup-scripts)
      - [Set up the Collective Knowledge framework (CK)](#set-up-the-collective-knowledge-framework--ck-)
      - [Set up system dependencies and Docker](#set-up-system-dependencies-and-docker)
    + [`[HR]` Build the ResNet50 Docker image](#--hr---build-the-resnet50-docker-image)
      - [`[H1]` Test the ResNet50 image](#--h1---test-the-resnet50-image)
    + [`[HR]` Update the configuration file (once per device)](#--hr---update-the-configuration-file--once-per-device-)
  * [B. Initial device setup under the `root` user](#b-initial-device-setup-under-the--root--user)
    + [`[H1]` Connect to the device as `root`](#--h1---connect-to-the-device-as--root-)
    + [`[D1]` Clone the repository with setup scripts](#--d1---clone-the-repository-with-setup-scripts)
    + [`[D1S]` Run](#--d1s---run)
    + [`[D1S]` Set the user password](#--d1s---set-the-user-password)
  * [C. Initial device setup under the `krai` user](#c-initial-device-setup-under-the--krai--user)
    + [`[H1]` Connect to the device as `krai`](#--h1---connect-to-the-device-as--krai-)
    + [`[D1]` Update scripts permissions](#--d1---update-scripts-permissions)
    + [`[D1]` Run](#--d1---run)
  * [D. Set up ImageNet](#d-set-up-imagenet)
    + [`[H1]` Copy the ImageNet dataset from the host to the device](#--h1---copy-the-imagenet-dataset-from-the-host-to-the-device)
    + [`[D1]` Preprocess ImageNet on the device](#--d1---preprocess-imagenet-on-the-device)
      - [Detect the dataset](#detect-the-dataset)
      - [Preprocess the dataset](#preprocess-the-dataset)
  * [E. Set up QAIC Platform SDK](#e-set-up-qaic-platform-sdk)
    + [`[HR]` Copy the Platform SDK from the host to the device](#--hr---copy-the-platform-sdk-from-the-host-to-the-device)
    + [`[DSR]` Uninstall/Install the Platform SDK on the device](#--dsr---uninstall-install-the-platform-sdk-on-the-device)
  * [F. Install the workloads](#f-install-the-workloads)
    + [`[HR]` Compile the workloads on the host and copy to the device](#--hr---compile-the-workloads-on-the-host-and-copy-to-the-device)
  * [Further info](#further-info)

<small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc</a></i></small>

</details>

- Host Setup
- Device Setup (`root`)
- Device Setup (`krai`)
- Setup ImageNet
- Setup QAIC Platform SDK
- Install the workloads

## A. Host setup

We describe 

- set up from scratch an Edge AI appliance similar to the [Qualcomm Cloud AI 100 Edge Development Kit](https://www.qualcomm.com/content/dam/qcomm-martech/dm-assets/documents/prod_brief_qcom_cloud_ai_100_dev_kit.pdf) (AEDK), which we call "the device". 

We assume that the user operates 

- an Ubuntu machine (or a Windows machine under WSL), which we call "the host".

<details markdown="1">
  <summary>Instructions</summary>

- running on the host (marked with `H`)
- running on the device (marked with `D`)
- to be run as superuser (marked with `S`).
- to be run only once (marked with `1`).
- to be repeated as needed (marked with `R`)
  * e.g. when updating to new SDK versions.

TODO: a bit unclear for readers with one character
</details>



### Prerequisites
We need three things:

- 50GB space
- apps/sdks
- dataset

<details>
<pre><code>$ tree $WORKSPACE_DIR -L 2
/workspace
├── datasets
│   └── imagenet
└── sdks
    ├── qaic-apps-<a vartag='SDK_VER'>1.8.2.10</a>.zip
    ├── qaic-platform-sdk-aarch64-ubuntu-<a vartag='SDK_VER'>1.8.2.10</a>.zip
    └── qaic-platform-sdk-x86_64-ubuntu-<a vartag='SDK_VER'>1.8.2.10</a>.zip

3 directories, 3 files</code></pre>
</details>

#### 50G Space

We assume that the host machine

- at least 50G of free space
- a user-writable directory e.g. `WORKSPACE_DIR=/workspace`.


They will hold 

- QAIC Apps/Platform SDKs
- datasets (e.g. ImageNet)
- Docker images

```
export WORKSPACE_DIR=/workspace
mkdir -p $WORKSPACE_DIR/sdks
mkdir -p $WORKSPACE_DIR/datasets
```

#### Copy the QAIC Apps/Platform SDKs

- [Download](https://www.qualcomm.com/products/technology/processors/cloud-artificial-intelligence/cloud-ai-100#Software) the latest Apps SDK (e.g. `AIC_Apps_SDK.ZIP.1.0 Installer x86_00058.1`), x86_64/ubuntu Platform SDK (e.g. `AIC_Platform_SDK.ZIP.1.0 Installer x86_Ubuntu_00069.1`) 
- aarch64/ubuntu Platform SDK 

Example:`AIC_Platform_SDK.ZIP.1.0 Installer ARM_Ubuntu_00069.1`

- Extract (`unzip`) the archives to obtain the Apps/Platform SDK archives of the same version (e.g. `qaic-apps-sdk-1.8.2.10.zip`,  `qaic-platform-sdk-x86_64-ubuntu-1.8.2.10.zip`, `qaic-platform-sdk-aarch64-ubuntu-1.8.2.10.zip`). 
- Copy these Apps/Platform SDK archives to `$WORKSPACE_DIR/sdks`.

#### Copy the ImageNet validation dataset

- Copy to `$WORKSPACE_DIR/datasets` the ImageNet dataset directory (called e.g. `IMAGENET_NAME=imagenet`), containing 50,000 images with the file names like `ILSVRC2012_val_00000001.JPEG`.


### `[H1]` Common host setup

- clone repo (containing setup scripts)
- setup ck
- setup sys dependencies and docker

#### Clone the repository with setup scripts

```
git clone https://github.com/krai/ck-qaic /tmp/ck-qaic
```

#### Set up the Collective Knowledge framework (CK)

```
cd /tmp/ck-qaic/script/setup.docker
WORKSPACE_DIR=/workspace bash setup_ck.sh
```

#### Set up system dependencies and Docker

```
cd /tmp/ck-qaic/script/setup.docker
WORKSPACE_DIR=/workspace bash setup_ubuntu.sh
```

**NB:** Log out and log back in for the user to be added into the necessary groups.

### `[HR]` Build the ResNet50 Docker image

```
WORKLOADS=resnet50 \
WORKSPACE_DIR=/workspace \
SDK_DIR=/workspace/sdks SDK_VER=1.8.2.10 \
DATASETS_DIR=/workspace/datasets IMAGENET_NAME=imagenet \
COMPILE_PRO=no COMPILE_STD=no \
DOCKER_OS=ubuntu bash setup_images.sh
```

#### `[H1]` Test the ResNet50 image

If the host machine has at least QAIC PCIe card installed, you can test the image as follows:
```
ck run cmdgen:benchmark.image-classification.qaic-loadgen --docker --verbose \
--model=resnet50 --sdk=1.8.2.10 --sut=q1_std_edge --scenario=offline --mode=accuracy
...
accuracy=75.898%, good=37949, total=50000
```

### `[HR]` Update the configuration file (once per device)

Go to the following directory:
```
cd $(ck find repo:ck-qaic)/script/setup.aedk
```
and edit the `config.sh` file to update: the IP address (`DEVICE_IP`) and port (`DEVICE_PORT`) of the device, the path to the directory with datasets (`HOST_DATASETS_DIR=$WORKSPACE/datasets`).

**NB:** The full installation can take more than 50G. If the space on the root partition (`/`) of the device is limited and you wish to use a different partition to create the home directory under e.g. mounted as `/data`, then also update `DEVICE_BASE_DIR=/data`.

Init `config.sh`:
```
source $(ck find repo:ck-qaic)/script/setup.aedk/config.sh
```

## B. Initial device setup under the `root` user

- connect to the device as `root`
- clone the scripts
- change `config.sh` and run
- set the user password

### `[H1]` Connect to the device as `root`
Connect to the device as `root` e.g.:
```
ssh -p ${DEVICE_PORT} root@${DEVICE_IP}
```

### `[D1]` Clone the repository with setup scripts

```
git clone https://github.com/krai/ck-qaic /tmp/ck-qaic
```

### `[D1S]` Run

Go to the temporary directory:
```
cd /tmp/ck-qaic/script/setup.aedk
```

Check the config file:
```
cat ./config.sh
```

<details><pre>
#!/bin/bash

export DEVICE_IP=aedk3
export DEVICE_PORT=3233
export DEVICE_BASE_DIR="/home"
export DEVICE_GROUP=krai
export DEVICE_USER=krai
export DEVICE_OS=ubuntu
export DEVICE_OS_OVERRIDE=no
export DEVICE_DATASETS_DIR="${DEVICE_BASE_DIR}/${DEVICE_USER}"
export HOST_DATASETS_DIR="/datasets"
export PYTHON_VERSION=3.9.14
export TIMEZONE="US/Central"
export INSTALL_BENCHMARK_RESNET50=yes
export INSTALL_BENCHMARK_BERT=no
</pre></details>

Source it & run:
```
source ./config.sh && ./1.run_as_root.sh
```

Alternatively, you can override variables from the command line e.g.:
```
time DEVICE_BASE_DIR=/data TIMEZONE=London/Europe ./1.run_as_root.sh
```

<details><pre>
root@aus655-gloria-1:~# df -h /home
Filesystem      Size  Used Avail Use% Mounted on
/dev/root        99G   11G   89G  11% /
root@aus655-gloria-1:~# df -h /datasets
Filesystem      Size  Used Avail Use% Mounted on
/dev/nvme0n1p1  880G   77M  835G   1% /datasets
root@aus655-gloria-1:/tmp/ck-qaic/script/setup.aedk# time DEVICE_BASE_DIR=/datasets TIMEZONE=US/Central ./1.run_as_root.sh
...
Sat Jul 23 09:05:56 CDT 2022
real    3m42.599s
user    6m4.276s
sys     1m5.008s
</pre></details>

### `[D1S]` Set the user password
```
passwd ${DEVICE_USER}
```

## C. Initial device setup under the `krai` user

- connect the device under the user we set
- update scripts permissions
- run as `krai`

### `[H1]` Connect to the device as `krai`

Connect to the device as `krai` e.g.:
```
ssh -p ${DEVICE_PORT} krai@${DEVICE_IP}
```

### `[D1]` Update scripts permissions
```
sudo chown -R krai:krai /tmp/ck-qaic
sudo chmod u+x /tmp/ck-qaic/script/setup.aedk/*.sh
```

### `[D1]` Run
```
cd /tmp/ck-qaic/script/setup.aedk
source ./config.sh && time ./2.run_as_krai.sh
source ~/.bashrc
source ./config.sh && time ./3.run_as_krai.sh
```

## D. Set up ImageNet

### `[H1]` Copy the ImageNet dataset from the host to the device
```
source $(ck find repo:ck-qaic)/script/setup.aedk/config.sh
scp -r -P ${DEVICE_PORT} ${HOST_DATASETS_DIR}/imagenet krai@${DEVICE_IP}:${DEVICE_DATASETS_DIR}
```

### `[D1]` Preprocess ImageNet on the device

#### Detect the dataset
```
echo "full" | ck detect soft:dataset.imagenet.val --extra_tags=ilsvrc2012,full \
--full_path=${DEVICE_DATASETS_DIR}/imagenet/ILSVRC2012_val_00000001.JPEG
```

#### Preprocess the dataset

```
ck install package --dep_add_tags.dataset-source=original,full \
--tags=dataset,imagenet,val,full,preprocessed,using-opencv,for.resnet50.quantized,layout.nhwc,side.224,validation
```

## E. Set up QAIC Platform SDK

These steps are to be repeated for each new SDK version (`SDK_VER` below).

### `[HR]` Copy the Platform SDK from the host to the device

```
export SDK_VER=1.8.2.10
source $(ck find repo:ck-qaic)/script/setup.aedk/config.sh
scp -P ${DEVICE_PORT} \
${WORKSPACE}/sdks/qaic-platform-sdk-aarch64-ubuntu-${SDK_VER}.zip \
${DEVICE_USER}@${DEVICE_IP}:${DEVICE_BASE_DIR}/${DEVICE_USER}
```

### `[DSR]` Uninstall/Install the Platform SDK on the device

Specify `SDK_DIR`, the path to a directory with one or more Platform SDK archives, and `SDK_VER`, the Platform SDK version.
The full path to the Platform SDK archive is formed as follows: `PLATFORM_SDK=${SDK_DIR}/qaic-platform-sdk-aarch64-ubuntu-${SDK_VER}.zip`.

```
SDK_DIR=${DEVICE_BASE_DIR}/${DEVICE_USER} SDK_VER=1.8.2.10 bash $(ck find ck-qaic:script:setup.aedk)/install_platform_sdk.sh
```

Alternatively, directly specify `PLATFORM_SDK`, the full path to the Platform SDK archive.

<details><pre>
SDK_DIR=$HOME SDK_VER=1.8.2.10 $(ck find ck-qaic:script:setup.aedk)/install_platform_sdk.sh
</pre></details>

Pretend that the device has the Apps SDK installed as well:
```
sudo cp /opt/qti-aic/versions/{platform,apps}.xml
```

Reboot the device for the changes to take effect.

## F. Install the workloads

### `[HR]` Compile the workloads on the host and copy to the device

```
cd $(ck find ck-qaic:script:setup.aedk)
WORKLOADS=resnet50 SDK_VER=1.8.2.10 \
DEVICE_IP=192.168.0.12 DEVICE_PORT=1234 DEVICE_PASSWORD=12345678 \
DEVICE_BASE_DIR=/home DEVICE_USER=krai DEVICE_TYPE=aedk ./install_to_aedk.sh
```

<details>

- On the host:
<pre>
krai@aus655-el-01-5:/local/mnt/workspace/krai/CK-REPOS/ck-qaic/script/setup.aedk&dollar; time WORKLOADS=resnet50 SDK_VER=1.8.2.10 DEVICE_USER=krai DEVICE_IP=192.168.0.12 DEVICE_PORT=1234 DEVICE_PASSWORD=12345678 DEVICE_BASE_DIR=/home DEVICE_TYPE=aedk ./install_to_aedk.sh
...
DONE (installing workloads).
real    6m58.061s
user    0m3.306s
sys     0m2.730s
</pre>

- On the device:
<pre>
krai@aus655-gloria-2:~$ ck show env --tags=qaic,model
Env UID:         Target OS: Bits: Name:                   Version: Tags:

fd3d44a38096fd5c   linux-64    64 Qualcomm Cloud AI model 1.8.2.12 64bits,bs.8,calibrated-by-qaic,compiled,compiled-by-qaic,converted,host-os-linux-64,image-classification,model,qaic,qualcomm,qualcomm-ai,qualcomm-cloud-ai,resnet50,resnet50.aedk.offline,target-os-linux-64,v1,v1.8,v1.8.2,v1.8.2.10,v1.8.2.12
43f4a098f915ab32   linux-64    64 Qualcomm Cloud AI model 1.8.2.12 64bits,bs.1,calibrated-by-qaic,compiled,compiled-by-qaic,converted,host-os-linux-64,image-classification,model,qaic,qualcomm,qualcomm-ai,qualcomm-cloud-ai,resnet50,resnet50.aedk.singlestream,target-os-linux-64,v1,v1.8,v1.8.2,v1.8.2.10,v1.8.2.12
ba6b84938baa22b5   linux-64    64 Qualcomm Cloud AI model 1.8.2.12 64bits,bs.1,calibrated-by-qaic,compiled,compiled-by-qaic,converted,host-os-linux-64,image-classification,model,qaic,qualcomm,qualcomm-ai,qualcomm-cloud-ai,resnet50,resnet50.aedk.multistream,target-os-linux-64,v1,v1.8,v1.8.2,v1.8.2.10,v1.8.2.12
</pre>
</details>


## Further info

Please contact anton@krai.ai if you have any problems or questions.
