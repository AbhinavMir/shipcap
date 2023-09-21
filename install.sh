#!/bin/bash

# Compile the program using the Makefile
make

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Install the binary
    sudo make install
else
    echo "Compilation failed. Installation aborted."
fi
