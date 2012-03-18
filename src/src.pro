TEMPLATE = app
QT += declarative
QT -= gui
CONFIG += link_pkgconfig
PKGCONFIG = commhistory
TARGET = "smsbackuprestore"
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += util.h catcher.h
SOURCES += main.cpp util.cpp
#FORMS#

  unix {
    #VARIABLES
    isEmpty(PREFIX) {
        PREFIX = /usr
  }
BINDIR = $$PREFIX/bin
DATADIR =$$PREFIX/share

DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"
DEFINES += QT_USE_QSTRINGBUILDER

#MAKE INSTALL

INSTALLS += target qmlgui desktop service iconxpm icon26 icon48 icon64

  target.path =$$BINDIR

  qmlgui.path = $$DATADIR/smsbackuprestore
  qmlgui.files += smsbackuprestore.qml

  desktop.path = $$DATADIR/applications
  desktop.files += $${TARGET}.desktop

  service.path = $$DATADIR/dbus-1/services/
  service.files += com.meego.$${TARGET}.service

  iconxpm.path = $$DATADIR/pixmap
  iconxpm.files += ../data/maemo/$${TARGET}.xpm

  icon26.path = $$DATADIR/icons/hicolor/26x26/apps
  icon26.files += ../data/26x26/$${TARGET}.png

  icon48.path = $$DATADIR/icons/hicolor/48x48/apps
  icon48.files += ../data/48x48/$${TARGET}.png

  icon64.path = $$DATADIR/icons/hicolor/64x64/apps
  icon64.files += ../data/64x64/$${TARGET}.png
}
