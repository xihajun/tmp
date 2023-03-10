#!/bin/bash

# BERT-99% (mixed precision).
BERT99_OFFLINE_OVERRIDE_BATCH_SIZE=4096
BERT99_SERVER_OVERRIDE_BATCH_SIZE=300
BERT99_OFFLINE_TARGET_QPS=12400
BERT99_SERVER_TARGET_QPS=11600

# BERT-99.9% (FP16 precision).
BERT999_OFFLINE_OVERRIDE_BATCH_SIZE=4096
BERT999_SERVER_OVERRIDE_BATCH_SIZE=200
BERT999_OFFLINE_TARGET_QPS=5900
BERT999_SERVER_TARGET_QPS=5499

# ResNet50.
RESNET50_OFFLINE_TARGET_QPS=370000
RESNET50_SERVER_TARGET_QPS=327000
RESNET50_MAX_WAIT=50

RUN_CMD_COMMON_SUFFIX_DEFAULT="--vc --pre_fan=250 --post_fan=50"
