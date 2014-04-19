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
};

#endif // CControl_H
