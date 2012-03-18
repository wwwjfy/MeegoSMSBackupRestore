# SMS Backup and Restore for Meego

## Import

Usage:

> ./smsbackuprestore import [filename]

After testing, importing will do around 100 messages per minute on N9.
It'll commit every 200 messages, otherwise, it's possible to appear "The task queue's background thread stalled" if committing everything on one go.

## Export

Usage:

>./smsbackuprestore export [filename]

Exporting is quite fast as it need not commit to tracker database.