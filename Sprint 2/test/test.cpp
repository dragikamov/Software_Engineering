#include <QtTest>
#include <QApplication>

#define TESTING

#include "../src/pencilproducer.h"


/**
 * \brief The Test class
 */
class Test : public QObject
{
    Q_OBJECT

public:
    /**
     * \brief The Test constructor
     */
    Test();

    /**
     * \brief The Test destructor
     */
    ~Test();

private slots:
    /**
     * \brief Check for the pencil price
     */
    void changingPencilPrice();

    /**
     * \brief Check for the sell function
     */
    void testSellPencils();

    /**
     * \brief Check for testing the balance
     */
    void testBalance();

    /**
     * \brief Function to test the APM
     */
    void testAPM();

    /**
     * \brief Function to test the Materials
     */
    void testMaterials();
};

Test::Test(){}
Test::~Test(){}

void Test::changingPencilPrice()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    PencilProducer p;

    for(int i = 0; i < 100; i++) 
    {
        p.on_plusButton_clicked();
    }
    for(int i = 0; i < 320; i++) 
    {
        p.on_minusButton_clicked();
    }

    // Price should not be negative after attempting to decrement below zero
    QVERIFY(p.getPencilPrice() >= 0.0);
}

void Test::testSellPencils()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    PencilProducer p;

    // Produce 6 pencils
    for(int i = 0; i < 6; i++)
    {
        p.on_makePencil_clicked();
    }
    unsigned int pencilsProduced = p.getInventoryToDate();
    QCOMPARE(pencilsProduced, p.getInventoryToDate());

    for(int i = 0; i < 3; i++)
    {
        p.sell();
    }
    QCOMPARE(p.getInventory(), 3);
}

void Test::testBalance()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    PencilProducer p;

    // Check default value of bank balance
    QCOMPARE(p.getBalance(), 145.00);

    for(int i = 0; i < 6; i++)
    {
        p.on_makePencil_clicked();
        p.sell();
    }
    // Check after selling 6 pencils of default value of 1.00
    QCOMPARE(p.getBalance(), 151.00);
}

void Test::testAPM()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);

    PencilProducer p;

    // Try to buy apm with no money
    p.on_buyMoreButton_clicked();
    QCOMPARE(p.getCountAPM(), 0);

    for(int i = 0; i < 10; i++)
    {
        p.on_makePencil_clicked();
        p.sell();
    }
    double price = p.getPriceAPM();

    // After selling 10 pencils our balance should be 155 and
    // the default price of the APM is 150 so we could buy it
    p.on_buyMoreButton_clicked();
    QCOMPARE(p.getCountAPM(), 1);

    // After one has been sold the price should have risen 10%
    QCOMPARE(p.getPriceAPM(), price * 1.1);
}

void Test::testMaterials()
{
    int argc = 0;
    char *argv[1];
    QApplication app(argc, argv);
    
    PencilProducer p;

    for(int i = 0; i < 1000; i++)
    {
        p.update_wood_graph();

        // Check if the prices go out of their range
        QVERIFY(p.getGraphPrice() >= 1500.00);
        QVERIFY(p.getGraphPrice() <= 2500.00);

        QVERIFY(p.getWoodPrice() >= 1000.00);
        QVERIFY(p.getWoodPrice() <= 2000.00);
    }

    // Check if we can buy materials with default balance
    p.on_buyGraphite_clicked();
    p.on_buyWood_clicked();

    // The values should have remained on 1000
    QCOMPARE(p.getGraphiteLeft(), 1000);
    QCOMPARE(p.getWoodLeft(), 1000);
}

QTEST_APPLESS_MAIN(Test)

#include "test.moc"
