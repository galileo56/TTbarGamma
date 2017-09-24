//------------------------------------------------------------------------------
/// \file RHad.h
//
// Author(s):
//    Vicent Mateu
//
// Copyright:
//    Copyright (C) 2016  Vicent Mateu
//
// Description:
//    Interface of class RHad
//------------------------------------------------------------------------------

#ifndef RHAD_H_
#define RHAD_H_

#include "Running.h"
#include "ElectroWeak.h"

namespace radiative
{
//------------------------------------------------------------------------------
/**
 * \class DeltaMass
 *
 * \brief Computes the pole-to-MSbar subtraction terms, as well as the pole mass from the MS-bar
 *
 *
 *
 * \class RHad
 *
 * \brief Computes the total hadronic cross section in fixed order, with or without initial photon radiation.
 *
 * The computation is performed for massive and massless quarks. No running of alphaQED implemented.
 * The total hadronic cross section is completely inclusive over angles and final-state configuraritions
 * The total hadronic cross section with an ISR photon is completely differential in the photon solid angle: d sigma/dx/dOmega
 * The "cone" radiative cross section is completely inclusive in the hadron side, but integrates in a cone for the photon momentum.
 * x = E_gamma/Q; cTheta = cos(theta), theta is azimutal angle of the photon, measured w.r.t. the beam direction
 * mu refers to the QCD renormalization scales in all cases. Therefore in the case of ISR it has to be chosen around the hadronic system invariant mass.
 * both alphaS and MS-bar quark mass are evaluated at the scale mu. In the pose scheme only alphaS is evaluated at the scale mu.
 *
 * \class MassCorrComputer
 *
 * \brief Computes various radiative corrections for the massive cross section.
 *
 *  Not intended for direct use
 */
 
//------------------------------------------------------------------------------
class DeltaMass
{
private:
    Running _AlphaMass;   // needs as the sole input one object of the class Running
    double _coef[4][3];
public:
   DeltaMass(Running AlphaMass);
   void deltaMSbar(double mu, double deltaM[]);  // deltaM contains the pole-to-MSbar subtraction terms
   double mPole(int order, double mu);           // pole mass
};

//------------------------------------------------------------------------------
class RHad {
private:
    double _rQ[5][3];
    double _alphaQED;      // alphaQED(mZ), no further running implemented
    Running _AlphaMass;    // needs as an input one object of the class Running. This specifies the number of flavors.
    DeltaMass _deltaM;
    ElectroWeak _factors;  // needs as an input one object of the class Electroweak
    int _scheme;           // 0 for pole mass, 1 for MS-bar
    int _order;            // up to alphaS^order
    double _q;             // c.o.m. energy
    double _eH;            // ration between renormalization scale and hadronic system energy: eH = mu/Q/sqrt(1 - 2*x) 
    double _theta;         // polar angle between beam axis and photon momentum
    double _deltaTheta;    // half-amplitude of cone
    double _qF;
    static double integrandMass(double x, void * params);
    static double integrandMassCone(double x, void * params);
    static double integrand(double x, void * params);
    static double integrandCone(double x, void * params);
public:
    RHad(int scheme, int order, double q, double eH, double theta, double deltaTheta, Running AlphaMass, ElectroWeak factors);
    double gInt(double x);
    double g(double x);
    double mPole;                          // pole mass as computed from MS-bar
    double rHad(double q, double mu);      // massless total hadronic cross section normalized to di-muon cross section
    double sigma(double q, double mu);     // massless total hadronic cross section, mediated by a photon only!
    double sigmaMass(double q, double mu); // massive total hadronic cross section
    double sigmaMassRadiative(double x);   // massive total hadronic cross section
    double sigmaRadiative(double x); // massless total hadronic cross section with an ISR photon
    double rHadMass(int current, double q, double mu); // massive total hadronic cross section normalized to di-muon cross section. scheme = 0, 1 for pole and MS-bar. current = 1, 2 for vector and axial.
    double sigmaMassRadiativeCone(double x);            // massive total hadronic cross section, integrated inside a cone around theta, amplitude deltaTheta
    double sigmaRadiativeCone(double x);                // massless total hadronic cross section with an ISR photon, integrated inside a cone around theta, amplitude deltaTheta.
    double sigmaMassRadiativeCum(double x0, double x1); // massive total hadronic cross section, integrated in a bin of photon energy.
    double sigmaRadiativeCum(double x0, double x1);     // massless total hadronic cross section, integrated in a bin of photon energy.
    double sigmaRadiativeConeCum(double x0, double x1); // massless total hadronic cross section, integrated inside a cone around theta, amplitude deltaTheta in a bin of photon energy.    double sigmaMassRadiativeCum(double x0, double x1); // massive total hadronic cross section, integrated inside a cone around theta, amplitude deltaTheta in a bin of photon energy.
    double sigmaMassRadiativeConeCum(double x0, double x1); // massive total hadronic cross section, integrated inside a cone around theta, amplitude deltaTheta in a bin of photon energy.
};

//------------------------------------------------------------------------------
class MassCorrComputer {
private:
    double _m;
    double _v;
public:
    MassCorrComputer(double m, double v);
    double rVTree;
    double rATree;
    double rV1loop;
    double rA1loop;
    double aVMS;
    double aAMS;
};

} // namespace radiative

#endif // RHAD_H_
