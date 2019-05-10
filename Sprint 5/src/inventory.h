#ifndef INVENTORY_H
#define INVENTORY_H

class inventory{
private:
    double graphite;  ///< The amount of graphite we have in inventory
    double wood;  ///< The amount of wood we have in inventory
    int pencils;  ///< The amount of pencils we have in the current inventory
    int pencilsToDate = 0;  ///< Amount of pencils up to date
    int APM;  ///< The number of APMs that we own

public:

    /**
     * \brief A plain inventory class constructor
    */ 
    inventory();

    /**
     * \brief A plain inventory class destructor
    */ 
    ~inventory();

    /**
     * \brief A getter method for the amount of wood in our inventory
     * \return The amount of wood in our inventory
    */ 
    double getWood() const;

    /**
     * \brief A getter method for the amount of graphite in our inventory
     * \return The amount of graphite in our inventory
    */ 
    double getGraphite() const;

    /**
     * \brief A getter method for the amount of pencils in our inventory
     * \return The amount of pencils in our inventory
    */ 
    int getPencils() const;

    /**
     * \brief A getter method for the amount of pencils to date
     * \return The amount of pencils to date
    */ 
    int getPencilsToDate() const;

    /**
     * \brief A getter method for the number of APMs in our inventory
     * \return The number of APMs in our inventory
    */ 
    int getAPM() const;

    /**
     * \brief A setter method for the amount of pencils in our inventory
     * \param value The amount of pencils being set
     * \return void
    */ 
    void setPencils(int value);

    /**
     * \brief A setter method for the amount of pencils to date
     * \param value The amount of pencils being set
     * \return void
    */ 
    void setPencilsToDate(int value);

    /**
     * \brief A setter method for the number of APMs in our inventory
     * \param value The number of APMs being set
     * \return void
    */ 
    void setAPM(int value);

    /**
     * \brief A setter method for the amount of graphite in our inventory
     * \param value The amount of graphite being set
     * \return void
    */ 
    void setGraphite(double value);

    /**
     * \brief A setter method for the amount of wood in our inventory
     * \param value The amount of wood being set
     * \return void
    */ 
    void setWood(double value);
};

#endif // INVENTORY_H
