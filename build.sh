#!/bin/bash
rm -rf build
mkdir -p build
gcc ./src/heap.c -o build/heap