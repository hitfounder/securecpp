#!/bin/bash

key=$(<data/key.txt)
iv=$(<data/iv.txt)
echo "Key: $key"
echo "IV: $iv"
echo "Data to encrypt: `cat data/in`"
openssl enc -aes-256-cbc -in data/in -K "$key" -iv "$iv" -out data/out -v
echo "Encrypted: `xxd -ps -u data/out`"

openssl enc -d -aes-256-cbc -in data/out -K "$(<data/key.txt)" -iv "$iv" -out data/dec -v
echo "Decrypted: `cat data/dec`"
