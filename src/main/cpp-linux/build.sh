#!/usr/bin/env bash
set -e

cmake -B build -S .
cmake --build build --config Release
