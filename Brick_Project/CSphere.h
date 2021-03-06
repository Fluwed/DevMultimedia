#ifndef CSPHERE_H
#define CSPHERE_H

#include "CObject.h"
#include <QVector>

class CSphere : public CObject //Dérive de CObjet
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
    virtual int         iIsPicked(CVector3* _poOrigin);
    virtual void        vGetSpeed(CVector3 *_oSpeed);
    virtual void        vSetSpeed(CVector3 *_oSpeed);
    virtual void        vSetDurability(int _iDurability);
    virtual int         iGetDurability();
};

#endif // CSPHERE_H
