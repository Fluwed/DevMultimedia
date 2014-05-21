#ifndef CWEBCAM_H
#define CWEBCAM_H

#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

class CWebcam : public QWidget
{
    Q_OBJECT

private:
    QPushButton*        m_poWebCamButton;
    QCheckBox*          m_poDetectCheckBox;
    QCheckBox*          m_poTrackCheckBox;
    QCheckBox*          m_poTrackCrop;
    QCheckBox*          m_poTrackZone;
    QTimer*             m_poTimer;
    QLabel*             m_poLabel;
    cv::Mat             m_oImgCam;
    cv::Mat             m_oImage;
    cv::Mat             m_oTemp;
    cv::VideoCapture*   m_poWebcam;

    int m_iX ;
    int m_iDelta_x ;
    int m_iTemp_x ;

public:
    CWebcam(QWidget *parent = 0);
    ~CWebcam();

    void                vDisplayImage();
    void                vDetectHand(int m_iX, int Y);
    void                vTrackHand();
    void                vMatchingMethod();
    bool                bIsTracking();
    float               fGetPosition();

    void vGetImg();
private slots:
    void                vAcquire();
    void                vStartWebCam();
    };


#endif // CWEBCAM_H
