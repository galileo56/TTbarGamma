//------------------------------------------------------------------------------
/// \file ElectroWeak.cpp
//
// Author(s):
//    Vicent Mateu
//
// Copyright:
//    Copyright (C) 2012  Vicent Mateu
//
//    This file is part of the SCETlib library. SCETlib is distributed under the
//    terms of the GNU General Public License version 3 (GPLv3), see the COPYING
//    file that comes with this distribution for details.
//    Please respect the academic usage guidelines in the GUIDELINES file.
//
// Description:
//    Implementation of class ElectroWeak
//------------------------------------------------------------------------------

#include "ElectroWeak.h"
#include <math.h>

namespace radiative
{

//------------------------------------------------------------------------------
ElectroWeak::ElectroWeak(double mZ, double gammaZ, double sin2ThetaW): _mZ(mZ),
_gammaZ(gammaZ), _sin2ThetaW(sin2ThetaW)
{
  double sinWein = sqrt(_sin2ThetaW) ;
  double CosWein = sqrt( 1. - pow(sinWein,2) ) ;
  double sCWein = 2. * sinWein * CosWein ;

  _ve = (- 0.5 + 2. * _sin2ThetaW)/sCWein ;
  _ae =  - 0.5/sCWein ;

  _vUp = (0.5 - 4./3. * _sin2ThetaW)/sCWein ;
  _aUp = 0.5/sCWein ;
  
  _vDown = ( - 0.5 + 2./3. * _sin2ThetaW)/sCWein ;

}

double ElectroWeak::charge(int nf){

double Qquark;

   switch (nf) {
      case 6:
      case 4:
      case 2:
         Qquark = 2./3.;
      break;
      case 5:
      case 3:
      case 1:
         Qquark = - 1./3.;
         break;
      default:
         Qquark = 0;
         break;
   };

   return Qquark;
}

void ElectroWeak::ewFactors(int nf, double Q, double coef[2])
{
double Q2 = pow(Q, 2);
double Q4 = pow(Q2, 2);
double prop = Q2 - pow(_mZ, 2) ;
double prop2 = pow(prop,2) ;
double ratio = prop2 + Q4 * pow(_gammaZ/_mZ,2);
double Qquark, vt;

   switch (nf) {
      case 6:
      case 4:
      case 2:
         Qquark = 2./3.;
         vt = _vUp ;
         break;
      case 5:
      case 3:
      case 1:
         Qquark = - 1./3.;
         vt = _vDown ;
         break;
      default:
         Qquark = 0;
         vt = 0;
         break;
   };

 double electron = Q4 * ( pow(_ve,2) + pow(_ae,2) ) ; 

 coef[0] = pow(Qquark,2) + ( electron * pow(vt,2) - 2. * Q2 * _ve * vt * Qquark * prop )/ratio ;
 coef[1] = electron * pow(_aUp,2)/ratio ;

}


} // namespace radiative	
