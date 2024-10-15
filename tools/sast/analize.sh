#/bin/sh

rm -rf CMakeFiles/ CMakeCache.txt pvs_report clang_report
scan-build cmake .
scan-build -o clang_report make

pvs-studio-analyzer credentials PVS-Studio Free FREE-FREE-FREE-FREE
pvs-studio-analyzer trace -- make
pvs-studio-analyzer analyze
plog-converter -a GA:1,2 -t fullhtml PVS-Studio.log -o pvs_report
