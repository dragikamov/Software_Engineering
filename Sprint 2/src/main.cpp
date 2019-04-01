/**
 * \file main.cpp
 */

#include <QApplication>
#include "pencilproducer.h"

#include <iostream>

/**
 * \brief The main function
 * 
 * \param argc Number of arguments at execution
 * \param argv All the arguments at execution
 * \return Successful/Failed execution
 */
int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    PencilProducer w;
    w.show();

    return app.exec();
}
