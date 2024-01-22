#!/bin/bash

privKey=data/rsa_priv.pem
pubKey=data/rsa_pub.pem

inputData=data/in
encryptedData=data/out
decrtptedData=data/dec

# Generate private key
openssl genpkey -algorithm rsa -pkeyopt rsa_keygen_bits:2048 -pkeyopt rsa_keygen_pubexp:65537 -pkeyopt rsa_keygen_primes:2 -out $privKey -outform PEM
echo "Generated private key:"
(head -n 4; echo "..."; tail -n 4) < $privKey
openssl pkey -text -in $privKey

echo

# Get public key from private
openssl rsa -in $privKey -pubout -out $pubKey
echo "Generated public key:"
(head -n 4; echo "..."; tail -n 4) < $pubKey
openssl pkey -text -pubin -in $pubKey

echo

# Encrypting data using public key
openssl pkeyutl -encrypt -in $inputData -inkey $pubKey -pubin -out $encryptedData -pkeyopt rsa_padding_mode:oaep
echo "Encrypted: `xxd -ps -u $encryptedData`"

# Decrypting data using private key
openssl pkeyutl -decrypt -in $encryptedData -inkey $privKey -out $decrtptedData -pkeyopt rsa_padding_mode:oaep
echo "Decrypted: `cat $decrtptedData`"
