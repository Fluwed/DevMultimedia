#include "CControl.h"
#include "CBrique.h"
#include "CSphere.h"
#include <qdebug.h>
#include <QTimer>

/*---------------------------------------------------------------------------*/
CControl::CControl(CModel* _model)
{
    m_poModel = _model;
    m_fSpeed = 0.6;
}


/*---------------------------------------------------------------------------*/
CControl::~CControl()
{
}

/*---------------------------------------------------------------------------*/
int CControl::fSpeed()
{
    return m_fSpeed;
}

/*---------------------------------------------------------------------------*/
void CControl::setFSpeed(int fSpeed)
{
    m_fSpeed = fSpeed;
}

/*---------------------------------------------------------------------------*/
void CControl::vAddObject()
{
    m_poModel->vAdd();
    m_poModel->vNewLife();
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
    int isPicked=-1;
    float distance=10000;
    CObject* Sphere;
    CVector3 Speed;
    CVector3 poPos;
    Sphere=m_poModel->poGetObject(5);
    Sphere->vGetPosition(&poPos);

    for (int i=6;i<m_poModel->iGetNbObjects();i++)
    {
        CObject* Brique;
        CVector3 poInter;
        int iFace;
        Brique=m_poModel->poGetObject(i);
        if (Brique->iIsPicked(_poOrigin, _poDir, &poInter, &iFace)==1)
        {

            //qDebug()<<poPos.fGetX()<<poPos.fGetY()<<poPos.fGetZ();
            if(poInter.fDistance(*_poOrigin)<distance)
            {
                distance=poInter.fDistance(*_poOrigin);
                vResetPicked();
                isPicked=Brique->iGetID();
                Brique->vSetPicked(iFace);
                Sphere->vGetSpeed(&Speed);
                Speed.vSetZ(-Speed.fGetZ());
                Sphere->vSetSpeed(&Speed);
                if (Brique->iGetDurability()<2)
                {
                    m_poModel->vDel(isPicked);
                }
                else
                {
                    int Durability;
                    Durability=Brique->iGetDurability();
                    Brique->vSetDurability(Durability-1);
                }
            }
        }
    }

    /*-------------------------     PALET    -------------------------------------*/
    CObject* Palet;
    CVector3 poInter;
    int iFace;

    Palet=m_poModel->poGetObject(4);

    if (Palet->iIsPicked(_poOrigin, _poDir, &poInter, &iFace)==1)
    {
        if(poInter.fDistance(*_poOrigin)<distance)
        {
            distance=poInter.fDistance(*_poOrigin);
            vResetPicked();
            isPicked=Palet->iGetID();
            Palet->vSetPicked(iFace);
            Sphere->vGetSpeed(&Speed);

            /*------  INTERACTION SELON LA POSITION DE LA SPHERE SUR LE PALET  -------*/
            float iCoef;
            float iSphereSpeed;
            CVector3 poPalet;

            Palet->vGetPosition(&poPalet);
            iCoef=(poPalet.fGetY() - poInter.fGetY())/poPalet.fGetY(); //iCoef entre -1 et 1 mais il existe quelque cas où ce n'est pas vrai on utilise donc des if

            iCoef=iCoef*2;
            iSphereSpeed=Speed.fGetZ();
            if (iCoef>0.4)
            {
                iCoef=0.4;
            }

            if (iCoef<-0.4)
            {
                iCoef=-0.4;
            }

            if (iCoef<=0)
            {
                Speed.vSetZ(m_fSpeed+iCoef);
            }

            if (iCoef>0)
            {
                Speed.vSetZ(m_fSpeed-iCoef);
            }


            //Speed.vSetZ(-iSphereSpeed);
            Speed.vSetY(-iCoef);
            //qDebug()<<iCoef;
            Sphere->vSetSpeed(&Speed);

        }
    }
    /*----------------------------------------------------------------------------*/

    if (poPos.fGetY()>25)
    {

        Sphere->vGetSpeed(&Speed);
        if (Speed.fGetY()>0)
        {
            Speed.vSetY(-Speed.fGetY());
            Sphere->vSetSpeed(&Speed);
        }
    }
    if (poPos.fGetY()<-25)
    {

        Sphere->vGetSpeed(&Speed);
        if (Speed.fGetY()<0)
        {
            Speed.vSetY(-Speed.fGetY());
            Sphere->vSetSpeed(&Speed);
        }
    }
    if (poPos.fGetZ()>17)
    {
        Sphere->vGetSpeed(&Speed);
        if (Speed.fGetZ()>0)
        {
            Speed.vSetZ(-Speed.fGetZ());
            Sphere->vSetSpeed(&Speed);
        }
    }

    if(poPos.fGetZ()<-14 )
    {
        Sphere->vGetSpeed(&Speed);
        if (Speed.fGetZ()<0)
        {
            Speed.vSetZ(-Speed.fGetZ());
            Sphere->vSetSpeed(&Speed);
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

void CControl::vMovePalet(int Key, bool is_moving)
{

    if (Key==Qt::Key_Q)
    {
        is_moving_left = is_moving;
    }
    if (Key==Qt::Key_D)
    {
        is_moving_right = is_moving;
    }
}

void CControl::vStart()
{
        m_poModel->vSetSpeed(m_fSpeed);
}

void CControl::timerEvent()
{
    {
        if (is_moving_left)
        {
            palet=m_poModel->poGetObject(4);
            palet->vGetPosition(&oPos);
            oPos.vSetY(oPos.fGetY()-0.75);
            oPos.vSetZ(oPos.fGetZ());
            palet->vSetPosition(&oPos);
        }

        if (is_moving_right)
        {
            palet=m_poModel->poGetObject(4);
            palet->vGetPosition(&oPos);
            oPos.vSetY(oPos.fGetY()+0.75);
            oPos.vSetZ(oPos.fGetZ());
            palet->vSetPosition(&oPos);
        }

    }
}

