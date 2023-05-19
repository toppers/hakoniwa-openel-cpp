#!/bin/bash
#export DELTA_MSEC=20
#export MAX_DELAY_MSEC=100
#export GRPC_PORT=50051
#export UDP_SRV_PORT=54001
#export UDP_SND_PORT=54002
#export CORE_IPADDR=172.30.224.33
echo "INFO: ACTIVATING MOSQUITTO"
mosquitto -c ./config/mosquitto.conf &
MQTT_PORT=1883
sleep 2

echo "INFO: ACTIVATING HAKO-MASTER"
hako-master ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT} ${UDP_SRV_PORT} ${UDP_SND_PORT} ${MQTT_PORT} & > /dev/null 

sleep 1

#python3 ${PYTHON_PROG} &
#LAST_PID=$!
sleep 1

while [ 1 ]
do
    sleep 10
done

