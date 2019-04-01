/*
 * newmain.cpp
 * se-01-team-12
 */

#include <QGuiApplication>
#include "HelloForm.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    HelloForm form;
    form.show();

    return app.exec();
}
