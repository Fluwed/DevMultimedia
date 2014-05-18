#include "CObject.h"

/*---------------------------------------------------------------------------*/
CObject::CObject()
{
    m_iId = -1;
    m_iDurability = 1;
}

/*---------------------------------------------------------------------------*/
CObject::CObject(int _iId)
{
    m_iId = _iId;
}

/*---------------------------------------------------------------------------*/
int CObject::iGetID()
{
    return m_iId;
}

/*---------------------------------------------------------------------------*/
void CObject::vSetPosition(CVector3* _oPos)
{
    m_oPosition.vSet(*_oPos);
}

/*---------------------------------------------------------------------------*/
void CObject::vGetPosition(CVector3* _poPos)
{
    _poPos->vSet(m_oPosition);
}

