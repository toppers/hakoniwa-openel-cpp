#!/bin/bash

source runtime/docker/env.bash

if [ $# -ne 1 ]
then
	echo "Usage: $0 {run|build}"
	exit 1
fi
OPT=${1}
HAKONIWA_TOP_DIR=`pwd`
IMAGE_NAME=`cat runtime/docker/image_name.txt`
IMAGE_TAG=`cat runtime/docker/appendix/latest_version.txt`
DOCKER_IMAGE=toppersjp/${IMAGE_NAME}:${IMAGE_TAG}

if [ ${OPT} == "build" ]
then
	docker run \
		-v ${HOST_WORKDIR}:${DOCKER_WORKDIR} \
		-v `pwd`/sample:${DOCKER_WORKDIR}/sample \
		-v `pwd`/openel-cpp:${DOCKER_WORKDIR}/openel-cpp \
		-v `pwd`/hakoniwa-core-cpp-client:${DOCKER_WORKDIR}/hakoniwa-core-cpp-client \
		-v `pwd`/hakoniwa-ros2pdu:${DOCKER_WORKDIR}/hakoniwa-ros2pdu \
		-v `pwd`/openel-device:${DOCKER_WORKDIR}/openel-device \
		-it --rm \
		--net host \
		-e RUN_MODE=build \
		--name ${IMAGE_NAME} ${DOCKER_IMAGE} 
	exit 0
fi


if [[ "$(uname -r)" == *microsoft* ]]
then
    OS_TYPE=wsl2
elif [[ "$(uname)" == "Darwin" ]]
then
    OS_TYPE=Mac
else
    OS_TYPE=Linux
fi

if [ ${OS_TYPE} != "Mac" ]
then
	docker ps > /dev/null
	if [ $? -ne 0 ]
	then
	    sudo service docker start
	    echo "waiting for docker service activation.. "
	    sleep 3
	fi
fi

if [ ${OS_TYPE} = "wsl2" ]
then
	export RESOLV_IPADDR=`cat /etc/resolv.conf  | grep nameserver | awk '{print $NF}'`
	NETWORK_INTERFACE=$(route | grep '^default' | grep -o '[^ ]*$' | tr -d '\n')
	CORE_IPADDR=$(ifconfig "${NETWORK_INTERFACE}" | grep netmask | awk '{print $2}')
elif [ ${OS_TYPE} = "Mac" ]
then
	if [ $# -ne 1 ]
	then
		echo "Usage: $0 <port>"
		exit 1
	fi
	#NETWORK_INTERFACE=$(netstat -rnf inet | grep '^default' | awk '{print $4}')
	#CORE_IPADDR=$(ifconfig "${NETWORK_INTERFACE}" | grep netmask | awk '{print $2}')
	CORE_IPADDR="127.0.0.1"
else
	IPADDR="127.0.0.1"
fi

docker run \
	-v ${HOST_WORKDIR}:${DOCKER_WORKDIR} \
	-v `pwd`/sample:${DOCKER_WORKDIR}/sample \
	-v `pwd`/openel-cpp:${DOCKER_WORKDIR}/openel-cpp \
	-v `pwd`/hakoniwa-core-cpp-client:${DOCKER_WORKDIR}/hakoniwa-core-cpp-client \
	-v `pwd`/hakoniwa-ros2pdu:${DOCKER_WORKDIR}/hakoniwa-ros2pdu \
	-v `pwd`/openel-device:${DOCKER_WORKDIR}/openel-device \
	-it --rm \
	--net host \
	-e RUN_MODE=run \
	-e CORE_IPADDR=${CORE_IPADDR} \
	-e DELTA_MSEC=${DELTA_MSEC} \
	-e MAX_DELAY_MSEC=${MAX_DELAY_MSEC} \
	-e GRPC_PORT=${GRPC_PORT} \
	-e UDP_SRV_PORT=${UDP_SRV_PORT} \
	-e UDP_SND_PORT=${UDP_SND_PORT} \
	--name ${IMAGE_NAME} ${DOCKER_IMAGE} 
