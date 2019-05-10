#define TESTING

#include <gtest/gtest.h>
#include <jsoncpp/json/json.h>
#include "../src/wallet.h"
#include "../src/inventory.h"
#include "../src/window.h"
#include "../src/window.cpp"
#include "../src/api.h"
#include <QApplication>

TEST(curlTest, WrongURL)
{
    API *api;
    api = new API();
    api->setNewURLStorage("https://wrongurl.com");

    api->enable();
    EXPECT_EQ(api->acquireServerUrl(), false);
    delete api;
}

TEST(curlTest2, JSONparsing)
{
    API *api;
    api = new API();
    api->setNewURLStorage("ec2-54-93-180-138.eu-central-1.compute.amazonaws.com");

    api->enable();
    EXPECT_EQ(api->acquireServerUrl(), false);
    delete api;
}

TEST(curlTest3, serverURLEmpty)
{
    API *api;
    api = new API();
    api->setNewURLStorage("http://ec2-54-93-180-138.eu-central-1.compute.amazonaws.com/getscores");

    api->enable();
    EXPECT_EQ(api->acquireServerUrl(), false);
    delete api;
}

TEST(curlTest4, APIDisable)
{
    API *api;
    api = new API();
    api->disable();
    api->acquireServerUrl();

    Json::Value jsonData = api->getTopScores();

    EXPECT_EQ(jsonData.asString(), "");
    delete api;
}

TEST(curlTest5, uploadScore)
{
    API *api;
    api = new API();
    api->enable();

    std::string token = qEnvironmentVariable(SE_TOKEN).toStdString();
    std::string jacobsId = qEnvironmentVariable(JACOBS_ID).toStdString();
    std::string gameUsername = qEnvironmentVariable(GAME_USERNAME).toStdString();

    Score score;
    score.username = gameUsername;
    score.id = jacobsId;
    score.token = token;
    score.score = 25000;

    EXPECT_EQ(api->uploadScore(&score), true);
    delete api;
}

TEST(randomNumTest, RandomNumIsConstrained)
{
    Window window;

    EXPECT_EQ(window.getisOpen(), true);

    window.on_startGame_clicked();
    window.playAgainButton_clicked();
    window.on_add_marketing_clicked();

    EXPECT_EQ(window.gameWallet.getMarketing(), 3);

    for(int i = 0;i < 21;i++)
    {
        window.on_add_marketing_clicked();
    }

    EXPECT_EQ(window.gameWallet.getMarketing(), 30);
    EXPECT_LT(window.randomNum(1, 10), 11);
    EXPECT_GT(window.randomNum(1, 10), 0);
}

TEST(buyTest, buyDebitsAccount)
{
    Window window;
    window.gameWallet.setMoney(10);

    EXPECT_EQ(window.buy(5), 1);
    EXPECT_EQ(window.gameWallet.getMoney(), 5);

    window.gameWallet.setMoney(4);
    EXPECT_EQ(window.buy(5), 0);
}

TEST(sellTest, sellCreditsAccount)
{
    Window window;
    window.gameWallet.setMoney(10);
    window.gameWallet.setPriceOfPencil(0.5);
    window.gameInventory.setPencils(5);

    window.sell();
    EXPECT_EQ(window.gameWallet.getMoney(), 10.5);
    EXPECT_EQ(window.gameInventory.getPencils(), 4);
}

TEST(computeRateTest, DemandRateFormula)
{
    Window window;
    window.gameWallet.setPriceOfPencil(1);
    window.highScoreBoardLoad();

    window.gameWallet.setMoney(5000);
    window.on_inc_money_clicked();
    window.on_upgradeAPM_clicked();

    window.computeRate();
    EXPECT_EQ(window.gameWallet.getRate(), 1);
}

TEST(on_minusBtn_clickedTest, priceDecrement)
{
    Window window;
    window.gameWallet.setPriceOfPencil(1.05);

    window.gameInventory.setPencilsToDate(4000);
    window.gen_intelligence();

    window.on_minusBtn_clicked();
    EXPECT_EQ(window.gameWallet.getPriceOfPencil(), 1.00);
}

TEST(on_plusBtn_clickedTest, priceIncrement)
{
    Window window;
    window.gameWallet.setPriceOfPencil(0.95);

    window.on_plusBtn_clicked();
    EXPECT_EQ(window.gameWallet.getPriceOfPencil(), 1.00);
}

TEST(on_buyMoreBtn_clickedTest, apmIncrement)
{
    Window window;
    window.gameInventory.setAPM(9);
    window.gameWallet.setMoney(200);
    window.on_inc_materials_clicked();

    window.on_buyMoreBtn_clicked();
    EXPECT_EQ(window.gameInventory.getAPM(), 10);
    EXPECT_EQ(window.gameWallet.getMoney(), 50);
    EXPECT_EQ(window.gameWallet.getPriceOfAPM(), 165);
}

TEST(on_mkPen_clickedTest, pencilIncrement)
{
    Window window;
    window.gameInventory.setPencils(1);
    window.gameInventory.setPencilsToDate(1);
    window.gameInventory.setGraphite(1.20);
    window.gameInventory.setWood(1.21);

    window.on_mkPen_clicked();

    window.gen_intelligence();
    EXPECT_EQ(window.gameInventory.getPencils(), 2);
    EXPECT_EQ(window.gameInventory.getPencilsToDate(), 2);
    EXPECT_EQ(window.gameInventory.getGraphite(), 1);
    EXPECT_EQ(window.gameInventory.getWood(), 1);

    window.gameInventory.setPencils(1);
    window.gameInventory.setPencilsToDate(1);
    window.gameInventory.setGraphite(0);
    window.gameInventory.setWood(0);
    EXPECT_EQ(window.gameInventory.getPencils(), 1);
    EXPECT_EQ(window.gameInventory.getPencilsToDate(), 1);
    EXPECT_EQ(window.gameInventory.getGraphite(), 0);
    EXPECT_EQ(window.gameInventory.getWood(), 0);
}

TEST(on_buyWood_clickedTest, WoodIncrement)
{
    Window window;
    window.gameWallet.setMoney(2000);
    window.gameWallet.setPriceOfWood(1000);
    window.gameInventory.setWood(0);
    window.on_radioButton_clicked(true);
    window.on_radioButton_clicked(false);

    window.on_buyWood_clicked();
    EXPECT_EQ(window.gameWallet.getMoney(), 1000);
    EXPECT_EQ(window.gameInventory.getWood(), 100);
}

TEST(on_buyGraphite_clickedTest, GraphiteIncrement)
{
    Window window;
    window.gameWallet.setMoney(2000);
    window.gameWallet.setPriceOfGraphite(1000);
    window.gameInventory.setGraphite(0);

    window.on_buyGraphite_clicked();
    EXPECT_EQ(window.gameWallet.getMoney(), 1000);
    EXPECT_EQ(window.gameInventory.getGraphite(), 100);

    window.closeState();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
