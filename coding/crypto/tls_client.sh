#!/bin/bash

port=11111

openssl s_client -connect localhost:$port <<< "Hello"
