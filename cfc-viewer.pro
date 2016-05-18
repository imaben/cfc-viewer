TEMPLATE = app
TARGET = cfc-viewer
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += qt link_pkgconfig
PKGCONFIG += hiredis
LIBS += `pkg-config --libs hiredis`
# Input
SOURCES += main.cpp mainwindow.cpp
