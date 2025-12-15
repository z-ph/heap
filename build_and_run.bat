@REM rm -rf build
@REM mkdir -p build
@REM gcc ./src/heap.c -o build/heap
@echo off
rmdir /s /q build
mkdir build
gcc .\src\main.c -o build\main.exe
.\build\main.exe