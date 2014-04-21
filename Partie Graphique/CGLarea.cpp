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

    //gluPerspective(35.0f, (GLfloat)m_width/(GLfloat)m_height, 0.1f, 100.0f);
    //glFrustrum();
    //gluPerspective(30.0f, 1, 1.0f, 100.0f);

    glOrtho(-20.0, +20.0, -20.0, +20.0, 0.0, 60.0);

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
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    updateCamera();
}

/*---------------------------------------------------------------------------*/
void CGLArea::paintRef(void)
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glColor3f(0, 1, 0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glColor3f(0, 0, 1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glEnd();
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
            if (i<2)
            {
                glRotated(90,1,0,0);
            }
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
        if (m_poModel->iGetNbObjects()>15)
            MoveSphere();
        glLoadIdentity();
        glFlush();
    }
}

/*---------------------------------------------------------------------------*/
void CGLArea::mousePressEvent(QMouseEvent* _event)
{
    CVector3 _poRayOrigin;
    CVector3 _poRayDir;

    m_poCtrl->vResetPicked(); // On déselectionne tout les cubes
    m_oLastPos = _event->pos();
    convertMouseToRay(_event->x(),_event->y(),&_poRayOrigin, &_poRayDir);
    m_poCtrl->iCheckPicked(&_poRayOrigin, &_poRayDir); // On vérifie si un cube à été touché


    CVector3 oSpeed(0,0,-0.25);
    CObject* Sphere = new CSphere();


    Sphere=m_poModel->poGetObject(5);
    Sphere->SetSpeed(&oSpeed);

}

/*---------------------------------------------------------------------------*/
void CGLArea::mouseMoveEvent(QMouseEvent* _event)
{
    // Get the mouse movement
    int dx = _event->x() - m_oLastPos.x();
    int dy = _event->y() - m_oLastPos.y();

    // Convert it in a modification of the spherical coordinates
    if (_event->buttons() & Qt::RightButton)
    {
        m_fAzimuth = m_fAzimuth - MOUSE_FACTOR * dx;
        if(m_fAzimuth > k_2PI)
            m_fAzimuth = m_fAzimuth-k_2PI;
        if(m_fAzimuth < 0.0)
            m_fAzimuth = m_fAzimuth+k_2PI;

        m_fElevation = m_fElevation + MOUSE_FACTOR * dy;
        if(m_fElevation > k_PI/2)
            m_fElevation = k_PI/2;
        if(m_fElevation < -k_PI/2)
            m_fElevation = -k_PI/2;
    }

    // Current position becomes the last one
    m_oLastPos = _event->pos();

    // Update everything
    updateCamera();
    //updateGL();
}

/*---------------------------------------------------------------------------*/
void CGLArea::mouseReleaseEvent(QMouseEvent* _event)
{
}

/*---------------------------------------------------------------------------*/
void CGLArea::convertMouseToRay(int _x, int _y, CVector3* _poRayOrigin, CVector3* _poRayDir)
{
    GLint aiViewport[4];
    GLdouble afModelMatrix[16];
    GLdouble afProjectionMatrix[16];

    glGetIntegerv(GL_VIEWPORT, aiViewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, afModelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, afProjectionMatrix);

    GLfloat fWinY = GLfloat(aiViewport[3] - _y);


    double x0, y0, z0;
    gluUnProject( (double) _x, fWinY, 0.0f, // Near
                  afModelMatrix, afProjectionMatrix, aiViewport,
                  &x0, &y0, &z0 );
    _poRayOrigin->vSet(x0, y0, z0);


    double x1, y1, z1;
    gluUnProject( (double) _x, fWinY, 1.0f, // Far
                  afModelMatrix, afProjectionMatrix, aiViewport,
                  &x1, &y1, &z1 );
    _poRayDir->vSet(x1 - x0, y1 - y0, z1 - z0);
    _poRayDir->iNormalize();
}

void CGLArea::MoveSphere ()
{
    CVector3 oPos(0,0,0);
    CVector3 oSpeed(0,0,0);
    CObject* Sphere = new CSphere();


    Sphere=m_poModel->poGetObject(5);
    Sphere->vGetPosition(&oPos);
    Sphere->GetSpeed(&oSpeed);
    oPos.vSetX(oPos.fGetX()+oSpeed.fGetX());
    oPos.vSetY(oPos.fGetY()+oSpeed.fGetY());
    oPos.vSetZ(oPos.fGetZ()+oSpeed.fGetZ());
    m_poModel->poGetObject(5)->vSetPosition(&oPos);

}

