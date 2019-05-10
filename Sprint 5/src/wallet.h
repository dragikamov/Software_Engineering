#ifndef WALLET_H
#define WALLET_H

class wallet{
private:
    double money;  ///< The amount of money we have
    double priceOfPencil;  ///< The current price of a pencil
    double priceOfAPM;  ///< The current price of an APM
    double priceOfWood;  ///< The current price of wood
    double priceOfGraphite;  ///< The current price of graphite
    unsigned int rate;  ///< The current rate
    double intelligence;  ///< The current amount of intelligence
    double marketing;  ///< The current amount of marketing
    double priceOfMarketing;  ///< The current price of buying a marketing
    bool marketingUnlocked;  ///< The state of the lock on marketing

public:

    /**
     * \brief A plain wallet class constructor
    */ 
    wallet();

    /**
     * \brief A plain wallet class destructor
    */ 
    ~wallet();

    /**
     * \brief A getter method for the status of the lock of marketing
     * \return The status of the lock of marketing
    */ 
    bool getMarketingUnlocked();

    /**
     * \brief A getter method for the current price of marketing
     * \return The current price of marketing
    */ 
    double getPriceOfMarketing();

    /**
     * \brief A getter method for the current amount of marketing
     * \return The current amount of marketing
    */ 
    double getMarketing();

    /**
     * \brief A getter method for the current amount of intelligence
     * \return The current amount of intelligence
    */ 
    double getIntelligence();

    /**
     * \brief A getter method for the current money we have
     * \return The current money we have
    */ 
    double getMoney();

    /**
     * \brief A getter method for the current price of a pencil
     * \return The current price of a pencil
    */ 
    double getPriceOfPencil();

    /**
     * \brief A getter method for the current price of an APM
     * \return The current price of an APM
    */
    double getPriceOfAPM();

    /**
     * \brief A getter method for the current rate
     * \return The current rate
    */ 
    double getRate();

    /**
     * \brief A getter method for the current price of wood
     * \return The current price of wood
    */ 
    double getPriceOfWood();

    /**
     * \brief A getter method for the current price of graphite
     * \return The current price of graphite
    */ 
    double getPriceOfGraphite();

    /**
     * \brief A setter method for money
     * \param value The money set
     * \return void
    */ 
    void setMoney(double value);

    /**
     * \brief A setter method for the status of the marketing lock
     * \param value The status of the marketing lock
     * \return void
    */ 
    void setMarketingUnlocked(bool value);

    /**
     * \brief A setter method for the price of a marketing
     * \param value The new price of marketing
     * \return void
    */ 
    void setPriceOfMarketing(double value);

    /**
     * \brief A setter method for marketing
     * \param value The new value of marketing
     * \return void
    */ 
    void setMarketing(double value);

    /**
     * \brief A setter method for intelligence
     * \param value The new value of intelligence
     * \return void
    */ 
    void setIntelligence(double value);

    /**
     * \brief A setter method for the price of a pencil
     * \param value The new price of a pencil
     * \return void
    */ 
    void setPriceOfPencil(double price);

    /**
     * \brief A setter method for rate
     * \param value The new rate value
     * \return void
    */ 
    void setRate(int value);

    /**
     * \brief A setter method for the price of an APM
     * \param value The new price of an APM
     * \return void
    */ 
    void setPriceOfAPM(double value);

    /**
     * \brief A setter method for the price of wood
     * \param value The new price of wood
     * \return void
    */ 
    void setPriceOfWood(double value);

    /**
     * \brief A setter method for the price of graphite
     * \param value The new price of graphite
     * \return void
    */ 
    void setPriceOfGraphite(double value);

    /**
     * \brief A method to add money to the current balance
     * \param amount The amount being added to our balance
     * \return void
    */ 
    void addMoney(double amount);

    /**
     * \brief A method to remove money from our balance
     * \param amount The amount being withdrawn from our balance
     * \return void
    */ 
    void removeMoney(double amount);
};


#endif // WALLET_H
