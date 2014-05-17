#include "CControl.h"
#include "CBrique.h"
#include "CSphere.h"
#include <qdebug.h>
#include <QTimer>

/*---------------------------------------------------------------------------*/
CControl::CControl(CModel* _model)
{
    m_poModel = _model;
    is_moving_left=false;
    is_moving_right=false;
    m_fSpeed = 0.6;
    m_iLife=3;
    m_bStart=false;
    m_bStickySphere=true;
}


/*---------------------------------------------------------------------------*/
CControl::~CControl()
{
}

/*-------------------------------GETTER--------------------------------------*/
bool CControl::bStickySphere() const
{
    return m_bStickySphere;
}

/*-------------------------------SETTER--------------------------------------*/
void CControl::setBStickySphere(bool bStickySphere)
{
    m_bStickySphere = bStickySphere;
}

/*-------------------------------GETTER--------------------------------------*/
bool CControl::bStart() const
{
    return m_bStart;
}

/*-------------------------------SETTER--------------------------------------*/
void CControl::setBStart(bool bIsStarted)
{
    m_bStart = bIsStarted;
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

/*------------------ MISE EN PLACE DE L'ESPACE DE JEU -----------------------*/
void CControl::vSetGame()
{
    m_poModel->vSetGame();
}

/*--------------------- REMISE A ZERO DE LA SPHERE --------------------------*/
void CControl::vSetNewLife()
{
    m_poModel->vSetLife();
}

/*-------------------- RESPONSABLE DE LA PARTIE HITBOX ----------------------*/
int CControl::iCheckPicked(CVector3 *_poOrigin) // Permet de dire quel cube est sélectionné
{
    int isPicked=-1;
    bool touched=false;
    CObject* Sphere;
    CVector3 Speed;
    CVector3 poPos;
    Sphere=m_poModel->poGetObject(5);
    Sphere->vGetPosition(&poPos);

    for (int i=6;i<m_poModel->iGetNbObjects();i++)
    {
        CObject* Brique;
        Brique=m_poModel->poGetObject(i);
        if (Brique->iIsPicked(_poOrigin)==1)
        {
            isPicked=Brique->iGetID();
            if(touched==false)
            {
                Sphere->vGetSpeed(&Speed);
                Speed.vSetZ(-Speed.fGetZ());
                Sphere->vSetSpeed(&Speed);
            }

            CVector3 poBriqpos;
            Brique->vGetPosition(&poBriqpos);

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
            touched=true;
        }

    }
    touched = false;
    /*-------------------------     PALET    -------------------------------------*/
    CObject* Palet;

    Palet=m_poModel->poGetObject(4);

    if (Palet->iIsPicked(_poOrigin)==1)
    {
        Sphere->vGetSpeed(&Speed);

        /*------  INTERACTION SELON LA POSITION DE LA SPHERE SUR LE PALET  -------*/
        float iCoef;
        float iSphereSpeed;
        CVector3 poPalet;

        Palet->vGetPosition(&poPalet);
        if (poPalet.fGetY()==0)
        {
            iCoef = 0;
        }
        else
        {
            iCoef =(poPalet.fGetY() - _poOrigin->fGetY())/poPalet.fGetY(); //iCoef entre -1 et 1 mais il existe quelque cas où ce n'est pas vrai on utilise donc des if
        }
        iCoef = iCoef*2;

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
        if (iCoef<=0.2 && iCoef>=-0.2)
        {
            Speed.vSetZ(m_fSpeed/1.5);
        }


        Speed.vSetY(-iCoef);
        Sphere->vSetSpeed(&Speed);


    }
    /*---------------------------------  MUR  ------------------------------------*/

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
        m_iLife=m_iLife-1;
        vSetNewLife();
        m_bStickySphere=true;
        m_bStart=true;
    }
    return isPicked;
}

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
void CControl::vStart()
{
    m_poModel->vSetSpeed(m_fSpeed);
}

/*----------------------------------------------------------------------------*/
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

