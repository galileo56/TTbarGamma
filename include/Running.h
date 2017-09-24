//------------------------------------------------------------------------------
/// \file Alpha.h
//
// Author(s):
//    Vicent Mateu
//
// Copyright:
//    Copyright (C) 2016  Vicent Mateu
//
// Description:
//    Interface of class Alpha
//------------------------------------------------------------------------------

#ifndef ALPHA_H
#define ALPHA_H

#include "Anom.h"
#include <complex>

namespace radiative
{

//------------------------------------------------------------------------------
/**
 * \class Running
 *
 * \brief Computes the running of the strong coupling constant and heavy quark masses.
 *
 * It uses a semi-analytic expansion for alphaS in which alpha*log is treated as O(1).
 * There is no approximation from the heavy masses
 * It computes the threshold matching at the specified points
 *
 */
 
//------------------------------------------------------------------------------
class Running
{
private:
    int _order;       // number of terms in the included in the beta function. 1 < order < 4
    int _nF;          // number of active flavors: alpha_s^(nF)
    double _mZ;       // reference scale mb < mZ < mt; Usually the Z-boson mass.
    double _mW;       // mass of W boson
    double _aQEDmZ;   // alphaQED(mZ)
    double _aMz;      // reference value alpha_s^(5)(mZ)
    double _alphaRef; // internal use
    double _muRef;    // internal use
    double _aQEDref;  // internal use
    double _betaQED;  // internal use
    double _muQEDref; // internal use
    double _mt;       // top (for nf = 6) or bottom (for nf < 5) mass. m(m) in MS-bar.
    double _muM;      // scale at which the top (nf = 6) or bottom (nf < 5) is integrated out
    double _mCharm;   // charm mass, only used if nf < 4
    double _muCharm;  // scale at which the charm mass is integrated out
    double alphaQEDGeneric(double beta, double mz, double amz, double mu);
public:
    Running(int order = 4, int nF = 6, double mZ = 91.187, double aMz = 0.1184,
    double mt = 170., double muM = 170., double mCharm = 1.4, double muCharm = 1.4,
    double mW = 80.385, double aQEDmZ = 1/127.925);

    AnDim run;
    double aQED;            // same as _aQEDmZ
    double mass(double mu);     // running mass for top, bottom, charm, ... for nf = 6, 5, 4, ...
    double alphaGeneric(int nf, double mz, double amz, double mu); // Generical alphaS in which no threshold matching is performed.
    double alpha(double mu);    // alphaS evaluated at the scale mu, includes threshold matching. 
    double alphaQED(double mu); // alphaQED evaluated at the scale mu, includes threshold matching. 
    double mTop;                // top (for nf = 6) or bottom (for nf < 5) mass. m(m) in MS-bar
    std::complex<double> alpha(std::complex<double> mu);
    std::complex<double> alphaGeneric(int nf, double mz, double amz, std::complex<double> mu);
};

} // namespace radiative

#endif // ALPHA_H
