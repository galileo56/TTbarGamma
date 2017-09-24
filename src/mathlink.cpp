#include <string>

#include "RHad.h"
#include <gsl/gsl_sf_dilog.h>

using namespace radiative;

double sigmaRad(int order, int nf, double mW, double Mz, double aMz, double alphaQED, double gammaZ,
double sin2ThetaW, double mQ, double muQ, double mCharm, double muCharm, double x,
double theta, double q, double eh){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(1, order, q, eh, theta, 0., alpha6, EW);

   return rhad5.sigmaRadiative(x);
}

double sigmaRadCone(int order, int nf, double mW, double Mz, double aMz, double alphaQED,
double gammaZ, double sin2ThetaW, double mQ, double muQ, double mCharm, double muCharm,
double x, double theta, double deltaTheta, double q, double eh){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(1, order, q, eh, theta, deltaTheta, alpha6, EW);

   return rhad5.sigmaRadiativeCone(x);
}

double radiativeCone(double x, double theta, double deltaTheta){

   Running alpha6(4, 6, 91.187, 0.118, 170, 170, 170, 0, 0, 0.1);
   ElectroWeak EW(91.187, 0, 0.2);
   RHad rhad5(1, 0, 100, 1, theta, deltaTheta, alpha6, EW);

   return rhad5.gInt(x);
}

double radiativeKernel(double x, double theta){

   Running alpha6(4, 6, 91.187, 0.118, 170, 170, 170, 0, 0, 0.1);
   ElectroWeak EW(91.187, 0, 0.2);
   RHad rhad5(1, 0, 100, 1, theta, 0, alpha6, EW);

   return rhad5.g(x);
}

double sigmaMassRad(int scheme, int order, int nf, double mW, double Mz, double aMz,
double alphaQED, double gammaZ, double sin2ThetaW, double mQ, double muQ, double mCharm,
double muCharm, double x, double theta, double q, double eh){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(scheme, order, q, eh, theta, 0., alpha6, EW);

   return rhad5.sigmaMassRadiative(x);
}

double sigmaMassRadCone(int scheme, int order, int nf, double mW, double Mz, double aMz,
double alphaQED, double gammaZ, double sin2ThetaW, double mQ, double muQ, double mCharm,
double muCharm, double x, double theta, double deltaTheta, double q, double eh){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(scheme, order, q, eh, theta, deltaTheta, alpha6, EW);

   return rhad5.sigmaMassRadiativeCone(x);
}

double sigmaMassRadConeCum(int scheme, int order, int nf, double mW, double Mz, double aMz,
double alphaQED, double gammaZ, double sin2ThetaW, double mQ, double muQ, double mCharm,
double muCharm, double x0, double x1, double theta, double deltaTheta, double q, double eh){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(scheme, order, q, eh, theta, deltaTheta, alpha6, EW);

   return rhad5.sigmaMassRadiativeConeCum(x0, x1);
}

double sigmaMassRadCum(int scheme, int order, int nf, double mW, double Mz, double aMz,
double alphaQED, double gammaZ, double sin2ThetaW, double mQ, double muQ, double mCharm,
double muCharm, double x0, double x1, double theta, double q, double eh){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(scheme, order, q, eh, theta, 0., alpha6, EW);

   return rhad5.sigmaMassRadiativeCum(x0, x1);
}

double sigmaRadCum(int order, int nf, double mW, double Mz, double aMz, double alphaQED,
double gammaZ, double sin2ThetaW, double mQ, double muQ, double mCharm, double muCharm,
double x0, double x1, double theta, double q, double eh){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(0, order, q, eh, theta, 0., alpha6, EW);

   return rhad5.sigmaRadiativeCum(x0, x1);
}

double sigmaRadConeCum(int order, int nf, double mW, double Mz, double aMz, double alphaQED,
double gammaZ, double sin2ThetaW, double mQ, double muQ, double mCharm, double muCharm,
double x0, double x1, double theta, double deltaTheta, double q, double eh){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(0, order, q, eh, theta, deltaTheta, alpha6, EW);

   return rhad5.sigmaRadiativeConeCum(x0, x1);
}

double sigmaHadMass(int scheme, int order, int nf, double mW, double Mz, double aMz,
double alphaQED, double gammaZ, double sin2ThetaW, double mQ, double muQ, double mCharm,
double muCharm, double q, double mu){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, gammaZ, sin2ThetaW);
   RHad rhad5(scheme, order, q, 1., 0., 0., alpha6, EW);

   return rhad5.sigmaMass(q, mu);
}

void ewfactors(int nf, double Q, double Mz, double gammaZ, double sin2ThetaW){
ElectroWeak ew(Mz, gammaZ, sin2ThetaW);
double res[2];
ew.ewFactors(nf, Q, res);
   MLPutRealList(stdlink, res, 2);
   MLEndPacket(stdlink);
}

void betaQCD(int nf){
AnDim anomDim(nf);
double result[4];
   for(int i = 0; i < 4; ++i){result[i] = anomDim.beta[i];}
   MLPutRealList(stdlink, result, 4);
   MLEndPacket(stdlink);
}

void gammaMassQCD(int nf){
AnDim anomDim(nf);
double result[4];
   for(int i = 0; i < 4; ++i){result[i] = anomDim.gammaMass[i];}
   MLPutRealList(stdlink, result, 4);
   MLEndPacket(stdlink);
}

double alphaqcd(int order, int nf, double Mz, double aMz, double mQ, double muQ,
double mCharm, double muCharm, double mu){

   Running alpha6(order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, 80.383, 1/127.925);

   return alpha6.alpha(mu);
}

double massqcd(int order, int nf, double Mz, double aMz, double mQ, double muQ,
double mCharm, double muCharm, double mu){

   Running alpha6(order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, 80.383, 1/127.925);

   return alpha6.mass(mu);
}

double polemass(int order, int nf, double Mz, double aMz, double mQ, double muQ,
double mCharm, double muCharm, double mu){

   Running alpha6(order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, 80.383, 1/127.925);
   DeltaMass deltaM(alpha6);

   return deltaM.mPole(3, mu);
}

double alphageneric(int order, int nf, double Mz, double aMz, double mu){

   Running alpha6(order, nf, Mz, aMz, 170., 170., 1.3, 1.3, 80.383, 1/127.925);

   return alpha6.alphaGeneric(nf, Mz, aMz, mu);
}

double alphaQED(int nf, double Mw, double Mz, double aMz, double mu){

   Running alpha6(4, nf, Mz, 0.118, 170., 170., 1.3, 1.3, Mw, aMz);

   return alpha6.alphaQED(mu);
}

double rhad(int order, int nf, double Mz, double aMz, double mQ, double muQ,
double mCharm, double muCharm, double q, double mu){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, 80.383, 1/127.925);
   ElectroWeak EW(Mz, 20., 0.2);
   RHad rhad5(1, order, q, 1., 0., 0., alpha6, EW);

   return rhad5.rHad(q, mu);
}

double sigmaHad(int order, int nf, double mW, double Mz, double aMz, double alphaQED,
double mQ, double muQ, double mCharm, double muCharm, double q, double mu){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mW, alphaQED);
   ElectroWeak EW(Mz, 20., 0.2);
   RHad rhad5(1, order, q, 1., 0., 0., alpha6, EW);

   return rhad5.sigma(q, mu);
}

double rhadmass(int scheme, int current, int order, int nf, double Mz, double aMz,
double mQ, double muQ, double mCharm, double muCharm, double q, double mu){

   Running alpha6(4, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, 80.383, 1/127.925);
   ElectroWeak EW(Mz, 20., 0.2);
   RHad rhad5(scheme, order, q, 1., 0., 0., alpha6, EW);

   return rhad5.rHadMass(current, q, mu);
}

double diLog(double mu){return gsl_sf_dilog(mu);}

int main(int argc, char* argv[])
{
	return MLMain(argc, argv);
}

