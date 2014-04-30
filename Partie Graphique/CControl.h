#ifndef CControl_H
#define CControl_H

#include "CModel.h"

class CControl
{
private:
    CModel*         m_poModel;


public:
    CControl(CModel *_model);
    ~CControl();

    void            vAddObject(int _iId);
    void            vDelObject();
    int             iCheckPicked(CVector3* _poOrigin, CVector3* _poDir);
    void            vResetPicked();
    void            vMovePalet(int Key, bool pressed);
    bool is_moving_left, is_moving_right;
    CObject* palet;
    CVector3 oPos;

    void timerEvent();
};

#endif // CControl_H
