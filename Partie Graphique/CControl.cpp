#include "CControl.h"
#include "CBrique.h"
#include <qdebug.h>

/*---------------------------------------------------------------------------*/
CControl::CControl(CModel* _model)
{
    m_poModel = _model;
}


/*---------------------------------------------------------------------------*/
CControl::~CControl()
{
}


/*---------------------------------------------------------------------------*/
void CControl::vAddObject(int _iId)
{
    m_poModel->vAdd(_iId);
    vResetPicked();
}

/*---------------------------------------------------------------------------*/
void CControl::vDelObject()
{
    int id;
    for (int i=0;i<m_poModel->iGetNbObjects();i++)
    {
        if(m_poModel->poGetObject(i)->iGetCurFace()!=-1)
        {
            id=m_poModel->poGetObject(i)->iGetID();
            m_poModel->vDel(id);
        }
    }
}

/*---------------------------------------------------------------------------*/
int CControl::iCheckPicked(CVector3 *_poOrigin, CVector3 *_poDir) // Permet de dire quel cube est sélectionné
{
    int isPicked=0;
    float distance=100000;
    for (int i=0;i<m_poModel->iGetNbObjects();i++)
    {
        CObject* Cube = new CBrique();
        CVector3 poInter;
        int iFace;
        Cube=m_poModel->poGetObject(i);
        if (Cube->iIsPicked(_poOrigin, _poDir, &poInter, &iFace)==1)
        {
            if(poInter.fDistance(*_poOrigin)<distance)
            {
                distance=poInter.fDistance(*_poOrigin);
                vResetPicked();
                isPicked=Cube->iGetID();
                Cube->vSetPicked(iFace);
                //delete Cube; //Fait planter l'appli
            }
        }
    }
    return isPicked;
}

/*----------------------------------------------------------------------------*/
void CControl::vResetPicked() // Permet de déselectionner tout les cubes
{
    for (int i=0;i<m_poModel->iGetNbObjects();i++)
    {
        CObject* Cube = new CBrique();
        Cube=m_poModel->poGetObject(i);
        Cube->vSetPicked(-1);
    }
}


