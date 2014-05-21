#include "CGLarea.h"
#include <math.h>
#ifdef __APPLE__
#include "GLUT/glut.h"
#else
#include "GL/glu.h"
#endif
#include <QMouseEvent>
#include <qdebug.h>
#include "QTimer"
#include "CSphere.h"



#define k_PI            ((double)3.1415926535897932384626433832795)
#define k_2PI           ((double)(k_PI + k_PI))
#define MOUSE_FACTOR    ((double)0.005)


/*---------------------------------------------------------------------------*/
CGLArea::CGLArea(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    m_poModel = NULL;

    m_fAzimuth = 0.0;
    m_fElevation = 0.0;
    m_fRadius = 20.0;
}

/*---------------------------------------------------------------------------*/
CGLArea::~CGLArea()
{
}

/*---------------------------------------------------------------------------*/
void CGLArea::vSetModel(CModel *_poModel, CControl *_poCtrl)
{
    m_poModel = _poModel;
    m_poCtrl = _poCtrl;
}

/*---------------------------------------------------------------------------*/
QSize CGLArea::minimumSizeHint() const
{
    return QSize(50, 50);
}

/*---------------------------------------------------------------------------*/
QSize CGLArea::sizeHint() const
{
    return QSize(700, 700);
}

/*---------------------------------------------------------------------------*/
void CGLArea::updateCamera(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-30.0, +30.0, -30.0, +30.0, 0.0, 120.0);

    gluLookAt(m_fRadius*cos(m_fAzimuth)*cos(m_fElevation),
              m_fRadius*sin(m_fAzimuth)*cos(m_fElevation),
              m_fRadius*sin(m_fElevation),
              0,0,0,
              0,0,1);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*---------------------------------------------------------------------------*/
void CGLArea::resizeGL(int _width, int _height)
{
    int side = qMin(_width, _height);
    glViewport((_width - side) / 2, (_height - side) / 2, side, side);

    updateCamera();
}

/*---------------------------------------------------------------------------*/
void CGLArea::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //Couleur du Background

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    updateCamera();
}

/*---------------------------------------------------------------------------*/
void CGLArea::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(m_poModel != NULL)
    {
        glLoadIdentity();

        // Draw a referential
        //paintRef();

        // Then draw the cubes
        for(int i=0; i<m_poModel->iGetNbObjects(); i++)
        {
            CObject* poCurrent = m_poModel->poGetObject(i);

            CVector3 oPos;
            poCurrent->vGetPosition(&oPos);

            glLoadIdentity();
            glTranslatef(oPos.fGetX(), oPos.fGetY(), oPos.fGetZ());

            // For each face...
            for(int j=0; j<poCurrent->iGetNbFaces(); j++)
            {
                CVector3 oColor;
                poCurrent->vGetSideColor(j, &oColor);
                glColor3f(oColor.fGetX(), oColor.fGetY(), oColor.fGetZ());

                glBegin(GL_POLYGON);
                // For each vertex of the face
                for(int k=0;k<poCurrent->iGetNbVertices(j);k++)
                {
                    CVector3 oVertex;
                    poCurrent->vGetVertex(j,k,&oVertex);
                    glVertex3f(oVertex.fGetX(), oVertex.fGetY(), oVertex.fGetZ());
                }
                glEnd();
            }
        }
        if (m_poModel->iGetNbObjects()>5) // Tout ce qui est lié à l'animation dynamique
        {
            if (m_poCtrl->m_bStickySphere==true) // Permet que la sphère colle au palet tant que le jeu n'a pas commencé.
            {
                m_poCtrl->vSetNewLife();
            }
            /*if (m_poCtrl->m_bStart==true) // Décompte de 5 secondes avant le lancement de la partie
            {
                m_poCtrl->setBStart(false);
                QTimer::singleShot(5000, this, SLOT(vStartGame()));
            }*/

            m_poCtrl->vTimerEvent(); // Permet le mouvement fluide du palet
            MoveSphere(); // Permet le mouvement fluide de la sphère
        }
        glLoadIdentity();
        glFlush();
    }
}

/*---------------------------------------------------------------------------*/
void CGLArea::MoveSphere()
{
    CVector3 oPos(0,0,0);
    CVector3 oSpeed(0,0,0);
    CVector3 _poRayOrigin;
    CObject* Sphere;


    Sphere=m_poModel->poGetObject(5);
    Sphere->vGetPosition(&oPos);
    Sphere->vGetSpeed(&oSpeed);
    oPos.vSetX(oPos.fGetX()+oSpeed.fGetX());
    oPos.vSetY(oPos.fGetY()+oSpeed.fGetY());
    oPos.vSetZ(oPos.fGetZ()+oSpeed.fGetZ());
    m_poModel->poGetObject(5)->vSetPosition(&oPos);


    Sphere->vGetPosition(&_poRayOrigin);

    m_poCtrl->iCheckPicked(&_poRayOrigin);

}
