/**
 * \file pencilproducer.h
 */

#ifndef PENCILPRODUCER_H
#define PENCILPRODUCER_H

#include <QMainWindow>

namespace Ui {
class PencilProducer;
}

/**
 * \brief The PencilProducer class
 */
class PencilProducer : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * \brief Constructor for the PencilProducer
     */
    explicit PencilProducer(QWidget *parent = nullptr);
    
    /**
     * \brief Destructor for the PencilProducer object
     */
    ~PencilProducer();

private:
    /** \brief An object for the interface */
    Ui::PencilProducer *ui;

    /** \brief Amount of pencils in current inventory */
    unsigned int inventory = 0;

    /** \brief Amount of pencils in inventory to date */
    unsigned int inventory_to_date = 0;

    /** \brief Amount of graphite left in inventory */
    double graph_left = 1000.00;

    /** \brief Amount of wood left in inventory */
    double wood_left = 1000.00;

    /** \brief Amount money on our account */
    double balance = 145.00;

    /** \brief Current price of wood */
    unsigned int woodPrice = 1500;

    /** \brief Current price of graphite */
    unsigned int graphPrice = 2000;

    /** \brief Current price of pencil */
    double pencilPrice = 1.00;

    /** \brief Public demand (shown on the interface as an integer) */    
    unsigned int publicDemand = 1;

    /** \brief Number of APMs we own */    
    unsigned int countAPM2000 = 0;

    /** \brief Price of the current APM */
    double priceAPM2000 = 150.0;

    /** \brief Demand rate (used only while computing) */
    double demandRate = 0.0;

public slots:
    /**
     * \brief Update all values to the GUI
     *
     * \return void
     */
    void update_display();

    /**
     * \brief Random integer generator
     *
     * \param low The lower bound
     * \param high The higher bound
     * \return A random integer between low and high
     */
    int randInt(int low, int high);

    /**
     * \brief Update of wood graph
     *
     * \result void
     */
    void update_wood_graph();

    /**
     * \brief Check if we have enough funds to buy something
     *
     * \param amount The price that is to be subtracted from our account
     * \return Whether we have that money in our account to be subtracted
     */
    bool buy(double amount);

    /**
     * \brief Sell a pencil
     *
     * \return void
     */
    void sell();

    /**
     * \brief Make pencil button action
     *
     * \return void
     */
    void on_makePencil_clicked();

    /**
     * \brief Buy wood action
     *
     * \return void
     */
    void on_buyWood_clicked();

    /**
     * \brief Buy graphite action
     *
     * \return void
     */
    void on_buyGraphite_clicked();

    /**
     * \brief Compute rate
     *
     * \return void
     */
    void compute_rate();

    /**
     * \brief Decrease of price action
     *
     * \return void
     */
    void on_minusButton_clicked();

    /**
     * \brief Increase of price action
     *
     * \return void
     */
    void on_plusButton_clicked();

    /**
     * \brief Buy more button action
     *
     * \return void
     */
    void on_buyMoreButton_clicked();

    /**
     * \brief Implementing the automatic machine for making pencils
     * 
     * \return void
     */
    void apm_make();

    /**
     * \brief Getter method for the balance
     * 
     * \return The current balance
     */
    double getBalance();

    /**
     * \brief Getter method for the amount of pencils in inventory
     * 
     * \return The number of pencils in the current inventory
     */
    unsigned int getInventory();

    /**
     * \brief Getter method for the amount of pencils in inventory (to date)
     * 
     * \return The number of pencils in the inventory (to date)
     */
    unsigned int getInventoryToDate();

    /**
     * \brief Getter method for graphite in the inventory
     * 
     * \return Graphite in the inventory
     */
    double getGraphiteLeft();

    /**
     * \brief Getter method for wood in the inventory
     * 
     * \return Wood in the inventory
     */
    double getWoodLeft();

    /**
     * \brief Getter method for the price of the pencil
     * 
     * \return The price of the current pencil
     */
    double getPencilPrice();

    /**
     * \brief Getter method for the number of APMs
     * 
     * \return The number of APMs
     */
    unsigned int getCountAPM();

    /**
     * \brief Getter method for the price of an APM
     * 
     * \return The price of an APM
     */
    double getPriceAPM();

    /**
     * \brief Getter method for the price of graphite
     * 
     * \return The price of graphite
     */
    unsigned int getGraphPrice();

    /**
     * \brief Getter method for the price of wood
     * 
     * \return The price of wood
     */
    unsigned int getWoodPrice();
};

#endif // PENCILPRODUCER_H
