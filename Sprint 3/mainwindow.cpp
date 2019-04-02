/**
 *  @file     mainwindow.cpp
 *  @brief    The logic of the calculator.
 *  @include  mainwindow.h
 */

#include "mainwindow.h"
#include <QTimer>
#include <QtCore>
#include <QRandomGenerator>
#include "ui_mainwindow.h"
#include "pencilmakermodel.h"
#include <algorithm>
#include <cmath>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

void MainWindow::render(PencilMakerModel *model)
{
    // update uis
    ui->total_pencils->setText(QString("Pencils Produced (to date): %1").arg(model->total_pencils));

    /**
     * displays public demand
    */
    ui->demand->setText("Public Demand: " + QString::number(1.00 / model->pencil_price, 'f', 2));

    /**
     * displays number of pencils in the inventory
    */
    ui->pencils_inv->setText(QString("Pencils in Inventory: %1").arg(model->pencils_in_inv));

    /**
     * displays price of a pencil
    */
    ui->pencil_price->setText("Pencil Price: " + QString::number(model->pencil_price, 'f', 2));

    /**
     * displays woods in the inventory
    */
    ui->woodleft->setText("Wood Left: " + QString::number(model->wood, 'f', 2));

    /**
     * displays graphite in the inventory
    */
    ui->graphiteleft->setText("Graphite Left: " + QString::number(model->graphite, 'f', 2));

    /**
     * displays bank balance
    */
    ui->totalbalance->setText("$" + QString::number(model->bank_balance, 'f', 2));

    if (model->intelligenceVisible)
    {
        /**
         * displays intelligence
        */
        ui->totalintelligence->setText(QString::number(model->intelligence));
    }

    /**
     * displays price of wood and graphite
    */
    ui->buywood->setText("Buy Wood\n$" + QString::number(model->price_wood, 'f', 2) + " / 100.00 m");
    ui->buygraphite->setText("Buy Graphite\n$" + QString::number(model->price_graphite, 'f', 2) + " / 100.00 m");

    /**
     * displays number of APMs
     * in the beginning
    */
    ui->autopencil->setText(QString("AutoPencil2000: %1").arg(model->apm));

    /**
     * displays production of APMs
    */
    ui->pencil_rate->setText(QString("Rate: %1 pencils / minute").arg(model->apm * 2 * 60));

    /**
     * displays production of APMs
     * in the beginning
    */
    ui->buy_APM->setText("Buy More\n$" + QString::number(model->apm_price, 'f', 2));

    /**
     * disables make pencil button if wood and graphite
     * is less than required quantity to make pencil
    */
    if (model->wood < 0.21 || model->graphite < 0.20)
    {
        ui->makepencil->setEnabled(0);
    }
    else
    {
        ui->makepencil->setEnabled(1);
    }

    /**
     * disables buy wood and buy graphite buttons if bank balance
     * is not enough to purchase wood or graphite
    */
    if (model->bank_balance < model->price_graphite)
    {
        ui->buygraphite->setEnabled(0);
    }
    else
    {
        ui->buygraphite->setEnabled(1);
    }

    if (model->bank_balance < model->price_wood)
    {
        ui->buywood->setEnabled(0);
    }
    else
    {
        ui->buywood->setEnabled(1);
    }

    /**
     * disables buy more buttons if bank balance
     * is not enough or apm inventory is 10
    */
    if (model->bank_balance < model->apm_price || model->apm == 10)
    {
        ui->buy_APM->setEnabled(0);
    }
    else
    {
        ui->buy_APM->setEnabled(1);
    }

    /**
     * disables the pencil price decrease button
     * if pencil price is less than or equal to zero
    */
    if (model->pencil_price - 0.05 <= 0)
    {
        ui->pencil_price_dec->setEnabled(0);
    }
    else
    {
        ui->pencil_price_dec->setEnabled(1);
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new PencilMakerModel; // a new model
    render(model);                // show the view

    ui->intelligence->setVisible(false);      // setting the text for Intelligence to invisible
    ui->totalintelligence->setVisible(false); // setting the Intelligence currency to invisible
    ui->debugBtn->setVisible(false);          // setting the debugging button to invisible

    /**
     * initializing wood_graphite_timer that updates the price of
     * graphite and wood and the pencil inventory every 5 secs
    */
    QTimer *wood_graphite_timer = new QTimer(this);
    wood_graphite_timer->start(5000);
    connect(wood_graphite_timer, SIGNAL(timeout()), this, SLOT(priceofwood()));     // randomization of wood price
    connect(wood_graphite_timer, SIGNAL(timeout()), this, SLOT(priceofgraphite())); // randomization of graphite price

    /**
     * initializing inv_timer that updates the pencils in the
     * inventory every 1 secs, and also using the same timer
     * for updating the second currency
    */
    QTimer *inv_timer = new QTimer(this);
    inv_timer->start(1000);
    connect(inv_timer, SIGNAL(timeout()), this, SLOT(pencilInventory()));       // to sell pencils
    connect(inv_timer, SIGNAL(timeout()), this, SLOT(incPencilInventory()));    // to produce using apm
    connect(inv_timer, SIGNAL(timeout()), this, SLOT(intelligenceInventory())); // to generate a single intelligence

    /**
     * calls method onPencilButtonClicked() after make
     * pencil has been clicked
    */
    connect(ui->makepencil, SIGNAL(clicked()), this, SLOT(onPencilButtonClicked()));

    /**
     * calls method pencilPriceInc() after + has been clicked
    */
    connect(ui->pencil_price_inc, SIGNAL(clicked()), this, SLOT(pencilPriceInc()));

    /**
     * calls method pencilPriceDec() after - has been clicked
    */
    connect(ui->pencil_price_dec, SIGNAL(clicked()), this, SLOT(pencilPriceDec()));

    /**
     * calls method onBuyWoodButtonClicked() after buy wood has been clicked
    */
    connect(ui->buywood, SIGNAL(clicked()), this, SLOT(onBuyWoodButtonClicked()));

    /**
     * calls method onBuyGraphiteButtonClicked() after buy graphite has been clicked
    */
    connect(ui->buygraphite, SIGNAL(clicked()), this, SLOT(onBuyGraphiteButtonClicked()));

    /**
     * calls method onBuyGraphiteButtonClicked() after buy graphite has been clicked
    */
    connect(ui->buy_APM, SIGNAL(clicked()), this, SLOT(buyAPM()));

    /**
     * calls method upgradableAPM() after upgrade APM has been clicked
    */
    connect(ui->upgradeAPM, SIGNAL(clicked()), this, SLOT(upgradableAPM()));

    /**
     * calls method marketing() after marketing has been clicked
    */
    connect(ui->marketing, SIGNAL(clicked()), this, SLOT(marketing()));

    /**
     * calls method debug() after debug button has been clicked
    */
    connect(ui->debugBtn, SIGNAL(clicked()), this, SLOT(debug()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::onPencilButtonClicked()
{
    // update resources
    model->total_pencils++;
    model->pencils_in_inv++;
    model->wood -= 0.21;
    model->graphite -= 0.20;
    render(model);
}

void MainWindow::pencilPriceInc()
{
    /**
     * pencil price increases by 0.5 after
     * pencil_price_inc has been clicked
    */
    model->pencil_price = model->pencil_price + 0.05;

    render(model);
}

void MainWindow::pencilPriceDec()
{

    if (model->pencil_price >= 0.05)
    {
        /**
         * pencil price decreases by 0.5 after
         * pencil_price_dec has been clicked
        */
        model->pencil_price = model->pencil_price - 0.05;

        render(model);
    }
}

void MainWindow::pencilInventory()
{
    /**
     * number of pencils sold depending on the
     * rate at which the pencils are being sold
    */
    double rate = 1.00 / model->pencil_price * pow(1.1, model->nMarketing);
    int pencils_sold = std::min(static_cast<int>(floor(5 * rate)), model->pencils_in_inv);

    /**
     * update number of pencils in inventory
     * depending on the number of pencils sold
    */
    model->pencils_in_inv = model->pencils_in_inv - pencils_sold;

    /**
     * amount that should be credited to the account
     * balance based on the current price and the number
     * of pencils sold
    */
    double credit = model->pencil_price * pencils_sold;

    /**
     * increase the bank balance by the credit amount
    */
    model->bank_balance = model->bank_balance + credit;

    /**
     * displays iventory of pencils and bank balance
     * after it has been updated
    */
    render(model);
}

void MainWindow::incPencilInventory()
{
    // calcuate the amount allowed to be produced
    int pencilProduced = std::min(static_cast<int>(floor(2 * model->apm * model->upgradeAPM)), static_cast<int>(floor(model->wood / 0.21)));
    pencilProduced = std::min(pencilProduced, static_cast<int>(floor(model->graphite / 0.20)));

    model->total_pencils += pencilProduced;
    model->pencils_in_inv += pencilProduced;
    model->wood -= (0.21 * pencilProduced);
    model->graphite -= (0.21 * pencilProduced);
    render(model);
}

void MainWindow::intelligenceInventory()
{
    if (model->total_pencils >= 3000 and model->intelligence < 200)
    {
        model->intelligence += 1;
        render(model);
    }
    if (model->intelligenceVisible == true and model->intelligence == 0)
    {
        model->intelligenceVisible = false;
        ui->intelligence->setVisible(model->intelligenceVisible);
        ui->totalintelligence->setVisible(model->intelligenceVisible);
    }
    else if (model->intelligenceVisible == false and model->intelligence > 0)
    {
        model->intelligenceVisible = true;
        ui->intelligence->setVisible(model->intelligenceVisible);
        ui->totalintelligence->setVisible(model->intelligenceVisible);
    }
}

void MainWindow::priceofwood()
{
    /**
     * generates random number between 1000 and 2000 and
     * updates the label of buy wood button
    */
    model->price_wood = QRandomGenerator::global()->bounded(1000.00) + 1000.00;
    render(model);
}

void MainWindow::onBuyWoodButtonClicked()
{
    if (model->bank_balance >= model->price_wood)
    {
        /**
         * updates bank balance after wood has been purchased
        */
        model->bank_balance -= model->price_wood;

        /**
         * updates amount of wood in the inventory after wood has been purchased
        */
        model->wood += 100.00;

        render(model);
    }
}

void MainWindow::priceofgraphite()
{
    /**
     * generates random number between 1500 and 2500 and
     * updates the label of buy wood button
    */
    model->price_graphite = QRandomGenerator::global()->bounded(1000.00) + 1500.00;

    render(model);
}

void MainWindow::onBuyGraphiteButtonClicked()
{
    if (model->bank_balance >= model->price_graphite)
    {
        /**
         * updates bank balance after graphite has been purchased
        */
        model->bank_balance -= model->price_graphite;

        /**
         * updates amount of graphite in the inventory after graphite has been purchased
        */
        model->graphite += 100.00;

        render(model);
    }
}

void MainWindow::buyAPM()
{
    if (model->bank_balance >= model->apm_price)
    {
        /**
         * updates the bank balance
        */
        model->bank_balance -= model->apm_price;

        /**
         * updates the number of APMs
        */
        model->apm++;

        /**
         * updates the price of next APM purchase
        */
        model->apm_price *= 1.1;
        render(model);
    }
}

void MainWindow::upgradableAPM()
{
    if (model->upgradeAPM == 1.00 and model->intelligence >= model->upgradeAPMPrice)
    {
        model->upgradeAPM = 1.10;
        model->intelligence -= model->upgradeAPMPrice;
        model->upgradeAPMPrice += 150;
        ui->upgradeAPM->setText("Upgrade APM\n" + QString::number(model->upgradeAPMPrice) + " Intelligence");
    }
    else if (model->upgradeAPM > 1.00 and model->upgradeAPM < 1.20 and model->intelligence >= model->upgradeAPMPrice and model->total_pencils >= 5000)
    {
        model->upgradeAPM = 1.20;
        model->intelligence -= model->upgradeAPMPrice;
        ui->upgradeAPM->setEnabled(false);
        ui->upgradeAPM->setText("APM Upgraded\nfully");
    }
}

void MainWindow::marketing()
{
    if (!model->marketingUnlocked)
    {
        if (model->intelligence >= 100)
        {
            model->marketingUnlocked = true;
            model->intelligence -= 100;
            ui->marketing->setText("Upgrade Marketing for $" + QString::number(model->marketingPrice, 'f', 2));
        }
    }
    else
    {
        if (model->bank_balance >= model->marketingPrice)
        {
            model->nMarketing += 1;
            model->bank_balance -= model->marketingPrice;
            model->marketingPrice *= 1.10;
            ui->marketing->setText("Upgrade Marketing for $" + QString::number(model->marketingPrice, 'f', 2));
        }
    }
}

int MainWindow::getPencilsInv()
{
    return model->pencils_in_inv;
}

int MainWindow::getTotalPencils()
{
    return model->total_pencils;
}

double MainWindow::getBalance()
{
    return model->bank_balance;
}

double MainWindow::getPencilPrice()
{
    return model->pencil_price;
}

double MainWindow::getWoodInv()
{
    return model->wood;
}

double MainWindow::getGraphiteInv()
{
    return model->graphite;
}

double MainWindow::getWoodPrice()
{
    return model->price_wood;
}

double MainWindow::getGraphitePrice()
{
    return model->price_graphite;
}

int MainWindow::getNAPM()
{
    return model->apm;
}

double MainWindow::getAPMPrice()
{
    return model->apm_price;
}

void MainWindow::on_saveBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save the pencil maker"), "",
                                                    tr("Pencil File (*.pcl);;All Files (*)"));

    // make sure it loads properly
    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        // safty check
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_0);
        out << model;
    }
}

void MainWindow::on_loadBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open a pencil maker"), "",
                                                    tr("Pencil File (*.pcl);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_0);
        in >> model;
        render(model); // rerender the correct view
    }
}

void MainWindow::on_debug_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->debugBtn->setVisible(true);
    }
    else if(arg1 == 0)
    {
        ui->debugBtn->setVisible(false);
    }
}

void MainWindow::debug()
{
    model->bank_balance += 1000.00;
    model->pencils_in_inv += 1000;
    model->total_pencils += 1000;
    model->wood += 10.00;
    model->graphite += 10.00;
    render(model);
}
