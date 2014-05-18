#ifndef VECTOR3_H
#define VECTOR3_H

/*-----------------------------------------------------------*
 * Three dimension vector class.
 * This class implements the basic operations that are usually
 * performed on a 3d vector.
 *
 * Author: Mathieu Ippersiel (mathieu.ippersiel@ipter.fr)
 * Date : January 2013
 *-----------------------------------------------------------*/

class CVector3
{

public:
    // Constructors
    CVector3();
    CVector3(float _fX, float _fY, float _fZ);
    CVector3(CVector3 const& _oSrc);

    // Get/Setters
    float   fGetX(void)       {return m_fX;}
    float   fGetY(void)       {return m_fY;}
    float   fGetZ(void)       {return m_fZ;}
    void    vSetX(float _fX)  {m_fX = _fX;}
    void    vSetY(float _fY)  {m_fY = _fY;}
    void    vSetZ(float _fZ)  {m_fZ = _fZ;}
    void    vSet(float _fX, float _fY, float _fZ);
    void    vSet(CVector3 const & _oSrc);

    // Mathematical functions
    float   fDistance(CVector3 _oB);
    float   fNorm();
    int     iNormalize();
    void    vCross(CVector3 const& _oA, CVector3 const& _oB);
    float   fDot(CVector3 const& _oB);

    /* Operator overloads */
    friend  CVector3    operator+(CVector3 const& _oA, CVector3 const& _oB);
    friend  CVector3    operator-(CVector3 const& _oA, CVector3 const& _oB);
    friend  void        operator+=(CVector3 & _oA, CVector3 const& _oB);

private:
    float   m_fX;
    float   m_fY;
    float   m_fZ;
};

#endif // VECTOR3_H
