#ifndef CControl_H
#define CControl_H

#include "CModel.h"
#include <QSound>

class CControl
{
private:
    CModel*         m_poModel;      // Pointeur vers le Model
    float           m_fSpeed;       // Vitesse initiale de la sphère (difficulté
    int             m_iLvl;         // Numéro de niveau à charger
    int             m_iDifficulty;  // Difficulté (augmente à chaque série de 3 niveaux
    QSound*         m_poSound;      // Musique de Jeu
    QSound*         m_poEndSound;   // Musique de fin de partie

public:
    CControl(CModel *_model);       // Constructeur
    ~CControl();                    // Déconstructeur

    int             m_iScore;           // Score de la partie
    int             m_iLife;            // Vie de la partie
    bool            bIs_moving_left;    // Indique si le palet doit allez a gauche (Controle au clavier)
    bool            bIs_moving_right;   // Indique si le palet doit allez a droite (Controle au clavier)
    bool            m_bStickySphere;    // Indique si la sphère doit coller au palet ou pas
    CObject*        m_poPalet;          // Pointeur vers le Palet
    CVector3        m_oPos;             // Vecteur de position servant dans quelque fonction


    int             iCheckPicked(CVector3* _poOrigin);      // Fonction responsable de gérer les collisions de la sphère
    bool            bStickySphere() const;                  // Getter de m_bStickySphere
    void            setBStickySphere(bool bStickySphere);   // Setter de m_bStickySphere
    int             fSpeed();                               // Getter de m_fSpeed
    void            setFSpeed(int fSpeed);                  // Setter de m_fSpeed
    void            vTimerEvent();                          // Gère les mouvement du palet en fonction des bool bIs_moving_
    void            vSetGame();                             // Met en place le jeu (Mur/Palet/Sphère)
    void            vMovePalet(int Key, bool pressed);      // Attribue les valeur au bool bIs_moving_ selon les touches du clavier appuyées
    void            vStart();                               // Donne une vitesse à la sphère et lance la musique du jeu
    void            vSetNewLife();                          // Permet de lancer la méthode associer de la classe Model
    void            vResetGame();                           // Permet de remettre à zéro le jeu (game over)
    void            vLevelFinished();                       // Permet de générer un nouveau niveau
    void            vSave(QString text, int _iScore);       // Permet de sauvegarder ces scores
    void            vTrackPalet(float _X);                  // Permet de bouger le palet avec la méthode de tracking
    void            vPauseMusic();                          // Permet de mettre sur pause la musique du jeu
    void            vResume();                              // Permet de remettre la musique
    QStringList     vLoadHighScore();                       // Permet de charger les scores enregistrés précédemment
};

#endif // CControl_H
