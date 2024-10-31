#!/bin/bash

str="Hello World!"
echo "Input string: $str"

key=$(<data/key128.txt)
openssl dgst -sha256 -mac hmac -macopt hexkey:$key <<< $str
openssl dgst -sha256 <<< $str

openssl dgst -mac cmac -macopt cipher:aes-128-cbc -macopt hexkey:$key <<< $str

