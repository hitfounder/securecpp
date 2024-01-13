#!/bin/bash

test_encryption() {
    start=`date +%s%N`
    for i in $(seq 1 1000);
    do
        openssl enc $1 -in data/in -K "$(<data/key.txt)" -iv "$(<data/iv.txt)" -out data/out
    done
    end=`date +%s%N`
    echo Encryption time for $1 was `expr $end - $start` nanoseconds.
}

test_decryption() {
    openssl enc $1 -in data/in -K "$(<data/key.txt)" -iv "$(<data/iv.txt)" -out data/out
    start=`date +%s%N`
    for i in $(seq 1 1000);
    do
        openssl enc -d $1 -in data/out -K "$(<data/key.txt)" -iv "$(<data/iv.txt)" -out data/dec
    done
    end=`date +%s%N`
    echo Decryption time for $1 was `expr $end - $start` nanoseconds.
}

test_encryption "-aes-256-cbc"
test_encryption "-chacha20"
test_decryption "-aes-256-cbc"
test_decryption "-chacha20"
