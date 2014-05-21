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
    m_iX = 150;
    m_iDelta_x = 0;
    m_iTemp_x = 100;

    m_poWebCamButton = new QPushButton(tr("Demarrer aquisition"));
    m_poLabel = new QLabel(tr("Image"));
    m_poTrackCheckBox= new QCheckBox(tr("Tracking"));
    m_poTrackCrop= new QCheckBox(tr("Tracking sur la partie haute de la webcam uniquement"));
    m_poTrackZone= new QCheckBox(tr("Afficher le suivi de tracking"));


    connect(m_poWebCamButton, SIGNAL(clicked()), this, SLOT(vStartWebCam()));

    QVBoxLayout *vl1=new QVBoxLayout;
    vl1->addWidget(m_poTrackCheckBox);
    vl1->addWidget(m_poTrackCrop);
    vl1->addWidget(m_poTrackZone);
    vl1->addWidget(m_poWebCamButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_poLabel);
    layout->addLayout(vl1);
    layout->addStretch();

    setLayout(layout);
    setWindowTitle(tr("Track WebCam"));

    m_poTimer=new QTimer(this);
    connect(m_poTimer, SIGNAL(timeout()), this, SLOT(vAcquire()),Qt::AutoConnection);
    show();

    vStartWebCam();
}

CWebcam::~CWebcam()
{
    delete m_poWebcam;
}

bool CWebcam::bIsTracking()
{
    return m_poTrackCheckBox->isChecked();
}

float CWebcam::fGetPosition()
{
    return m_iX;
}


void CWebcam::vDisplayImage()
{
    if (m_oImage.data!=NULL)
    {
        cv::flip(m_oImage,m_oImage,1); // process the image
        // change color channel ordering
        cv::cvtColor(m_oImage,m_oImage,CV_BGR2RGB);
        // Qt image
        QImage img= QImage((const unsigned char*)(m_oImage.data),
                           m_oImage.cols,m_oImage.rows,QImage::Format_RGB888);
        // display on label
        m_poLabel->setPixmap(QPixmap::fromImage(img));
        // resize the label to fit the image
        m_poLabel->resize(m_poLabel->pixmap()->size());
    }
    else QMessageBox(QMessageBox::Critical,tr("Error"),tr("Image is void")).exec();
}


void CWebcam::vAcquire()
{
    *m_poWebcam >> m_oImgCam;
    if (!m_oImgCam.empty()) {
        ::resize(m_oImgCam,m_oImage,Size(),1,1,CV_INTER_AREA);
        if (!m_poTrackCheckBox->isChecked()) vDetectHand(150,100);
        if (m_poTrackCheckBox->isChecked()) vTrackHand();
        vDisplayImage();

    }

}

void CWebcam::vStartWebCam()
{
    if (!m_poTimer->isActive())
    {
        m_poWebcam= new cv::VideoCapture(0);
        m_poWebcam->set(CV_CAP_PROP_FRAME_HEIGHT,240);
        m_poWebcam->set(CV_CAP_PROP_FRAME_WIDTH,320);
        m_poTimer->start(300);
        m_poWebCamButton->setText(tr("Arreter aquisition"));

    }
    else
    {
        m_poTimer->stop();
        delete m_poWebcam;
        m_poWebcam=0;
        m_poWebCamButton->setText(tr("Demarrer aquisition"));
    }
}

void CWebcam::vDetectHand(int X, int Y)
{
    Mat frame;
    cv::Rect rectRoi(X,Y,70,40);
    rectangle(m_oImage,rectRoi,Scalar( 0, 200, 10),2,8,0);

    m_oTemp=m_oImage.clone();
    m_oTemp=m_oTemp(rectRoi);
    cv::flip(m_oTemp,m_oTemp,1);

}


void CWebcam::vTrackHand()
{
    vMatchingMethod();

}



void CWebcam::vMatchingMethod()
{
    /// Source image to display
    Mat img_display;
    Mat result;

    int match_method;


    if (m_poTrackCrop->isChecked())
    {
        Point pt1=Point (0,100);
        Point pt2=Point (330,100);
        cv::line(m_oImage,pt1,pt2,Scalar(10,10,255),2,8,0);
       // cv::Mat img(m_oImage);
        cv::Rect myROI(0, 0, 320, 100);
        img_display = m_oImage(myROI);
    }
    else
    {
        img_display=m_oImage;
    }


    /// Create the result matrix
    int result_cols =  img_display.cols - m_oTemp.cols + 1;
    int result_rows = img_display.rows - m_oTemp.rows + 1;

    result.create( result_cols, result_rows, CV_32FC1 );

    /// Do the Matching and Normalize
    matchTemplate( img_display, m_oTemp, result,5 );
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

    m_iDelta_x = m_iTemp_x - matchLoc.x;


    if (m_poTrackZone->isChecked())
    {
        rectangle( img_display, matchLoc, Point( matchLoc.x + m_oTemp.cols , matchLoc.y + m_oTemp.rows ), Scalar(0, 200, 210), 2, 8, 0 );
    }

    m_iTemp_x = matchLoc.x;

    m_iX = matchLoc.x;
}


