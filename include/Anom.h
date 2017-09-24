//------------------------------------------------------------------------------
/// \file Anom.h
//
// Author(s):
//    Vicent Mateu
//
// Copyright:
//    Copyright (C) 2016  Vicent Mateu
//
//
// Description:
//    Interface of class Anom
//------------------------------------------------------------------------------

#ifndef ANOM_H
#define ANOM_H

namespace radiative
{

//------------------------------------------------------------------------------
/**
 * \class Anom
 *
 * \brief Provides the mass anomalous dimension plus the beta function.
 *
 * The QCD beta funcion and mass anomalous dimensions are computed in the MS-bar scheme for a given number of flavors, up to four loops
 * It also provides two functions that are necessary for the running of the quark masses and to compute the mu dependence of observables
 * 
 */
//------------------------------------------------------------------------------


class AnDim
{
private:
    int _nf;                 // Number of active flavors
public:
    AnDim(int Nf = 6);
    double beta[4];         // QCD beta function in MS-bar scheme
    double gammaMass[4];    // QCD mass anomalous dimension in the MS-bar scheme
    void expandAlpha(double coef[][3]);              // mu dependent terms for QCD observables
    double wTilde(int order, double a0, double a1);  // Running kernel for quark masses
    int numFlav;                                     // Gives back the number of active flavors
};

} // namespace radiative

#endif // ANDIM_H
