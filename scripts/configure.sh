#!/bin/sh
dir="$HOME/smsbackuprestore/build"
/scratchbox/login mkdir -p $dir
/scratchbox/login -d $dir cmake ..
