#include "CWebcam.h"
#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>


using namespace cv;

CWebcam::CWebcam(QWidget *parent)
    : QWidget(parent)
{
    webCamButton = new QPushButton(tr("Demarrer aquisition"));
    label = new QLabel(tr("Image"));
    trackCheckBox= new QCheckBox(tr("Tracking"));
    trackCrop= new QCheckBox(tr("Tracking sur la partie haute de la webcam uniquement"));
    trackZone= new QCheckBox(tr("Afficher le suivi de tracking"));


    connect(webCamButton, SIGNAL(clicked()), this, SLOT(startWebCam()));

    QVBoxLayout *vl1=new QVBoxLayout;
    vl1->addWidget(trackCheckBox);
    vl1->addWidget(trackCrop);
    vl1->addWidget(trackZone);
    vl1->addWidget(webCamButton);
    //vl1->addStretch();
    //QHBoxLayout *hl=new QHBoxLayout;

    //hl->addLayout(vl1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addLayout(vl1);
    layout->addStretch();

    setLayout(layout);
    setWindowTitle(tr("Track WebCam"));

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(aquire()));
    show();

    startWebCam();
}

CWebcam::~CWebcam()
{
    delete webcam;
}

bool CWebcam::bIsTracking()
{
    return trackCheckBox->isChecked();
}

float CWebcam::fGetPosition()
{
    return X;
}


void CWebcam::displayImage()
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


void CWebcam::aquire()
{
    *webcam >> imgCam;
    if (!imgCam.empty()) {
        ::resize(imgCam,image,Size(),1,1,CV_INTER_AREA);
        if (!trackCheckBox->isChecked()) detectHand(X,Y);
        if (trackCheckBox->isChecked()) trackHand();
        displayImage();

    }

}

void CWebcam::startWebCam()
{
    if (!timer->isActive())
    {
        webcam= new cv::VideoCapture(0);
        webcam->set(CV_CAP_PROP_FRAME_HEIGHT,240);
        webcam->set(CV_CAP_PROP_FRAME_WIDTH,320);
        qDebug()<<"hauteur"<<webcam->get(CV_CAP_PROP_FRAME_HEIGHT);
        qDebug()<<"largeur"<<webcam->get(CV_CAP_PROP_FRAME_WIDTH);
        webcam->set(5, 60);  //frame rate
        timer->start(60);
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

void CWebcam::detectHand(int X, int Y)
{
    Mat frame;
    // Position X 150/Y 100 Taille X/Y (inverse)
    cv::Rect rectRoi(X,Y,70,40);
    // Scalar (R,G,B), ,Epaisseur,0
    rectangle(image,rectRoi,Scalar( 0, 200, 10),2,8,0);

    temp=image.clone();
    temp=temp(rectRoi);
    cv::flip(temp,temp,1);
    //imshow("test",temp);

}


void CWebcam::trackHand()
{
    MatchingMethod();
    /*pt1=Point (0,200);
    pt2=Point (330,200);
    cv::line(image,pt1,pt2,Scalar(10,10,255),2,8,0);*/
}



void CWebcam::MatchingMethod()
{
    /// Source image to display
    Mat img_display;
    Mat result;

    //img_display=image;

    const char* image_window = "Source Image";
    const char* result_window = "Result window";

    int match_method;

    // You mention that you start with a CVMat* imagesource

    if (trackCrop->isChecked())
    {
        Point pt1=Point (0,100);
        Point pt2=Point (330,100);
        cv::line(image,pt1,pt2,Scalar(10,10,255),2,8,0);
    // Transform it into the C++ cv::Mat format
    cv::Mat img(image);
    // Setup a rectangle to define your region of interest
    cv::Rect myROI(0, 0, 320, 100);

    // Crop the full image to that image contained by the rectangle myROI
    // Note that this doesn't copy the data
    img_display = img(myROI);
    }
    else
    {
       img_display=image;
    }

    //image.copyTo( img_display );

    /// Create the result matrix
    int result_cols =  img_display.cols - temp.cols + 1;
    int result_rows = img_display.rows - temp.rows + 1;

    result.create( result_cols, result_rows, CV_32FC1 );

    /// Do the Matching and Normalize
    //imshow("image",image);
    matchTemplate( img_display, temp, result,5 );
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


    Delta_x = Temp_x - matchLoc.x;
    Delta_y = Temp_y - matchLoc.y;


    //Delta = 10;

    if (trackZone->isChecked())
    {
    rectangle( img_display, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar(0, 200, 210), 2, 8, 0 );
    }

    if(Delta_x > 6 || Delta_y > 3)
    {

    }
    qDebug()<<"Delta_x  "<<Delta_x<<"   Delta_y "<<Delta_y<<"   Loc.x "<<matchLoc.x<<"  Loc.y "<<matchLoc.y;

    Temp_x = matchLoc.x;
    Temp_y = matchLoc.y;





    X = matchLoc.x;
    Y = matchLoc.y;


    //rectangle( result, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar::all(0), 2, 8, 0 );
    //imshow( result_window, result );
    //cv::flip(img_display,img_display,1);
    //imshow( image_window, img_display );


    return;
}


