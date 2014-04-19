#ifndef CGLAREA_H
#define CGLAREA_H

#include <QGLWidget>
#include <CVector3.h>
#include <CControl.h>


class CGLArea : public QGLWidget
{
    Q_OBJECT

private:
    CModel*         m_poModel;
    QPoint          m_oLastPos;
    float           m_fAzimuth;
    float           m_fElevation;
    float           m_fRadius;
    CControl*       m_poCtrl;

public:
    CGLArea(QWidget *parent = 0);
    ~CGLArea();

    void            vSetModel(CModel* _poModel, CControl *_poCtrl);
    QSize           minimumSizeHint() const;
    QSize           sizeHint() const;

    void            mousePressEvent(QMouseEvent* _event);
    void            mouseMoveEvent(QMouseEvent* _event);
    void            mouseReleaseEvent(QMouseEvent* _event);

    void            updateCamera(void);

    void            convertMouseToRay(int _x, int _y, CVector3 *_poRayOrigin, CVector3 *_poRayDir);

    void MoveSphere(float value);
protected:
    void            initializeGL();
    void            paintGL();
    void            resizeGL(int _width, int _height);

private:
    void            paintRef(void);
};

#endif // CGLAREA_H
