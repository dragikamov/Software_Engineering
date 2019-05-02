#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <ctime>
#include <QDebug>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    connect(nam, &QNetworkAccessManager::finished, this, &MainWindow::getMainURL);
    const QUrl url = QUrl("https://matiusulung.com/se.json");
    QNetworkRequest request(url);
    nam->get(request);

    QTimer *timer0 = new QTimer(this);
    QTimer *timer1 = new QTimer(this);
    QTimer *timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    timer4 = new QTimer(this);

    connect(timer1, SIGNAL(timeout()), this, SLOT(generateIntelligence()));
    connect(timer1, SIGNAL(timeout()), this, SLOT(PencilsProduced()));
    connect(timer0, SIGNAL(timeout()), this, SLOT(Display()));
    timer0->start(100);
    timer1->start(1000);

    connect(timer2, SIGNAL(timeout()), this, SLOT(WoodGraphiteRand()));
    timer2->start(5000);

    connect(ui->MakePencil, SIGNAL(clicked()), this, SLOT(onMakePencilclicked()));
    connect(ui->IncreasePrize, SIGNAL(clicked()), this, SLOT(onIncreasePrizeclicked()));
    connect(ui->DecreasePrize, SIGNAL(clicked()), this, SLOT(onDecreasePrizeclicked()));

    // APM implementation
    connect(timer3, SIGNAL(timeout()), this, SLOT(AutoPencil2000()));
    timer3->setInterval(static_cast<int>(makePencilTime));
    timer3->start();

    // Selling Pencils
    connect(timer4, SIGNAL(timeout()), this, SLOT(sellPencil()));
    timer4->setInterval(static_cast<int>(sellPencilTime));
    timer4->start();

    // Extended Function: Upgrade APM
    connect(ui->upgradeApm, SIGNAL(clicked()), this, SLOT(onUpgradeApmClicked()));
    // Extended Function: Marketing
    connect(ui->marketing, SIGNAL(clicked()), this, SLOT(onMarketingClicked()));    

    // Extended Function: Save&Load
    connect(ui->save, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    //connect(ui->load, SIGNAL(clicked()), this, SLOT(onLoadClicked()));

    // Extended Function: Debugging Tool
    connect(ui->inventory, SIGNAL(clicked()), this, SLOT(inventory_clicked()));
    connect(ui->manufactured, SIGNAL(clicked()), this, SLOT(manufactured_clicked()));
    connect(ui->grantMoney, SIGNAL(clicked()), this, SLOT(grantMoney_clicked()));
    connect(ui->woodGranite, SIGNAL(clicked()), this, SLOT(woodGraphite_clicked()));
    ui->grantMoney->setVisible(false);
    ui->woodGranite->setVisible(false);
    ui->inventory->setVisible(false);
    ui->manufactured->setVisible(false);
    connect(ui->checkBox, SIGNAL(clicked(bool)), this, SLOT(debugEnabled(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PencilsProduced()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh : mm : ss");
    ui->PencilsProduced->setText("Pencils produced (" + text + ") : " + QString::number(maxPencils));
}

void MainWindow::Display()
{
    ui->BankBalance->setText("$" + QString::number(bankbalance, 'f', 2));
    ui->WoodLeft->setText("Wood left: " + QString::number(wood_left, 'f', 2) + " m");
    ui->GraphiteLeft->setText("Graphite left: " + QString::number(graphite_left, 'f', 2) + " m");
    ui->Inventory->setText("Pencils in Inventory: " + QString::number(inventory));
    ui->PencilPrize->setText("Prize of Pencil: $" + QString::number(pencilprize, 'f', 2));
    ui->PublicDemand->setText("Public Demand: " + QString::number(publicDemand, 'f', 2));
    ui->PencilRate->setText("Rate : " + QString::number(autopencilrate * 60) + " pencils / minute");
    ui->AutoPencil->setText("AutoPencil2000: " + QString::number(autopencil));
    ui->buy_more_label->setText("$" + QString::number(autopencilprize, 'f', 2));

    ui->Intelligence->setText("Intelligence: " + QString::number(intelligence));
    if (maxPencils < 3000)
    {
        ui->Intelligence->setVisible(false);
    }
    else
    {
        ui->Intelligence->setVisible(true);

    }

    if (maxPencils < 3000)
    {
        ui->marketing->setVisible(false);
    }
    else
    {
        ui->marketing->setVisible(true);
    }
    
    if (marketUnlock == 1)
    {
        ui->marketing->setText("Upgrade Marketing");
    }
}

void MainWindow::onMakePencilclicked()
{
    if (wood_left >= 0.21 && graphite_left >= 0.20)
    {
            inventory += 1;
            wood_left -= 0.21;
            graphite_left -= 0.20;
            maxPencils += 1;
    }
}

void MainWindow::sellPencil()
{
    if (inventory >= 1)
    {
        bankbalance += pencilprize;
        inventory -= 1;
    }
}

void MainWindow::onDecreasePrizeclicked()
{
    if (pencilprize >= 0.05)
    {
        pencilprize -= 0.05;
        publicDemand = 1.00 / pencilprize * pow(1.1, marketRate);
        sellPencilTime = 0.20 / publicDemand * 1000.00;
        timer4->setInterval(static_cast<int>(sellPencilTime));
    }
}

void MainWindow::onIncreasePrizeclicked()
{
    pencilprize += 0.05;
    publicDemand = 1.00 / pencilprize * pow(1.1, marketRate);
    sellPencilTime = 0.20 / publicDemand * 1000.00;
    timer4->setInterval(static_cast<int>(sellPencilTime));
}

void MainWindow::WoodGraphiteRand()
{
    woodPrice = UpdateRandomNumber(1000.00, 2000.00);
    ui->buy_wood_label->setText("$" + QString::number(woodPrice) + "/100.00m");

    graphitePrice = UpdateRandomNumber(1500.00, 2500.00);
    ui->buy_graphite_label->setText("$" + QString::number(graphitePrice) + "/100.00m");
}

double MainWindow::UpdateRandomNumber(double low, double high)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    double random = low + static_cast <double> (rand())
                    / (static_cast <double> (RAND_MAX/(high-low)));

    return random;
}

void MainWindow::on_BuyWood_clicked()
{
    if (bankbalance >= woodPrice)
    {
        bankbalance -= woodPrice;
        wood_left += 100.00;
    }
}

void MainWindow::on_BuyGraphite_clicked()
{
    if (bankbalance >= graphitePrice)
    {
        bankbalance -= graphitePrice;
        graphite_left += 100.00;
    }
}

void MainWindow::AutoPencil2000()
{
    if (autopencil >= 1
            && autopencil < 11
            && wood_left >= autopencil * 0.21
            && graphite_left >= autopencil * 0.20)
    {
        inventory += autopencil * 1;
        wood_left -= autopencil * 0.21 * 1;
        graphite_left -= autopencil * 0.20 * 1;
        maxPencils += autopencil * 1;
        timer3->setInterval(static_cast<int>(makePencilTime));
    }
}

void MainWindow::on_BuyMore_clicked()
{
    if (autopencil < 10)
    {
        if (bankbalance >= autopencilprize)
        {
            bankbalance -= autopencilprize;
            autopencilprize += 0.1 * autopencilprize;
            autopencil += 1;
        }
    }
    else
    {
        ui->BuyMore->setEnabled(false);
    }
}

void MainWindow::generateIntelligence()
{
    if (maxPencils >= 3000 && intelligence < 200)
    {
        intelligence += 1;
    }
}

void MainWindow::onUpgradeApmClicked()
{
    if (apmLevel == 0 && intelligence >= 50)
    {
        autopencilrate *= 1.1;
        intelligence -= 50;
        apmLevel += 1;
        makePencilTime = 1.00 / autopencilrate * 1000.00;
    }
    else if (apmLevel == 1 && intelligence ==200 && maxPencils >= 5000)
    {
        autopencilrate *= 1.1;
        intelligence -= 200;
        apmLevel += 1;
        makePencilTime = 1.00 / autopencilrate * 1000.00;
    }
}

void MainWindow::onMarketingClicked()
{
    if (marketUnlock == 0 && intelligence >= 100)
    {
        marketUnlock = 1;
        intelligence -= 100;
        ui->marketing->setText("Upgrade Marketing");
    }
    else if (marketUnlock == 1 && bankbalance >= 500)
    {
        bankbalance -= 500;
        marketRate +=1;
        publicDemand = 1.00 / pencilprize * pow(1.1, marketRate);
        sellPencilTime = 0.20 / publicDemand * 1000.00;
    }
}

void MainWindow::onSaveClicked()
{
    // Asking where to save the file
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save the pencil maker"), "",
                                                    tr("Pencil File (*.pcl)"));

    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        time_t now = time(nullptr);
        char* ct = ctime(&now);

        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        // Writing all the variables in the file
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_0);

        out << wood_left << graphite_left;
        out << inventory << bankbalance;
        out << pencilprize << publicDemand;
        out << autopencil << autopencilprize;
        out << maxPencils << intelligence;
        out << apmLevel << marketUnlock;
        out << marketRate << autopencilrate;
        out << sellPencilTime << makePencilTime;
        out << woodPrice << graphitePrice;

        out << "Pencil Producer savefile: " << ct;
    }

    // Sending data to the server
    const QString upload_url = QString::fromStdString("http://" + mainURL + "/uploadscore");
    QUrl seUrl = QUrl(upload_url);
    QNetworkRequest req(seUrl);
    QJsonObject json;

    QString jacobs = qEnvironmentVariable("JACOBS_ID");
    QString se = qEnvironmentVariable("SE_USERNAME");
    QString game = qEnvironmentVariable("GAME_USERNAME");

    json.insert("jacobs-id",jacobs);
    json.insert("se-token", se);
    json.insert("game-username",game);
    json.insert("score",QJsonValue::fromVariant(maxPencils));

    QJsonDocument doc(json);
    QByteArray data= doc.toJson();
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.size()));
    QNetworkAccessManager *networkManager =  new QNetworkAccessManager(this);;
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(reqFinished(QNetworkReply*)));
    networkManager->post(req, data);
}

void MainWindow::reqFinished(QNetworkReply *rep)
{
    QString strReply = rep->readAll();
    qDebug() << rep->attribute(QNetworkRequest::HttpStatusCodeAttribute);
}

void MainWindow::woodGraphite_clicked()
{
    graphite_left += 10.00;
    wood_left += 10.00;
}
void MainWindow::inventory_clicked()
{
    inventory += 1000.00;
}

void MainWindow::manufactured_clicked()
{
    maxPencils += 1000.00;
}

void MainWindow::grantMoney_clicked()
{
    bankbalance += 1000.00;
}

void MainWindow::debugEnabled(bool clicked)
{
    if (clicked)
    {
        ui->grantMoney->setVisible(true);
        ui->woodGranite->setVisible(true);
        ui->inventory->setVisible(true);
        ui->manufactured->setVisible(true);
    }
    else
    {
        ui->grantMoney->setVisible(false);
        ui->woodGranite->setVisible(false);
        ui->inventory->setVisible(false);
        ui->manufactured->setVisible(false);
    }
}

unsigned int MainWindow::getInventory()
{
    return inventory;
}

unsigned int MainWindow::getMaxPencils()
{
    return maxPencils;
}

double MainWindow::getWoodLeft()
{
    return wood_left;
}

double MainWindow::getGraphiteLeft()
{
    return graphite_left;
}

double MainWindow::getBankBalance()
{
    return bankbalance;
}

double MainWindow::getPencilPrize()
{
    return pencilprize;
}

double MainWindow::getPublicDemand()
{
    return publicDemand;
}

unsigned int MainWindow::getAutoPencil()
{
    return autopencil;
}

double MainWindow::getAutoPencilPrize()
{
    return autopencilprize;
}

unsigned int MainWindow::getIntelligence()
{
    return intelligence;
}

unsigned int MainWindow::getAPMLevel()
{
    return apmLevel;
}

unsigned int MainWindow::getMarketUnlock()
{
    return marketUnlock;
}

unsigned int MainWindow::getMarketRate()
{
    return marketRate;
}

double MainWindow::getAutoPencilRate()
{
    return autopencilrate;
}

double MainWindow::getSellPencilTime()
{
    return sellPencilTime;
}

double MainWindow::getMakePencilTime()
{
    return makePencilTime;
}

double MainWindow::getWoodPrice()
{
    return woodPrice;
}

double MainWindow::getGraphitePrice()
{
    return graphitePrice;
}

void MainWindow::setInventory(unsigned int setInventory)
{
    inventory = setInventory;
}

void MainWindow::setMaxPencils(unsigned int setMaxPencils)
{
    maxPencils = setMaxPencils;
}

void MainWindow::setWoodLeft(double setWoodLeft)
{
    wood_left = setWoodLeft;
}

void MainWindow::setGraphiteLeft(double setGraphiteLeft)
{
    graphite_left = setGraphiteLeft;
}

void MainWindow::setBankBalance(double setBankBalance)
{
    bankbalance = setBankBalance;
}

void MainWindow::setPencilPrize(double setPencilPrize)
{
    pencilprize = setPencilPrize;
}

void MainWindow::setPublicDemand(double setPublicDemand)
{
    publicDemand = setPublicDemand;
}

void MainWindow::setAutoPencil(unsigned int setAutoPencil)
{
    autopencil = setAutoPencil;
}

void MainWindow::setAutoPencilPrize(double setAutoPencilPrize)
{
    autopencilprize = setAutoPencilPrize;
}

void MainWindow::setIntelligence(unsigned int setIntelligence)
{
    intelligence = setIntelligence;
}

void MainWindow::setAPMLevel(unsigned int setAPMLevel)
{
    apmLevel = setAPMLevel;
}

void MainWindow::setMarketUnlock(unsigned int setMarketUnlock)
{
    marketUnlock = setMarketUnlock;
}

void MainWindow::setMarketRate(unsigned int setMarketRate)
{
    marketRate = setMarketRate;
}

void MainWindow::setAutoPencilRate(double setAutoPencilRate)
{
    autopencilrate = setAutoPencilRate;
}

void MainWindow::setSellPencilTime(double setSellPencilTime)
{
    sellPencilTime = setSellPencilTime;
}

void MainWindow::setMakePencilTime(double setMakePencilTime)
{
    makePencilTime = setMakePencilTime;
}

void MainWindow::setWoodPrice(double setWoodPrice)
{
    woodPrice = setWoodPrice;
}

void MainWindow::setGraphitePrice(double setGraphitePrice)
{
    graphitePrice = setGraphitePrice;
}

void MainWindow::on_exit_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);

     // Loading the scoreboard again when exiting from game mode
     QNetworkAccessManager *nam = new QNetworkAccessManager(this);
     connect(nam, &QNetworkAccessManager::finished, this, &MainWindow::getScores);
     const QString score_url = QString::fromStdString("http://" + mainURL + "/getscores");
     const QUrl url = QUrl(score_url);
     QNetworkRequest request(url);
     nam->get(request);
}

void MainWindow::on_start_Button_clicked()
{
    // Setting all the variables and going to the game screen
    inventory = 0;

    maxPencils = 0;

    wood_left = 1000.00;

    graphite_left = 1000.00;

    bankbalance = 145.00;

    pencilprize = 1.00;

    publicDemand = 1.00;

    autopencil = 0;

    autopencilprize = 150.00;

    intelligence = 0;

    apmLevel = 0;

    marketUnlock = 0;

    marketRate = 0;

    autopencilrate = 2.00;

    sellPencilTime = 0.20 / publicDemand * 1000.00;

    makePencilTime = 1.00 / autopencilrate * 1000.00;

    woodPrice = 1000.00;

    graphitePrice = 1500.00;

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_load_Button_clicked()
{
    // Ask for which file to load from
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open a pencil maker"), "",
                                                    tr("Pencil File (*.pcl);;All Files (*)"));
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                        file.errorString());
            return;
        }

        // Import all data
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_0);

        in >> wood_left >> graphite_left;
        in >> inventory >> bankbalance;
        in >> pencilprize >> publicDemand;
        in >> autopencil >> autopencilprize;
        in >> maxPencils >> intelligence;
        in >> apmLevel >> marketUnlock;
        in >> marketRate >> autopencilrate;
        in >> sellPencilTime >> makePencilTime;
        in >> woodPrice >> graphitePrice;

        // Go to the game screen
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::getMainURL(QNetworkReply *reply)
{
    QString str;
    str = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    mainURL = (jsonObject["link"].toString()).toStdString();

    // After getting the mainURL we are sending a request to the /getscores
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    connect(nam, &QNetworkAccessManager::finished, this, &MainWindow::getScores);
    const QString score_url = QString::fromStdString("http://" + mainURL + "/getscores");
    const QUrl url = QUrl(score_url);
    QNetworkRequest request(url);
    nam->get(request);
}

void MainWindow::getScores(QNetworkReply *reply)
{
    QString str;
    str = reply->readAll();

    QList<QString> userNames;
    QList<int> userScores;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["highscores"].toArray();

    int n = 0;

    foreach (const QJsonValue &value, jsonArray) {
        QJsonObject obj = value.toObject();
        userNames.append(obj["game-username"].toString());
        userScores.append(obj["score"].toInt());
        n++;
    }

    // Bubble sort on the scoreboard
    bool swapped = true;
    int x = -1;

    while(swapped)
    {
        swapped = false;
        x += 1;
        for(int i = 1; i < (n - x);i++)
        {
            if(userScores.at(i-1) < userScores.at(i))
            {
                userScores.swap(i-1, i);
                userNames.swap(i-1, i);

                swapped = true;
            }
        }
    }

    // Preparing the string that is used to be shown on the welcome screen
    std::string scores = "";

    for(int i = 0;i < n;i++)
    {
        scores.append((userNames.at(i)).toStdString());
        scores.append(" : ");
        scores.append(std::to_string(userScores.at(i)));
        scores.append("\n\n");
    }
    ui->scoreboard->setText(QString::fromStdString(scores));
}
