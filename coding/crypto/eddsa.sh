#!/bin/bash

privKey=data/ecdsa_pss_priv.pem
pubKey=data/ecdsa_pss_pub.pem

inputData=data/in
hash=data/hash
signature=data/signature

# Generate private key
openssl genpkey -algorithm ED25519 \
    -out $privKey -outform PEM
echo "Generated private key:"
(head -n 4; echo "..."; tail -n 4) < $privKey
openssl pkey -text -in $privKey

# Get public key from private
openssl pkey -in $privKey -pubout -out $pubKey
echo "Generated public key:"
(head -n 4; echo "..."; tail -n 4) < $pubKey
openssl pkey -text -pubin -in $pubKey

# Sign
# Eddsa always uses sha512,
# so we could not pass external digest.
# "rawin" is necessary
openssl pkeyutl -sign \
  -rawin -in $inputData -inkey $privKey \
  -out $signature
echo "Signature is: `xxd -ps -u $signature`"

# Verify
openssl pkeyutl -verify \
  -rawin -in $inputData -sigfile $signature \
  -pubin -inkey $pubKey
