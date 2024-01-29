#!/bin/bash

echo "Random by OpenSSL: "
openssl rand -hex 32

echo "Random by /dev/urandom: "
dd if=/dev/urandom bs=32 count=1 2> /dev/null | xxd -p -c 32