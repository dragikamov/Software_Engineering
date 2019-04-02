#ifndef PENCILMAKERMODEL_H
#define PENCILMAKERMODEL_H
#include <QDataStream>

/**
 * @brief The PencilMakerModel struct is used to keep track of internal states
 */
struct PencilMakerModel
{
    int pencils_in_inv = 0; /**< pencils in the inventory */

    int total_pencils = 0; /**< total pencils produced */

    double bank_balance = 145.00; /**< total bank balance */

    bool intelligenceVisible = false; /**< visibility of Intelligence */

    int intelligence = 0; /**< total intelligence */

    double pencil_price = 1.00; /**< price of pencil */

    double wood = 1000.00; /**< wood in the inventory */

    double graphite = 1000.00; /**< graphite in the inventory */

    double price_wood = 1000.00; /**< price of wood */

    double price_graphite = 1500.00; /**< price of graphite */

    int apm = 0; /**< number of APMs */

    double apm_price = 150.00; /**< price of APMs */

    double upgradeAPM = 1.00; /**< upgrade of APM */

    int upgradeAPMPrice = 50; /**< upgrade price of APM */

    bool marketingUnlocked = false; /**< marketing lock */

    double marketingPrice = 500.00; /**< price of a marketing tool */

    int nMarketing = 0; /**< number of marketing bought */
};

/**
 * @fn operator>>
 * @brief operator >> for loading
 * @param in
 * @param model
 * @return
 */
QDataStream &operator>>(QDataStream &in, PencilMakerModel *model);

/**
 * @fn operator<<
 * @brief operator << for saving
 * @param out
 * @param model
 * @return
 */
QDataStream &operator<<(QDataStream &out, PencilMakerModel *model);

#endif // PENCILMAKERMODEL_H
