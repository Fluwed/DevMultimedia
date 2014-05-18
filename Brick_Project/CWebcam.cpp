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
    //detectCheckBox = new QCheckBox(tr("Detection initiale"));
    trackCheckBox= new QCheckBox(tr("Tracking"));



    connect(webCamButton, SIGNAL(clicked()), this, SLOT(startWebCam()));

    QVBoxLayout *vl1=new QVBoxLayout;
    //vl1->addWidget(detectCheckBox);
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

    startWebCam();
}

CWebcam::~CWebcam()
{
    delete webcam;
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
        //if (Delta < 5) detectHand(X,Y);
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
        qDebug()<<"hauteur"<<webcam->get(CV_CAP_PROP_FRAME_WIDTH);
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
    imshow("test",temp);

}


void CWebcam::trackHand()
{
    MatchingMethod();
}

void CWebcam::MatchingMethod()
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
    imshow("image",image);
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


    Delta_x = Temp_x - matchLoc.x;
    Delta_y = Temp_y - matchLoc.y;


    //Delta = 10;

    rectangle( image, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar(0, 200, 210), 2, 8, 0 );

    if(Delta_x > 6 || Delta_y > 3)
    {
        qDebug()<<"Delta_x  "<<Delta_x<<"   Delta_y "<<Delta_y<<"   Loc.x "<<matchLoc.x<<"  Loc.y "<<matchLoc.y;
    }

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

}
