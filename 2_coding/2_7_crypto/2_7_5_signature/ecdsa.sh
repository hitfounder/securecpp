#!/bin/bash

privKey=data/ecdsa_priv.pem
pubKey=data/ecdsa_pub.pem

inputData=data/in
hash=data/hash
signature=data/signature

# Generate private key
openssl genpkey -algorithm EC \
    -pkeyopt ec_paramgen_curve:P-256 \
    -pkeyopt ec_param_enc:named_curve \
    -out $privKey -outform PEM
echo "Generated private key:"
(head -n 4; echo "..."; tail -n 4) < $privKey
openssl pkey -text -in $privKey

# Get public key from private
openssl pkey -in $privKey -pubout -out $pubKey
echo "Generated public key:"
(head -n 4; echo "..."; tail -n 4) < $pubKey
openssl pkey -text -pubin -in $pubKey

# Calculate hash
openssl dgst -sha256 -binary -out $hash $inputData
echo "Hash of input file is: `xxd -ps -u $hash`"

# Sign
openssl pkeyutl -sign \
  -in $hash -inkey $privKey \
  -out $signature \
  -pkeyopt digest:sha256
echo "Signature is: `xxd -ps -u $signature`"

# Verify
openssl pkeyutl -verify \
  -in $hash -sigfile $signature \
  -pubin -inkey $pubKey \
  -pkeyopt digest:sha256
