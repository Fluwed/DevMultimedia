#ifndef CGLAREA_H
#define CGLAREA_H

#include <QGLWidget>
#include <CVector3.h>
#include <CControl.h>


class CGLArea : public QGLWidget
{
    Q_OBJECT

private:
    CModel*         m_poModel;      // Pointeur vers le Model
    float           m_fAzimuth;     // Angle pour la caméra
    float           m_fElevation;   // Angle pour la caméra
    float           m_fRadius;      // Angle pour la caméra
    CControl*       m_poCtrl;       // Pointeur vers le controleur

public:
    CGLArea(QWidget *parent = 0);
    ~CGLArea();

    void            vSetModel(CModel* _poModel, CControl *_poCtrl); // Setter des pointeur
    QSize           minimumSizeHint() const;                        // Configuration de la taille du widget OpenGL
    QSize           sizeHint() const;                               // Configuration de la taille de widget OpenGL
    void            updateCamera(void);                             // Permet de configurer la caméra d'OpenGL
    void            MoveSphere();                                   // Permet le mouvement de la sphère


protected:
    void            initializeGL();                                 // Initialise OpenGL
    void            paintGL();                                      // Déclenché à chaque UpdateGL, s'occupe de l'affichage graphique d'OpenGL
    void            resizeGL(int _width, int _height);              // Permet d'adapter la taille d'OpenGL à celle du widget
};

#endif // CGLAREA_H
