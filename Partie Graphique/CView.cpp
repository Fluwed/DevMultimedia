#include "CView.h"
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

/*---------------------------------------------------------------------------*/
CView::CView(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label= new QLabel("Pour lancer la partie appuyer sur E.     Contrôles: Q = Gauche / D = Droite          (⌐■_■)");

    m_poGlArea = new CGLArea();

    QVBoxLayout* oBtnRLayout = new QVBoxLayout();
    oBtnRLayout->addWidget(m_poGlArea);
    oBtnRLayout->addWidget(label);

    setLayout(oBtnRLayout);
    setWindowTitle(tr("Look at the cubes"));

    QTimer::singleShot(100, this, SLOT(vSetGame()));



}

/*---------------------------------------------------------------------------*/
CView::~CView()
{
}


/*---------------------------------------------------------------------------*/
void CView::vSetControl(CControl* _oCtrl)
{
    m_poCtrl = _oCtrl;
}

/*---------------------------------------------------------------------------*/
void CView::vSetModel(CModel* _poMdl)
{
    m_poModel = _poMdl;
    m_poGlArea->vSetModel(_poMdl, m_poCtrl);
}


/*---------------------------------------------------------------------------*/
void CView::vSetGame(void)
{
    m_poCtrl->vAddObject();
    m_poGlArea->updateGL();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), m_poGlArea, SLOT(updateGL()));
    timer->start(0);
}

/*---------------------------------------------------------------------------*/
void CView::vDelFunction(void)
{

    m_poCtrl->vDelObject();

}

/*---------------------------------------------------------------------------*/
void CView::vStartGame()
{
    m_poCtrl->vStart();
}

/*---------------------------------------------------------------------------*/
void CView::keyPressEvent(QKeyEvent* _event)
{
    m_poCtrl->vMovePalet(_event->key(),true);
    if (_event->key()==Qt::Key_E)
    {
        /*QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(vStartGame()));
        timer->start(3000);*/
         QTimer::singleShot(2000, this, SLOT(vStartGame()));
    }

}

/*---------------------------------------------------------------------------*/
void CView::keyReleaseEvent(QKeyEvent* _event)
{
    m_poCtrl->vMovePalet(_event->key(),false);
}

