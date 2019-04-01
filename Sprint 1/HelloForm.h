/*
 * HelloForm.h
 * se-01-team-12
 */

#ifndef _HELLOFORM_H
#define	_HELLOFORM_H

#include "ui_HelloForm.h"

class HelloForm : public QDialog {
    Q_OBJECT
public:
    /**
     * \brief Constructor for HelloForm.
     */
    HelloForm();
    /**
     * \brief Destructor for HelloForm.
     */
    virtual ~HelloForm();
private:
    /*
     * \brief An object of type HelloForm
     */
    Ui::HelloForm widget;
};

#endif	/* _HELLOFORM_H */
