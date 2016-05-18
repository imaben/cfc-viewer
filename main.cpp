#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyMainWindow *mainWindow = new MyMainWindow(&app);
    mainWindow->setWindowTitle("CFC Viewer");

    mainWindow->show();
    return app.exec();
}
