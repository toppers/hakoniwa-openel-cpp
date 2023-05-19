#!/bin/bash

if [ ${RUN_MODE} == "build" ]
then
    cd sample/tb3model
    bash build.bash clean
    bash build.bash all
    exit 0
fi

echo "INFO: ACTIVATING MOSQUITTO"
mosquitto -c ./config/mosquitto.conf &
MQTT_PORT=1883
sleep 2

echo "INFO: ACTIVATING HAKO-MASTER"
hako-master ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT} ${UDP_SRV_PORT} ${UDP_SND_PORT} ${MQTT_PORT} & > /dev/null 

sleep 1

cd sample/tb3model
./cmake-build/hako-openel &
LAST_PID=$!
sleep 1

while [ 1 ]
do
    sleep 10
done

