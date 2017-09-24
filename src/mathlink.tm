:Evaluate:	BeginPackage["mathlinkpackage`"]

:Evaluate:      Print["     Package for top production at a linear collider "]
:Evaluate:      Print["     Author:            Vicent Mateu                 "]
:Evaluate:      Print["     Last modification: 04 - 02 - 2016               "]
:Evaluate:      Print["     Version:           1.00                         "]

:Evaluate: Mzdef = 91.187

:Evaluate: mWdef = 80.385

:Evaluate: aMzdef = 0.1184

:Evaluate: aQEDdef = 1/127.925

:Evaluate: aQEDdef = 0.00781751

:Evaluate:	RHad::usage="RHad[order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, Q, mu] computes the total hadronic cross section normalized to the dimuon production, ignoring mass corrections. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaHad::usage="SigmaHad[order, nf, mW, Mz, aMz, aQED, mQ, muQ, mCharm, muCharm, Q, mu] computes the total hadronic cross section ignoring mass corrections. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaRad::usage="SigmaRad[order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x, theta, Q, mu] computes the total hadronic cross section including an ISR photon, completely differential in photon momentum solid angle and in x = Egamma/Q, ignoring mass corrections. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaRadCone::usage="SigmaRadCone[order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x, theta, deltaTheta, Q, mu] computes the total hadronic cross section including an ISR photon, diffential in x = Egamma/Q and integrating inside a cone around the photon momentum, ignoring mass corrections. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	RadiativeCone::usage="RadiativeCone[x, theta, deltaTheta] computes the cone integrating kernel."

:Evaluate:	RadiativeKernel::usage="RadiativeKernel[x, theta] computes the radiative kernel."

:Evaluate:	SigmaMassRad::usage="SigmaMassRad[scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x, theta, Q, mu] computes the total massive hadronic cross section including an ISR photon, completely differential in photon momentum solid angle and in x = Egamma/Q. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaMassRadCone::usage="SigmaMassRadCone[scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x, theta, deltaTheta, Q, mu] computes the total massive hadronic cross section including an ISR photon, differential x = Egamma/Q and integrating inside a cone around the photon momentum. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaMassRadConeCum::usage="SigmaMassRadConeCum[scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x0, x1, theta, deltaTheta, Q, eh] computes the total massive hadronic cross section including an ISR photon, integrating in x = Egamma/Q and inside a cone around the photon momentum. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaMassRadCum::usage="SigmaMassRadCum[scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x0, x1, theta, Q, eh] computes the total massive hadronic cross section including an ISR photon, integrating in x = Egamma/Q. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaRadConeCum::usage="SigmaRadConeCum[order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x0, x1, theta, deltaTheta, Q, eh] computes the total massless hadronic cross section including an ISR photon, integrating in x = Egamma/Q and inside a cone around the photon momentum. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaRadCum::usage="SigmaRadCum[order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x0, x1, theta, Q, eh] computes the total massless hadronic cross section including an ISR photon, integrating in x = Egamma/Q. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	SigmaHadMass::usage="SigmaHadMass[scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, Q, mu] computes the total hadronic cross section for a massive quark, including EW factors. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	RHadMass::usage="RHadMass[scheme, current, order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, Q, mu] computes the total hadronic cross section normalized to the dimuon production, including mass corrections. scheme = 0, 1 for pole and MS-bar. current = 1, 2 for vector or axial-vector mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	AlphaQCD::usage="AlphaQCD[order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu] computes alpha strong for nf active flavors, computing threshold matching. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	AlphaGeneric::usage="AlphaGeneric[order, nf, Mz, aMz, mu] computes alpha strong for nf active flavors, no threshold matching computed. Refrence point is alphaS(nf, Mz) = aMz."

:Evaluate:	AlphaQED::usage="AlphaQED[nf, Mw, Mz, aMz, mu] computes alphaQED for nf active flavors, threshold matching computed. Refrence point is alphaQED(Mz) = aMz."

:Evaluate:	MassQCD::usage="MassQCD[order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu] computes the running of the MS-bar mass for nf active flavors. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:	PoleMass::usage="PoleMass[order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu] computes the pole mass from the MS-bar for nf active flavors. mQ refers to the top (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4."

:Evaluate:  BetaQCD::usage = "BetaQCD[nf] computes the QCD beta function"

:Evaluate:  GammaMass::usage = "GammaMass[nf] computes the quark anomalous dimension"

:Evaluate:	DiLog::usage="DiLog[x] computes the dilogarithm"

:Evaluate:  EWFactors::usage="EWFactors[nf, Q, Mz, GammaZ, sin2ThetaW] electroweak factors"

:Evaluate:	Begin["`private`"]

:Begin:
:Function:      ewfactors
:Pattern:       EWFactors[nf_, Q_, Mz_, GammaZ_, sin2ThetaW_]
:Arguments:     {nf, Q, Mz, GammaZ, sin2ThetaW}
:ArgumentTypes: {Integer, Real, Real, Real, Real}
:ReturnType:    Manual
:End:

:Begin:
:Function:      betaQCD
:Pattern:       BetaQCD[nf_]
:Arguments:     {nf}
:ArgumentTypes: {Integer}
:ReturnType:    Manual
:End:

:Begin:
:Function:      gammaMassQCD
:Pattern:       GammaMass[nf_]
:Arguments:     {nf}
:ArgumentTypes: {Integer}
:ReturnType:    Manual
:End:

:Begin:
:Function:		alphaqcd
:Pattern:		AlphaQCD[order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, muCharm_, mu_]
:Arguments:		{order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		rhadmass
:Pattern:		RHadMass[scheme_, current_, order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, 
                muCharm_, q_, mu_]
:Arguments:		{scheme, current, order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, q, mu}
:ArgumentTypes:	{Integer, Integer, Integer, Integer, Real, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		rhad
:Pattern:		RHad[order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, muCharm_, q_, mu_]
:Arguments:		{order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, q, mu}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaHad
:Pattern:		SigmaHad[order_, nf_, mW_, Mz_, aMz_, aQED_, mQ_, muQ_, mCharm_, muCharm_,
                 q_,  mu_]
:Arguments:		{order, nf, mW, Mz, aMz, aQED, mQ, muQ, mCharm, muCharm, q, mu}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaRad
:Pattern:		SigmaRad[order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_, sin2ThetaW_, mQ_,
                muQ_, mCharm_, muCharm_, x_, theta_, q_, mu_]
:Arguments:		{order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm,
                 muCharm, x, theta, q, mu}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real, Real, Real, 
                Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaRadCone
:Pattern:		SigmaRadCone[order_, nf_, _mW_, Mz_, aMz_, aQED_, gammaZ_, sin2ThetaW_,
                mQ_, muQ_, mCharm_, muCharm_, x_, theta_, deltaTheta_, q_, mu_]
:Arguments:		{order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm,
                muCharm, x, theta, deltaTheta, 
                q, mu}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real, Real, Real,
                Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		radiativeCone
:Pattern:		RadiativeCone[x_, theta_, deltaTheta_]
:Arguments:		{x, theta, deltaTheta}
:ArgumentTypes:	{Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		radiativeKernel
:Pattern:		RadiativeKernel[x_, theta_]
:Arguments:		{x, theta}
:ArgumentTypes:	{Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaMassRad
:Pattern:		SigmaMassRad[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,
                sin2ThetaW_, mQ_, muQ_, mCharm_,  muCharm_, x_, theta_, q_, mu_]
:Arguments:		{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,
                mCharm, muCharm, x, theta, q,  mu}
:ArgumentTypes:	{Integer, Integer, Integer, Real, Real, Real, Real, Real, Real, Real,
                Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaMassRadCone
:Pattern:		SigmaMassRadCone[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,  
                sin2ThetaW_, mQ_, muQ_, mCharm_,  muCharm_, x_, theta_, deltaTheta_, q_, 
                mu_]
:Arguments:		{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,
                mCharm, muCharm, x, theta, deltaTheta, q,  mu}
:ArgumentTypes:	{Integer, Integer, Integer, Real, Real, Real, Real, Real, Real, Real,
                Real, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaMassRadConeCum
:Pattern:		SigmaMassRadConeCum[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,  
                sin2ThetaW_, mQ_, muQ_, mCharm_,  muCharm_, x0_, x1_, theta_, deltaTheta_, 
                q_, eh_]
:Arguments:		{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,
                mCharm, muCharm, x0, x1, theta, deltaTheta, q,  eh}
:ArgumentTypes:	{Integer, Integer, Integer, Real, Real, Real, Real, Real, Real, Real,
                Real, Real, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaRadConeCum
:Pattern:		SigmaRadConeCum[order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_, sin2ThetaW_,
                mQ_, muQ_, mCharm_,  muCharm_, x0_, x1_, theta_, deltaTheta_, q_, eh_]
:Arguments:		{order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, 
                muCharm, x0, x1, theta, deltaTheta, q, eh}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real, Real,
                Real, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaMassRadCum
:Pattern:		SigmaMassRadCum[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,  
                sin2ThetaW_, mQ_, muQ_, mCharm_,  muCharm_, x0_, x1_, theta_, q_, eh_]
:Arguments:		{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,
                mCharm, muCharm, x0, x1, theta, q,  eh}
:ArgumentTypes:	{Integer, Integer, Integer, Real, Real, Real, Real, Real, Real, Real,
                Real, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaRadCum
:Pattern:		SigmaRadCum[order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_, sin2ThetaW_,
                mQ_, muQ_, mCharm_,  muCharm_, x0_, x1_, theta_, q_, eh_]
:Arguments:		{order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, 
                muCharm, x0, x1, theta, q,  eh}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real, Real,
                Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		sigmaHadMass
:Pattern:		SigmaHadMass[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,
                sin2ThetaW_, mQ_, muQ_, mCharm_, muCharm_, q_, mu_]
:Arguments:		{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,
                 mCharm, muCharm, q, mu}
:ArgumentTypes:	{Integer, Integer, Integer, Real, Real, Real, Real, Real, Real, Real, 
                Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		massqcd
:Pattern:		MassQCD[order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, muCharm_, mu_]
:Arguments:		{order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		polemass
:Pattern:		PoleMass[order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, muCharm_, mu_]
:Arguments:		{order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		alphageneric
:Pattern:		AlphaGeneric[order_, nf_, Mz_, aMz_, mu_]
:Arguments:		{order, nf, Mz, aMz, mu}
:ArgumentTypes:	{Integer, Integer, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		alphaQED
:Pattern:		AlphaQED[nf_, mW_, Mz_, aMz_, mu_]
:Arguments:		{nf, mW, Mz, aMz, mu}
:ArgumentTypes:	{Integer, Real, Real, Real, Real}
:ReturnType:	Real
:End:

:Begin:
:Function:		diLog
:Pattern:		DiLog[mu_]
:Arguments:		{mu}
:ArgumentTypes:	{Real}
:ReturnType:	Real
:End:

:Evaluate:	End[]
:Evaluate:	EndPackage[]
