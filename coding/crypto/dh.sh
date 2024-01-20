#!/bin/bash

param=data/dh_param.pem

privKey1=data/dh_priv_1.pem
privKey2=data/dh_priv_2.pem

pubKey1=data/dh_pub_1.pem
pubKey2=data/dh_pub_2.pem

sharedSecret1=data/secret1
sharedSecret2=data/secret2

generate_private_key() {
    openssl genpkey -paramfile $1 -out $2
    echo "Generated private key:"
    (head -n 4; echo "..."; tail -n 4) < $2
}

generate_public_key() {
    openssl pkey -in $1 -pubout -out $2
    echo "Generated public key:"
    (head -n 4; echo "..."; tail -n 4) < $2
}

# Create DH parameters
openssl genpkey -genparam -algorithm DH -out $param -pkeyopt dh_paramgen_prime_len:2048 -pkeyopt dh_paramgen_generator:2

echo "DH parameters:"
openssl pkeyparam -in $param -text
echo

# Generate first private key
generate_private_key $param $privKey1
echo

# Generate second private key
generate_private_key $param $privKey2
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
