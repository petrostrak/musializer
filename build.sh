#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra `pkg-config --cflags raylib`"
LIBS="`pkg-config --cflags raylib`"

clang $CFLAGS -o musializer main.c $LIBS