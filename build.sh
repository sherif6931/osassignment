#!/bin/bash

# yes... too lazy to write this twice, or trice, or quatrice, or quintice
make clean

if make; then
    if lsmod | grep -q "mkvm"; then
        sudo rmmod mkvm
    fi

    sudo insmod mkvm.ko

    if lsmod | grep -q "mkvm"; then
        echo "✅ Mod loaded."

        sudo dmesg -w
    else
        echo "❌ Mod didn't load for some reason."
	exit 1
    fi
else
    echo "❌ Compilation failed."
    exit 1
fi
