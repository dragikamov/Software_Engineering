/**
 * \file pencilproducer.cpp
 */

#include "pencilproducer.h"
#include "ui_pencilproducer.h"
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <QtMath>

void PencilProducer::update_display()
{
    ui->displayInvDate->setText(QString::number(inventory_to_date));
    ui->displayInv->setText(QString::number(inventory));
    ui->displayWood->setText(QString::number(wood_left, 'f', 2) + " m");
    ui->displayGraph->setText(QString::number(graph_left, 'f', 2) + " m");
    ui->displayBalance->setText("$" + QString::number(balance, 'f', 2));
}

PencilProducer::PencilProducer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PencilProducer)
{
    ui->setupUi(this);
    update_display();
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    update_wood_graph();

    ui->displayPencilPrice->setText("$" + QString::number(pencilPrice, 'f', 2));

    #ifndef TESTING

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_wood_graph()));
    timer->start(5000);

    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(compute_rate()));
    timer2->start(200);

    QTimer *timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(sell()));
    timer3->start(1000);

    QTimer *timer4 = new QTimer(this);
    connect(timer4, SIGNAL(timeout()), this, SLOT(apm_make()));
    timer4->start(1000);
    
    #endif // TESTING
}

PencilProducer::~PencilProducer()
{
    delete ui;
}

int PencilProducer::randInt(int low, int high)
{
    return qrand() % ((high+1) - low) + low;
}

void PencilProducer::update_wood_graph()
{
    woodPrice = randInt(1000, 2000);
    graphPrice = randInt(1500, 2500);
    ui->displayWoodPrice->setText("$" + QString::number(woodPrice) + " / 100m");
    ui->displayGraphPrice->setText("$" + QString::number(graphPrice) + " / 100m");
}

bool PencilProducer::buy(double amount)
{
    if(balance >= amount)
    {
        balance = balance - amount;
        ui->displayBalance->setText("$" + QString::number(balance, 'f', 2));
        return true;
    }else
    {
        return false;
    }
}

void PencilProducer::sell()
{
    if(inventory > 0 && publicDemand > 0)
    {
        inventory = inventory - 1;
        balance = balance +  pencilPrice;
        update_display();
    }
}

void PencilProducer::on_makePencil_clicked()
{
    inventory = inventory + 1;
    inventory_to_date = inventory_to_date + 1;

    if(graph_left >= 0.20 && wood_left >= 0.21)
    {
        graph_left = graph_left - 0.20;
        wood_left = wood_left - 0.21;
    }
    update_display();
}

void PencilProducer::on_buyWood_clicked()
{
    if(buy(woodPrice) == true)
    {
        wood_left = wood_left + 100.00;
        update_display();
    }
}


void PencilProducer::on_buyGraphite_clicked()
{
    if(buy(graphPrice) == true)
    {
        graph_left = graph_left + 100;
        update_display();
    }
}

void PencilProducer::compute_rate()
{
    demandRate = qFabs(1 / pencilPrice);
    publicDemand = (int) (demandRate * 5);
    ui->displayPublicDemand->setText(QString::number(publicDemand));
    update_display();
}

void PencilProducer::on_minusButton_clicked()
{
    if(pencilPrice > 0.05)
    {
        pencilPrice = qFabs(pencilPrice - 0.05);
        ui->displayPencilPrice->setText("$" + QString::number(pencilPrice, 'f', 2));
    }
}

void PencilProducer::on_plusButton_clicked()
{
    pencilPrice = pencilPrice + 0.05;
    ui->displayPencilPrice->setText("$" + QString::number(pencilPrice, 'f', 2));
}

void PencilProducer::on_buyMoreButton_clicked()
{
    if(countAPM2000 < 10)
    {
        if(buy(priceAPM2000) == true)
        {
            countAPM2000 = countAPM2000 + 1;
            priceAPM2000 = priceAPM2000 * 1.1;
            ui->displayAutoPencil2000->setText(QString::number(countAPM2000));
            ui->displayAutoPencil200Price->setText("$" + QString::number(priceAPM2000));
        }
    }
}

void PencilProducer::apm_make()
{
    unsigned int s = (unsigned int) (countAPM2000 * 2);

    for(unsigned int i = 0; i < s; i++)
    {
        if((s > 0) && graph_left >= 0.20 && wood_left >= 0.21)
        {
            inventory = inventory + 1;
            inventory_to_date = inventory_to_date + 1;
            graph_left = graph_left -  0.20;
            wood_left = wood_left - 0.21;
            update_display();
        }
    }
}

double PencilProducer::getBalance()
{
    return balance;
}

unsigned int PencilProducer::getInventory()
{
    return inventory;
}

unsigned int PencilProducer::getInventoryToDate()
{
    return inventory_to_date;
}

double PencilProducer::getGraphiteLeft()
{
    return graph_left;
}

double PencilProducer::getWoodLeft()
{
    return wood_left;
}

double PencilProducer::getPencilPrice()
{
    return pencilPrice;
}

unsigned int PencilProducer::getCountAPM()
{
    return countAPM2000;
}

double PencilProducer::getPriceAPM()
{
    return priceAPM2000;
}

unsigned int PencilProducer::getGraphPrice()
{
    return graphPrice;
}

unsigned int PencilProducer::getWoodPrice()
{
    return woodPrice;
}