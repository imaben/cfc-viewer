#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QDockWidget>
#include <QLabel>
#include <QPixmap>
#include <QWebView>
#include <QSplitter>
#include <QString>
#include <QFile>
#include <QDir>
#include <QTimer>
#include <QObject>
#include "mainwindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyMainWindow *mainWindow = new MyMainWindow(&app);
    mainWindow->setWindowTitle("CFC Viewer");

    mainWindow->show();
    return app.exec();
}
