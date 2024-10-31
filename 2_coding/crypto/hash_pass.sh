#!/bin/bash

openssl kdf -keylen 64 \
    -kdfopt pass:my_password \
    -kdfopt salt:my_salt \
    -kdfopt n:1024 \
    -kdfopt r:8 \
    -kdfopt p:16 \
    -kdfopt maxmem_bytes:10485760 \
    SCRYPT
# Result
# 6C:C6:CC:16:6F:94:8A:C2:63:B0:45:E6:F9:4F:FD:F6:5B:50:11:F5:D2:4E:1B:D8:36:75:6A:AB:BE:8E:98:63:1A:0D:F5:E1:94:9E:8C:96:A0:3D:3C:38:7D:F5:F7:DA:31:4F:68:0D:32:47:4A:75:16:74:4D:FA:50:A8:BF:4B

# Argon2 available since OpenSSL 3.2
#openssl kdf -keylen 64 \
#    -kdfopt pass:my_password \
#    -kdfopt salt:my_salt_salt
#    -kdfopt lanes:2 \
#    -kdfopt memcost:65536 \
#    -kdfopt iter:10 \
#    ARGON2D
# Result
# 40:C9:FC:7B:F3:8F:F1:FE:B3:AB:0D:5B:3D:EA:C2:1A:BC:B4:5F:C5:CF:04:35:04:DC:C2:9B:2A:76:D9:AE:30:63:71:82:D7:C8:38:6D:9A:26:79:9C:62:1C:60:89:F7:CF:36:80:06:51:A2:43:98:DA:4F:17:4C:00:A0:B8:60
