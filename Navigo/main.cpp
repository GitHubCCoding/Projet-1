#include "fenprincipale.h"
#include <QApplication>
#include <QtWebKitWidgets>
#include <QtWidgets>
#include <QMainWindow>
#include <QMouseEvent>

/*
void QMainWindow::mousePressEvent(QMouseEvent *){
    emit clicked();
}
*/

int main(int argc, char *argv[])
{
    //QWebSettings::clearMemoryCaches();
    QApplication a(argc, argv);

    FenPrincipale w;
    w.show();

    return a.exec();
}
