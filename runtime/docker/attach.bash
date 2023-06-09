#!/bin/bash

IMAGE_NAME=toppersjp/`cat runtime/docker/image_name.txt`
IMAGE_TAG=`cat runtime/docker/appendix/latest_version.txt`
DOCKER_IMAGE=${IMAGE_NAME}:${IMAGE_TAG}

DOCKER_ID=`docker ps | grep "${DOCKER_IMAGE}" | awk '{print $1}'`

docker exec -it ${DOCKER_ID} /bin/bash
