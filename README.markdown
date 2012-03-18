# SMS Backup and Restore for Meego

## Installation

Deb file can be downloaded from <https://github.com/wwwjfy/MeegoSMSBackupRestore/downloads>.

run on device

    dpkg -i smsbackuprestore_0.1_armel.deb

## Functionalities

### Import

Usage:

    smsbackuprestore import [filename]

After testing, importing will do around 100 messages per minute on N9.
It'll commit every 200 messages to quiet warning "The task queue's background thread stalled".

### Export

Usage:

    smsbackuprestore export [filename]

Exporting is quite fast as it need not commit to tracker database.

## Why not use standard Meego SDK

Because Meego SDK doesn't support SMS manipulation, new SMS can not be in Draft, so I use [Harmattan Platform SDK](http://harmattan-dev.nokia.com/platform-sdk/).

## TODO

GUI

## Thanks

Thank [Philipp Zabel](philipp.zabel@gmail.com), the author of [mff](http://gitorious.org/mff/mff), which imports SMS messages from N900(el-v1.db). The deb file can be downloaded in <http://talk.maemo.org/showthread.php?t=77415&page=4>

Referencing a lot commhistory-tool.cpp in [libcommhistory](https://gitorious.org/commhistory/libcommhistory).