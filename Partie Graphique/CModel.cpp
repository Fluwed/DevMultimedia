#include "CModel.h"
#include "CBrique.h"
#include "CMurH.h"
#include "CMurV.h"
#include "CPalet.h"
#include "CSphere.h"
#include <qDebug.h>
#include <QTimer>


/*---------------------------------------------------------------------------*/
CModel::CModel()
{
}

/*---------------------------------------------------------------------------*/
CModel::~CModel()
{
    // Remove everything
    while(m_oDatas.count() > 0)
    {
        int iIndex = m_oDatas.count() - 1;

        CObject* poCurrent = m_oDatas[iIndex];
        m_oDatas.remove(iIndex);
        delete poCurrent;
    }
}

/*---------------------------------------------------------------------------*/
void CModel::vSetGame()
{
    // Ajout des 4 murs dans le QVector et du Palet

    CObject* poMur = new CMurH(); // Mur de droite / Position 0 dans le model
    CObject* poMur1 = new CMurH(); // Mur de gauche / Position 1 dans le model
    CObject* poMur2 = new CMurV(); // Mur du haut / Position 2 dans le model
    CObject* poMur3 = new CMurV(); // Mur du bas / Position 3 dans le model
    CObject* poPalet = new CPalet(); // Palet / Position 4 dans le model
    CObject* poSphere = new CSphere(); // Sphere / Position 5 dans le model

    CVector3 oPosMur(0,0,18);
    CVector3 oPosMur1(0,0,-15);
    CVector3 oPosMur2(0,26,0);
    CVector3 oPosMur3(0,-26,0);
    poMur->vSetPosition(&oPosMur);
    poMur1->vSetPosition(&oPosMur1);
    poMur2->vSetPosition(&oPosMur2);
    poMur3->vSetPosition(&oPosMur3);

    m_oDatas.append(poMur);
    m_oDatas.append(poMur1);
    m_oDatas.append(poMur2);
    m_oDatas.append(poMur3);

    CVector3 oPosPalet(0,0,-12);
    poPalet->vSetPosition(&oPosPalet);

    CVector3 oPosSphere(0,0,-100);
    poSphere->vSetPosition(&oPosSphere);

    m_oDatas.append(poPalet);
    m_oDatas.append(poSphere);

}

/*---------------------------------------------------------------------------*/
void CModel::vDel(int _iId)
{
    bool found = false;
    int iIndex = 0;

    // Look for the needed object and remove it.
    while( (!found) && (iIndex < m_oDatas.size()))
    {
        CObject* poCurrent = m_oDatas[iIndex];
        if(poCurrent->iGetID() == _iId)
        {
            m_oDatas.remove(iIndex);
            delete poCurrent;
            found = true;
        }
        iIndex++;
    }
}

/*---------------------------------------------------------------------------*/
int CModel::iGetNbObjects()
{
    return m_oDatas.count();
}

/*---------------------------------------------------------------------------*/
CObject* CModel::poGetObject(int _iIndex)
{
    return m_oDatas[_iIndex];
}

/*---------------------------------------------------------------------------*/
float CModel::fGetRandom()
{
    int High = 5.0;
    int Low = -5.0;
    float Div = 3.0;

    float result = ((float) (qrand() % ((High + 1) - Low) + Low))/Div;

    return result;
}

/*---------------------------------------------------------------------------*/
void CModel::vNewPos(CVector3 *_poPos, int _face)
{
    switch(_face)
    {
    case 0:
        _poPos->vSetZ(_poPos->fGetZ()-1);
        break;
    case 1:
        _poPos->vSetX(_poPos->fGetX()+1);
        break;
    case 2:
        _poPos->vSetY(_poPos->fGetY()+1);
        break;
    case 3:
        _poPos->vSetX(_poPos->fGetX()-1);
        break;
    case 4:
        _poPos->vSetY(_poPos->fGetY()-1);
        break;
    case 5:
        _poPos->vSetZ(_poPos->fGetZ()+1);
        break;
    }
}

/*---------------------------------------------------------------------------*/

void CModel::vLoadLevel(int _iLvl)
{
    switch(_iLvl)
    {
    case 1:
        for (int i=0;i<10;i++)
        {
            CObject* poObj = new CBrique(i);
            CVector3 oPos(0,-22.5+5*i,15);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }
        for (int i=10;i<20;i++)
        {
            CObject* poObj = new CBrique(i);
            CVector3 oPos(0,-22.5+5*i-50,13);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }
        break;
    case 2:
        for (int i=0;i<10;i++)
        {
            CObject* poObj = new CBrique(i);
            CVector3 oPos(0,-22.5+5*i,11);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }
        for (int i=10;i<16;i++)
        {
            CObject* poObj = new CBrique(i);
            CVector3 oPos(0,-12.5+5*i-50,13);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }
        for (int i=16;i<20;i++)
        {
            CObject* poObj = new CBrique(i);
            CVector3 oPos(0,-7.5+5*i-80,15);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }
        break;
    case 3:
        for (int i=0;i<10;i++)
        {
            CObject* poObj = new CBrique(i,2);
            CVector3 oPos(0,-22.5+5*i,15);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }
        for (int i=10;i<20;i++)
        {
            CObject* poObj = new CBrique(i,2);
            CVector3 oPos(0,-22.5+5*i-50,7);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }
        for (int i=20;i<23;i++)
        {
            CObject* poObj = new CBrique(i,2);
            CVector3 oPos(0,-22.5,13-2*i+40);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }
        for (int i=23;i<26;i++)
        {
            CObject* poObj = new CBrique(i,2);
            CVector3 oPos(0,22.5,13-2*i+46);
            poObj->vSetPosition(&oPos);
            m_oDatas.append(poObj);
        }

        CObject* poObj = new CBrique(26,0);
        CVector3 oPos(0,-10,12.5);
        poObj->vSetPosition(&oPos);
        m_oDatas.append(poObj);
        CObject* poObj2 = new CBrique(27,0);
        CVector3 oPos2(0,-10,10);
        poObj2->vSetPosition(&oPos2);
        m_oDatas.append(poObj2);
        CObject* poObj3 = new CBrique(28,0);
        CVector3 oPos3(0,-15,11.25);
        poObj3->vSetPosition(&oPos3);
        m_oDatas.append(poObj3);
        CObject* poObj4 = new CBrique(29,0);
        CVector3 oPos4(0,-5,11.25);
        poObj4->vSetPosition(&oPos4);
        m_oDatas.append(poObj4);

        CObject* poObj5 = new CBrique(30,3);
        CVector3 oPos5(0,10,12.5);
        poObj5->vSetPosition(&oPos5);
        m_oDatas.append(poObj5);
        CObject* poObj6 = new CBrique(31);
        CVector3 oPos6(0,10,10);
        poObj6->vSetPosition(&oPos6);
        m_oDatas.append(poObj6);
        CObject* poObj7 = new CBrique(32,4);
        CVector3 oPos7(0,15,11.25);
        poObj7->vSetPosition(&oPos7);
        m_oDatas.append(poObj7);
        CObject* poObj8 = new CBrique(33,5);
        CVector3 oPos8(0,5,11.25);
        poObj8->vSetPosition(&oPos8);
        m_oDatas.append(poObj8);


        break;
    }
}

void CModel::vSetLife()
{
    CObject* poSphere; // Sphere / Position 5 dans le model
    CObject* poPalet;

    poPalet=poGetObject(4);
    poSphere=poGetObject(5);

    CVector3 oPosPalet(0,0,0);
    poPalet->vGetPosition(&oPosPalet);

    CVector3 oPosSphere(0,0,0);
    oPosSphere.vSetY(oPosPalet.fGetY());
    oPosSphere.vSetZ(-10.4);
    poSphere->vSetPosition(&oPosSphere);
    vSetSpeed(0.0);
}

void CModel::vSetSpeed(float _fSpeed)
{
    CObject* poSphere;
    poSphere=poGetObject(5);
    CVector3 oSpeedSphere(0,0,_fSpeed/2);
    poSphere->vSetSpeed(&oSpeedSphere);
}
