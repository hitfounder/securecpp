#!/bin/bash

key=$(<data/key.txt)
echo "Key: $key"
echo "Data to encrypt: `cat data/in`"
openssl enc -aes-256-ecb -in data/in -K "$key" -out data/out -v
echo "Encrypted: `xxd -ps -u data/out`"

openssl enc -d -aes-256-ecb -in data/out -K "$key" -out data/dec -v
echo "Decrypted: `cat data/dec`"
