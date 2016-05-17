#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include <QSplitter>
#include <QMenu>
#include <QApplication>
#include <QStatusBar>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QStringListModel>
#include <hiredis/hiredis.h>

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    QApplication *application;

    QGroupBox *grpBox;
    QGroupBox *grpBox2;

    QLabel *lbHost;
    QLabel *lbPort;
    QLabel *lbHtName;
    QLabel *lbSearch;

    QLineEdit *textHost;
    QLineEdit *textPort;
    QLineEdit *textHtName;
    QLineEdit *textSearch;

    QPushButton *btnFetch;

    QListWidget *listWidget;

    QStatusBar *statusBar;

    QString strHost;
    QString strPort;
    QString strHtName;

    redisContext *redis;

    QStringList funcList;

public:
    MyMainWindow(QApplication *app);
    virtual ~MyMainWindow() {};

protected:
    void drawGroupBox();
    void drawLabel();
    void drawTextEdit();
    void drawPushButton();
    void drawListWidget();
    void drawStatusBar();

    void registerSignal();

    void fillListView(QString keyword = NULL);

private slots:
    void onFetch();
    void onSearchChanged(const QString &);
};

#endif