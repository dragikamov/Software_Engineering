#include "window.h"
#include "ui_window.h"
#include <QtMath>
#include <QTime>
#include <QTimer>
#include <QtGlobal>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <random>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void Window::setisOpen()
{
    isOpen = true;
}

bool Window::getisOpen()
{
    return isOpen;
}

void Window::u_display()
{
    ui->displayInvDate->setText(QString::number(gameInventory.getPencilsToDate()));
    ui->displayInv->setText(QString::number(gameInventory.getPencils()));
    ui->displayWood->setText(QString::number(gameInventory.getWood(), 'f', 2) + " m");
    ui->displayGraph->setText(QString::number(gameInventory.getGraphite(), 'f', 2) + " m");
    ui->displayAccount->setText("$" + QString::number(gameWallet.getMoney(), 'f', 2));
    ui->displayWoodPr->setText("$" + QString::number(gameWallet.getPriceOfWood()) + " / 100m");
    ui->displayGraphPr->setText("$" + QString::number(gameWallet.getPriceOfGraphite()) + " / 100m");
    ui->displayPublicDemand->setText(QString::number(gameWallet.getRate()));
    ui->displayPencilPrice->setText("$" + QString::number(gameWallet.getPriceOfPencil(), 'f', 2));
    ui->displayAutoPencil2000->setText(QString::number(gameInventory.getAPM()));
    ui->displayAutoPencil200Price->setText("Price of APM: $" + QString::number(gameWallet.getPriceOfAPM()));
    ui->upgradeAPM->setText("Upgrade APM\n$" +  QString::number(gameWallet.getPriceOfMarketing()));
    if(gameWallet.getIntelligence()<100 || gameWallet.getMarketingUnlocked() == true)
    {
        ui->unlockMarketing->setEnabled(false);
    }
    else
    {
        ui->unlockMarketing->setEnabled(true);
    }
}

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    setisOpen();
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec()));
    U_WoodAndGraphite();
    ui->displayPencilPrice->setText("$" + QString::number(gameWallet.getPriceOfPencil(), 'f', 2));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(computeRate()));
    timer->start(500);

    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(apm_make()));
    timer2->start(1000);

    QTimer *timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(sell()));
    timer3->start(500);

    QTimer *timer4 = new QTimer(this);
    connect(timer4, SIGNAL(timeout()), this, SLOT(U_WoodAndGraphite()));
    timer4->start(5000);

    QTimer *timer5 = new QTimer(this);
    connect(timer5, SIGNAL(timeout()), this, SLOT(u_display()));
    timer5->start(500);

    QTimer *intel = new QTimer(this);
    connect(intel, SIGNAL(timeout()), this, SLOT(gen_intelligence()));
    intel->start(1000);

    connect(ui->saveStateButton, SIGNAL(released()),this,SLOT(saveState()));
    connect(ui->closeStateButton, SIGNAL(released()),this,SLOT(closeState()));
    connect(ui->exitButton, SIGNAL(released()),this,SLOT(closeState()));
    connect(ui->playAgain, SIGNAL(released()),this,SLOT(playAgainButton_clicked()));

    ui->inc_money->setVisible(false);
    ui->inc_penc_inv->setVisible(false);
    ui->add_intelligence->setVisible(false);
    ui->inc_materials->setVisible(false);
    ui->intelligence->setVisible(false);
    ui->upgradeAPM->setVisible(false);
    ui->unlockMarketing->setVisible(false);
    ui->add_marketing->setVisible(false);

    /* Set the API and the ENV VARs */
    this->api = new API();
    this->token = qEnvironmentVariable(SE_TOKEN).toStdString();
    this->jacobsId = qEnvironmentVariable(JACOBS_ID).toStdString();
    this->gameUsername = qEnvironmentVariable(GAME_USERNAME).toStdString();
    if(this->token.empty() || this->jacobsId.empty() || this->gameUsername.empty())
    {
        fprintf(stderr, "Could not acquire token, jacobs-id or game-username: "
                        "API is disabled\n");
        #ifndef TESTING
        QMessageBox::critical(this, "API disabled", "Could not acquire SE-TOKEN, JACOBS-ID or GAME_USERNAME!");
        #endif // TESTING
        api->disable();
    }

    /* Truncate the game username if it's longer than GAME_USERNAME_MAX_LEGNTH */
    if(this->gameUsername.length() > GAME_USERNAME_MAX_LENGTH)
    {
        this->gameUsername = this->gameUsername.substr(0, GAME_USERNAME_MAX_LENGTH);
        #ifndef TESTING
        QMessageBox::information(this, "Shortening GAME_USERNAME", "The GAME_USERNAME is longer than the maximum allowence and because of that it is truncated.");
        #endif // TESTING
    }

    highScoreBoardLoad();
}

Window::~Window()
{
    delete api;
    delete ui;
}

int Window::randomNum(int low, int high)
{
    //obtain a random number from hardware
    std::random_device rd;
    //seed the generator
    std::mt19937 eng(rd());
    //price between 1000 and 2000
    std::uniform_int_distribution<> distr(low, high);
    return distr(eng);
}

void Window::U_WoodAndGraphite()
{
    gameWallet.setPriceOfWood(randomNum(1000, 2000));
    gameWallet.setPriceOfGraphite(randomNum(1500, 2500));
}

bool Window::buy(double num)
{
    if(gameWallet.getMoney() < num)
    {
        #ifndef TESTING
        QMessageBox::information(this, "Insufficient funds", "You don't have enough money at this moment to buy this!");
        #endif // TESTING
        return false;
    }
    else
    {
        gameWallet.removeMoney(num);
        return true;
    }
}

void Window::sell()
{
    int pencils = gameInventory.getPencils();
    if (pencils > 0)
    {
        gameWallet.addMoney(gameWallet.getPriceOfPencil());
        gameInventory.setPencils(pencils - 1);
    }
}

void Window::on_mkPen_clicked()
{
    double wood = gameInventory.getWood();
    double graph = gameInventory.getGraphite();
    int pencils = gameInventory.getPencils();
    int pencilsToDate = gameInventory.getPencilsToDate();
    if(graph > 0.20 && wood > 0.21)
    {
        gameInventory.setPencils(pencils + 1);
        gameInventory.setPencilsToDate(pencilsToDate + 1);
        gameInventory.setGraphite(graph - 0.20);
        gameInventory.setWood(wood - 0.21);
    }
    if(1.00 <= graph && graph < 1.40)
    {
        #ifndef TESTING
        QMessageBox::information(this, "Graphite inventory low", "You won't have anymore graphite to make pencils. Consider buying soon.");
        #endif // TESTING
    }
    if(1.00 <= wood && wood < 1.41)
    {
        #ifndef TESTING
        QMessageBox::information(this, "Wood inventory low", "You won't have anymore wood to make pencils. Consider buying soon.");
        #endif // TESTING
    }
    int x = gameInventory.getPencils();
    int y = gameInventory.getPencilsToDate();
    if(x >= 25000 || y >= 25000)
    {
        ui->stackedWidget->setCurrentIndex(2);
        highScoreBoardLoad();
    }
}

void Window::on_buyWood_clicked()
{
    if(buy(gameWallet.getPriceOfWood()) == true)
    {
        double wood = gameInventory.getWood();
        gameInventory.setWood(wood + 100.00);
    }
}

void Window::on_buyGraphite_clicked()
{
    if(buy(gameWallet.getPriceOfGraphite()) == true)
    {
        double graphite = gameInventory.getGraphite();
        gameInventory.setGraphite(graphite + 100);
    }
}

void Window::computeRate()
{
    gameWallet.setRate(static_cast<int>(qFabs((1 / gameWallet.getPriceOfPencil()))*(
        pow(1.1, gameWallet.getMarketing()))));
    ui->displayPublicDemand->setText(QString::number(gameWallet.getRate()));
    u_display();
}

void Window::on_minusBtn_clicked()
{
    double pencilPrice = gameWallet.getPriceOfPencil();
    if(pencilPrice > 0.05)
    {
        gameWallet.setPriceOfPencil(qFabs(pencilPrice - 0.05));
    }
    else
    {
        #ifndef TESTING
        QMessageBox::critical(this, "Pencil price too low", "The pencil price cannot go lower anymore!");
        #endif // TESTING
    }
}

void Window::on_plusBtn_clicked()
{
    double pencilPrice = gameWallet.getPriceOfPencil();
    gameWallet.setPriceOfPencil(pencilPrice + 0.05);
}

void Window::on_buyMoreBtn_clicked()
{
    int numAPM = gameInventory.getAPM();
    double priceAPM = gameWallet.getPriceOfAPM();
    if (numAPM < 10)
    {
        if(buy(gameWallet.getPriceOfAPM()) == true)
        {
            gameWallet.setPriceOfAPM(priceAPM * 1.1);
            gameInventory.setAPM(numAPM + 1);
        }
    }
    else
    {
        #ifndef TESTING
        QMessageBox::information(this, "Maximum number of APMs", "You have bought the maximum amount of APMs allowed in this game. You cannot buy more APMs.");
        #endif // TESTING
    }
}

void Window::apm_make()
{
    int s = static_cast<int>(gameInventory.getAPM() * 2); // total number produced in a second;
    for(int i = 0; i < s; i++)
    {
        on_mkPen_clicked();
    }
}

void Window::gen_intelligence()
{
    if(gameInventory.getPencilsToDate() < 3000)
    {
        return;
    }
    else
    {
        if(gameWallet.getIntelligence() < 200.00)
        {
            gameWallet.setIntelligence(gameWallet.getIntelligence() + 1.00);
        }
        ui->intelligence->setText("Intelligence: " + QString::number(gameWallet.getIntelligence()));
        ui->intelligence->setVisible(true);
        ui->unlockMarketing->setVisible(true);
    }
}

void Window::on_radioButton_clicked(bool checked)
{
    if(checked == true)
    {
        ui->inc_money->setVisible(true);
        ui->inc_penc_inv->setVisible(true);
        ui->add_intelligence->setVisible(true);
        ui->inc_materials->setVisible(true);
        ui->add_marketing->setVisible(true);
    }
    else
    {
        ui->inc_money->setVisible(false);
        ui->inc_penc_inv->setVisible(false);
        ui->add_intelligence->setVisible(false);
        ui->inc_materials->setVisible(false);
        ui->add_marketing->setVisible(false);
    }
}

void Window::on_inc_money_clicked()
{
    gameWallet.addMoney(1000);
}

void Window::on_inc_penc_inv_clicked()
{
    int x = gameInventory.getPencils();
    int y = gameInventory.getPencilsToDate();
    gameInventory.setPencils(x+1000);
    gameInventory.setPencilsToDate(y+1000);
    x = gameInventory.getPencils();
    y = gameInventory.getPencilsToDate();
    if(x >= 25000 || y >= 25000)
    {
        ui->stackedWidget->setCurrentIndex(2);
        highScoreBoardLoad();
    }
}

void Window::on_inc_materials_clicked()
{
    double graphite = gameInventory.getGraphite();
    double wood = gameInventory.getWood();
    gameInventory.setGraphite(graphite + 10);
    gameInventory.setWood(wood + 10);
}

void Window::on_unlockMarketing_clicked()
{
    gameWallet.setMarketingUnlocked(true);
    gameWallet.setIntelligence(gameWallet.getIntelligence() - 100);
    ui->upgradeAPM->setVisible(true);
}

void Window::on_upgradeAPM_clicked()
{
    if(buy(gameWallet.getPriceOfMarketing()) == true)
    {
        double price = gameWallet.getPriceOfMarketing();
        if(gameWallet.getMarketing() + 1.00 > 30.00)
        {
            #ifndef TESTING
            QMessageBox::information(this, "Marketing levels at maximum", "The current levels of marketing are at maximum, you cannot buy more marketing.");
            #endif // TESTING
        }
        else
        {
            gameWallet.setMarketing(gameWallet.getMarketing() + 1.00);
        }
        gameWallet.setPriceOfMarketing(price+(price/10));
    }
}

void Window::saveState()
{
    double money = gameWallet.getMoney();
    double priceOfPencil = gameWallet.getPriceOfPencil();
    double priceOfAPM = gameWallet.getPriceOfAPM();
    double priceOfWood = gameWallet.getPriceOfWood();
    double priceOfGraphite = gameWallet.getPriceOfGraphite();
    double intelligence = gameWallet.getIntelligence();
    double marketing = gameWallet.getMarketing();
    double priceOfMarketing = gameWallet.getPriceOfMarketing();
    bool marketingUnlocked = gameWallet.getMarketingUnlocked();

    double graphite = gameInventory.getGraphite();
    double wood = gameInventory.getWood();
    int pencils = gameInventory.getPencils();
    int pencilsToDate = gameInventory.getPencilsToDate();
    int APM = gameInventory.getAPM();

    QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save the pencil inventory"), "",
                                                        tr("Pencil File (*.pcl)"));

    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            #ifndef TESTING
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            #endif // TESTING
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_0);

        out << money << priceOfPencil;
        out << priceOfAPM << priceOfWood;
        out << priceOfGraphite << intelligence;
        out << marketing << priceOfMarketing;
        out << marketingUnlocked << graphite;
        out << wood << pencils;
        out << pencilsToDate << APM;

        Score score;
        score.username = this->gameUsername;
        score.id = this->jacobsId;
        score.token = this->token;
        score.score = pencilsToDate;

        if(!(api->uploadScore(&score)))
        {
            #ifndef TESTING
            QMessageBox::critical(this, "ERROR", "Cannot upload scores");
            #endif // TESTING
        }
    }
}

void Window::closeState()
{
    this->close();
    isOpen = false;
}

void Window::highScoreBoardLoad()
{
    /* Get the data */
    Json::Value jsonData = this->api->getTopScores();

    if(jsonData.empty())
    {
        #ifndef TESTING
        QMessageBox::critical(this, "Error", "Couldn't get the High Scores from the website.");
        #endif // TESTING
    }

    /* Put it in another data structure and sort it in descending order */
    string newText = "Num|User|Score\n----------\n";
    vector< pair<int, string> > scores;
    for(Json::Value score : jsonData["highscores"])
    {
        scores.push_back(make_pair(score["score"].asInt(),
                         score["game-username"].asString()));
    }

    sort(scores.rbegin(), scores.rend());
    for(uint i = 0; i < scores.size(); i++)
    {
        newText = newText + to_string(i+1) + "|" + scores[i].second + "|" +
                to_string(scores[i].first) + "\n";
    }

    /* Display on board */
    this->ui->highScoreBoard->setText(QString::fromStdString(newText));
    this->ui->highScoreBoard_1->setText(QString::fromStdString(newText));
}

void Window::playAgainButton_clicked()
{
    ui->radioButton->setChecked(false);

    gameWallet.setMoney(145.00);
    gameWallet.setMarketingUnlocked(false);
    gameWallet.setPriceOfMarketing(500.00);
    gameWallet.setMarketing(0.0);
    gameWallet.setIntelligence(0.0);
    gameWallet.setPriceOfPencil(1.00);
    gameWallet.setRate(1.00);
    gameWallet.setPriceOfAPM(150.00);
    gameWallet.setPriceOfWood(0.00);
    gameWallet.setPriceOfGraphite(0.00);

    gameInventory.setPencils(0);
    gameInventory.setPencilsToDate(0);
    gameInventory.setAPM(0);
    gameInventory.setGraphite(1000.00);
    gameInventory.setWood(1000.00);

    U_WoodAndGraphite();

    ui->inc_money->setVisible(false);
    ui->inc_penc_inv->setVisible(false);
    ui->add_intelligence->setVisible(false);
    ui->inc_materials->setVisible(false);
    ui->intelligence->setVisible(false);
    ui->upgradeAPM->setVisible(false);
    ui->unlockMarketing->setVisible(false);
    ui->add_marketing->setVisible(false);

    ui->stackedWidget->setCurrentIndex(1);
}

void Window::on_add_intelligence_clicked()
{
    if(gameWallet.getIntelligence() + 10.00 > 200.00)
    {
        #ifndef TESTING
        QMessageBox::information(this, "Intelligence levels at maximum", "The current levels of intelligence are at maximum, ou cannot add more intelligence.");
        #endif // TESTING
        gameWallet.setIntelligence(200.00);
    }
    else
    {
        gameWallet.setIntelligence(gameWallet.getIntelligence() + 10.00);
    }
    ui->intelligence->setText("Intelligence: " + QString::number(gameWallet.getIntelligence()));
    ui->intelligence->setVisible(true);
}

void Window::on_add_marketing_clicked()
{
    if(gameWallet.getMarketing() + 3.00 > 30.00)
    {
        #ifndef TESTING
        QMessageBox::information(this, "Marketing levels at maximum", "The current levels of marketing are at maximum, you cannot add more marketing.");
        #endif // TESTING
        gameWallet.setMarketing(30.00);
    }
    else
    {
        gameWallet.setMarketing(gameWallet.getMarketing() + 3.00);
    }
    gameWallet.setMarketingUnlocked(true);
}

void Window::on_startGame_clicked()
{
    ui->radioButton->setChecked(false);

    gameWallet.setMoney(145.00);
    gameWallet.setMarketingUnlocked(false);
    gameWallet.setPriceOfMarketing(500.00);
    gameWallet.setMarketing(0.0);
    gameWallet.setIntelligence(0.0);
    gameWallet.setPriceOfPencil(1.00);
    gameWallet.setRate(1.00);
    gameWallet.setPriceOfAPM(150.00);
    gameWallet.setPriceOfWood(0.00);
    gameWallet.setPriceOfGraphite(0.00);

    gameInventory.setPencils(0);
    gameInventory.setPencilsToDate(0);
    gameInventory.setAPM(0);
    gameInventory.setGraphite(1000.00);
    gameInventory.setWood(1000.00);

    U_WoodAndGraphite();

    ui->inc_money->setVisible(false);
    ui->inc_penc_inv->setVisible(false);
    ui->add_intelligence->setVisible(false);
    ui->inc_materials->setVisible(false);
    ui->intelligence->setVisible(false);
    ui->upgradeAPM->setVisible(false);
    ui->unlockMarketing->setVisible(false);
    ui->add_marketing->setVisible(false);

    ui->stackedWidget->setCurrentIndex(1);
}

void Window::on_loadButton_clicked()
{
    double money;
    double priceOfPencil;
    double priceOfAPM;
    double priceOfWood;
    double priceOfGraphite;
    double intelligence;
    double marketing;
    double priceOfMarketing;
    bool marketingUnlocked;

    double graphite;
    double wood;
    int pencils;
    int pencilsToDate;
    int APM;
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
            #ifndef TESTING
            QMessageBox::information(this, tr("Unable to open file"),
                                        file.errorString());
            #endif // TESTING
            return;
        }

        // Import all data
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_0);

        in >> money >> priceOfPencil;
        in >> priceOfAPM >> priceOfWood;
        in >> priceOfGraphite >> intelligence;
        in >> marketing >> priceOfMarketing;
        in >> marketingUnlocked >> graphite;
        in >> wood >> pencils;
        in >> pencilsToDate >> APM;

        gameWallet.setMoney(money);
        gameWallet.setPriceOfPencil(priceOfPencil);
        gameWallet.setPriceOfAPM(priceOfAPM);
        gameWallet.setPriceOfWood(priceOfWood);
        gameWallet.setPriceOfGraphite(priceOfGraphite);
        gameWallet.setIntelligence(intelligence);
        gameWallet.setMarketing(marketing);
        gameWallet.setPriceOfMarketing(priceOfMarketing);
        gameWallet.setMarketingUnlocked(marketingUnlocked);

        gameInventory.setGraphite(graphite);
        gameInventory.setWood(wood);
        gameInventory.setPencils(pencils);
        gameInventory.setPencilsToDate(pencilsToDate);
        gameInventory.setAPM(APM);

        u_display();

        // Go to the game screen
        ui->stackedWidget->setCurrentIndex(1);
    }
}
