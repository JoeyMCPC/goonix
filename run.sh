#!/bin/bash

qemu-system-x86_64 \
  -m 512M \
  -cdrom image.iso \
  -boot d \
  -serial stdio \
  -no-shutdown \
  -no-reboot

