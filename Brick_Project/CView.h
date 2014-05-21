#ifndef CView_H
#define CVIew_H

#include <QWidget>
#include "CGLArea.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSound>
#include <CWebcam.h>

class CView : public QWidget
{
    Q_OBJECT

private:
    bool            m_bScoreVisible;    // Permet de dire si les highscore sont visibles
    bool            m_bPause;           // Permet de dire si le jeu est sur pause
    bool            m_bMusic;           // Permet de dire si la musique est sur pause
    CModel*         m_poModel;          // Pointeur vers le Model
    CControl*       m_poCtrl;           // Pointeur vers le Controleur
    CGLArea*        m_poGlArea;         // Pointeur vers OpenGL
    QLabel*         m_poScore;          // Label affichant le Score
    QLabel*         m_poLife;           // Label affichant les viex
    QLabel*         m_poInfo;           // Label affichant les messages d'information (décompte, score final)
    QTimer*         m_poClock;          // Timer responsable du départ de la balle
    QVBoxLayout*    m_poVLayout;        // Layout OpenGL et Informations
    QVBoxLayout*    m_poGameScore;      // Layout Secondaire
    QVBoxLayout*    m_poHighScore;      // Layout des HighScores
    QHBoxLayout*    m_poHLayout;        // Layout Principale
    QPushButton*    m_poMusicBtn;       // Bouton pour (dés)activer la musique
    QPushButton*    m_poSaveBtn;        // Bouton permettant de sauvegarder son score
    QDialog*        m_poSave;           // Fenêtre permettant de sauvegarder son score en fin de partie
    QLineEdit*      m_poLineEdit;       // Permet de récupérer le nom de l'utilisateur en fin de partie
    int             m_iTimer;           // Décompteur pour m_poClock
    int             m_iFinalScore;      // Score quand le nombre de vie tombe à zéro
    CWebcam*        m_poWebcam;         // Widget affichant la Webcam et gérant le tracking
    QTimer*         m_poTimer;          // Timer gérant la gestion dynamique des mouvement, niveaux, scores etc...


    
public:
    CView(QWidget *parent = 0);
    ~CView();

    void            vSetControl(CControl* _oCtrl);      // Setter du Controleur
    void            vSetModel(CModel* _poMdl);          // Setter du Model
    void            keyPressEvent(QKeyEvent *_event);   // Permet de gérer l'appuie d'une touche du clavier
    void            keyReleaseEvent(QKeyEvent *_event); // Permet de gérer le relachement d'une touche du clavier

public slots:
    void            vSetGame();                         // Permet d'afficher les mur et le palet
    void            vStartGame();                       // Permet de lancer la partie
    void            vUpdateTime();                      // Permet le décompte à l'appuie de la touche E pour lancer la partie
    void            vUpdateGame();                      // Permet d'actualiser les scores en temps réel, dire au controleur de changer de niveau etc..
    void            vHighScore();                       // Permet d'afficher les HighScores
    void            vSave();                            // Permet de sauvegarder un HighScore dans le Model par l'utilisateur
    void            vSaveScore();                       // Permet d'afficher le HighScore précédent directement dans le layout concerné
    void            vTracking();                        // Permet de lancer le tracking et d'afficher le layout correspondant
    void            vPause();                           // Permet de mettre le jeu en pause
    void            vSetMusic();                        // Permet de mettre en pause la musique
};

#endif // CVIew_H













