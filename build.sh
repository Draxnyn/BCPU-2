#!/usr/bin/env bash
# build.sh — compila o assembler (dentro de assembler/)

set -e

# entra em assembler/
cd assembler

# gera Makefiles em assembler/build
cmake -G "Unix Makefiles" -B build

# compila dentro de assembler/build
cmake --build build
