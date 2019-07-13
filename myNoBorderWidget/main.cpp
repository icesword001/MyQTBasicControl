#include <QApplication>
#include "QNoBorderWidget.h"
#include "QCustomWidget.h"
#include <QGraphicsDropShadowEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    QWidget w;
//    w.show();

    QCustomWidget* w = new QCustomWidget();
    w->setFixedSize(550, 500);
//    w->setShadow();
    w->show();

    return a.exec();
}
