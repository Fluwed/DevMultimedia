#include "CMurV.h"
#include <QAbstractAnimation>
#include "qdebug.h"

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

float m_fVerticess[8][3] = {
    {   -0.75,     0.25,    -15.2 },    // 0 front top left
    {    0.75,     0.25,    -15.2 },    // 1 front top right
    {    0.75,    -0.25,    -15.2 },    // 2 front bottom right
    {   -0.75,    -0.25,    -15.2 },    // 3 front bottom left
    {   -0.75,     0.25,     18.2 },    // 4 rear top left
    {    0.75,     0.25,     18.2 },    // 5 rear top right
    {    0.75,    -0.25,     18.2 },    // 6 rear bottom right
    {   -0.75,    -0.25,     18.2 }     // 7 rear bottom left
};


/*---------------------------------------------------------------------------*/
CMurV::CMurV()
{
}

/*---------------------------------------------------------------------------*/
CMurV::CMurV(int _id) : CObject(_id)
{

}

/*---------------------------------------------------------------------------*/
int CMurV::iGetNbFaces()
{
    return m_iNbFaces;
}

/*---------------------------------------------------------------------------*/
int CMurV::iGetNbVertices(int _iFace)
{
    return m_iNbVertices[_iFace];
}

/*---------------------------------------------------------------------------*/
void CMurV::vGetVertex(int _iFace, int _iVertex, CVector3* _poVect)
{
    _poVect->vSet( m_fVerticess[m_iFaces[_iFace][_iVertex]][0],
            m_fVerticess[m_iFaces[_iFace][_iVertex]][1],
            m_fVerticess[m_iFaces[_iFace][_iVertex]][2] );
}

/*---------------------------------------------------------------------------*/
void CMurV::vGetSideColor(int _face, CVector3* _poColor)
{
    switch(_face)
    {
    case 5:
        _poColor->vSet(1.0, 0.0, 0.0);
        break;
    case 4:
        _poColor->vSet(1.0, 1.0, 0.0);
        break;
    case 3:
        _poColor->vSet(0.0, 1.0, 0.0);
        break;
    case 2:
        _poColor->vSet(0.0, 1.0, 1.0);
        break;
    case 1:
        _poColor->vSet(0.0, 0.0, 1.0);
        break;
    case 0:
    default:
        _poColor->vSet(1.0, 0.0, 1.0);
        break;
    }
}

int CMurV::iIsPicked(CVector3* _poOrigin)
{

}

void CMurV::vGetSpeed(CVector3 *_oSpeed)
{

}

void CMurV::vSetSpeed(CVector3 *_oSpeed)
{

}

int CMurV::iGetDurability()
{

}

void CMurV::vSetDurability(int _iDurability)
{

}
