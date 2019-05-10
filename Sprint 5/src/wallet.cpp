#include "wallet.h"
#include <QMessageBox>

wallet::wallet()
{
    money = 145;
    priceOfPencil = 1;
    priceOfAPM = 150;
    priceOfWood = 0;
    priceOfGraphite = 0;
    rate = 1.0;
    intelligence = 0;
    marketing = 0;
    priceOfMarketing = 500;
    marketingUnlocked = false;
}

wallet::~wallet()
{}

bool wallet::getMarketingUnlocked()
{
    return marketingUnlocked;
}

double wallet::getPriceOfMarketing()
{
    return priceOfMarketing;
}

double wallet::getMarketing()
{
    return marketing;
}

double wallet::getIntelligence()
{
    return intelligence;
}

double wallet::getMoney()
{
    return money;
}

double wallet::getPriceOfPencil()
{
    return priceOfPencil;
}

double wallet::getPriceOfAPM()
{
    return priceOfAPM;
}

double wallet::getRate()
{
    return rate;
}

double wallet::getPriceOfWood()
{
    return priceOfWood;
}

double wallet::getPriceOfGraphite()
{
    return priceOfGraphite;
}

void wallet::setMoney(double value)
{
	money = value;
}

void wallet::setMarketingUnlocked(bool value)
{
    marketingUnlocked = value;
}

void wallet::setPriceOfMarketing(double value)
{
    priceOfMarketing = value;
}

void wallet::setMarketing(double value)
{
    marketing = value;
}

void wallet::setIntelligence(double value)
{
    intelligence = value;
}

void wallet::setPriceOfPencil(double price)
{
    priceOfPencil = price;
}

void wallet::setRate(int value)
{
    rate = static_cast<unsigned int>(value);
}

void wallet::setPriceOfAPM(double value)
{
    priceOfAPM = value;
}

void wallet::setPriceOfWood(double value)
{
    priceOfWood = value;
}

void wallet::setPriceOfGraphite(double value)
{
    priceOfGraphite = value;
}

void wallet::addMoney(double amount)
{
    money = money + amount;
}

void wallet::removeMoney(double amount)
{
    money = money - amount;
}
