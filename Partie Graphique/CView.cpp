#include "CView.h"
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>

/*---------------------------------------------------------------------------*/
CView::CView(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label= new QLabel("Pour lancer la boule, appuyer sur E.     Contrôles: Q = Gauche / D = Droite          (⌐■_■)");
    m_poGameScore= new QLabel(" ");

    m_poGlArea = new CGLArea();

    QVBoxLayout* oBtnRLayout = new QVBoxLayout();
    oBtnRLayout->addWidget(m_poGlArea);
    oBtnRLayout->addWidget(m_poGameScore);
    oBtnRLayout->addWidget(label);


    setLayout(oBtnRLayout);
    setWindowTitle(tr("Bricks Project"));

    QTimer::singleShot(100, this, SLOT(vSetGame()));

    QTimer *game = new QTimer(this);
    connect(game, SIGNAL(timeout()), this, SLOT(vUpdateGame()));
    game->start(100);

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
    m_poCtrl->vSetGame();
    m_poGlArea->updateGL();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), m_poGlArea, SLOT(updateGL()));
    timer->start(0);
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
        m_poGameScore->setText("Lancement dans : 5 sec");
        m_iTimer=5;

        m_poClock = new QTimer(this);
        connect(m_poClock, SIGNAL(timeout()), this, SLOT(updateTime()));
        m_poClock->start(1000);
    }

}

/*---------------------------------------------------------------------------*/
void CView::keyReleaseEvent(QKeyEvent* _event)
{
    m_poCtrl->vMovePalet(_event->key(),false);
}

void CView::updateTime()
{
    m_iTimer--;
    m_poGameScore->setText("Lancement dans : " + QString::number(m_iTimer)+ " sec");
    if (m_iTimer==0)
    {
        m_poClock->stop();
        m_poCtrl->setBStickySphere(false);
        m_poCtrl->vStart();
    }
}

void CView::vUpdateGame()
{
    /*----------------------------------- Affichage score une fois la partie commencée --------------------------------------*/
    if (m_poCtrl->bStickySphere()==false)
    {
        m_poGameScore->setText("Score : "+ QString::number(m_poCtrl->m_iScore) +" ------ Vie Restantes : "+ QString::number(m_poCtrl->m_iLife));
    }

    /*----------------------------------- Fonction de Gestion des niveaux --------------------------------------*/
    m_poCtrl->vLevelFinished();
    /*----------------------------------- Affichage score une fois la partie terminée et remise à zéro des variables --------------------------------------*/
    if (m_poCtrl->m_iLife==0)
    {
        m_iFinalScore=m_poCtrl->m_iScore;
        m_poGameScore->setText("Partie terminée avec un score de "+ QString::number(m_iFinalScore) +". Appuyer sur E pour rejouer");
        m_poCtrl->vResetGame();
    }
}
