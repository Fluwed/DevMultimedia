#include <QApplication>
#include "CView.h"
#include "CControl.h"
#include "CModel.h"


/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    QApplication oApp(argc, argv);

    CModel      oModel;
    CView       oView;
    CControl    oCtrl(&oModel);

    oView.vSetControl(&oCtrl);
    oView.vSetModel(&oModel);

    oView.show();

    return oApp.exec();
}
