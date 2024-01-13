#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ]
then
    echo "Specify text file as first argument, bin file as second argument"
    exit
fi

xxd -r -p $1 $2