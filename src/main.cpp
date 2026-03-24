#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle("CMC8401 针刺提花机控制系统");
    w.resize(800, 480);
    w.show();
    return app.exec();
}
