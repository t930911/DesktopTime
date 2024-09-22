#include "widget.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/font/font.ttf");
    Widget w;
    w.show();
    return a.exec();
}
