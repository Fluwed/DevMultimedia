#include "CMurH.h"
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

float m_fVertices[8][3] = {
    {   -0.5,     26,    -0.25 },    // 0 front top left
    {    0.5,     26,    -0.25 },    // 1 front top right
    {    0.5,    -26,    -0.25 },    // 2 front bottom right
    {   -0.5,    -26,    -0.25 },    // 3 front bottom left
    {   -0.5,     26,     0.25 },    // 4 rear top left
    {    0.5,     26,     0.25 },    // 5 rear top right
    {    0.5,    -26,     0.25 },    // 6 rear bottom right
    {   -0.5,    -26,     0.25 }     // 7 rear bottom left
};


/*---------------------------------------------------------------------------*/
CMurH::CMurH()
{
}

/*---------------------------------------------------------------------------*/
CMurH::CMurH(int _id) : CObject(_id)
{
    /*if (_id==0)
    {
        m_fVertices= {
            {   -0.5,     0.25,    -15 },    // 0 front top left
            {    0.5,     0.25,    -15 },    // 1 front top right
            {    0.5,    -0.25,    -15 },    // 2 front bottom right
            {   -0.5,    -0.25,    -15 },    // 3 front bottom left
            {   -0.5,     0.25,     15 },    // 4 rear top left
            {    0.5,     0.25,     15 },    // 5 rear top right
            {    0.5,    -0.25,     15 },    // 6 rear bottom right
            {   -0.5,    -0.25,     15 }     // 7 rear bottom left
        };
    m_fVertices[0][0]=-0.5;
    m_fVertices[1][0]=0.5;
    m_fVertices[2][0]=0.5;
    m_fVertices[3][0]=-0.5;
    m_fVertices[4][0]=-0.5;
    m_fVertices[5][0]=0.5;
    m_fVertices[6][0]=0.5;
    m_fVertices[7][0]=0.5;
    m_fVertices[0][1]=0.25;
    m_fVertices[1][1]=0.25;
    m_fVertices[2][1]=-0.25;
    m_fVertices[3][1]=-0.25;
    m_fVertices[4][1]=0.25;
    m_fVertices[5][1]=0.25;
    m_fVertices[6][1]=-0.25;
    m_fVertices[7][1]=-0.25;
    m_fVertices[0][2]=-15;
    m_fVertices[1][2]=-15;
    m_fVertices[2][2]=-15;
    m_fVertices[3][2]=-15;
    m_fVertices[4][2]=15;
    m_fVertices[5][2]=15;
    m_fVertices[6][2]=15;
    m_fVertices[7][2]=15;
    }*/
}

/*---------------------------------------------------------------------------*/
int CMurH::iGetNbFaces()
{
    return m_iNbFaces;
}

/*---------------------------------------------------------------------------*/
int CMurH::iGetNbVertices(int _iFace)
{
    return m_iNbVertices[_iFace];
}

/*---------------------------------------------------------------------------*/
void CMurH::vGetVertex(int _iFace, int _iVertex, CVector3* _poVect)
{
    _poVect->vSet( m_fVertices[m_iFaces[_iFace][_iVertex]][0],
            m_fVertices[m_iFaces[_iFace][_iVertex]][1],
            m_fVertices[m_iFaces[_iFace][_iVertex]][2] );
}

/*---------------------------------------------------------------------------*/
void CMurH::vGetSideColor(int _face, CVector3* _poColor)
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
    if (m_oPosition.fGetZ()<-10)
        _poColor->vSet(1.0, 0.0, 0.0);
}

int CMurH::iIsPicked(CVector3* _poOrigin)
{

}

void CMurH::vGetSpeed(CVector3 *_oSpeed)
{

}

void CMurH::vSetSpeed(CVector3 *_oSpeed)
{

}

int CMurH::iGetDurability()
{

}

void CMurH::vSetDurability(int _iDurability)
{

}
