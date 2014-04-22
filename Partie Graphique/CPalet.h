#ifndef CPALET_H
#define CPALET_H

#include "CObject.h"

class CPalet : public CObject
{
public:
    CPalet();
    CPalet(int _id);

    virtual int iGetNbFaces();
    virtual int iGetNbVertices(int _iFace);
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void vGetSideColor(int _face, CVector3* _poColor);
    int iIsPicked(CVector3 *_poOrigin, CVector3 *_poDir, CVector3 *_poIntersection, int *_iPickedFace);

    virtual void GetSpeed(CVector3 *_oSpeed);
    virtual void SetSpeed(CVector3 *_oSpeed);
};

#endif // CPalet.h