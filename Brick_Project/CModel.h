#ifndef CModel_H
#define CModel_H

#include "CObject.h"
#include <qvector.h>
#include <QStringList>

class CModel
{
private:
    QVector<CObject*>   m_oDatas;      // Tableau d'objet contenant tout ce qui est crée par OpenGL
    QStringList         m_oHighscore;  // Tableau regroupant les HighScores

public:
    CModel();
    ~CModel();

    int                 iGetNbObjects();                                        // Permet de savoir la taille de m_oDatas
    void                vSetGame();                                             // Permet d'ajouter à m_oDatas les Murs, le palet et la sphère
    void                vDel(int _iId);                                         // Permet de supprimer un CObjet de m_oDatas avec son Id
    void                vLoadLevel(int _iLvl);                                  // Permet de mettre les briques correspondant à un niveau dans m_oDatas
    void                vSetLife();                                             // Permet de positionner la sphère juste au dessus du palet et de placer ceux-ci au centre
    void                vSetSpeed(float _fSpeed);                               // Permet de donner une vitesse à la sphère
    void                vLoadHighScore();                                       // Permet de charger les highscores à partir d'un fichier .txt
    void                vSave(QString _otText, int _iScore);                    // Permet de sauvegarder un score dans le .txt
    void                vResetLevel();                                          // Permet d'effacer toutes les briques contenu dans m_oDatas
    QStringList         oHighscore() const;                                     // Getter de m_oHighScore
    CObject*            poGetObject(int _iIndex);                               // Setter de m_oHighScore
};

#endif // CModel_H
