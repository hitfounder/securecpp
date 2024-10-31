#!/bin/bash

key=$(<data/key256.txt)
iv=$(<data/iv128.txt)
echo "Key: $key"
echo "IV: $iv"
echo "Data to encrypt: `cat data/in`"
# AES in CTR mode is a kind of stream cipher,
# so it does not require padding, you could specify -nopad
openssl enc -aes-256-ctr -in data/in -K "$key" -iv "$iv" -out data/out -v -nopad
echo "Encrypted: `xxd -ps -u data/out`"

openssl enc -d -aes-256-ctr -in data/out -K "$key" -iv "$iv" -out data/dec -v -nopad
echo "Decrypted: `cat data/dec`"
