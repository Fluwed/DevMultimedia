#ifndef CView_H
#define CVIew_H

#include <QWidget>
#include "CGLArea.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSound>
#include <CWebcam.h>

class CView : public QWidget
{
    Q_OBJECT

private:
    bool            m_bScoreVisible;
    bool            m_bPause;
    bool            m_bMusic;
    CModel*         m_poModel;
    CControl*       m_poCtrl;
    CGLArea*        m_poGlArea;
    QLabel*         m_poScore;
    QLabel*         m_poLife;
    QLabel*         m_poInfo;
    QTimer*         m_poClock;
    QVBoxLayout*    m_poVLayout;
    QVBoxLayout*    m_poGameScore;
    QVBoxLayout*    m_poHighScore;
    QHBoxLayout*    m_poHLayout;
    QPushButton*    m_poMusicBtn;
    QDialog*        m_poSave;
    QLineEdit*      m_poLineEdit;
    QPushButton*    m_poSaveBtn;
    int             m_iTimer;
    int             m_iFinalScore;
    CWebcam*        m_poWebcam;
    QTimer*         m_poTimer;


    
public:
    CView(QWidget *parent = 0);
    ~CView();

    void            vSetControl(CControl* _oCtrl);
    void            vSetModel(CModel* _poMdl);
    void            keyPressEvent(QKeyEvent *_event);
    void            keyReleaseEvent(QKeyEvent *_event);

private:
    void            vResetList(void);

public slots:
    void            vSetGame();
    void            vStartGame();
    void            vUpdateTime();
    void            vUpdateGame();
    void            vHighScore();
    void            vSave();
    void            vSaveScore();
    void            vTracking();
    void            vPause();
    void            vSetMusic();
};

#endif // CVIew_H













