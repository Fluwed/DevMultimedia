#ifndef CView_H
#define CVIew_H

#include <QWidget>
#include "CGLArea.h"
#include <QLabel>


class CView : public QWidget
{
    Q_OBJECT

private:
    CModel*         m_poModel;
    CControl*       m_poCtrl;
    CGLArea*        m_poGlArea;
    QLabel*         m_poGameScore;
    QTimer*         m_poClock;
    int             m_iTimer;
    
public:
    CView(QWidget *parent = 0);
    ~CView();

    void            vSetControl(CControl* _oCtrl);
    void            vSetModel(CModel* _poMdl);

    void keyPressEvent(QKeyEvent *_event);
    void keyReleaseEvent(QKeyEvent *_event);
private:
    void            vResetList(void);

public slots:
    void            vSetGame(void);
    void            vStartGame(void);

    void updateTime();
};

#endif // CVIew_H













