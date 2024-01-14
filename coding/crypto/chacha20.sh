#!/bin/bash

key=$(<data/key256.txt)
iv=$(<data/iv128.txt)
echo "Key: $key"
echo "IV: $iv"
echo "Data to encrypt: `cat data/in`"
# Here could be -nopad option, because padding as absent in stream cypher
# For block cypher, like aes, -nopad option will return error if input data is not multiple block size
openssl enc -chacha20 -in data/in -K "$key" -iv "$iv" -out data/out -v -nopad
echo "Encrypted: `xxd -ps -u data/out`"

openssl enc -d -chacha20 -in data/out -K "$key" -iv "$iv" -out data/dec -v -nopad
echo "Decrypted: `cat data/dec`"
