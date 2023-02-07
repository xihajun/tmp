#!/bin/bash

# BERT-99% (mixed precision).
BERT99_OFFLINE_OVERRIDE_BATCH_SIZE=4096
BERT99_SERVER_OVERRIDE_BATCH_SIZE=1024
BERT99_OFFLINE_TARGET_QPS=6155
BERT99_SERVER_TARGET_QPS=5800

# BERT-99.9% (FP16 precision).
BERT999_OFFLINE_OVERRIDE_BATCH_SIZE=4096
BERT999_SERVER_OVERRIDE_BATCH_SIZE=1024
BERT999_OFFLINE_TARGET_QPS=2900
BERT999_SERVER_TARGET_QPS=2650

# ResNet50.
RESNET50_OFFLINE_TARGET_QPS=170000
RESNET50_SERVER_TARGET_QPS=173000
RESNET50_MAX_WAIT=1800

RUN_CMD_COMMON_SUFFIX_DEFAULT="--vc --pre_fan=250 --post_fan=50"
