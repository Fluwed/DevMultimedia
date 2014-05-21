#ifndef CObject_H
#define CObject_H

#include "CVector3.h"

class CObject
{
private:


protected:
    CVector3       m_oPosition;     // Position de l'objet (x,y,z)

public:
    int             m_iId;          // Id de l'objet
    int             m_iDurability;  // Durée de vie de l'objet (surtout pour les briques)

    CObject();
    CObject(int _iId);

    int             iGetID();                                                       // Getter de m_iId
    void            vSetPosition(CVector3* _oPos);                                  // Setter de m_oPosition
    void            vGetPosition(CVector3* _poPos);                                 // Getter de m_oPosition
    virtual int     iGetNbFaces() = 0;                                              // Permet d'obtenir le nombre de face de l'objet
    virtual int     iGetNbVertices(int _iFace) = 0;                                 // Permet d'obtenir le nombre de vertex de l'objet
    virtual void    vGetVertex(int _iFace, int _iVertex, CVector3* _poVect) = 0;    // Permet d'obtenir la position d'un vertex associer à une face
    virtual void    vGetSideColor(int _face, CVector3* _poColor) = 0;               // Permet d'obtenir la couleur d'une face de l'objet
    virtual int     iIsPicked(CVector3* _poOrigin)=0;                               // Permet de définir la HitBox de l'objet
    virtual void    vGetSpeed(CVector3 *_oSpeed) = 0;                               // Getter de la vitesse de l'objet
    virtual void    vSetSpeed(CVector3 *_oSpeed) = 0;                               // Setter de la vitesse de l'objet
    virtual void    vSetDurability(int _iDurability) = 0;                           // Setter de  m_iDurability
    virtual int     iGetDurability() = 0;                                           // Getter de m_iDurability

};

#endif // CObject_H
