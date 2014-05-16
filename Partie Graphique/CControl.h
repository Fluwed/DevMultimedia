#ifndef CControl_H
#define CControl_H

#include "CModel.h"

class CControl
{
private:
    CModel*         m_poModel;
    float           m_fSpeed;


public:
    CControl(CModel *_model);
    ~CControl();

    CObject*        palet;
    CVector3        oPos;

    void            vAddObject();
    void            vDelObject();
    int             iCheckPicked(CVector3* _poOrigin, CVector3* _poDir);
    void            vResetPicked();
    void            vMovePalet(int Key, bool pressed);
    void            vStart();
    bool            is_moving_left=false;
    bool            is_moving_right=false;

    void timerEvent();

    int fSpeed();
    void setFSpeed(int fSpeed);
};

#endif // CControl_H
