#ifndef CControl_H
#define CControl_H

#include "CModel.h"

class CControl
{
private:
    CModel*         m_poModel;
    float           m_fSpeed;
    int             m_iLife;


public:
    CControl(CModel *_model);
    ~CControl();

    bool            m_bStart;
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
    bool            bStart() const;
    void            setBStart(bool bIsStarted);
    bool            bStickySphere() const;
    void            setBStickySphere(bool bStickySphere);
};

#endif // CControl_H
