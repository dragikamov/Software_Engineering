/**
 *  @file     mainwindow.h
 *  @brief    Class and method declaration
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pencilmakermodel.h"

namespace Ui {
class MainWindow;
}

/**
 *  @class  MainWindow
 *  @brief  Class to implement the Pencil Producer game
 *  @detail In this class we will define the constructor/descructor and all the other methods we need to make it run. As for the first Spring, we are in need of a cons/dest only.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @fn MainWindow
     * @param parent
     * @brief constructor
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @fn ~MainWindow
     * @brief destructor
     */
    ~MainWindow();
    /**
     * @fn render
     * @brief MainWindow::render Render the view according to the model
     * @param model
     * It also takes care of enabling and diabling the buttons
     */
    void render(PencilMakerModel* model);

    /**
     * @fn getPencilsInv
     * @brief Getter method for number of pencils in the inventory
     * @return Pencils in the current inventory
    */
    int getPencilsInv();

    /**
     * @fn getTotalPencils
     * @brief Getter method for number of pencils in the inventory(to date)
     * @return Pencils in the inventory(to date)
    */
    int getTotalPencils();

    /**
     * @fn getBalance
     * @brief Getter method for the current balance
     * @return Current balance
    */
    double getBalance();

    /**
     * @fn getPencilPrice
     * @brief Getter method for the current price of a pencil
     * @return Current price of a pencil
    */
    double getPencilPrice();

    /**
     * @fn getWoodInv
     * @brief Getter method for the amount of wood in the inventory
     * @return Amount of wood in the inventory
    */
    double getWoodInv();

    /**
     * @fn getGraphiteInv
     * @brief Getter method for the amount of graphite in the inventory
     * @return Amount of graphite in the inventory
    */
    double getGraphiteInv();

    /**
     * @fn getWoodPrice
     * @brief Getter method for the current price of wood
     * @return Current price of wood
    */
    double getWoodPrice();

    /**
     * @fn getGraphitePrice
     * @brief Getter method for the current price of graphite
     * @return Current price of graphite
    */
    double getGraphitePrice();

    /**
     * @fn getNAPM
     * @brief Getter method for the number of APMs
     * @return APMs owned
    */
    int getNAPM();

    /**
     * @fn getAPMPrice
     * @brief Getter method for the current price of an APM
     * @return Current price of an APM
    */
    double getAPMPrice();
public slots:

    /**
     * @fn onPencilButtonClicked
     * @brief actions that need to be taken after
     *        make pencil has been clicked
     */
    void onPencilButtonClicked();

    /**
     * @fn pencilPriceInc
     * @brief actions that need to be taken after
     *        make pencil_price_inc has been clicked
    */
    void pencilPriceInc();

    /**
     * @fn pencilPriceDec
     * @brief actions that need to be taken after
     *        make pencil_price_dec has been clicked
    */
    void pencilPriceDec();

    /**
     * @fn pencilInventory
     * @brief determines pencils in inventory every 5 secs
    */
    void pencilInventory();

    /**
     * @fn incPencilInventory
     * @brief increase inventory every second
    */
    void incPencilInventory();

    /**
     * @fn intelligenceInventory
     * @brief increase intelligence every second
    */
    void intelligenceInventory();

    /**
     * @fn priceofwood
     * @brief determines price of wood every 5 secs
    */
    void priceofwood();

    /**
     * @fn onBuyWoodButtonClick
     * @brief actions that need to be taken after
     * buy wood has been clicked
    */
    void onBuyWoodButtonClicked();

    /**
     * @fn priceofgraphite
     * @brief determines price of graphite every 5 secs
    */
    void priceofgraphite();

    /**
     * @fn onBuyGraphiteButtonClicked
     * @brief actions that need to be taken after
     * buy graphite has been clicked
    */
    void onBuyGraphiteButtonClicked();

    /**
     * @fn buyAPM
     * @brief actions that need to be taken after
     * buy more has been clicked
    */
    void buyAPM();

    /**
     * @fn upgradableAPM
     * @brief actions that need to be taken after
     * upgrade APM has been clicked
     */
    void upgradableAPM();

    /**
     * @fn marketing
     * @brief actions that need to be taken after
     * upgrade marketing has been clicked
    */ 
    void marketing();

private slots:
    /**
     * @fn on_saveBtn_clicked
     * @brief actions that need to be taken after
     * save to file has been clicked
    */
    void on_saveBtn_clicked();

    /**
     * @fn on_loadBtn_clicked
     * @brief actions that need to be taken after
     * load from file has been clicked
    */
    void on_loadBtn_clicked();

    /**
     * @fn on_debug_stateChanged
     * @brief actions that need to be taken after
     * the checkbox has been checked or unchecked
     * @param arg1 The state of the checkbox
     */
    void on_debug_stateChanged(int arg1);

    /**
     * @fn debug
     * @brief actions that need to be taken after
     * the debugging button has been clicked
     */
    void debug();

private:

    Ui::MainWindow *ui; /**< pointer to user interface */

    PencilMakerModel* model; /**< pointer to inventory */

};

#endif // MAINWINDOW_H
