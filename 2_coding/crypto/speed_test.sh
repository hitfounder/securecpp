#!/bin/bash

test_encryption() {
    start=`date +%s%N`
    for i in $(seq 1 1000);
    do
        openssl enc $1 -in data/in -K $2 -iv $3 -out data/out
    done
    end=`date +%s%N`
    echo Encryption time for $1 was `expr $end - $start` nanoseconds.
}

test_decryption() {
    openssl enc $1 -in data/in -K $2 -iv $3 -out data/out
    start=`date +%s%N`
    for i in $(seq 1 1000);
    do
        openssl enc -d $1 -in data/out -K $2 -iv $3 -out data/dec
    done
    end=`date +%s%N`
    echo Decryption time for $1 was `expr $end - $start` nanoseconds.
}

key256="$(<data/key256.txt)"
key128="$(<data/key128.txt)"
iv128="$(<data/iv128.txt)"

test_encryption "-aes-256-cbc" $key256 $iv128
test_encryption "-aes-128-cbc" $key128 $iv128
test_encryption "-chacha20" $key256 $iv128
test_decryption "-aes-256-cbc" $key256 $iv128
test_decryption "-aes-128-cbc" $key128 $iv128
test_decryption "-chacha20" $key256 $iv128
