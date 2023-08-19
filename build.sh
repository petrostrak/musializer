#!/bin/sh

export LD_LIBRARY_PATH=/usr/local/lib64

set -xe

CFLAGS="-Wall -Wextra `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib` -lglfw -lm -ldl -lpthread"

clang $CFLAGS -o musializer main.c $LIBS