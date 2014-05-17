#ifndef CMurV_H
#define CMurV_H

#include "CObject.h"

class CMurV : public CObject
{
public:
    CMurV();
    CMurV(int _id);

    virtual int iGetNbFaces();
    virtual int iGetNbVertices(int _iFace);
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void vGetSideColor(int _face, CVector3* _poColor);
    int iIsPicked(CVector3 *_poOrigin);

    virtual void vGetSpeed(CVector3 *_oSpeed);
    virtual void vSetSpeed(CVector3 *_oSpeed);

    virtual void vSetDurability(int _iDurability);
    virtual int iGetDurability();
};

#endif // CMURV_H
