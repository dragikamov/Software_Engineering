#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow pencilapp;
    pencilapp.show();

    return app.exec();
}

