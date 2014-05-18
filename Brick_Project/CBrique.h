#ifndef CBRIQUE_H
#define CBRIQUE_H

#include "CObject.h"

class CBrique : public CObject
{
public:
    CBrique();
    CBrique(int _id);
    CBrique(int _id,int _iDurability);

    virtual int iGetNbFaces();
    virtual int iGetNbVertices(int _iFace);
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void vGetSideColor(int _face, CVector3* _poColor);
    int iIsPicked(CVector3 *_poOrigin);

    virtual void vGetSpeed(CVector3 *_oSpeed);
    virtual void vSetSpeed(CVector3 *_oSpeed);

    void vSetDurability(int _iDurability);
    int iGetDurability();

};

#endif // CBRIQUE_H
