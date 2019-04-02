#include <QApplication>
#include <QtTest>

#include "../mainwindow.h"
#include "../pencilmakermodel.h"
#include <QFile>
#include <QDataStream>

/**
 * @brief The Test class
 */
class Test : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief The Test constructor
     */
    Test();

    /**
     * @brief The Test destructor
     */
    ~Test();

private slots:
    /**
     * @fn changingPencilPrice
     * @brief Check for the pencil price
     */
    void changingPencilPrice();

    /**
     * @fn testSellPencils
     * @brief Check for the sell function
     */
    void testSellPencils();

    /**
     * @fn testBalance
     * @brief Check for testing the balance
     */
    void testBalance();

    /**
     * @fn testAPM
     * @brief Function to test the APM
     */
    void testAPM();

    /**
     * @fn testMaterials
     * @brief Function to test the Materials
     */
    void testMaterials();

    /**
     * @fn testPencilMakerModel
     * @brief Function to test the save and load
    */ 
    void testPencilMakerModel();
};

Test::Test() {}
Test::~Test() {}

void Test::changingPencilPrice()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    MainWindow p;

    for (int i = 0; i < 100; i++)
    {
        p.pencilPriceInc();
    }
    for (int i = 0; i < 320; i++)
    {
        p.pencilPriceDec();
    }

    // Price should not be negative after attempting to decrement below zero
    QVERIFY(p.getPencilPrice() >= 0.0);
}

void Test::testSellPencils()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    MainWindow p;

    // Produce 5 pencils
    for (int i = 0; i < 5; i++)
    {
        p.onPencilButtonClicked();
    }
    unsigned int pencilsProduced = p.getTotalPencils();
    QCOMPARE(pencilsProduced, p.getTotalPencils());

    p.pencilInventory();
    QCOMPARE(p.getPencilsInv(), 0);
}

void Test::testBalance()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    MainWindow p;

    // Check default value of bank balance
    QCOMPARE(p.getBalance(), 145.00);

    for (int i = 0; i < 5; i++)
    {
        p.onPencilButtonClicked();
    }
    p.pencilInventory();

    // Check after selling 5 pencils of default value of 1.00
    QCOMPARE(p.getBalance(), 150.00);
}

void Test::testAPM()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    MainWindow p;

    // Try to buy apm with no money
    p.buyAPM();
    QCOMPARE(p.getNAPM(), 0);

    for (int i = 0; i < 10; i++)
    {
        p.onPencilButtonClicked();
    }
    p.pencilInventory();
    p.pencilInventory();
    double price = p.getAPMPrice();

    // After selling 10 pencils our balance should be 155 and
    // the default price of the APM is 150 so we could buy it
    p.buyAPM();
    QCOMPARE(p.getNAPM(), 1);

    // After one has been sold the price should have risen 10%
    QCOMPARE(p.getAPMPrice(), price * 1.1);
}

void Test::testMaterials()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    MainWindow p;

    for (int i = 0; i < 1000; i++)
    {
        p.priceofwood();
        p.priceofgraphite();

        // Check if the prices go out of their range
        QVERIFY(p.getGraphitePrice() >= 1500.00);
        QVERIFY(p.getGraphitePrice() <= 2500.00);

        QVERIFY(p.getWoodPrice() >= 1000.00);
        QVERIFY(p.getWoodPrice() <= 2000.00);
    }

    // Check if we can buy materials with default balance
    p.onBuyGraphiteButtonClicked();
    p.onBuyWoodButtonClicked();

    // The values should have remained on 1000
    QCOMPARE(p.getGraphiteInv(), 1000);
    QCOMPARE(p.getWoodInv(), 1000);
}

void Test::testPencilMakerModel()
{
    PencilMakerModel *model1 = new PencilMakerModel();
    PencilMakerModel *model2 = new PencilMakerModel();
    QFile file1("test.dat");
    QVERIFY(file1.open(QIODevice::WriteOnly));
    QDataStream s1(&file1);
    s1.setVersion(QDataStream::Qt_5_0);
    model1->apm = 10;
    model2->graphite = 2.1;
    s1 << model1;
    file1.close();

    QFile file2("test.dat");
    QVERIFY(file2.open(QIODevice::ReadOnly));
    QDataStream s2(&file2);
    s2.setVersion(QDataStream::Qt_5_0);
    s2 >> model2;
    file2.close();
    QCOMPARE(model1->apm, model2->apm);
    QCOMPARE(model1->graphite, model2->graphite);
}

QTEST_APPLESS_MAIN(Test)
#include "test.moc"
