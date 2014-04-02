#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "webcamwindow.h"

using namespace cv;

WebCamWindow::WebCamWindow(QWidget *parent)
    : QWidget(parent)
{
    webCamButton = new QPushButton(tr("Demarrer aquisition"));
    label = new QLabel(tr("Image"));
    detectCheckBox = new QCheckBox(tr("Detection initiale"));
    trackCheckBox= new QCheckBox(tr("Tracking"));

    connect(webCamButton, SIGNAL(clicked()), this, SLOT(startWebCam()));

    QVBoxLayout *vl1=new QVBoxLayout;
    vl1->addWidget(detectCheckBox);
    vl1->addWidget(trackCheckBox);
    QHBoxLayout *hl=new QHBoxLayout;
    hl->addWidget(webCamButton);
    hl->addLayout(vl1);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addLayout(hl);

    setLayout(layout);
    setWindowTitle(tr("Track WebCam"));

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(aquire()));

}

WebCamWindow::~WebCamWindow()
{
    delete webcam;
}

void WebCamWindow::displayImage()
{
    if (image.data!=NULL)
    {
        cv::flip(image,image,1); // process the image
        // change color channel ordering
        cv::cvtColor(image,image,CV_BGR2RGB);
        // Qt image
        QImage img= QImage((const unsigned char*)(image.data),
                           image.cols,image.rows,QImage::Format_RGB888);
        // display on label
        label->setPixmap(QPixmap::fromImage(img));
        // resize the label to fit the image
        label->resize(label->pixmap()->size());
    }
    else QMessageBox(QMessageBox::Critical,tr("Error"),tr("Image is void")).exec();
}


void WebCamWindow::aquire()
{
    *webcam >> imgCam;
    if (!imgCam.empty()) {
        ::resize(imgCam,image,Size(),1,1,CV_INTER_AREA);
        if (detectCheckBox->isChecked() && !trackCheckBox->isChecked()) detectHand();
        if (trackCheckBox->isChecked()) trackHand();
        displayImage();
    }

}

void WebCamWindow::startWebCam()
{
    if (!timer->isActive())
    {
        webcam= new cv::VideoCapture(0);
        timer->start(50);
        webCamButton->setText(tr("Arreter aquisition"));

    }
    else
    {
        timer->stop();
        delete webcam;
        webcam=0;
        webCamButton->setText(tr("Demarrer aquisition"));
    }
}

void WebCamWindow::detectHand()
{
    Mat frame;
    Mat temp;
    // Position X/Y Taille X/Y (inverse)
    cv::Rect rectRoi(250,200,150,100);
    // Scalar (R,G,B), ,Epaisseur,0
    rectangle(image,rectRoi,Scalar( 0, 200, 10),2,8,0);
    webcam->retrieve(frame, 0);
    temp=frame.clone();
    temp=temp(rectRoi);
    vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(9);
    imwrite("Template.png",temp,compression_params);
}

void WebCamWindow::trackHand()
{
    cv::Rect rectRoi(250,200,150,100);
    rectangle(image,rectRoi,Scalar( 200, 200, 10),2,8,0);


}
