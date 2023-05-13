@echo off

if not exist build cmake -B build

cmake --build build && build\Debug\midas.exe
echo Return Code: %errorlevel%
