#ifndef WEBCAMWINDOW_H
#define WEBCAMWINDOW_H

#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

class WebCamWindow : public QWidget
{
    Q_OBJECT
    
public:
    WebCamWindow(QWidget *parent = 0);
    ~WebCamWindow();
    void displayImage();
    void detectHand();
    void trackHand();

private slots:
    void aquire();
    void startWebCam();


private:
    QPushButton *webCamButton;
    QCheckBox *detectCheckBox;
    QCheckBox *trackCheckBox;
    QTimer *timer;
    QLabel *label;
    cv::Mat imgCam;
    cv::Mat image;
    cv::VideoCapture *webcam;
    cv::Mat temp;
    };

#endif // WEBCAMWINDOW_H
