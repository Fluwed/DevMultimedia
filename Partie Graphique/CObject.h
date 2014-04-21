#ifndef CObject_H
#define CObject_H

#include "CVector3.h"

class CObject
{
private:
    int         m_iId;
    int         m_iCurFace=-1;


protected:
     CVector3    m_oPosition;

public:
    CObject();
    CObject(int _iId);

    int         iGetID();
    int         iGetCurFace();

    void        vSetPosition(CVector3* _oPos);
    void        vGetPosition(CVector3* _poPos);
    void        vSetPicked(int _iPicked);

    virtual int iGetNbFaces() = 0;
    virtual int iGetNbVertices(int _iFace) = 0;
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect) = 0;
    virtual void vGetSideColor(int _face, CVector3* _poColor) = 0;
    virtual int iIsPicked(CVector3* _poOrigin, CVector3* _poDir, CVector3* _poInter, int* _iFace)=0;

    virtual void GetSpeed(CVector3 *_oSpeed) = 0;
    virtual void SetSpeed(CVector3 *_oSpeed) = 0;


};

#endif // CObject_H
