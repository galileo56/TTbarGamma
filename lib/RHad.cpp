//------------------------------------------------------------------------------
/// \file RHad.cpp
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
//    Implementation of class RHad
//------------------------------------------------------------------------------

#include "RHad.h"

#include <math.h>

#include <cmath>

#include <gsl/gsl_integration.h>
#include <gsl/gsl_sf_dilog.h>
#include <gsl/gsl_math.h>

namespace radiative
{

//------------------------------------------------------------------------------
DeltaMass::DeltaMass(Running AlphaMass): _AlphaMass(AlphaMass)
{
int nh = 1;
int nl = _AlphaMass.run.numFlav - 1;

for ( int i = 0; i < 3; i++){
   for (int j = 1; j < 4; j++){
       _coef[j][i] = 0. ;
   }
}

  _coef[0][0] = 4./3. ;
  _coef[0][1] = 13.33982910125516 + 0.10356715567659536 * nh - 1.041366911171631 * nl ;
  _coef[0][2] = 188.67172035165487 + 1.8591544419385237 * nh + 0.06408045019609998 * pow(nh,2)
    - 26.677375174269212 * nl +  0.022243482163948114 * nh * nl + 0.6526907490815437 * pow(nl,2) ;

  _coef[1][0] = 2.;
  _coef[1][1] = ( 2076. - 104. * (nl + nh) )/144. ;
  _coef[2][1] = 7.5 - 1./3. * (nl + nh) ;

  _coef[1][2] = 195.00458387187263 - 12.596570845269987 * nh -
 0.12305711613007586 * pow(nh,2) - 27.480713714296932 * nl +
 0.5171751456386657 * nh * nl + 0.6402322617687417 * pow(nl, 2);

  _coef[2][2] = ( 2696.625 - 288.75 * (nh + nl) + 6.5 * pow(nl + nh, 2) ) / 27. ;
  _coef[3][2] = ( 877.5 - 84. * (nl + nh) + 2. * pow(nl + nh, 2) ) / 27. ;

}

//------------------------------------------------------------------------------
double DeltaMass::mPole(int order, double mu)
{
double deltaM[3], res = _AlphaMass.mass(mu);

deltaMSbar(mu, deltaM);

for ( int i = 0; i < order; i++){
    res += deltaM[i];
}
return res;
}

//------------------------------------------------------------------------------
void DeltaMass::deltaMSbar(double mu, double deltaM[])
{
double massMu = _AlphaMass.mass(mu), alphaMu = _AlphaMass.alpha(mu) / 3.141592653589793 ;
double logM = log(mu/massMu);

for ( int i = 0; i < 3; i++){
   deltaM[i] = _coef[0][i];
   for (int j = 1; j < i + 2; j++){
       deltaM[i] += _coef[j][i] * pow(logM, j) ;
   }
    deltaM[i] *= pow(alphaMu, i + 1) * massMu ;
}

}

//------------------------------------------------------------------------------
MassCorrComputer::MassCorrComputer(double m, double v): _m(m), _v(v)
{
double c, b, d, pV, pA, qV, qA, Amass, v2, kV, kA, m2, x;

   if (_m > 0.5)
   rVTree = rATree = rV1loop = rA1loop = aAMS = aVMS = 0. ;

   else{

   m2 = pow(_m,2);
   v2 = pow(_v,2);

   x = 1 - _v ;

   rVTree = _v * ( 3. - v2 )/2.;
   rATree = pow(_v,3);

   if (x > 0.001){

   pV = 33./24. + 11./12. * v2 - 7./24. * pow(v2,2);
   pA =  21./32. + 59./32. * v2 + 19./32. * pow(v2,2) - 3./32. * pow(v2,3);

   qV = 5./4. * _v - 3./4. * pow(_v,3) ;
   qA = - 21./16. * _v + 15./8. * pow(_v,3) + 3./16. * pow(_v,5) ;

   c = 1 + _v ;
   b = (1. - _v)/c ;
   d = 1./( 1. - v2/3. ) ;

   Amass = ( 1. + v2 ) * (  gsl_sf_dilog( pow(b,2) ) + 2. * gsl_sf_dilog(b) - log(b) * log( pow(c,3)/8./v2 )  )
   + 3. * _v * log( m2/_v ) - _v * log(_v);

   kV = Amass - ( pV * log(b) - qV) * d;
   kV = kV/_v;

   kA = Amass - ( pA * log(b) - qA ) / v2;
   kA = kA/_v;

   rV1loop = 4./3. * rVTree * kV ;
   rA1loop = 4./3. * rATree * kA ;}

   else{

   double lx = log(x/2.) ;
   rV1loop = 1. + 6. * x - pow(x,2) * (0.5 + 6. * lx) -  pow(x,3)  * (161./54. + 4./9. * lx) ;
   rA1loop = 1. - x * (3. + 6. * lx) -  pow(x,2) * (1. - 9. * lx) +  pow(x,3) * (353./108.  - 40./9. * lx) ;
   }

   aAMS = - 12. * m2 * _v ;
   aVMS = - 24. * pow(m2,2)/_v ;}

}

//------------------------------------------------------------------------------
RHad::RHad(int scheme, int order, double q, double eH, double theta, double deltaTheta,
Running AlphaMass, ElectroWeak factors):
 _scheme(scheme), _order(order), _q(q), _eH(eH), _theta(theta), _deltaTheta(deltaTheta),
 _AlphaMass(AlphaMass), _factors(factors), _deltaM(AlphaMass)
{

  _alphaQED = _AlphaMass.alphaQED(_q);

  _qF = _factors.charge(_AlphaMass.run.numFlav);

  double v;

   _rQ[0][0] = 1;
   _rQ[0][1] = 1.985707398577798 - 0.11529539789360388 * _AlphaMass.run.numFlav;
   _rQ[0][2] = -6.636935585488629 - 1.2001340534564595 * _AlphaMass.run.numFlav -
                0.0051783553199245685 * pow( _AlphaMass.run.numFlav,2);

   for (int i = 0 ; i < 3 ; ++i) {
      for (int j = 1 ; j < 5 ; ++j) {
         _rQ[j][i] = 0;
      }
   }

   _AlphaMass.run.expandAlpha(_rQ);

}

//------------------------------------------------------------------------------
double RHad::rHadMass(int current, double q, double mu)
{
double v, tree, m, loop, sch, res, delta[3];
double alphaMu = _AlphaMass.alpha(mu) / M_PI ;

  _deltaM.deltaMSbar(mu, delta);
   mPole = _deltaM.mPole(3,_AlphaMass.mTop);

   switch (_scheme) {
      case 0:
         m = _deltaM.mPole(3,_AlphaMass.mTop);
         break;
      case 1:
         m = _AlphaMass.mass(mu);
         break;
      default:
         m = 0;
         break;
   };

v = sqrt( 1. - 4. * pow(  m/q, 2 )  );
MassCorrComputer elements(m/q,v);

   switch (current) {
      case 1:
         tree = elements.rVTree;
         loop = elements.rV1loop;
         sch  = elements.aVMS;
         break;
      case 2:
         tree = elements.rATree;
         loop = elements.rA1loop;
         sch  = elements.aAMS;
         break;
         tree = 0;
         break;
   };

res = 0;

if ( q > 2 * m && _order >= 0 ) res = tree;

if ( q > 2 * m && _order >= 1 ) {
   res += alphaMu * loop;
   if (_scheme == 1){
      res += delta[0] * sch/m;
   }
}

return res;
}

//------------------------------------------------------------------------------
double RHad::rHad(double q, double mu)
{
   double alphaMu = _AlphaMass.alpha(mu) / M_PI ;
   double logMu = log(q / mu);
   double rQ[2] = {0 , 0};

   for (int i = 0 ; i < 2 ; ++i) {
      for (int j = 0 ; j < i + 2 ; ++j) {
         rQ[i] += _rQ[j][i + 1] * pow(-logMu, j);
      }
   }

   double res;

   switch (_order) {
      case 0:
         res = 1;
         break;
      case 1:
         res = 1 + alphaMu;
         break;
      case 2:
         res  = 1 + alphaMu + pow(alphaMu,2) * rQ[0] ;
         break;
      case 3:
         res = 1 + alphaMu + pow(alphaMu,2) * rQ[0] + pow(alphaMu,3) * rQ[1] ;
         break;
      default:
         res = 0;
         break;
   };

   return res;
}

//------------------------------------------------------------------------------
double RHad::sigma(double q, double mu)
{
double coef[2];
 _factors.ewFactors(_AlphaMass.run.numFlav, q, coef);

   return 4. * pow( _AlphaMass.alphaQED(q)/q ,2 ) * M_PI * (coef[0] + coef[1])
   * rHad(q, mu);
}

//------------------------------------------------------------------------------
double RHad::sigmaMass(double q, double mu)
{
double coef[2];
 _factors.ewFactors(_AlphaMass.run.numFlav, q, coef);

   return 4. * pow( _AlphaMass.alphaQED(q)/q,2 ) * M_PI * ( coef[0] *
   rHadMass(1, q, mu) + coef[1] * rHadMass(2, q, mu) );
}

//------------------------------------------------------------------------------
double RHad::sigmaMassRadiative(double x)
 { if ( 1 <= 2 * x || x <= 0) return 0;
   if ( 1 > 2 * x && x > 0 ) return _alphaQED / pow(M_PI,2) *
   sigmaMass( _q * sqrt(1 - 2 * x), _eH * _q * sqrt(1 - 2 * x) ) * g(x);
}

//------------------------------------------------------------------------------
double RHad::sigmaRadiative(double x)
{
   return _alphaQED / pow(M_PI,2) * sigma( _q * sqrt(1 - 2 * x), _eH * _q * sqrt(1 - 2 * x) ) * g(x);
}

//------------------------------------------------------------------------------
double RHad::sigmaRadiativeCone(double x)
{ if ( 1 <= 2 * x || x <= 0) return 0;
   if ( 1 > 2 * x && x > 0 ) return 2 * _alphaQED / M_PI *
   sigma( _q * sqrt(1 - 2 * x), _eH * _q * sqrt(1 - 2 * x) ) * gInt(x);
}

//------------------------------------------------------------------------------
double RHad::sigmaMassRadiativeCone(double x)
{ if ( 1 <= 2 * x || x <= 0) return 0;
   if ( 1 > 2 * x && x > 0 ) return 2 * _alphaQED / M_PI *
   sigmaMass( _q * sqrt(1 - 2 * x), _eH * _q * sqrt(1 - 2 * x) ) * gInt(x);
}

//------------------------------------------------------------------------------
double RHad::g(double x)
{
double c2 = pow( cos(_theta), 2);

   return (  1 - 2 * x + (1 + c2) * pow(x,2) ) / (1 - c2) / x;
}

//------------------------------------------------------------------------------
double RHad::gInt(double x)
{
   return (  ( 1 - 2 * x * (1 - x) ) * sin(2 * _deltaTheta) -
   pow(x,2) * _deltaTheta * ( cos(2 * _deltaTheta) - cos(2 * _theta) )  ) / x /
   sqrt(    (  1 - pow( cos(_theta + _deltaTheta), 2 )  ) *
   (  1 - pow( cos(_theta - _deltaTheta), 2 )  )   );
}

//------------------------------------------------------------------------------

double RHad::integrandMassCone(double x, void * point){

RHad * params = static_cast<RHad *>(point);

return params -> sigmaMassRadiativeCone(x) ;
}

//------------------------------------------------------------------------------

double RHad::integrandMass(double x, void * point){

RHad * params = static_cast<RHad *>(point);

return params -> sigmaMassRadiative(x) ;
}

//------------------------------------------------------------------------------

double RHad::integrandCone(double x, void * point){

RHad * params = static_cast<RHad *>(point);

return params -> sigmaRadiativeCone(x) ;
}

//------------------------------------------------------------------------------

double RHad::integrand(double x, void * point){

RHad * params = static_cast<RHad *>(point);

return params -> sigmaRadiative(x) ;
}

//------------------------------------------------------------------------------
double RHad::sigmaMassRadiativeConeCum(double x0, double x1)
{
double result, error;

   gsl_integration_workspace* w = gsl_integration_workspace_alloc (1000);

   gsl_function F;
   F.function = integrandMassCone;
   F.params = this;

   gsl_integration_qags (&F, x0, x1, 0, 1e-7, 1000, w, &result, &error);

   return result;
}

//------------------------------------------------------------------------------
double RHad::sigmaRadiativeConeCum(double x0, double x1)
{
double result, error;

   gsl_integration_workspace* w = gsl_integration_workspace_alloc (1000);

   gsl_function F;
   F.function = integrandCone;
   F.params = this;

   gsl_integration_qags (&F, x0, x1, 0, 1e-7, 1000, w, &result, &error);

   return result;
}

//------------------------------------------------------------------------------
double RHad::sigmaMassRadiativeCum(double x0, double x1)
{
double result, error;

   gsl_integration_workspace* w = gsl_integration_workspace_alloc (1000);

   gsl_function F;
   F.function = integrandMass;
   F.params = this;

   gsl_integration_qags (&F, x0, x1, 0, 1e-7, 1000, w, &result, &error);

   return result;
}

//------------------------------------------------------------------------------
double RHad::sigmaRadiativeCum(double x0, double x1)
{
double result, error;

   gsl_integration_workspace* w = gsl_integration_workspace_alloc (1000);

   gsl_function F;
   F.function = integrand;
   F.params = this;

   gsl_integration_qags (&F, x0, x1, 0, 1e-7, 1000, w, &result, &error);

   return result;
}

} // namespace radiative
