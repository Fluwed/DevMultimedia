#include "CControl.h"
#include "CBrique.h"
#include "CSphere.h"
#include <qdebug.h>
#include <QTimer>
#include <QSound>

/*---------------------------------------------------------------------------*/
CControl::CControl(CModel* _model)
{
    m_poModel = _model;
    is_moving_left=false;
    is_moving_right=false;
    m_fSpeed = 0.6;
    m_iLife=3;
    m_bStickySphere=true;
    m_iScore=0;
    m_iLvl=1;
    m_iDifficulty=1;
    m_poEndSound = new QSound("End.wav");
    m_poSound = new QSound("LvL.wav");
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
                QSound::play("Explosion.wav");
                m_iScore=m_iScore+10;
            }
            else
            {
                int Durability;
                Durability=Brique->iGetDurability();
                Brique->vSetDurability(Durability-1);
                m_iScore=m_iScore+5;
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


        Speed.vSetY(iCoef);
        Sphere->vSetSpeed(&Speed);
        QSound::play("Bounce.wav");
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

    if (m_poSound->isFinished())
    {
        m_poEndSound->stop();
        m_poSound->play();
        m_poSound->setLoops(99);
    }
}

/*----------------------------------------------------------------------------*/
void CControl::timerEvent()
{
    {
        if (is_moving_left)
        {
            palet=m_poModel->poGetObject(4);
            palet->vGetPosition(&oPos);
            if (oPos.fGetY()>-22.4)
            {
                oPos.vSetY(oPos.fGetY()-0.75);
            }
            oPos.vSetZ(oPos.fGetZ());
            palet->vSetPosition(&oPos);
        }

        if (is_moving_right)
        {
            palet=m_poModel->poGetObject(4);
            palet->vGetPosition(&oPos);
            if (oPos.fGetY()<22.4)
            {
                oPos.vSetY(oPos.fGetY()+0.75);
            }
            oPos.vSetZ(oPos.fGetZ());
            palet->vSetPosition(&oPos);
        }

    }
}

/*---------------------------------------------------------------------------*/
void CControl::vResetGame()
{
    m_fSpeed = 0.6;
    m_iLife=3;
    m_bStickySphere=true;
    m_iScore=0;
    m_iLvl=1;
    m_poSound->stop();
    m_poEndSound->play();
    m_poModel->vResetLevel();
    m_poModel->vLoadLevel(m_iLvl);
}

/*---------------------------------------------------------------------------*/
void CControl::vLevelFinished()
{
    if (m_poModel->iGetNbObjects()==6)
    {
        vSetNewLife();
        m_fSpeed=m_fSpeed+0.1;
        m_bStickySphere=true;
        m_poModel->vLoadLevel(m_iLvl);
        m_iLvl=m_iLvl+1;
        if(m_iLvl==5)
        {
            m_iLvl=1;
            m_fSpeed=m_fSpeed+0.2;
        }
    }

}

/*---------------------------------------------------------------------------*/
QStringList CControl::vLoadHighScore()
{
    m_poModel->vLoadHighScore();
    return m_poModel->oHighscore();
}

/*---------------------------------------------------------------------------*/
void CControl::vSave(QString _oText, int _iScore)
{
    m_poModel->vSave(_oText,_iScore);
}

/*---------------------------------------------------------------------------*/
void CControl::vTrackPalet(float _X)
{
    // _X Va de 0(Tout à droite) à 250
    float result;
    palet=m_poModel->poGetObject(4);
    palet->vGetPosition(&oPos);
    _X=_X/250;
    result=-44.8*_X+22.4;
    oPos.vSetY(result);
    palet->vSetPosition(&oPos);
}
