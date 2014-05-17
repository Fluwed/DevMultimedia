#ifndef CObject_H
#define CObject_H

#include "CVector3.h"

class CObject
{
private:


protected:
     CVector3    m_oPosition;

public:
    int         m_iId;
    int         m_iDurability;

    CObject();
    CObject(int _iId);

    int         iGetID();

    void        vSetPosition(CVector3* _oPos);
    void        vGetPosition(CVector3* _poPos);

    virtual int iGetNbFaces() = 0;
    virtual int iGetNbVertices(int _iFace) = 0;
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect) = 0;
    virtual void vGetSideColor(int _face, CVector3* _poColor) = 0;
    virtual int iIsPicked(CVector3* _poOrigin)=0;

    virtual void vGetSpeed(CVector3 *_oSpeed) = 0;
    virtual void vSetSpeed(CVector3 *_oSpeed) = 0;

    virtual void vSetDurability(int _iDurability) = 0;
    virtual int iGetDurability() = 0;

};

#endif // CObject_H
