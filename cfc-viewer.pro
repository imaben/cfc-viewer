TEMPLATE = app
TARGET = cfc-viewer
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += qt
LIBS += -lhiredis
QT += webkit
# Input
SOURCES += main.cpp mainwindow.cpp
