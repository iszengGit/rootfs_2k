#!/bin/sh

###make fs

/opt/EmbedSky/linaro-4.9/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/mkubi256M_2k ./rootfs

mv rootfs_2k.img publish/rootfs.img

cp publish/rootfs.img /mnt/hgfs/A7.project/pduc.a7.firmware.hw1/publish/

