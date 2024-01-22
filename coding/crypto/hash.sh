#!/bin/bash

str="Hello World!"
echo "Input string: $str"

openssl dgst -md5 <<< $str
openssl dgst -sha1 <<< $str
openssl dgst -sha256 <<< $str
openssl dgst -sha3-256 <<< $str
openssl dgst -sha3-512 <<< $str
