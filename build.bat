@echo off
echo Building Memory Vulnerabilities Test Project...
echo.

echo Note: This project requires a C++ compiler (g++ or clang) to build.
echo Please install a C++ compiler and update this script with the correct path.
echo.
echo Example installation options:
echo - MinGW-w64: https://www.mingw-w64.org/
echo - Microsoft Visual Studio Build Tools
echo - LLVM/Clang
echo.

echo Project structure created successfully!
echo To build manually after installing a compiler:
echo   g++ -std=c++17 -Wall -Wextra -Wpedantic -g -O0 -Iinclude src/vulnerabilities.cpp src/c_vulnerabilities.c tests/main.cpp -o memory_vulnerabilities
echo.
pause
