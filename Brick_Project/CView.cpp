#include "CView.h"
#include <QtGui>
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>

/*---------------------------------------------------------------------------*/
CView::CView(QWidget *parent)
    : QWidget(parent)
{
    m_iFinalScore=0;
    m_bScoreVisible=false;
    m_bPause=false;
    m_bMusic=true;
    m_poWebcam = new CWebcam(this);
    m_poWebcam->hide();

    QLabel* label= new QLabel("Pour lancer la boule, appuyer sur E.     Contrôles: Q = Gauche / D = Droite          (⌐■_■)");
    m_poScore = new QLabel(" Score : 0");
    m_poLife = new QLabel(" Vies : 3");
    m_poInfo = new QLabel("");

    m_poGlArea = new CGLArea();

    m_poVLayout = new QVBoxLayout();
    m_poHLayout = new QHBoxLayout();
    m_poGameScore = new QVBoxLayout();
    m_poHighScore = new QVBoxLayout();

    QPushButton* poTrackBtn = new QPushButton(tr("&Tracking"));
    QPushButton* poPauseBtn = new QPushButton(tr("&Pause"));
    QPushButton* poRankBtn = new QPushButton(tr("&HighScores"));
    m_poSaveBtn = new QPushButton(tr("&SaveScore"));

    m_poMusicBtn = new QPushButton(tr("&Désactiver Musique"));

    connect(poTrackBtn, SIGNAL(clicked()), this, SLOT(vTracking()));
    connect(poPauseBtn, SIGNAL(clicked()), this, SLOT(vPause()));
    connect(poRankBtn, SIGNAL(clicked()), this, SLOT(vHighScore()));
    connect(m_poSaveBtn, SIGNAL(clicked()), this, SLOT(vSaveScore()));
    connect(m_poMusicBtn, SIGNAL(clicked()), this, SLOT(vSetMusic()));

    /*--------------- Layout Principale ------------------*/
    m_poHLayout->addLayout(m_poVLayout);
    m_poHLayout->addLayout(m_poGameScore);
    m_poVLayout->addWidget(m_poGlArea);
    m_poVLayout->addWidget(m_poInfo);
    m_poVLayout->addWidget(label);

    /*--------------- Layout Secondaire ------------------*/
    m_poGameScore->addWidget(poTrackBtn);
    m_poGameScore->addWidget(poPauseBtn);
    m_poGameScore->addWidget(poRankBtn);
    m_poGameScore->addWidget(m_poSaveBtn);
    m_poGameScore->addWidget(m_poMusicBtn);
    m_poGameScore->addWidget(m_poScore);
    m_poGameScore->addWidget(m_poLife);
    m_poGameScore->addStretch();
    m_poSaveBtn->hide();

    setLayout(m_poHLayout);
    setWindowTitle(tr("Bricks Project"));

    QTimer::singleShot(100, this, SLOT(vSetGame()));

    //QTimer *game = new QTimer(this);
    //connect(game, SIGNAL(timeout()), this, SLOT(vUpdateGame()));
    //game->start(15);

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

    m_poTimer = new QTimer(this);
    connect(m_poTimer, SIGNAL(timeout()), m_poGlArea, SLOT(updateGL()),Qt::DirectConnection);
    connect(m_poTimer, SIGNAL(timeout()), this, SLOT(vUpdateGame()));
    m_poTimer->start(15);
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
        m_poSaveBtn->hide();
        m_poInfo->setText("Lancement dans : 3 sec");
        m_iTimer=3;
        m_poClock = new QTimer(this);
        connect(m_poClock, SIGNAL(timeout()), this, SLOT(vUpdateTime()));
        m_poClock->start(1000);
    }

}

/*---------------------------------------------------------------------------*/
void CView::keyReleaseEvent(QKeyEvent* _event)
{
    m_poCtrl->vMovePalet(_event->key(),false);
}

void CView::vUpdateTime(void)
{
    m_iTimer--;
    m_poInfo->setText("Lancement dans : " + QString::number(m_iTimer)+ " sec");
    if (m_iTimer==0)
    {
        m_poInfo->setText("");
        m_poClock->stop();
        m_poCtrl->setBStickySphere(false);
        m_poCtrl->vStart();
    }
}

void CView::vUpdateGame()
{
    /*----------------------------------- Affichage score une fois la partie commencée --------------------------------------*/
        m_poScore->setText(" Score : "+ QString::number(m_poCtrl->m_iScore));
        m_poLife->setText(" Vies : "+ QString::number(m_poCtrl->m_iLife));

    /*----------------------------------- Fonction de Gestion des niveaux --------------------------------------*/
    m_poCtrl->vLevelFinished();

    /*----------------------------------- Affichage score une fois la partie terminée et remise à zéro des variables --------------------------------------*/
    if (m_poCtrl->m_iLife==0)
    {
        m_iFinalScore=m_poCtrl->m_iScore;
        m_poInfo->setText("Partie terminée avec un score de "+ QString::number(m_iFinalScore) +". Appuyer sur E pour rejouer");
        m_poSaveBtn->show();
        m_poCtrl->vResetGame();
    }
    if (m_poWebcam->bIsTracking())
    {
        m_poCtrl->vTrackPalet(m_poWebcam->fGetPosition());
    }
}

void CView::vHighScore()
{
    if (m_bScoreVisible==false)
    {
        m_poHLayout->addLayout(m_poHighScore);
        QString s;
        QStringList oList;
        oList=m_poCtrl->vLoadHighScore();
        for (int i=0; i<oList.size();i++)
        {
            s=oList.at(i);
            QLabel* label=new QLabel (this);
            label->setText(s);
            m_poHighScore->addWidget(label);
        }
        m_poHighScore->addStretch();
        m_bScoreVisible=true;
    }
    else
    {
    }
}

void CView::vSaveScore()
{
    m_poSave = new QDialog(this);

    QLabel* poNameLabel = new QLabel(tr("Entrer un nom :"));
    m_poLineEdit = new QLineEdit();
    QPushButton* poSaveBtn = new QPushButton(tr("&Save"));
    connect(poSaveBtn, SIGNAL(clicked()), this, SLOT(vSave()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(poNameLabel);
    layout->addWidget(m_poLineEdit);
    layout->addWidget(poSaveBtn);

    m_poSave->setLayout(layout);
    m_poSave->setWindowTitle(tr("Save a Score"));
    m_poSave->show();
}

void CView::vSave(void){
    {
        QString oText = m_poLineEdit->text();

        if (oText.isEmpty()) {
            QMessageBox::information(this, tr("Empty Field"),
                                     tr("Please enter a name."));
            return;
        } else {
            m_poCtrl->vSave(oText,m_iFinalScore);
            m_poLineEdit->clear();
            m_poSave->hide();
            if (m_bScoreVisible==true)
            {
                QLabel* label=new QLabel (this);
                QString s=oText+" :    "+QString::number(m_iFinalScore);
                label->setText(s);
                m_poHighScore->insertWidget(m_poHighScore->count()-2,label);
            }
        }
    }
}

void CView::vTracking()
{
    m_poWebcam->show();
    m_poHLayout->addWidget(m_poWebcam);
}

void CView::vPause()
{
    if(m_bPause==false)
    {
        m_poTimer->stop();
        m_bPause=true;
    }
    else
    {
        m_poTimer->start();
    }

}

void CView::vSetMusic()
{
    if(m_bMusic==true)
    {
         m_poCtrl->vPauseMusic();
         m_bMusic=false;
         m_poMusicBtn->setText(tr("&Activer Musique"));
    }
    else
    {
        m_poCtrl->vResume();
        m_bMusic=true;
        m_poMusicBtn->setText(tr("&Désactiver Musique"));
    }
}
