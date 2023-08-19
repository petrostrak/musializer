#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra"

clang $CFLAGS -o musializer main.c