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
        webcam->set(5, 60);  //frame rate
        timer->start(20);
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
    // Position X/Y Taille X/Y (inverse)
    cv::Rect rectRoi(250,200,150,100);
    // Scalar (R,G,B), ,Epaisseur,0
    rectangle(image,rectRoi,Scalar( 0, 200, 10),2,8,0);
    temp=image.clone();
    temp=temp(rectRoi);
    cv::flip(temp,temp,1);
    imshow("test",temp);

}

void WebCamWindow::trackHand()
{
    cv::Rect rectRoi(250,200,150,100);
    rectangle(image,rectRoi,Scalar( 200, 200, 10),2,8,0);
    MatchingMethod();
}

void WebCamWindow::MatchingMethod()
{
    /// Source image to display
    Mat img_display;Mat result;

    const char* image_window = "Source Image";
    const char* result_window = "Result window";

    int match_method;

    image.copyTo( img_display );

    /// Create the result matrix
    int result_cols =  image.cols - temp.cols + 1;
    int result_rows = image.rows - temp.rows + 1;

    result.create( result_cols, result_rows, CV_32FC1 );

    /// Do the Matching and Normalize
    matchTemplate( image, temp, result,5 );
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );


    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
    else
    { matchLoc = maxLoc; }

    /// Show me what you got
    rectangle( image, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar::all(0), 2, 8, 0 );
    //rectangle( result, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar::all(0), 2, 8, 0 );

    flip(img_display,img_display,1);
    imshow( image_window, img_display );
    //imshow( result_window, result );
    //cv::flip(img_display,img_display,1);
    //imshow( image_window, img_display );


    return;
}
