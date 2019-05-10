#include "window.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[]){

    QApplication mainApp(argc, argv);

    // create and show your widgets here
    Window window;
    window.show();

    return mainApp.exec();
}
