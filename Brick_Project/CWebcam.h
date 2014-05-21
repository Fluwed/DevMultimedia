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
    QPushButton*        m_poWebCamButton;   // Boutton permettant de démarrer ou arreter la Webcam
    QCheckBox*          m_poTrackCheckBox;  // Une fois coché lance l'algorithme de tracking
    QCheckBox*          m_poTrackCrop;      // Permet de limiter à une zone de la webcam la détection
    QCheckBox*          m_poTrackZone;      // Permet de voir la recherche du template par l'algorithme
    QTimer*             m_poTimer;          // Timer responsable de l'acquisition d'image
    QLabel*             m_poLabel;          // Permet d'afficher les images récupérées de la Webcam
    cv::Mat             m_oImgCam;          // Image récupéré de la caméra
    cv::Mat             m_oImage;           // Image utilisé dans l'algorithme
    cv::Mat             m_oTemp;            // Image utilisé dans l'algorithme
    cv::VideoCapture*   m_poWebcam;         // Objet correspondant à la Webcam

    int m_iX ;                              // Position du template
    int m_iDelta_x ;                        // Nécessaire dans l'algorithme
    int m_iTemp_x ;                         // Nécessaire dans l'algorithme

public:
    CWebcam(QWidget *parent = 0);
    ~CWebcam();

    void                vDisplayImage();                // Permet d'afficher l'image récupérer de la Webcam sur m_poLabel
    void                vDetectHand(int m_iX, int Y);   // Permet l'acquisition du template au travers d'un rectangle
    void                vMatchingMethod();              // Algorithme de recherche du template
    bool                bIsTracking();                  // Getter de m_poTrackCheckBox
    float               fGetPosition();                 // Getter de m_iX
    void                vGetImg();                      // Fonction threadé qui s'occupe de récupérer les images de la Webcam et les mettre dans m_oImgCam
private slots:
    void                vAcquire();                     // Lancer par m_poTimer s'occupe de lancer les fonctions selon l'état des CheckBox
    void                vStartWebCam();                 // Permet de démarrer la Webcam ou l'arreter sur l'appui de m_poWebCamButton
    };


#endif // CWEBCAM_H
