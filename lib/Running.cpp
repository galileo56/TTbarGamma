//------------------------------------------------------------------------------
/// \file Running.cpp
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
//    Implementation of class Alpha
//------------------------------------------------------------------------------

#include "Running.h"
#include <gsl/gsl_math.h>

using namespace std;

namespace radiative
{

//------------------------------------------------------------------------------
Running::Running(int iorder, int nF, double mZ, double aMz, double mt, double muM,
   double mCharm, double muCharm, double mW, double aQEDmZ)
   : _nF(nF), _order(iorder), _mZ(mZ), _aMz(aMz), _mt(mt), _muM(muM), _mCharm(mCharm),
    _muCharm(muCharm), _mW(mW), _aQEDmZ(aQEDmZ), run(nF)
{
   double alpha5, aSoPi, lg, tab[4][4], nf;

    double betaZ = 80./9., betaW = 17/9., betaTopW = 11./4., betaTop = 32./3. ;

    aQED = aQEDmZ;

    if (_nF == 5){

    _aQEDref  = _aQEDmZ;
    _muQEDref = _mZ;
    _betaQED = betaZ;

    } else if ( _nF == 6 ){

//     _aQEDref = alphaQEDGeneric(betaZ, _mZ, _aQEDmZ,  _mW)  ;
//     _aQEDref = alphaQEDGeneric(betaW, _mW, _aQEDref, _mt) ;
     _aQEDref = alphaQEDGeneric(betaZ, _mZ, _aQEDmZ, _mt) ;

    _muQEDref = _mt ;
    _betaQED = betaTop;

    } else {
    _aQEDref  = 0.;
    _muQEDref = _mZ;
    _betaQED = 0. ;
    }

    mTop = _mt;

    for (int i = 0; i < 3; i++){
       for (int j = 0; j < 3; j++){
       tab[i][j] = 0.;
       }
    }

    tab[0][0] = 1. ;
    tab[1][1] = 1./6. ;
    tab[2][0] = - 11./72. ;
    tab[2][1] = 19./24. ;
    tab[2][2] = 1./36. ;
    tab[3][0] = - 1.0567081783962546 + 0.08465149176954732 * _nF ;
    tab[3][1] = 3427./864. - 281. * _nF/1728. ;
    tab[3][2] = 511./576. ;
    tab[3][3] = 1./216. ;

   if ( _nF <= 4 ){

   nf = 4;

      tab[1][1] = - 1./6. ;
      tab[2][0] = 11./72. ;
      tab[2][1] = - 19./24. ;
      tab[3][0] = 1.0567081783962546 - 0.08465149176954734 * (nf + 1) ;
      tab[3][1] = - ( 7074. - 281. * (nf + 1) )/1728. ;
      tab[3][2] = - 131./576. ;
      tab[3][3] = - 1./216. ;
      }

      if ( (_nF <= 4) || (_nF == 6) ) { //Running from Mz to muM = muTop or muBottom
         lg = 2. * log(_muM/_mt);
         alpha5 = alphaGeneric(5, _mZ, _aMz, _muM);
         aSoPi = alpha5/M_PI;
         _muRef = _muM;
         _alphaRef = 0.;

         for(int i = 0; i < _order; i++){
            for(int j = 0; j < _order; j++){
               _alphaRef += tab[i][j] * pow(lg, j) * pow(aSoPi,i);
               }
            }
         _alphaRef *= alpha5;

         if( _nF < 4){ //Running from muBottom to muCharm
      tab[3][0] = 1.0567081783962546 - 0.08465149176954734 * 4 ;
      tab[3][1] = - ( 7074. - 281. * 4 )/1728. ;
      lg = 2. * log(_muCharm/_mCharm);
      alpha5 = alphaGeneric(4, _muRef, _alphaRef, _muCharm);
      aSoPi = alpha5/M_PI;
      _muRef = _muCharm;
      _alphaRef = 0.;
         for(int i = 0; i < _order; i++){
            for(int j = 0; j < _order; j++){
               _alphaRef += tab[i][j] * pow(lg, j) * pow(aSoPi,i);
               }
            }
         _alphaRef *= alpha5;
         }
      }
      else if (_nF == 5) {
         _alphaRef = _aMz;
         _muRef = _mZ;
         }
}

//------------------------------------------------------------------------------
double Running::alphaQED(double mu)
{
   return alphaQEDGeneric(_betaQED, _muQEDref, _aQEDref, mu);
}

//------------------------------------------------------------------------------
double Running::mass(double mu)
{
double res, a0, a1;
a0 = alpha(_mt);
a1 = alpha(mu);
res = _mt * exp( run.wTilde(_order - 1, a0, a1) );
return res;
}

//------------------------------------------------------------------------------
double Running::alpha(double mu)
{
int nf;
if (_nF < 4 ){nf = 3;}   else {nf = _nF;}

   return alphaGeneric(nf, _muRef, _alphaRef, mu);
}

//------------------------------------------------------------------------------

complex<double> Running::alpha(complex<double> mu)
{
complex<double> a;
int nf;
if (_nF < 4 ){nf = 3;} else {nf = _nF;}
a = alphaGeneric(nf, _muRef, _alphaRef, mu);
return a;
}

//------------------------------------------------------------------------------
double Running::alphaQEDGeneric(double beta, double mz, double amz, double mu)
{
   double L = log(mu / mz);
   double res;

   res = 1. - 0.15915494309189535 * amz * L * beta;

   return amz/res;
}

//------------------------------------------------------------------------------
double Running::alphaGeneric(int nf, double mz, double amz, double mu)
{
   double L = log(mu / mz);
   AnDim betaQCD(nf);
   double arg = amz * L * betaQCD.beta[0]/M_PI/2.;
   double LG = log(1. + arg);
   double res;

   res = 1.;

   if (_order > 0) res+= arg ;

   if (_order > 1) res += betaQCD.beta[1] / betaQCD.beta[0]/M_PI/4. * amz * LG;

   if (_order > 2) res += 1. / (16. * pow(M_PI,2) + 8. * M_PI * amz * L * betaQCD.beta[0]) *
                ( pow(amz,2) * LG * pow(betaQCD.beta[1]/betaQCD.beta[0],2) -
                (  pow(amz,3) * L * pow(betaQCD.beta[1],2)/M_PI/2. ) /
                betaQCD.beta[0] + pow(amz,3) * L * betaQCD.beta[2]/M_PI/2.  ) ;

   if (_order > 3) res += 1. / 32. / M_PI / pow(2. * M_PI + amz * L * betaQCD.beta[0], 2) *
                (- pow(amz, 3) * pow(LG,2)  * pow(betaQCD.beta[1] / betaQCD.beta[0],3) +
                pow(amz, 5) * pow(L,2) * pow(betaQCD.beta[1],3) / betaQCD.beta[0] / 4. / pow(M_PI,2) -
                pow(amz, 5) * pow(L,2) * betaQCD.beta[1] * betaQCD.beta[2] / 2. / pow(M_PI,2) +
                2. * pow(amz,3) * LG * betaQCD.beta[1] * betaQCD.beta[2] / pow(betaQCD.beta[0],2) -
                pow(amz, 4) * L * betaQCD.beta[1] * betaQCD.beta[2] / betaQCD.beta[0]/ M_PI +
                pow(amz, 4) * L * betaQCD.beta[3] / M_PI +
                pow(amz, 5) * pow(L,2) * betaQCD.beta[0] * betaQCD.beta[3] / 4. / pow(M_PI,2));
   return amz/res;
}

//------------------------------------------------------------------------------
complex<double> Running::alphaGeneric(int nf, double mz, double amz, complex<double> mu)
{
   AnDim betaQCD(nf);
   complex<double> L = log(mu / mz), uno(1, 0);
   complex<double> argu = amz * L * betaQCD.beta[0]/M_PI/2.;
   complex<double> LG = log(uno + argu);
   complex<double> res;

   res = 1.;

   if (_order > 0) res+= argu;

   if (_order > 1) res += betaQCD.beta[1] / betaQCD.beta[0]/M_PI/4. * amz * LG;

   if (_order > 2) res += 1. / (16. * pow(M_PI,2) + 8. * M_PI * amz * L * betaQCD.beta[0]) *
                (pow(amz,2) * LG * pow(betaQCD.beta[1]/betaQCD.beta[0],2) -
                (  pow(amz,3) * L * pow(betaQCD.beta[1],2)/M_PI/2. ) /
                betaQCD.beta[0] + pow(amz,3) * L * betaQCD.beta[2]/M_PI/2.  ) ;

   if (_order > 3) res += 1. / 32. / M_PI / pow(2. * M_PI + amz * L * betaQCD.beta[0], 2) *
                (- pow(amz, 3) * pow(LG,2)  * pow(betaQCD.beta[1] / betaQCD.beta[0],3) +
                pow(amz, 5) * pow(L,2) * pow(betaQCD.beta[1],3) / betaQCD.beta[0] / 4. / pow(M_PI,2) -
                pow(amz, 5) * pow(L,2) * betaQCD.beta[1] * betaQCD.beta[2] / 2. / pow(M_PI,2) +
                2. * pow(amz,3) * LG * betaQCD.beta[1] * betaQCD.beta[2] / pow(betaQCD.beta[0],2) -
                pow(amz, 4) * L * betaQCD.beta[1] * betaQCD.beta[2] / betaQCD.beta[0]/ M_PI +
                pow(amz, 4) * L * betaQCD.beta[3] / M_PI +
                pow(amz, 5) * pow(L,2) * betaQCD.beta[0] * betaQCD.beta[3] / 4. / pow(M_PI,2));
   return amz/res;
}

} // namespace radiative
