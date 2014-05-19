#ifndef CWEBCAM_H
#define CWEBCAM_H

#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

class CWebcam : public QWidget
{
    Q_OBJECT

public:
    CWebcam(QWidget *parent = 0);
    ~CWebcam();
    void displayImage();
    void detectHand(int X, int Y);
    void trackHand();
    bool bIsTracking();
    float fGetPosition();

    void MatchingMethod();
private slots:
    void aquire();
    void startWebCam();


private:
    QPushButton *webCamButton;
    QCheckBox *detectCheckBox;
    QCheckBox *trackCheckBox;
    QCheckBox *trackCrop;
    QCheckBox *trackZone;
    QTimer *timer;
    QLabel *label;
    cv::Mat imgCam;
    cv::Mat image;
    cv::Mat temp;
    cv::VideoCapture *webcam;

    int X = 150;
    int Y = 100;
    int Delta_x = 0;
    int Temp_x = 100;
    int Delta_y = 0;
    int Temp_y = 150;
    };


#endif // CWEBCAM_H
