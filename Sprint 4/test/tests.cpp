#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>

#define private public
#include <QApplication>
#include "../src/mainwindow.h"

int argc = 0;
char** argv = 0;

TEST(testExtendedFunctions, initialization)
{
	QApplication app(argc, argv);
    MainWindow pencilapp;
    
    EXPECT_EQ(0, pencilapp.getIntelligence());
    EXPECT_EQ(0, pencilapp.getAPMLevel());
    EXPECT_EQ(0, pencilapp.getMarketUnlock());
    EXPECT_EQ(2.00, pencilapp.getAutoPencilRate());
    EXPECT_EQ(200, pencilapp.getSellPencilTime());
    EXPECT_EQ(500, pencilapp.getMakePencilTime());
}

TEST(testExtendedFunctions, upgradeAPM)
{
    QApplication app(argc, argv);
    MainWindow pencilapp;

    pencilapp.setIntelligence(200);
    pencilapp.onUpgradeApmClicked();

    EXPECT_EQ(2.2, pencilapp.getAutoPencilRate());
    EXPECT_EQ(150, pencilapp.getIntelligence());
    EXPECT_EQ(1, pencilapp.getAPMLevel());
}

TEST(testExtendedFunctions, Marketing)
{
    QApplication app(argc, argv);
    MainWindow pencilapp;

    pencilapp.setIntelligence(200);
    pencilapp.setBankBalance(1000.00);
    
    pencilapp.onMarketingClicked();
    EXPECT_EQ(1, pencilapp.getMarketUnlock());
    EXPECT_EQ(100, pencilapp.getIntelligence());
    EXPECT_EQ(0, pencilapp.getMarketRate());

    pencilapp.onMarketingClicked();
    EXPECT_EQ(500.00, pencilapp.getBankBalance());
    EXPECT_EQ(1, pencilapp.getMarketRate());
}

TEST(testExtendedFunctions, DebuggingTool)
{
    QApplication app(argc, argv);
    MainWindow pencilapp;

    
    pencilapp.woodGraphite_clicked();
    EXPECT_EQ(1010, pencilapp.getGraphiteLeft());
    EXPECT_EQ(1010, pencilapp.getWoodLeft());

    pencilapp.inventory_clicked();
    EXPECT_EQ(1000, pencilapp.getInventory());

    pencilapp.manufactured_clicked();
    EXPECT_EQ(1000, pencilapp.getMaxPencils());

    pencilapp.grantMoney_clicked();
    EXPECT_EQ(1145, pencilapp.getBankBalance());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#undef private
