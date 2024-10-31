#!/bin/bash

privKey1=data/ec_priv_1.pem
privKey2=data/ec_priv_2.pem

pubKey1=data/ec_pub_1.pem
pubKey2=data/ec_pub_2.pem

sharedSecret1=data/secret1
sharedSecret2=data/secret2

generate_private_key() {
    openssl genpkey -algorithm EC -pkeyopt ec_paramgen_curve:P-256 -pkeyopt ec_param_enc:named_curve -out $1 -outform PEM
    echo "Generated private key:"
    cat $1
    openssl pkey -text -in $1
}

generate_public_key() {
    openssl pkey -in $1 -pubout -out $2
    echo "Generated public key:"
    cat $2
}

# Generate firts private key
generate_private_key $privKey1
echo

# Generate second private key
generate_private_key $privKey2
echo

# Get first public key from private
generate_public_key $privKey1 $pubKey1
echo

# Get second public key from private
generate_public_key $privKey2 $pubKey2
echo

# Get shared secret for user 1
openssl pkeyutl -derive -inkey $privKey1 -peerkey $pubKey2 -out $sharedSecret1

# Get shared secret for user 2
openssl pkeyutl -derive -inkey $privKey2 -peerkey $pubKey1 -out $sharedSecret2

# Secrets will be the same
cmp $sharedSecret1 $sharedSecret2
echo "Shared secret: `xxd -ps -u $sharedSecret1`"
