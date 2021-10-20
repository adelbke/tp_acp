#!/bin/bash
# gcc main.c -lpthread -o executable
mkdir -p ./dist/$(dirname ${1%".c"})
gcc -w ./scripts/$1 -lpthread -o ./dist/${1%".c"}

./dist/${1%".c"}
