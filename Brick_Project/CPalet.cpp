#include "CPalet.h"
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
    {   -0.5,     3,    -0.5 },    // 0 front top left
    {    0.5,     3,    -0.5 },    // 1 front top right
    {    0.5,    -3,    -0.5 },    // 2 front bottom right
    {   -0.5,    -3,    -0.5 },    // 3 front bottom left
    {   -0.5,     3,     0.5 },    // 4 rear top left
    {    0.5,     3,     0.5 },    // 5 rear top right
    {    0.5,    -3,     0.5 },    // 6 rear bottom right
    {   -0.5,    -3,     0.5 }     // 7 rear bottom left
};


/*---------------------------------------------------------------------------*/
CPalet::CPalet()
{
    m_iId=-2;
}

/*---------------------------------------------------------------------------*/
CPalet::CPalet(int _id) : CObject(_id)
{
}

/*---------------------------------------------------------------------------*/
int CPalet::iGetNbFaces()
{
    return m_iNbFaces;
}

/*---------------------------------------------------------------------------*/
int CPalet::iGetNbVertices(int _iFace)
{
    return m_iNbVertices[_iFace];
}

/*---------------------------------------------------------------------------*/
void CPalet::vGetVertex(int _iFace, int _iVertex, CVector3* _poVect)
{
    _poVect->vSet( m_fVertices[m_iFaces[_iFace][_iVertex]][0],
            m_fVertices[m_iFaces[_iFace][_iVertex]][1],
            m_fVertices[m_iFaces[_iFace][_iVertex]][2] );
}

/*---------------------------------------------------------------------------*/
void CPalet::vGetSideColor(int _face, CVector3* _poColor)
{
    switch(_face)
    {
    case 1:
        _poColor->vSet(0.55, 0.90, 0.0);
        break;
    case 2:
        _poColor->vSet(1.0, 1.0, 0.0);
        break;
    case 5:
        _poColor->vSet(0.0, 1.0, 0.0);
        break;
    case 6:
        _poColor->vSet(0.0, 1.0, 1.0);
        break;
    case 3:
        _poColor->vSet(0.0, 0.0, 1.0);
        break;
    case 4:
    default:
        _poColor->vSet(1.0, 0.0, 1.0);
        break;
    }
}

/*---------------------------------------------------------------------------*/
int CPalet::iIsPicked(CVector3* _poOrigin)
{
    int iStatus=0;
    int iYSphere=_poOrigin->fGetY();
    int iZSphere=_poOrigin->fGetZ();
    int iYBrique=m_oPosition.fGetY();
    int iZBrique=m_oPosition.fGetZ();

    if ((iYSphere<=iYBrique+3.75) && ((iYSphere>=iYBrique-3.75)))
    {
        if ((iZSphere<=iZBrique+1.7) && ((iZSphere>=iZBrique-1.7)))
        {
            iStatus = 1;
        }
    }
    return iStatus;
}

/*---------------------------------------------------------------------------*/
void CPalet::vGetSpeed(CVector3 *_oSpeed)
{

}

/*---------------------------------------------------------------------------*/
void CPalet::vSetSpeed(CVector3 *_oSpeed)
{

}

/*---------------------------------------------------------------------------*/
int CPalet::iGetDurability()
{

}

/*---------------------------------------------------------------------------*/
void CPalet::vSetDurability(int _iDurability)
{

}

