#!/bin/bash

openssl kdf -keylen 16 \
            -kdfopt digest:SHA2-256 \
            -kdfopt key:password \
            -kdfopt salt:salt \
            -kdfopt info:app \
            HKDF
