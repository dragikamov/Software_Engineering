#ifndef WINDOW_H
#define WINDOW_H

#include "wallet.h"
#include "inventory.h"
#include "ui_window.h"
#include "api.h"
#include <gtest/gtest_prod.h>

#define JACOBS_ID                   "JACOBS_ID"
#define GAME_USERNAME               "GAME_USERNAME"
#define SE_TOKEN                    "SE_TOKEN"
#define GAME_USERNAME_MAX_LENGTH    15

/**
 * \brief Window Class. It is derived from QMainWindow.
 * A window provides a framework for
 * building an application's user interface.
*/
namespace Ui
{
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT  ///< The QObject class is the base class of all Qt objects.
public :
    /**
     * \brief A constructor of class Window
    */ 
    explicit Window(QWidget *parent = nullptr);

    /**
     * \brief A destructor of class Window
    */ 
    virtual ~Window();

    /**
     * \brief A setter method for setting the boolean of whether the window is open to true
     * \return void
    */ 
    void setisOpen();

    /**
     * \brief A getter method for getting the status of whether the window is open
     * \return The status of whether the window is open
    */ 
    bool getisOpen();

private:
    Ui::Window *ui;  ///< An instance of the interface window

    bool isOpen = false;  ///< The status of whether the window is open

    wallet gameWallet;  ///< An instance of the class Wallet
    inventory gameInventory;  ///< An instance of the class Inventory

    API *api;  ///< An instance of the server API used by the game

    std::string token;  ///< Used for storing the environmental variable SE-TOKEN
    std::string jacobsId;  ///< Used for storing the environmental variable JACOBS-ID
    std::string gameUsername;  ///< Used for storing the environmental variable GAME_USERNAME

private slots:
    /**
     * \brief Updates the user interface
     * \return void
    */
    void u_display();

    /**
     * \brief Updates prices of wood and graphite randomly
     * \result void
    */
    void U_WoodAndGraphite();

    /**
     * \brief Random Number generator
     * \param low The lower bound
     * \param high The higher bound
     * \return A random number between both the low and the high intervals
    */
    int randomNum(int low, int high);

    /**
     * \brief Checking if funds are enough to buy something
     * \param num Amount of money to be taken from the account
     * \return Whether we have enough funds to buy it or not
    */
    bool buy(double num);

    /**
     * \brief A function for selling a pen
     * \return void
    */
    void sell();

    /**
     * \brief A function for making a pen
     * \return void
    */
    void on_mkPen_clicked();

    /**
     * \brief A function for purchasing wood
     * \return void
    */
    void on_buyWood_clicked();

    /**
     * \brief A function for purchasing graphite
     * \return void
    */
    void on_buyGraphite_clicked();

    /**
     * \brief A function for computing the rate of the peoples' demand
     * \return void
    */
    void computeRate();

    /**
     * \brief A function for decreasing the price of a pen
     * \return void
    */
    void on_minusBtn_clicked();

    /**
     * \brief A function for increasing the price of a pen
     * \return void
     */
    void on_plusBtn_clicked();

    /**
     * \brief A function for the "Buy more" button being clicked
     * \return void
    */
    void on_buyMoreBtn_clicked();

    /**
     * \brief The Automatic Pencil Machine
     * \return void
    */
    void apm_make();

    /**
     * \brief Function for generating intelligence
     * \return void
    */
    void gen_intelligence();

    /**
     * \brief Function for saving the state of the game
     * \return void
    */
    void saveState();

    /**
     * \brief Function for closing the game window
     * \return void
    */
    void closeState();

    /**
     * \brief Function for loading the high score board
     * \return void
    */
    void highScoreBoardLoad();

    /**
     * \brief Function for starting the game again
     * \return void
    */
    void playAgainButton_clicked();


    FRIEND_TEST(randomNumTest, RandomNumIsConstrained);
    FRIEND_TEST(buyTest, buyDebitsAccount);
    FRIEND_TEST(sellTest, sellCreditsAccount);
    FRIEND_TEST(computeRateTest, DemandRateFormula);
    FRIEND_TEST(on_minusBtn_clickedTest, priceDecrement);
    FRIEND_TEST(on_plusBtn_clickedTest, priceIncrement);
    FRIEND_TEST(on_buyMoreBtn_clickedTest, apmIncrement);
    FRIEND_TEST(on_mkPen_clickedTest, pencilIncrement);
    FRIEND_TEST(on_buyWood_clickedTest, WoodIncrement);
    FRIEND_TEST(on_buyGraphite_clickedTest, GraphiteIncrement);

    /**
     * \brief A function for when the "Debug mode" is clicked
     * \param checked The status of the debug checkbox
     * \return void
    */ 
    void on_radioButton_clicked(bool checked);

    /**
     * \brief A function for the "Debug mode" for increasing money
     * \return void
    */ 
    void on_inc_money_clicked();

    /**
     * \brief A function for the "Debug mode" for increasing the inventory of pencils
     * \return void
    */ 
    void on_inc_penc_inv_clicked();

    /**
     * \brief A function for the "Debug mode" for increasing materials
     * \return void
    */ 
    void on_inc_materials_clicked();

    /**
     * \brief A function for when "Unlock Marketing" is clicked
     * \return void
    */ 
    void on_unlockMarketing_clicked();

    /**
     * \brief A function for when "Upgrade APM" is clicked
     * \return void
    */ 
    void on_upgradeAPM_clicked();

    /**
     * \brief A function for when "Add Intelligence" is clicked
     * \return void
    */
    void on_add_intelligence_clicked();

    /**
     * \brief A function for when "Add Marketing" is clicked
     * \return void
    */
    void on_add_marketing_clicked();

    /**
     * \brief A function for when "Start Game" is clicked
     * \return void
     */
    void on_startGame_clicked();

    /**
     * \brief A function for when "Load Game" is clicked
     * \return void
     */
    void on_loadButton_clicked();
};
#endif // WINDOW_H
