//------------------------------------------------------------------------------
/// \file ElectroWeak.h
//
// Author(s):
//    Vicent Mateu
//
// Copyright:
//    Copyright (C) 2016  Vicent Mateu
//
// Description:
//    Interface of class ElectroWeak
//------------------------------------------------------------------------------

#ifndef ELECTROWEAK_H
#define ELECTROWEAK_H

namespace radiative
{

//------------------------------------------------------------------------------
/**
 * \class ElectroWeak
 *
 * \brief Provides the Electroweak factors for the e+e- --> hadrons process
 *
 * It includes both photon and Z exchange. alphaQED factor not included.
 *
 * Uses an optimised Breit-Wigner for the Z propagator
 */
//------------------------------------------------------------------------------

class ElectroWeak
{
private:
    double _mZ;            // Z boson mass
    double _gammaZ;        // Z boson total width
    double _sin2ThetaW;    // Sinus of the Weak angle
    double _ve;
    double _ae;
    double _vUp;
    double _vDown;
    double _aUp;
public:
    ElectroWeak(double mZ = 91.187, double gammaZ = 2.4952,
    double sin2ThetaW = 0.23119);
    void ewFactors(int nf, double Q, double coef[2]); // coef stores the EW factors for vector [0] and axial [1] currents. nf is used to tag the quark produced in the primary vertex
    double charge(int nf);                           // charge of the nf-th quark
};


} // namespace radiative

#endif // ELECTROWEAK_H
