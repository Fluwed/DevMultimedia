#ifndef CSPHERE_H
#define CSPHERE_H

#include "CObject.h"
#include <QVector>

class CSphere : public CObject
{
private:
    QVector<CVector3>   m_oVertices;
    QVector<CVector3>   m_oFaces;

    CVector3            m_oSpeed;


    void                vGenerateData(void);
    void                vComputeTriangle(float* v1, float *v2, float *v3, int n);
    void                vPousserProfondeur(float v[3]);

public:
    CSphere();
    CSphere(int _id);
    ~CSphere();

    virtual int         iGetNbFaces();
    virtual int         iGetNbVertices(int _iFace);
    virtual void        vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void        vGetSideColor(int _face, CVector3 *_poColor);

    virtual int         iIsPicked(CVector3* _poOrigin, CVector3* _poDir, CVector3* _poIntersection, int* _iPickedFace);

    virtual void GetSpeed(CVector3 *_oSpeed);
    virtual void SetSpeed(CVector3 *_oSpeed);
};

#endif // CSPHERE_H
