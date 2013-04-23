#!/bin/sh
dir=$(dirname `readlink -f $0`)
project=$(basename "$dir")
debname="smsbackuprestore"
mnt=/scratchbox/users/$USER/home/$USER/$project

if ! mount | grep "$project on $mnt"; then
  sudo /scratchbox/sbin/sbox_ctl start
  sudo /scratchbox/sbin/sbox_sync

  mkdir -p $mnt
  sudo mount -o bind $dir $mnt
fi


/scratchbox/login -d $HOME find -maxdepth 2 -name $debname*.deb -delete
/scratchbox/login -d $HOME find -maxdepth 2 -name $debname*.changes -delete
/scratchbox/login -d $HOME find -maxdepth 2 -name $debname*.dsc -delete
/scratchbox/login -d $HOME find -maxdepth 2 -name $debname*.gz -delete

/scratchbox/login -d $HOME/$project qmake
/scratchbox/login -d $HOME/$project dpkg-buildpackage

deb=`/scratchbox/login -d $HOME find -maxdepth 1 -name $debname*.deb`
echo copying $deb from sbox $HOME to $HOME/$project
/scratchbox/login -d $HOME cp $deb $HOME/$project
