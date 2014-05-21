#include "CSphere.h"
#include <qmath.h>


#define k_PI        ((double)3.1415926535897932384626433832795)	/* PI number */
#define k_2PI       ((double)(k_PI + k_PI))	/* 2 PI */
#define MOUSE_FACTOR ((double)0.005)


/*---------------------------------------------------------------------------*/
CSphere::CSphere()
{
    m_iId=-3;
    vGenerateData();
    m_oSpeed.vSet(0.0,0.0,0.0);
}

/*---------------------------------------------------------------------------*/
CSphere::CSphere(int _id) : CObject(_id)
{
    vGenerateData();
}


/*---------------------------------------------------------------------------*/
CSphere::~CSphere()
{
    m_oVertices.clear();
    m_oFaces.clear();
}

/*---------------------------------------------------------------------------*/
int CSphere::iGetNbFaces()
{
    return m_oFaces.size();
}

/*---------------------------------------------------------------------------*/
int CSphere::iGetNbVertices(int _iFace)
{
    return 3;
}

/*---------------------------------------------------------------------------*/
void CSphere::vGetVertex(int _iFace, int _iVertex, CVector3* _poVect)
{
    int index = 0;

    switch(_iVertex)
    {
    case 0:
    default:
        index = m_oFaces[_iFace].fGetX();
        break;
    case 1:
        index = m_oFaces[_iFace].fGetY();
        break;
    case 2:
        index = m_oFaces[_iFace].fGetZ();
        break;
    }


    _poVect->vSet( m_oVertices[index].fGetX(),
                   m_oVertices[index].fGetY(),
                   m_oVertices[index].fGetZ() );
}

/*---------------------------------------------------------------------------*/
void CSphere::vGetSideColor(int _face, CVector3* _poColor)
{
    _poColor->vSet(0.0, 1.0, 1.0);
}


/*---------------------------------------------------------------------------*/
int CSphere::iIsPicked(CVector3* _poOrigin)
{
    return 0;
}


///////////////////////////////////////////////////////////
//  Approximation icosaedrale  de sphere
///////////////////////////////////////////////////////////

#define X .525731112119133606
#define Z .850650808352039932

static float sommets[12][3] = {
    {-X, 0, Z},
    {X, 0, Z},
    {-X, 0, -Z},
    {X, 0, -Z},
    {0, Z, X},
    {0, Z, -X},
    {0, -Z, X},
    {0, -Z, -X},
    {Z, X, 0},
    {-Z, X, 0},
    {Z, -X, 0},
    {-Z, -X, 0} };

static int sindex[20][3] = {
    {0, 4, 1},
    {0, 9, 4},
    {9, 5, 4},
    {4, 5, 8},
    {4, 8, 1},
    {8, 10, 1},
    {8, 3, 10},
    {5, 3, 8},
    {5, 2, 3},
    {2, 7, 3},
    {7, 10, 3},
    {7, 6, 10},
    {7, 11, 6},
    {11, 0, 6},
    {0, 1, 6},
    {6, 1, 10},
    {9, 0, 11},
    {9, 11, 2},
    {9, 2, 5},
    {7, 2, 11}, };

/*---------------------------------------------------------------------------*/
void CSphere::vPousserProfondeur(float v[3])
{
    float d = qSqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    v[0]=v[0]/d;
    v[1]=v[1]/d;
    v[2]=v[2]/d;
}

/*---------------------------------------------------------------------------*/
void CSphere::vComputeTriangle(float* v1, float *v2, float *v3, int n)
{
    int xyz;
    float v[3][3];

    if(n==0)
    {
        // normal : (v1[0], v1[1], v1[2])
        // vertex : (v1[0], v1[1], v1[2])
        m_oVertices.append(CVector3(v1[0], v1[1], v1[2]));
        // normal : (v2[0], v2[1], v2[2])
        // vertex : (v2[0], v2[1], v2[2])
        m_oVertices.append(CVector3(v2[0], v2[1], v2[2]));
        // normal : (v3[0], v3[1], v3[2])
        // vertex : (v3[0], v3[1], v3[2])
        m_oVertices.append(CVector3(v3[0], v3[1], v3[2]));

        int taille = m_oVertices.size();
        m_oFaces.append(CVector3(taille-3, taille-2, taille-1));
    }
    else
    {
        for(xyz=0; xyz<3; xyz++)
        {
            v[0][xyz]=(v1[xyz]+v2[xyz])/2;
            v[1][xyz]=(v1[xyz]+v3[xyz])/2;
            v[2][xyz]=(v3[xyz]+v2[xyz])/2;
        }

        vPousserProfondeur(v[0]);
        vPousserProfondeur(v[1]);
        vPousserProfondeur(v[2]);

        vComputeTriangle(v1, v[0], v[1], n-1);
        vComputeTriangle(v[0], v2, v[2], n-1);
        vComputeTriangle(v[0], v[1], v[2], n-1);
        vComputeTriangle(v[1], v[2], v3, n-1);
    }
}

/*---------------------------------------------------------------------------*/
void CSphere::vGenerateData(void)
{
    for (int i = 0; i <20; i++)
    {
        vComputeTriangle(sommets[sindex[i][2]], sommets[sindex[i][1]], sommets[sindex[i][0]], 3);
    }

}

/*---------------------------------------------------------------------------*/
void CSphere::vGetSpeed(CVector3* _oSpeed)
{
    _oSpeed->vSetX(m_oSpeed.fGetX());
    _oSpeed->vSetY(m_oSpeed.fGetY());
    _oSpeed->vSetZ(m_oSpeed.fGetZ());
}

/*---------------------------------------------------------------------------*/
void CSphere::vSetSpeed(CVector3* _oSpeed)
{
    m_oSpeed.vSetX(_oSpeed->fGetX());
    m_oSpeed.vSetY(_oSpeed->fGetY());
    m_oSpeed.vSetZ(_oSpeed->fGetZ());
}

/*---------------------------------------------------------------------------*/
int CSphere::iGetDurability()
{

}

/*---------------------------------------------------------------------------*/
void CSphere::vSetDurability(int _iDurability)
{

}
