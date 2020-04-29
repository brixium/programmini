#!/bin/sh
CURRENT_USER=$(whoami)
ROOT=root
KERNEL_VERSION=4.19.0-6-amd64
NOME_SCRIPT="$(basename $0)"

if [ $CURRENT_USER = $ROOT ]
then
	rm /boot/vmlinuz-$KERNEL_VERSION
	rm /boot/initrd-$KERNEL_VERSION
	rm /boot/initrd.img-$KERNEL_VERSION
	rm /boot/System-map-$KERNEL_VERSION
	rm /boot/System.map-$KERNEL_VERSION
	rm /boot/config-$KERNEL_VERSION
	rm -rf /lib/modules/$KERNEL_VERSION/
	rm /var/lib/initramfs/$KERNEL_VERSION
	rm /var/lib/initramfs-tools/$KERNEL_VERSION
	update-grub2
else
	echo "Per eseguire questo script sono richiesti i privilegi di root. Esegui:"
	echo "sudo sh $NOME_SCRIPT"
fi
