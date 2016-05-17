#include "mainwindow.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QUrl>
#include <QMessageBox>
#include "mainwindow.moc"

#define MAX_LIST_COUNT 2000

MyMainWindow::MyMainWindow(QApplication *app)
{
    application = app;
    drawGroupBox();
    drawLabel();
    drawTextEdit();
    drawPushButton();
    drawListWidget();
    drawStatusBar();

    registerSignal();
}

void MyMainWindow::drawGroupBox()
{
    grpBox = new QGroupBox(this);
    grpBox->setGeometry(QRect(10, 10, 760, 120));
    grpBox->show();

    grpBox2 = new QGroupBox(this);
    grpBox2->setGeometry(QRect(10, 160, 760, 800));
    grpBox2->show();
}

void MyMainWindow::drawLabel()
{
    lbHost = new QLabel(grpBox);
    lbHost->setText("Redis Host:");
    lbHost->setGeometry(QRect(20, 20, 150, 30));
    lbHost->show();

    lbPort = new QLabel(grpBox);
    lbPort->setText("Redis Port:");
    lbPort->setGeometry(QRect(300, 20, 150, 30));
    lbPort->show();

    lbHtName = new QLabel(grpBox);
    lbHtName->setText("Hash Table Name:");
    lbHtName->setGeometry(QRect(500, 20, 150, 30));
    lbHtName->show();

    lbHtName = new QLabel(grpBox2);
    lbHtName->setText("Search:");
    lbHtName->setGeometry(QRect(20, 10, 50, 30));
    lbHtName->show();

}

void MyMainWindow::drawTextEdit()
{
    textHost = new QLineEdit(grpBox);
    textHost->setText("127.0.0.1");
    textHost->setGeometry(QRect(100, 20, 140, 28));
    textHost->show();

    textPort = new QLineEdit(grpBox);
    textPort->setText("6379");
    textPort->setGeometry(QRect(385, 20, 50, 28));
    textPort->show();

    textHtName = new QLineEdit(grpBox);
    textHtName->setText("cfc_hash");
    textHtName->setGeometry(QRect(620, 20, 100, 28));
    textHtName->show();

    textSearch = new QLineEdit(grpBox2);
    textSearch->setGeometry(QRect(80, 10, 650, 28));
    textSearch->show();
}

void MyMainWindow::drawPushButton()
{
    btnFetch = new QPushButton(" Fetch ", grpBox);
    btnFetch->setGeometry(QRect(330, 70, 100, 30));
    btnFetch->show();
}

void MyMainWindow::drawListWidget()
{
    listWidget = new QListWidget(grpBox2);
    listWidget->setGeometry(QRect(20, 50, 715, 730));
    listWidget->show();
}

void MyMainWindow::drawStatusBar()
{
    statusBar = QMainWindow::statusBar();
    statusBar->showMessage("Done.");
}

void MyMainWindow::registerSignal()
{
    connect(btnFetch, SIGNAL(clicked()), this, SLOT(onFetch()));
    connect(textSearch, SIGNAL(textChanged(const QString &)), this, SLOT(onSearchChanged(const QString &)));
}

void MyMainWindow::onFetch()
{
    statusBar->showMessage("Fetching data...");

    strHost = textHost->text();
    strPort = textPort->text();
    strHtName = textHtName->text();

    if (strHost.isEmpty() || strPort.isEmpty() || strHtName.isEmpty()) {
        QMessageBox::about(NULL, "warning", "Invalid parameters!");
        return;
    }

    char *szTmp;
    QByteArray ba = strHost.toLatin1();
    szTmp = ba.data();

    redis = redisConnect(szTmp, strPort.toInt());
    if (redis == NULL || redis->err) {
        QMessageBox::about(NULL, "error", "Cannot connect to redis!");
        return;
    }

    ba = strHtName.toLatin1();
    szTmp = ba.data();

    redisReply *reply = NULL;
    reply = (redisReply *)redisCommand(redis, "HGETALL %s", szTmp);
    if (redis->err != 0 || reply == NULL || reply->type != REDIS_REPLY_ARRAY) {
        QMessageBox::about(NULL, "error", "Failed to fetch data!");
        return;
    }

    funcList.clear();

    size_t i = 0;
    char *key, *val;
    for (; i < reply->elements; i++) {
        key = reply->element[i++]->str;
        val = reply->element[i]->str;
        QString d = QString("%1(%2)").arg(key).arg(val);
        funcList.append(d);
        statusBar->showMessage(d);
    }
    freeReplyObject(reply);
    redisFree(redis);
    fillListView();
    statusBar->showMessage(QString("Done. total:%1").arg(funcList.count()));
}

void MyMainWindow::onSearchChanged(const QString &keyword)
{
    fillListView(keyword);
}

int MyMainWindow::fillListView(QString keyword)
{
    while (listWidget->count()) listWidget->takeItem(0);

    int i, j;
    if (keyword.isEmpty()) {
        for (i = 0; i < funcList.size(); i++) {
            if (i >= MAX_LIST_COUNT) {
                break;
            }
            listWidget->addItem(funcList.at(i));
        }
        return i;
    } else {
        for (i = 0, j = 0; i < funcList.size(); i++) {
            if (j >= MAX_LIST_COUNT) {
                break;
            }
            if (funcList.at(i).contains(keyword, Qt::CaseInsensitive)) {
                listWidget->addItem(funcList.at(i));
                j++;
            }
        }
        return j;
    }
}
