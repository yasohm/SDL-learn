#!/usr/bin/env bash
# Compile with sdl2-config to get correct include/link flags, and enable warnings
gcc -Wall -Wextra -std=c11 main.c -o main $(sdl2-config --cflags --libs)

# Run the program
./main
