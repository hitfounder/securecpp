#!/bin/bash

cert=data/tls_cert.pem
key=data/tls_key.pem
port=11111

openssl req -x509 -noenc -days 1000 -newkey rsa:2048 -keyout $key -out $cert -subj "/C=XX/ST=StateName/L=CityName/O=CompanyName/OU=CompanySectionName/CN=CommonNameOrHostname"
openssl s_server -tls1_3 -accept $port -cert $cert -key $key
