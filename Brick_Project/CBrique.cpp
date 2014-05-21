#include "CBrique.h"
#include "qdebug.h"
#include <QAbstractAnimation>

/*---------------------------------------------------------------------------*/
static const int m_iNbFaces = 6;

static const int m_iNbVertices[] = {4,4,4,4,4,4};

static const int m_iFaces[6][4] = {
    {   0,  3,  2,  1   },          // front side
    {   1,  2,  6,  5   },          // right side
    {   0,  1,  5,  4   },          // top side
    {   0,  4,  7,  3   },          // left side
    {   3,  7,  6,  2   },          // bottom side
    {   4,  5,  6,  7   },          // rear side
};

static const float m_fVertices[8][3] = {
    {   -0.75,     2.25,    -0.75 },    // 0 front top left
    {    0.75,     2.25,    -0.75 },    // 1 front top right
    {    0.75,    -2.25,    -0.75 },    // 2 front bottom right
    {   -0.75,    -2.25,    -0.75 },    // 3 front bottom left
    {   -0.75,     2.25,     0.75 },    // 4 rear top left
    {    0.75,     2.25,     0.75 },    // 5 rear top right
    {    0.75,    -2.25,     0.75 },    // 6 rear bottom right
    {   -0.75,    -2.25,     0.75 }     // 7 rear bottom left
};


/*---------------------------------------------------------------------------*/
CBrique::CBrique()
{

}

/*---------------------------------------------------------------------------*/
CBrique::CBrique(int _id) : CObject(_id)
{
    m_iId=_id;
    m_iDurability=1;
}

/*---------------------------------------------------------------------------*/
CBrique::CBrique(int _id, int _iDurability)
{
    m_iId=_id;
    m_iDurability=_iDurability;
}

/*---------------------------------------------------------------------------*/
int CBrique::iGetNbFaces()
{
    return m_iNbFaces;
}

/*---------------------------------------------------------------------------*/
int CBrique::iGetNbVertices(int _iFace)
{
    return m_iNbVertices[_iFace];
}

/*---------------------------------------------------------------------------*/
void CBrique::vGetVertex(int _iFace, int _iVertex, CVector3* _poVect)
{
    _poVect->vSet( m_fVertices[m_iFaces[_iFace][_iVertex]][0],
            m_fVertices[m_iFaces[_iFace][_iVertex]][1],
            m_fVertices[m_iFaces[_iFace][_iVertex]][2] );
}

/*---------------------------------------------------------------------------*/
void CBrique::vGetSideColor(int _face, CVector3* _poColor)
{
    switch(_face)
    {
    case 0:
        _poColor->vSet(1.0, 0.0, 0.0);
        break;
    case 1:
        _poColor->vSet(1.0, 1.0, 0.0);
        break;
    case 2:
        _poColor->vSet(0.0, 1.0, 0.0);
        break;
    case 3:
        _poColor->vSet(0.0, 1.0, 1.0);
        break;
    case 4:
        _poColor->vSet(0.0, 0.0, 1.0);
        break;
    case 5:
    default:
        _poColor->vSet(1.0, 0.0, 1.0);
        break;
    }

    switch(m_iDurability)
    {
    case 0:
        _poColor->vSet(0.32, 0.32, 0.32);
        break;
    case 1:
        _poColor->vSet(1.0, 0.89, 0.0);
        break;
    case 2:
        _poColor->vSet(0.75, 0.75, 0.75);
        break;
    case 3:
        _poColor->vSet(0.0, 0.0, 1.0);
        break;
    case 4:
        _poColor->vSet(1.0, 0.0, 0.0);
        break;
    case 5:
        _poColor->vSet(0.0, 1.0, 0.0);
        break;
    }
}

/*---------------------------------------------------------------------------*/
int CBrique::iIsPicked(CVector3* _poOrigin)
{
    int iStatus=0;
    float fYSphere=_poOrigin->fGetY();
    float fZSphere=_poOrigin->fGetZ();
    float fYBrique=m_oPosition.fGetY();
    float fZBrique=m_oPosition.fGetZ();

    if ((fYSphere<=fYBrique+3.1) && ((fYSphere>=fYBrique-3.1)))
    {
        if ((fZSphere<=fZBrique+1.6) && ((fZSphere>=fZBrique-1.6)))
        {
            iStatus = 1;
        }
    }
    if ((fYSphere<=fYBrique+2.25) && ((fYSphere>=fYBrique-2.25)))
    {
        if ((fZSphere<=fZBrique+0.75) && ((fZSphere>=fZBrique-0.75)))
        {
            iStatus = 0;
        }
    }
    return iStatus;
}

/*---------------------------------------------------------------------------*/
void CBrique::vGetSpeed(CVector3 *_oSpeed)
{

}

/*---------------------------------------------------------------------------*/
void CBrique::vSetSpeed(CVector3 *_oSpeed)
{

}

/*---------------------------------------------------------------------------*/
int CBrique::iGetDurability()
{
    return m_iDurability;
}

/*---------------------------------------------------------------------------*/
void CBrique::vSetDurability(int _iDurability)
{
    m_iDurability=_iDurability;
}
