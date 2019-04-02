/**
 *  @file     main.cpp
 *  @brief    Showing the window GUI.
 *  @include  mainwindow.h
 */

#include "mainwindow.h"
#include <QApplication>

/**
 * @param argc
 * @param argv
 * @return app.exec()
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
