# CK Commands

## Show loacal experiments
```
ck list local:experiment:* | sort<var>
```

```
ck clean local:experiment:*<var>
```

## Zip Experiments Example

```
ck zip experiments:* --archive_name=~/mlperf_v3.0-closed-heimdall.20230111.zip
```

## Add Repo based on the zipped file
```
ck add repo --zip=~/mlperf_v3.0-closed-heimdall.20230111.zip
```
CK will add a new entry named mlperf_v3.0-closed-heimdall.20230111 and you will find two experiments because it contains a backup version.


## CK Advance From Elim

```
ck search env --tags=object-detection,tf1-zoo,ssdlite-mobilenet-v2-coc
ck show local:env:24c46b2c81462488
ck cat local:env:24c46b2c81462488
```
ck copy
```
ck cp package:model-tf-faster-rcnn-inceptionv2-coco ck-object-detection:package:model-tf1-object-detection-zoo
```
```
ck cp sut:rpi4 ck-mlperf:sut:vim4
```
ck rename
```
ck rename [SRC] [DEST]
ck rename ck-object-detection:package:model-tf-faster-rcnn-zoo ck-object-detection:package:model-tf1-object-detection-zoo
ck rename sut:firefly sut:firefly-rk3399
```
find env:
```
ck show env:5a2bfed4b0237ca1
ck locate env:5a2bfed4b0237ca1
ck cat env:5a2bfed4b0237ca1
ck show env --tags=flatbuffers
```
Clean all environment and stuff accidentally installed
```
ck clean env -f
ck rm repo:ck-crowdtuning --all --force
python3.9 -m pip show tensorflow
du -hs /root/.local/*
```
`ck benchmark` command is essentially combination of `ck compile && ck run`
```
ck list local:experiment:*
ck list {directory}:{type}:*
```
change tags after creating env:
```
vi ~/CK/local/env/07a2f280d1c0bf6a/.cm/meta.json
```
```
ck pull repo --url=http://github.com/krai/ck-mlperf.git
```
```
ck rm experiment:mlperf_v2.1-closed-aedkr-qaic-v1.6.121-aic100-resnet50-offline-performance-target_qps.1
```
```
ck rm repo:mlperf_v3.1-closed-rpi4 --all -force
```
get variables
```
ck cat env --tags=mlperf,inference,source,r2.1
```