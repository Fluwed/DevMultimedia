#include "CView.h"
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>

/*---------------------------------------------------------------------------*/
CView::CView(QWidget *parent)
    : QWidget(parent)
{
    QPushButton* oAddBtn = new QPushButton(tr("&Add"));
    oAddBtn->show();
    QPushButton* oDelBtn = new QPushButton(tr("&Delete"));
    oDelBtn->show();

    m_poGlArea = new CGLArea();

    connect(oAddBtn, SIGNAL(clicked()), this, SLOT(vAddFunction()));
    connect(oDelBtn, SIGNAL(clicked()), this, SLOT(vDelFunction()));

    QVBoxLayout* oBtnRLayout = new QVBoxLayout();
    oBtnRLayout->addWidget(oAddBtn, Qt::AlignTop);
    oBtnRLayout->addWidget(oDelBtn);
    oBtnRLayout->addStretch();

    QHBoxLayout* oBtnHLayout = new QHBoxLayout();
    oBtnHLayout->addWidget(m_poGlArea);
    oBtnHLayout->addLayout(oBtnRLayout);

    setLayout(oBtnHLayout);
    setWindowTitle(tr("Look at the cubes"));
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
void CView::vAddFunction(void)
{
    for (int i=0;i<20;i++)
    {
    m_poCtrl->vAddObject(iNbCube);
    iNbCube=iNbCube+1;
    m_poGlArea->updateGL();
    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), m_poGlArea, SLOT(updateGL()));
    timer->start(0);
}

/*---------------------------------------------------------------------------*/
void CView::vDelFunction(void)
{

    m_poCtrl->vDelObject();
    m_poGlArea->updateGL();
}





