#ifndef CControl_H
#define CControl_H

#include "CModel.h"

class CControl
{
private:
    CModel*         m_poModel;
    float           m_fSpeed;
    int             m_iLvl;
    int             m_iDifficulty;



public:
    CControl(CModel *_model);
    ~CControl();

    int             m_iScore;
    int             m_iLife;
    bool            m_bStickySphere;
    CObject*        palet;
    CVector3        oPos;

    void            vSetGame();
    int             iCheckPicked(CVector3* _poOrigin);
    void            vMovePalet(int Key, bool pressed);
    void            vStart();
    bool            is_moving_left;
    bool            is_moving_right;

    void            timerEvent();

    int             fSpeed();
    void            setFSpeed(int fSpeed);
    void            vSetNewLife();
    bool            bStickySphere() const;
    void            setBStickySphere(bool bStickySphere);
    void            vResetGame();
    void            vLevelFinished();
};

#endif // CControl_H
