#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <math.h>
#include <QNetworkReply>

namespace Ui 
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*
    * \brief Main constructor of the app, connects everything together
    */
    explicit MainWindow(QWidget *parent = nullptr);

    /*
    * \brief Destructor for MainWindow
    */
    ~MainWindow();

#ifdef GTEST
    friend TEST;
#endif

private slots:
    /*
     * \brief Displays time in real-time and the max nr. of pencils produced since the app starts
    */
    void PencilsProduced();

    /*
     * \brief Displays nearly everything that you see in the app
    */
    void Display();

    /*
     * \brief Button when clicked makes a new pencil by using recourses
    */
    void onMakePencilclicked();

    /*
     * \brief Invisible public who buys pencils at a certain rate
    */
    void sellPencil();

    /*
     * \brief Button that when clicked, decreases the price of a pencil
    */
    void onDecreasePrizeclicked();

    /*
     * \brief Button that when clicked, increases the price of a pencil
    */
    void onIncreasePrizeclicked();

    /*
     * \brief Calls the randomizer for wood and graphite prices and shows them on the interface
    */
    void WoodGraphiteRand();

    /*
     * \brief Function generator of a random number from a specific range
     * \param low Lowest number in the range
     * \param high Highest number in the range
     * \return Returns the random number generated
    */
    double UpdateRandomNumber(double low, double high);

    /*
     * \brief A button that when clicked, can buy more wood if there is enough money
    */
    void on_BuyWood_clicked();

    /*
     * \brief Button that when clicked, buys more graphite if there is enough money
    */
    void on_BuyGraphite_clicked();

    /*
     * \brief Automatic pencil producer that can have a max of 10 instances
    */
    void AutoPencil2000();

    /*
     * \brief Button that when clicked, buys more instances of AutoPencil2000
    */
    void on_BuyMore_clicked();

    /*
     * \brief Intelligence generator
    */ 
    void generateIntelligence();

    /*
     * \brief Upgrade APM button action
    */ 
    void onUpgradeApmClicked();

    /*
     * \brief Upgrade Marketing button action
    */ 
    void onMarketingClicked();

    /*
     * \brief Save button action
    */ 
    void onSaveClicked();

    /*
     * \brief Helper function for posting the score
     * \param rep The reply that we get from the server of whether the upload was successful
    */
    void reqFinished(QNetworkReply *rep);

    /*
     * \brief Debugging tool: Wood and graphite +10 button action
    */ 
    void woodGraphite_clicked();

    /*
     * \brief Debugging tool: Increasing pencils in inventory
    */ 
    void inventory_clicked();

    /*
     * \brief Debugging tool: Increasing pencils in manufactured
    */ 
    void manufactured_clicked();

    /*
     * \brief Debugging tool: Adding 1000 to the bank balance
    */
    void grantMoney_clicked();
    
    /*
     * \brief Debugging tool: Checkbox for enabling and disabling the debugging tool
     * \param clicked The checkbox input
    */
    void debugEnabled(bool clicked);

    /*
     * \brief Getter method for the number of pencils in the inventory
     * \return The number of pencils in the inventory
    */
    unsigned int getInventory();

    /*
     * \brief Getter method for the number of pencils manufactured to date
     * \return The number of pencils manufactured to date
    */
    unsigned int getMaxPencils();

    /*
     * \brief Getter method for the number of wood
     * \return The number of wood
    */
    double getWoodLeft();

    /*
     * \brief Getter method for the number of graphite
     * \return The number of graphite
    */
    double getGraphiteLeft();

    /*
     * \brief Getter method for the bank balance
     * \return The bank balance
    */
    double getBankBalance();

    /*
     * \brief Getter method for the price of one pencil
     * \return The price of one pencil
    */
    double getPencilPrize();

    /*
     * \brief Getter method for the public demand
     * \return The public demand
    */
    double getPublicDemand();

    /*
     * \brief Getter method for the number of APM
     * \return The number of APM
    */
    unsigned int getAutoPencil();

    /*
     * \brief Getter method for the price of one APM
     * \return The price of one APM
    */
    double getAutoPencilPrize();

    /*
     * \brief Getter method for the number of intelligence
     * \return The number of intelligence
    */
    unsigned int getIntelligence();

    /*
     * \brief Getter method for the level of APM
     * \return The level of APM (0, 1, 2)
    */
    unsigned int getAPMLevel();

    /*
     * \brief Getter method for indicating whether the marketing function is unlocked
     * \return Status of the marketing function
    */
    unsigned int getMarketUnlock();

    /*
     * \brief Getter method for the rate of marketing
     * \return The rate of marketing
    */
    unsigned int getMarketRate();

    /*
     * \brief Getter method for the pencils produced by one APM per second
     * \return The number of pencils produced by one APM
    */
    double getAutoPencilRate();

    /*
     * \brief Getter method for the rate of selling one pencil
     * \return The rate of selling a pencil
    */
    double getSellPencilTime();

    /*
     * \brief Getter method for the rate of making one pencil by an APM
     * \return The rate of making a pencil by an APM
    */
    double getMakePencilTime();

    /*
     * \brief Getter method for the price of wood
     * \return The price of wood
    */ 
    double getWoodPrice();

    /*
     * \brief Getter method for the price of graphite
     * \return The price of graphite
    */ 
    double getGraphitePrice();

    /*
     * \brief Setter method for the number of pencils in the inventory
     * \param setInventory The number of pencils in the inventory
    */
    void setInventory(unsigned int setInventory);

    /*
     * \brief Setter method for the number of pencils manufactured to date
     * \param setMaxPencils The number of pencils manufactured to date
    */
    void setMaxPencils(unsigned int setMaxPencils);

    /*
     * \brief Setter method for the number of wood
     * \param setWoodLeft The number of wood
    */
    void setWoodLeft(double setWoodLeft);

    /*
     * \brief Setter method for the number of graphite
     * \param setGraphiteLeft The number of graphite
    */
    void setGraphiteLeft(double setGraphiteLeft);

    /*
     * \brief Setter method for the bank balance
     * \param setBankBalance The bank balance
    */
    void setBankBalance(double setBankBalance);

    /*
     * \brief Setter method for the pencil prize
     * \param setPencilPrize The pencil prize
    */
    void setPencilPrize(double setPencilPrize);

    /*
     * \brief Setter method for the public demand
     * \param setPublicDemand The public demand
    */
    void setPublicDemand(double setPublicDemand);

    /*
     * \brief Setter method for the number of APM
     * \param setAutoPencil The number of APM
    */
    void setAutoPencil(unsigned int setAutoPencil);

    /*
     * \brief Setter method for the prize of one APM
     * \param setAutoPencilPrize The prize of one APM
    */
    void setAutoPencilPrize(double setAutoPencilPrize);

    /*
     * \brief Setter method for the number of intelligence
     * \param setIntelligence The number of intelligence
    */
    void setIntelligence(unsigned int setIntelligence);

    /*
     * \brief Setter method for the level of the APM
     * \param setAPMLevel The level of the APM
    */
    void setAPMLevel(unsigned int setAPMLevel);

    /*
     * \brief Setter method for the status of the marketing function
     * \param setMarketUnlock The status of the marketing function
    */
    void setMarketUnlock(unsigned int setMarketUnlock);

    /*
     * \brief Setter method for the rate of marketing
     * \param setMarketRate The rate of marketing
    */
    void setMarketRate(unsigned int setMarketRate);

    /*
     * \brief Setter method for the number of pencils produced by one APM per second
     * \param setAutoPencilRate The number of pencils produced by one APM per second
    */
    void setAutoPencilRate(double setAutoPencilRate);

    /*
     * \brief Setter method for the rate of selling one pencil
     * \param setSellPencilTime The rate of selling one pencil
    */
    void setSellPencilTime(double setSellPencilTime);

    /*
     * \brief Setter method for the rate of making one pencil by an APM
     * \param setMakePencilTime The rate of makeing one pencil by an APM
    */
    void setMakePencilTime(double setMakePencilTime);

    /*
     * \brief Setter method for the price of wood
     * \param setWoodPrice The price of the wood
    */ 
    void setWoodPrice(double setWoodPrice);

    /*
     * \brief Setter method for the price of graphite
     * \param setGraphitePrice The price of graphite
    */ 
    void setGraphitePrice(double setGraphitePrice);

    /*
     * \brief Quit button action
    */
    void on_exit_clicked();

    /*
     * \brief Start game button action
    */
    void on_start_Button_clicked();

    /*
     * \brief Load button action
    */
    void on_load_Button_clicked();

    /*
     * \brief Function obtaining the mainURL and thus calling getScores
     * \param reply The reply received from the request of the website provided in the sprint writeup
    */
    void getMainURL(QNetworkReply *reply);

    /*
     * \brief Function obtaining the scores for the scoreboard from the mainURL
     * \param reply The reply received from the mainURL with the scores
    */
    void getScores(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;  ///< An instance of the interface

    QTimer *timer3;  ///< APM Implementation
    
    QTimer *timer4;  ///< Selling pencils

    unsigned int inventory = 0;  ///< Number of pencils in the inventory
    
    unsigned int maxPencils = 0;  ///< Number of pencils manufactured to date
    
    double wood_left = 1000.00;  ///< Number of wood
    
    double graphite_left = 1000.00;  ///< Number of graphite
    
    double bankbalance = 145.00;  ///< Bank balance
    
    double pencilprize = 1.00;  ///< Price of one pencil
    
    double publicDemand = 1.00;  ///< Public Demand

    unsigned int autopencil = 0;  ///< Number of APM
    
    double autopencilprize = 150.00;  ///< Price of one APM

    unsigned int intelligence = 0;  ///< Number of intelligence
    
    unsigned int apmLevel = 0;  ///< The level of the APM (0, 1, 2)
    
    unsigned int marketUnlock = 0;  ///< Indicating whether the marketing function is unlocked
    
    unsigned int marketRate = 0;  ///< Rate of marketing (m)
    
    double autopencilrate = 2.00;  ///< Pencils produced by one APM per second
    
    double sellPencilTime = 0.20 / publicDemand * 1000.00;  ///< Milliseconds needed for selling one pencil
    
    double makePencilTime = 1.00 / autopencilrate * 1000.00;  ///< Milliseconds needed for making one pencil of one APM

    double woodPrice = 1000.00;  ///< The default price of wood

    double graphitePrice = 1500.00;  ///< The default price of graphite

    std::string mainURL = "";  ///< The main URL which is received from the website provided in the sprint writeup
};

#endif // MAINWINDOW_H
