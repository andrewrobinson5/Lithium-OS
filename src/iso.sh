#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/brindille.kernel isodir/boot/brindille.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "LearOS" {
	multiboot /boot/brindille.kernel
}
EOF
grub-mkrescue -o learos.iso isodir
