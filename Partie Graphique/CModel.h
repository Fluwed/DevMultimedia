#ifndef CModel_H
#define CModel_H

#include "CObject.h"
#include <qvector.h>

class CModel
{
private:
    QVector<CObject*>   m_oDatas;      // Pointer to the model

    float               fGetRandom();

public:
    CModel();
    ~CModel();

    void                vAdd();
    void                vDel(int _iId);
    void vNewPos(CVector3 *_poPos, int _face);
    int                 iGetNbObjects();
    int                 iCheckPicked(CVector3* _poOrigin, CVector3* _poDir);
    CObject*            poGetObject(int _iIndex);
    void                vLoadLevel(int _iLvl);
    void                vNewLife();
    void                vSetSpeed(float _fSpeed);

};

#endif // CModel_H
