#!/bin/bash

# BERT-99% (mixed precision).
BERT99_SINGLESTREAM_TARGET_LATENCY=13
BERT99_OFFLINE_TARGET_QPS=220
BERT99_OFFLINE_OVERRIDE_BATCH_SIZE=4096

# ResNet50.
RESNET50_SINGLESTREAM_TARGET_LATENCY=1
RESNET50_MULTISTREAM_TARGET_LATENCY=2.5
RESNET50_OFFLINE_TARGET_QPS=7000
