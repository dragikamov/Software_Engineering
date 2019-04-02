#include "pencilmakermodel.h"

QDataStream& operator>>(QDataStream& in, PencilMakerModel* model){
    // load all parameters for the model
    in >> model->pencils_in_inv >>
            model->total_pencils >>
            model->bank_balance >>
            model->intelligenceVisible >>
            model->intelligence >>
            model->pencil_price >>
            model->wood >>
            model->graphite >>
            model->price_wood >>
            model->price_graphite >>
            model->apm >>
            model->apm_price >>
            model->upgradeAPM >>
            model->upgradeAPMPrice >>
            model->marketingUnlocked >>
            model->marketingPrice >>
            model->nMarketing;
    return in;
}

QDataStream& operator<<(QDataStream& out, PencilMakerModel* model){
    out << model->pencils_in_inv <<
           model->total_pencils <<
           model->bank_balance <<
           model->intelligenceVisible <<
           model->intelligence <<
           model->pencil_price <<
           model->wood <<
           model->graphite <<
           model->price_wood <<
           model->price_graphite <<
           model->apm <<
           model->apm_price <<
           model->upgradeAPM <<
           model->upgradeAPMPrice <<
           model->marketingUnlocked <<
           model->marketingPrice <<
           model->nMarketing;
    return out;
}
