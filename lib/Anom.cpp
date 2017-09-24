//------------------------------------------------------------------------------
/// \file Anom.cpp
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
//    Implementation of class Anom
//------------------------------------------------------------------------------

#include "Anom.h"
#include <math.h>

namespace radiative
{

//------------------------------------------------------------------------------
AnDim::AnDim(int Nf): _nf(Nf)
{
   beta[0] = 11. - (2. * _nf) / 3.;
   beta[1] = 102. - (38. * _nf) / 3.;
   beta[2] = 2857. / 2. - (5033. * _nf) / 18. + (325. * pow(_nf,2)) / 54.;
   beta[3] = 29242.964136194132 - 6946.289617003555 * _nf + 405.08904045986293 * pow(_nf,2) + 1.4993141289437586 * pow(_nf,3);

   gammaMass[0] = 1.;
   gammaMass[1] = 101./24. - 5. * _nf/36.;
   gammaMass[2] = 1249./64. - 2.284121493373736 * _nf - 35./1296. * pow(_nf,2);
   gammaMass[3] = 98.9434142552029 - 19.1074619186354 * _nf  + 0.27616255142989465 * pow(_nf,2)
    + 0.005793222354358382 * pow(_nf,3);

    for (int i = 0; i < 4; i++){ gammaMass[i] *= - pow(4,i + 1); }

   numFlav = _nf;
}

void AnDim::expandAlpha(double coef[][3])
{

   coef[1][1] = coef[0][0] * beta[0] / 2.;
   coef[1][2] = coef[0][1] * beta[0] + coef[0][0] * beta[1] / 8.;
   coef[2][2] = coef[0][0] * beta[0] * beta[0] / 4.;

   for (int i = 0 ; i < 3 ; ++i) {
      for (int j = i + 1 ; j < 5 ; ++j) {
         coef[j][i] = 0;
      }
   }
}


//------------------------------------------------------------------------------
double AnDim::wTilde(int order, double a0, double a1)
{
   double LOG = log(a1 / a0), res;
   
   res = 0.;
   
   if(order >-1) res += - gammaMass[0] * LOG / beta[0];

   if(order > 0) res += (a1 - a0) / beta[0] * 0.07957747154594767 *
               (beta[1] * gammaMass[0] / beta[0] - gammaMass[1]);

   if(order > 1) res +=  - ( pow(a1,2) - pow(a0,2) ) * 0.0031662869888230555 / beta[0] * ( pow(beta[1]/beta[0],2) * gammaMass[0] -
                     beta[2] * gammaMass[0] / beta[0] - beta[1] * gammaMass[1] / beta[0] + gammaMass[2] );

   if(order > 2) res += ( pow(a1,3) - pow(a0,3) ) * 0.0001679767418395807 / beta[0] * ( pow(beta[1]/beta[0],3) * gammaMass[0]
                     - 2 * beta[1] * beta[2] * gammaMass[0] / pow(beta[0],2) + beta[3] * gammaMass[0] / beta[0] -
                     pow(beta[1]/beta[0],2) * gammaMass[1] + beta[2] * gammaMass[1] / beta[0] + beta[1] * gammaMass[2] /
                     beta[0] - gammaMass[3]);
   return res;
}

} // namespace radiative	
