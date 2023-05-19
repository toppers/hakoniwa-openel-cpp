#!/bin/bash

IMAGE_NAME=`cat runtime/docker/image_name.txt`
IMAGE_TAG=`cat runtime/docker/appendix/latest_version.txt`
DOCKER_IMAGE=toppersjp/${IMAGE_NAME}:${IMAGE_TAG}
DOCKER_FILE=runtime/docker/Dockerfile
docker build -t ${DOCKER_IMAGE} -f ${DOCKER_FILE} .

