#include "CControl.h"
#include "CBrique.h"
#include "CSphere.h"
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
    float distance=10000;
    for (int i=6;i<m_poModel->iGetNbObjects();i++)
    {
        CObject* Cube;
        CObject* Sphere;
        CVector3 Speed;
        CVector3 poInter;
        CVector3 poPos;
        int iFace;
        Cube=m_poModel->poGetObject(i);
        Sphere=m_poModel->poGetObject(5);
        Sphere->vGetPosition(&poPos);

        if (Cube->iIsPicked(_poOrigin, _poDir, &poInter, &iFace)==1)
        {
            if(poInter.fDistance(*_poOrigin)<distance)
            {
                distance=poInter.fDistance(*_poOrigin);
                vResetPicked();
                isPicked=Cube->iGetID();
                Cube->vSetPicked(iFace);
                Sphere->GetSpeed(&Speed);

                Speed.vSetZ(-Speed.fGetZ());
                Sphere->SetSpeed(&Speed);
                m_poModel->vDel(isPicked);

                Cube=0;
                delete Cube;
                Sphere=0;
                delete Sphere;
            }
        }
        if (poPos.fGetY()>25)
        {

            Sphere->GetSpeed(&Speed);
            if (Speed.fGetY()>0)
            {
            Speed.vSetY(-Speed.fGetY());
            Sphere->SetSpeed(&Speed);
            }
        }
        if (poPos.fGetY()<-25)
        {

            Sphere->GetSpeed(&Speed);
            if (Speed.fGetY()<0)
            {
            Speed.vSetY(-Speed.fGetY());
            Sphere->SetSpeed(&Speed);
            }
        }
        if (poPos.fGetZ()>17)
        {
            Sphere->GetSpeed(&Speed);
            if (Speed.fGetZ()>0)
            {
            Speed.vSetZ(-Speed.fGetZ());
            Sphere->SetSpeed(&Speed);
            }
        }

        if(poPos.fGetZ()<-14 )
        {
            qDebug()<<" Z :"<<poPos.fGetZ()<< " Y : "<<poPos.fGetY();
            Sphere->GetSpeed(&Speed);
            if (Speed.fGetZ()<0)
            {
            Speed.vSetZ(-Speed.fGetZ());
            Sphere->SetSpeed(&Speed);
            }
        }

        //qDebug()<<" Z :"<<poPos.fGetZ()<< " Y : "<<poPos.fGetY();
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


