#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage: $0 {all|clean}"
	exit 1
fi

OPT=${1}

if [ ${OPT} == "all" ]
then
	cd cmake-build
	cmake ..
	make
else
	rm -rf cmake-build/*
fi

exit 0
