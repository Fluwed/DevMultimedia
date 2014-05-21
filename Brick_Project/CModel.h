#ifndef CModel_H
#define CModel_H

#include "CObject.h"
#include <qvector.h>
#include <QStringList>

class CModel
{
private:
    QVector<CObject*>   m_oDatas;      // Pointer to the model
    QStringList         m_oHighscore;

    float               fGetRandom();

public:
    CModel();
    ~CModel();

    int                 iGetNbObjects();
    int                 iCheckPicked(CVector3* _poOrigin, CVector3* _poDir);
    void                vSetGame();
    void                vDel(int _iId);
    void                vNewPos(CVector3 *_poPos, int _face);
    void                vLoadLevel(int _iLvl);
    void                vSetLife();
    void                vSetSpeed(float _fSpeed);
    void                vLoadHighScore();
    void                vSave(QString _otText, int _iScore);
    void                vResetLevel();
    QStringList         oHighscore() const;
    CObject*            poGetObject(int _iIndex);
};

#endif // CModel_H
