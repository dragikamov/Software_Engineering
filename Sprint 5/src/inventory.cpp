#include "inventory.h"

inventory::inventory()
{
	graphite = 1000;
	wood = 1000;
	pencils = 0;
	APM = 0;
}

inventory::~inventory()
{}

double inventory::getWood() const
{
        return wood;
}

double inventory::getGraphite() const
{
    return graphite;
}

int inventory::getPencils() const
{
    return pencils;
}

int inventory::getPencilsToDate() const
{
    return pencilsToDate;
}

int inventory::getAPM() const
{
    return APM;
}

void inventory::setPencils(int value)
{
    pencils = value;
}

void inventory::setPencilsToDate(int value)
{
    pencilsToDate = value;
}

void inventory::setAPM(int value)
{
    APM = value;
}

void inventory::setGraphite(double value)
{
    graphite = value;
}

void inventory::setWood(double value)
{
    wood = value;
}
