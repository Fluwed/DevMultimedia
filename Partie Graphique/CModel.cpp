#include "CModel.h"
#include "CBrique.h"
#include "CMurH.h"
#include "CMurV.h"
#include "CPalet.h"
#include "CSphere.h"
#include <qDebug.h>


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
void CModel::vAdd(int _iId)
{
    CObject* poObj = new CBrique(_iId);
    CVector3 Pos;
    int _face;

    // Création de deux lignes de briques
    if(m_oDatas.size() == 0)
    {
        CVector3 oPos(0,-23,15);
        poObj->vSetPosition(&oPos);
    }
    else if (_iId<10)
    {
        CVector3 oPos(0,-23+5*_iId,15);
        poObj->vSetPosition(&oPos);
    }
    else if (_iId>=10 && _iId<20)
    {
        CVector3 oPos(0,-23+5*_iId-50,13);
        poObj->vSetPosition(&oPos);
    }
    else
    {
        CVector3 oPos(0,-23+5*_iId-100,13-2*(_iId-20));
        poObj->vSetPosition(&oPos);
    }

    if (_iId<1) // Ajout des 4 murs dans le QVector et du Palet
    {
        CObject* poMur = new CMurH();
        CObject* poMur1 = new CMurH();
        CObject* poMur2 = new CMurV();
        CObject* poMur3 = new CMurV();
        CObject* poPalet = new CPalet();
        CObject* poSphere = new CSphere();

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

        CVector3 oPosSphere(0,0,-10);
        poSphere->vSetPosition(&oPosSphere);

        m_oDatas.append(poPalet);
        m_oDatas.append(poSphere);
    }
    m_oDatas.append(poObj);
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

