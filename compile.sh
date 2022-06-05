#!/bin/sh

set -e

gcc -Wall -O2 source/main.c -o build/telnet

./build/telnet "$@"
