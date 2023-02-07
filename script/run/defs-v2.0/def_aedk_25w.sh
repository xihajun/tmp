#!/bin/bash

# BERT-99% (mixed precision).
BERT99_SINGLESTREAM_TARGET_LATENCY=16
BERT99_MULTISTREAM_TARGET_LATENCY=40
BERT99_OFFLINE_TARGET_QPS=361
BERT99_OFFLINE_OVERRIDE_BATCH_SIZE=4096
BERT99_MULTISTREAM_OVERRIDE_BATCH_SIZE=8

# ResNet50.
RESNET50_SINGLESTREAM_TARGET_LATENCY=1
RESNET50_MULTISTREAM_TARGET_LATENCY=2
RESNET50_OFFLINE_TARGET_QPS=9900

# SSD-ResNet34.
SSD_RESNET34_SINGLESTREAM_TARGET_LATENCY=24
SSD_RESNET34_MULTISTREAM_TARGET_LATENCY=81
SSD_RESNET34_OFFLINE_TARGET_QPS=225

# SSD-MobileNet-v1.
SSD_MOBILENET_SINGLESTREAM_TARGET_LATENCY=1.8
SSD_MOBILENET_MULTISTREAM_TARGET_LATENCY=4.5
SSD_MOBILENET_OFFLINE_TARGET_QPS=5200
