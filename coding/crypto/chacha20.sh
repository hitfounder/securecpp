#!/bin/bash

key=$(<data/key.txt)
iv=$(<data/iv.txt)
echo "Key: $key"
echo "IV: $iv"
echo "Data to encrypt: `cat data/in`"
openssl enc -chacha20 -in data/in -K "$key" -iv "$iv" -out data/out -v
echo "Encrypted: `xxd -ps -u data/out`"

openssl enc -d -chacha20 -in data/out -K "$key" -iv "$iv" -out data/dec -v
echo "Decrypted: `cat data/dec`"
