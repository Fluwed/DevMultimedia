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

    void                vSetGame();
    void                vDel(int _iId);
    void vNewPos(CVector3 *_poPos, int _face);
    int                 iGetNbObjects();
    int                 iCheckPicked(CVector3* _poOrigin, CVector3* _poDir);
    CObject*            poGetObject(int _iIndex);
    void                vLoadLevel(int _iLvl);
    void                vSetLife();
    void                vSetSpeed(float _fSpeed);

    void                vLoadHighScore();
    QStringList         oHighscore() const;
    void                vSave(QString _otText, int _iScore);
    void vResetLevel();
};

#endif // CModel_H
