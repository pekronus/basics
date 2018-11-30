#!/bin/sh

DEV_ROOT="$HOME/dev"
cd "$DEV_ROOT/basics"
if [ ! -d bin ]; then
    mkdir bin
fi
cd bin
cmake ../src
