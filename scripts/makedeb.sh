#!/bin/sh

/scratchbox/login -d $HOME/smsbackuprestore dpkg-buildpackage

deb=`/scratchbox/login -d $HOME find -maxdepth 1 -name smsbackuprestore*.deb`
echo copying $deb from sbox $HOME to $HOME/smsbackuprestore
/scratchbox/login -d $HOME cp $deb $HOME/smsbackuprestore

