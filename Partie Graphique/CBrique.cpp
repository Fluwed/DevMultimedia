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
    if (iGetCurFace()!=-1 && iGetCurFace()==_face)
        _poColor->vSet(1.0, 1.0, 1.0);
}

int CBrique::iIsPicked(CVector3* _poOrigin, CVector3* _poDir, CVector3* _poIntersection, int* _iPickedFace)
{
    int iStatus = 0;
    int iPickedFace = -1; // -1 will mean "not initialized". Will then take the
    // value of the index of the side of the cube.
    float fClosestDistance = 1.5; // Something close to infinity.
    CVector3 oClosestIntersection; // Last found closest intersection


    // For all faces of the cube
    for(int i=0;i<6;i++)
    {
        // Compute the normal to the plane
        CVector3 ptO, ptA, ptB; // Vertices that we will use to define the vertors
        CVector3 OA, OB, n; // Vectors
        int iA = m_iFaces[i][0];
        int iO = m_iFaces[i][1];
        int iB = m_iFaces[i][2];
        float k;

        ptO = m_oPosition + CVector3(m_fVertices[iO][0], m_fVertices[iO][1], m_fVertices[iO][2]);
        ptA = m_oPosition + CVector3(m_fVertices[iA][0], m_fVertices[iA][1], m_fVertices[iA][2]);
        ptB = m_oPosition + CVector3(m_fVertices[iB][0], m_fVertices[iB][1], m_fVertices[iB][2]);

        OA = ptA - ptO;
        OB = ptB - ptO;
        n.vCross(OA, OB);

        // Vector from the Start point of the ray to the origin of the current plane.
        CVector3 SO = ptO - *_poOrigin;

        // Compute the numerator and denominator of the division for the value of k.
        float num = SO.fDot(n);
        float den = _poDir->fDot(n);

        // Avoid division by zero (In our case, meaning that the ray is parallel to the plane,
        // thus without intersection)
        if(qAbs(den) < 1e-8)
            continue;
        k = num / den; // parameter t of the intersection between the line and the plane

        // We only take the positive values of k, since we have a ray (we don't want values
        // of k behind the starting point of the ray)
        if(k > 0)
        {
            CVector3 ptM;

            // Compute the coordinates of the potential intersection according to the
            // parametric equation of the ray.
            ptM.vSet(_poOrigin->fGetX() + _poDir->fGetX() * k,
                     _poOrigin->fGetY() + _poDir->fGetY() * k,
                     _poOrigin->fGetZ() + _poDir->fGetZ() * k);

            // Validation of the intersecion: make sure it is in the square defined by the two vectors.
            // by projecting the intersection on each vetors.
            CVector3 OM = ptM - ptO;
            float p1 = OM.fDot(OA) / OA.fNorm();
            float p2 = OM.fDot(OB) / OB.fNorm();

            if((p1 > 0) && (p1 < 1) && (p2 > 0) && (p2 < 1))
            {
                float distance = _poOrigin->fDistance(ptM);

                if(distance < fClosestDistance)
                {
                    iPickedFace = i;
                    fClosestDistance = distance;
                    oClosestIntersection.vSet(ptM);
                }
            }
        }
    }

    // If something is found, set the variables to return
    if(iPickedFace > -1)
    {
        _poIntersection->vSet(oClosestIntersection);
        *_iPickedFace = iPickedFace;
        iStatus = 1;
        //qDebug()<<iStatus;
        //qDebug()<<"Dist :"<<fClosestDistance;
    }
    return iStatus;

}

void CBrique::GetSpeed(CVector3 *_oSpeed)
{

}

void CBrique::SetSpeed(CVector3 *_oSpeed)
{

}

