#!/bin/bash

IMAGE_NAME=`cat runtime/docker/image_name.txt`
IMAGE_TAG=`cat runtime/docker/appendix/latest_version.txt`
DOCKER_IMAGE=${IMAGE_NAME}:${IMAGE_TAG}

docker pull toppersjp/${DOCKER_IMAGE}
