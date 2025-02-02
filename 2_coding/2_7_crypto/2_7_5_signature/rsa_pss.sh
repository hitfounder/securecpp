#!/bin/bash

privKey=data/rsa_pss_priv.pem
pubKey=data/rsa_pss_pub.pem

inputData=data/in
hash=data/hash
signature=data/signature

# Generate private key
openssl genpkey -algorithm RSA-PSS \
    -pkeyopt rsa_keygen_bits:2048 \
    -pkeyopt rsa_pss_keygen_md:sha256 \
    -pkeyopt rsa_pss_keygen_mgf1_md:sha256 \
    -pkeyopt rsa_pss_keygen_saltlen:32 \
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
  -pkeyopt digest:sha256 \
  -pkeyopt rsa_padding_mode:pss \
  -pkeyopt rsa_pss_saltlen:32
echo "Signature is: `xxd -ps -u $signature`"

# Verify
openssl pkeyutl -verify \
  -in $hash -sigfile $signature \
  -pubin -inkey $pubKey \
  -pkeyopt digest:sha256 \
  -pkeyopt rsa_padding_mode:pss \
  -pkeyopt rsa_pss_saltlen:32
