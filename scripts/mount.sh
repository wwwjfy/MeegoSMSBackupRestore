#!/bin/sh
dir=$HOME/Code/smsbackuprestore
mnt=/scratchbox/users/$USER/home/$USER/smsbackuprestore

sudo /scratchbox/sbin/sbox_ctl start
sudo /scratchbox/sbin/sbox_sync

mkdir $mnt
sudo mount -o bind $dir $mnt
