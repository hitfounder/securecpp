#!/bin/bash

hash=`openssl passwd -6 -noverify`
echo $hash
split=(${hash//$/ })
echo "Hash type '${split[0]}', generated salt '${split[1]}', hash '${split[2]}'"

hash_verify=`openssl passwd -salt $salt -6`
if [[ "$hash" == "$hash_verify" ]]
then
    echo "Password correct"
else
    echo "Password incorrect"
fi