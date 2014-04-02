#include <QApplication>
#include "webcamwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebCamWindow w;
    w.show();
    
    return a.exec();
}
