#ifndef CControl_H
#define CControl_H

#include "CModel.h"
#include <QSound>

class CControl
{
private:
    CModel*         m_poModel;
    float           m_fSpeed;
    int             m_iLvl;
    int             m_iDifficulty;
    QSound*         m_poSound;
    QSound*         m_poEndSound;

public:
    CControl(CModel *_model);
    ~CControl();

    int             m_iScore;
    int             m_iLife;
    bool            m_bStickySphere;
    CObject*        m_poPalet;
    CVector3        m_oPos;

    int             iCheckPicked(CVector3* _poOrigin);
    bool            bIs_moving_left;
    bool            bIs_moving_right;
    bool            bStickySphere() const;
    int             fSpeed();
    void            vTimerEvent();
    void            vSetGame();
    void            vMovePalet(int Key, bool pressed);
    void            vStart();
    void            setFSpeed(int fSpeed);
    void            vSetNewLife();
    void            setBStickySphere(bool bStickySphere);
    void            vResetGame();
    void            vLevelFinished();
    void            vSave(QString text, int _iScore);
    void            vTrackPalet(float _X);
    void            vPauseMusic();
    void            vResume();
    void            vNoMusic();
    void            vActivateMusic();

    QStringList     vLoadHighScore();
};

#endif // CControl_H
