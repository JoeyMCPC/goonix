#!/bin/bash

# Remove old binary
#rm iso_root/boot/goonix
# Remove old ISO image
rm -f image.iso

# Clean previous build artifacts
make clean

# Build the project
make

# Run any extra setup or copying steps
./exe.sh
./iso.sh

# Launch the OS in QEMU or whichever emulator you use
./run.sh

