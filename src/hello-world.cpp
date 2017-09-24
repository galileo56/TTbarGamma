// my first program in C++
/* This is a block comment */
/* can I do
   this*/

# include <iostream>
# include "RHad.h"

using namespace std;
using namespace radiative;

int main () //can I comment here?
{
    //Default options of the xsection_calculator
    double photon_energy, x;
    int order = 1; //Only 1 loop implemented.
    int scheme = 1; //0 for pole mass, 1 for m_s bar
    double energy_cm = 500;
    double eH = 1;
    double alphaQED = 1/127.925;
    //Theta is defined from 7º to 90º (excluding the beampipe), Phi is fully integrated
    double angle = 3.141592*48.5/180; //Pointing angle (theta) of the cone 48.5º
    double half_aperture =  3.141592*41.5/180;//Half aperture of the cone 41.5º
    Running running; //Default constructor called
    ElectroWeak factors; //Default constructor called
    RHad rhad6(scheme, order, energy_cm, eH, angle, half_aperture, running, factors);
    
    cout << "x, E_photon (GeV), E_hadrons (GeV), differential, cone \n\n";

    for (int i = 1; i < 52; i++) {
    photon_energy = energy_cm * 0.018 + (i - 1)/25.;
    x = photon_energy/energy_cm;
  cout << x << "  " << photon_energy << "  " << energy_cm * (1 - 2 * x) << " " << rhad6.sigmaMassRadiative(x) << " " << rhad6.sigmaMassRadiativeCone(x) << "\n\n" ;
  }
  
    cout << "\n integration over the cone and E_photon between 9 and 11 GeV \n\n";
  
   cout << rhad6.sigmaMassRadiativeConeCum(0.018, 0.022) << "\n";

    return 0;
}
