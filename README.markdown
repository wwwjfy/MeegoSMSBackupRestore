# SMS Backup and Restore for Meego

## Functionalities

### Import

Usage:

    ./smsbackuprestore import [filename]

After testing, importing will do around 100 messages per minute on N9.
It'll commit every 200 messages to quiet warning "The task queue's background thread stalled".

### Export

Usage:

    ./smsbackuprestore export [filename]

Exporting is quite fast as it need not commit to tracker database.

## Why not use standard Meego SDK

Because Meego SDK doesn't support SMS manipulation, new SMS can not be in Draft, so I use [Harmattan Platform SDK](http://harmattan-dev.nokia.com/platform-sdk/).

## TODO

GUI