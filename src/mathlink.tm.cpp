/*
 * This file automatically produced by /Applications/Mathematica.app/Contents/SystemFiles/Links/MathLink/DeveloperKit/MacOSX-x86-64/CompilerAdditions/mprep from:
 *	/Users/vmateu/GitHub/TTbarGamma/src/mathlink.tm
 *	/Users/vmateu/GitHub/TTbarGamma/src/mathlink.cpp
 * mprep Revision 18 Copyright (c) Wolfram Research, Inc. 1990-2013
 */

#define MPREP_REVISION 18

#if CARBON_MPREP
#include <Carbon/Carbon.h>
#include <mathlink/mathlink.h>
#else
#include "mathlink.h"
#endif

int MLAbort = 0;
int MLDone  = 0;
long MLSpecialCharacter = '\0';

MLINK stdlink = 0;
MLEnvironment stdenv = 0;
#if MLINTERFACE >= 3
MLYieldFunctionObject stdyielder = (MLYieldFunctionObject)0;
MLMessageHandlerObject stdhandler = (MLMessageHandlerObject)0;
#else
MLYieldFunctionObject stdyielder = 0;
MLMessageHandlerObject stdhandler = 0;
#endif /* MLINTERFACE >= 3 */

#if DARWIN_MATHLINK && CARBON_MPREP
#define rMenuBar	1128
#define rAboutBox	1128
#define rBadSIZE	1127
#define mApple		1128
#define iAbout		1
#define mFile		1129
#define mEdit		1130

AEEventHandlerUPP handle_core_ae_upp;
ModalFilterUPP about_filter_upp;
UserItemUPP outline_hook_upp;

extern pascal OSErr handle_core_ae( const AppleEvent* event, AppleEvent* reply, long refcon);
extern int init_macintosh( void);
extern void do_about_box( void);
extern int _handle_user_event( unsigned long ticks);

pascal OSErr handle_core_ae( const AppleEvent* event, AppleEvent* reply, long refcon)
{
	DescType eventid, gottype;
	Size got;
	reply = (AppleEvent*)0; /* suppress unused warning */
	refcon = 0; /* suppress unused warning */
	if( noErr == AEGetAttributePtr(event, keyEventIDAttr, typeType, &gottype, (Ptr)&eventid, sizeof(eventid), &got)
	&& errAEDescNotFound == AEGetAttributePtr(event, keyMissedKeywordAttr, typeWildCard, &gottype, nil, 0, &got)
	){
		switch(eventid){
		case kAEQuitApplication:
			MLDone = MLAbort = 1;
		case kAEOpenApplication:
			return noErr;
		}
	}
	return errAEEventNotHandled;
}


static void set_about_item(void){
	Str255 aboutitem;
	StringHandle abouthandle;

	GetMenuItemText( GetMenuHandle(mApple), iAbout, aboutitem);
	abouthandle = NewString( aboutitem);
	if( abouthandle){
		StringPtr curApName = LMGetCurApName();
		long len = Munger( (Handle)abouthandle, 1, "MathLink\252", 9, curApName + 1, *curApName); 
		if( len > 0){
			**abouthandle = (unsigned char)len; 
			HLock( (Handle)abouthandle);
			SetMenuItemText( GetMenuHandle(mApple), iAbout, *abouthandle);
		}
		DisposeHandle( (Handle)abouthandle);
	}
}


static pascal Boolean about_filter(DialogPtr dptr, EventRecord *theEvent, short *theItem){
	if( theEvent->what == keyDown || theEvent->what == autoKey){
		unsigned char theKey = (unsigned char)(theEvent->message & charCodeMask);
		if( theKey == 0x0D || (theKey == 0x03 && !(theEvent->modifiers & controlKey))){
			short itemType;
			ControlHandle okHdl;
			Rect itemRect;
#if UNIVERSAL_INTERFACES_VERSION >= 0x0301
			unsigned long Ticks;
#else
			long Ticks;
#endif
			GetDialogItem( dptr, ok, &itemType, (Handle*) &okHdl, &itemRect);
			HiliteControl( okHdl, kControlButtonPart);
#ifdef __cplusplus
			Delay( 3, &Ticks);
#else
			Delay( 3, (void *)&Ticks);
#endif
			HiliteControl( okHdl, 0);
			*theItem = ok;
			return true;
		}
	}
	return false;
}

static pascal void outline_hook(DialogRef dptr, short theItem){
	short  itemType;
	Handle itemHdl;
	Rect itemRect;
	PenState oldpen;
	GetDialogItem( dptr, theItem, &itemType, &itemHdl, &itemRect);
	GetPenState( &oldpen);
	PenSize( 3, 3);
	FrameRoundRect( &itemRect, 16, 16);
	SetPenState( &oldpen);
}



/* edit here and in mathlink.r */
static unsigned short missing_DITL[] = { 5,
	0, 0, 76, 120, 96, 200, 0x5C, 0x30, 0x30, 0x34, 0x5C, 0x30, 0x30, 0x32, 0x4F, 0x4B, /* '\004\002', 'OK', */
	0, 0, 12, 13, 30, 28, 0x5C, 0x32, 0x31, 0x30, 0x5C, 0x30, 0x30, 0x31, 0x41, 0x5C, 0x30, /*'\210\001', 'A\0', */
	0, 0, 12, 27, 30, 96, 0x5C, 0x32, 0x31, 0x30, 0x5C, 0x30, 0x31, 0x30, 0x20, 0x4D, 0x61, 0x74, 0x68, 0x4C, 0x69, 0x6E, 0x6B, /*'\210\010', 'Ma','th','Li','nk', */
	0, 0, 12, 95, 30, 308, 0x5C, 0x32, 0x31, 0x30, 0x5C, 0x30, 0x33, 0x34, 0x5C, 0x32, 0x35, 0x32, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x20, 0x67, 0x65, 0x6E, 0x65, 0x72, 0x61, 0x74, 0x65, 0x64, 0x20, 0x62, 0x79, 0x20, 0x6D, 0x70, 0x72, 0x65, 0x70, /*'\210\034', '\252','pr','og','ra','m ','ge','ne','ra','te','d ','by',' m','pr','ep', */
	0, 0, 42, 49, 56, 271, 0x5C, 0x32, 0x31, 0x30, 0x5C, 0x30, 0x35, 0x30, 0x6D, 0x70, 0x72, 0x65, 0x70, 0x5C, 0x32, 0x35, 0x31, 0x20, 0x57, 0x6F, 0x6C, 0x66, 0x72, 0x61, 0x6D, 0x20, 0x52, 0x65, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x20, 0x31, 0x39, 0x39, 0x30, 0x2D, 0x32, 0x30, 0x30, 0x32, /*'\210\050', 'mp','re','p ','\251 ','Wo','lf','ra','m','Re','se','ar','ch',', ','In','c.',' 1','99','0-','20','02', */ /* 1990-2002 */
	0, 0, 170, 10, 190, 30, 0x5C, 0x32, 0x30, 0x30, 0x5C, 0x30, 0x30, 0x30 /*'\200\000' */
};


int init_macintosh( void)
{
	static int initdone = 0;
	Handle menuBar;
	long attributes;

	/* semaphore required for preemptive threads */
	if( initdone) return initdone == 1;
	initdone = -1;

	/* should I check for MLNK resource too as launch-filtering is done based on it? */
	/* too late--since I'm running there likely wasn't a problem (this time anyway). */
	
	menuBar = GetNewMBar(rMenuBar);
	if( menuBar){
		SetMenuBar(menuBar);
		DisposeHandle(menuBar);
	}else{
		MenuHandle am, fm, em;
		am = NewMenu( mApple, (unsigned char*)"\001\024");
		fm = NewMenu( mFile, (unsigned char*)"\004File");
		em = NewMenu( mEdit, (unsigned char*)"\004Edit");
		if( !am || !fm || !em) return 0;
		AppendMenu( am, (unsigned char*)"\022About MathLink\252\311;-");
                DisableMenuItem(am, 0);
		InsertMenu( am, 0);
		AppendMenu( fm, (unsigned char*)"\006Quit/Q");
		InsertMenu( fm, 0);
		AppendMenu( em, (unsigned char*)"\043Undo/Z;-;Cut/X;Copy/C;Paste/V;Clear");
                DisableMenuItem(em, 0);
		InsertMenu( em, 0);
	}

	AppendResMenu( GetMenuHandle(mApple), 'DRVR');
	set_about_item();
	DrawMenuBar();
	about_filter_upp =  NewModalFilterUPP( about_filter);
	outline_hook_upp = NewUserItemUPP( outline_hook);
	if( Gestalt( gestaltAppleEventsAttr, &attributes) == noErr
	&& ((1 << gestaltAppleEventsPresent) & attributes)){
		handle_core_ae_upp = NewAEEventHandlerUPP( handle_core_ae);
		(void) AEInstallEventHandler( kCoreEventClass, typeWildCard, handle_core_ae_upp, 0, false);
	}else{
		return 0; /* this may be too strong since I am, after all, running. */
	}

	initdone = 1;
	return initdone == 1;
}

void do_about_box( void)
{
	GrafPtr oldPort;
	DialogPtr dptr;
	short item, itemType;
	Handle itemHdl;
	Rect itemRect;

	dptr = GetNewDialog( rAboutBox, nil, (WindowPtr)-1L);
	
	if( dptr == (DialogPtr)0){
		Handle items = NewHandle( sizeof(missing_DITL));
		static Rect bounds = {40, 20, 150, 340};

		if( ! items) return;
		BlockMove( missing_DITL, *items, sizeof(missing_DITL));

		dptr = NewColorDialog( nil, &bounds, (unsigned char*)"\005About",
					false, dBoxProc, (WindowPtr)-1L, false, 0, items);
                }
	
	if( dptr == (DialogPtr)0) return;
	GetPort (&oldPort);
	SetPort (GetDialogPort(dptr));
	GetDialogItem( dptr, ok, &itemType, &itemHdl, &itemRect);
	InsetRect( &itemRect, -4, -4);
	SetDialogItem( dptr, 6, userItem + itemDisable, (Handle)outline_hook_upp, &itemRect);

	FlushEvents( everyEvent, 0);
        ShowWindow( GetDialogWindow(dptr));

	do {
		ModalDialog( about_filter_upp, &item);
	} while( item != ok);

	DisposeDialog( dptr);
	SetPort( oldPort);
}

int _handle_user_event( unsigned long ticks)
{
	EventRecord event;

	if( WaitNextEvent(everyEvent, &event, ticks, nil)){
		long      menuResult = 0;
		short     menuID, menuItem;
		WindowPtr window;
		Str255    daName;

		switch ( event.what ) {
		case mouseDown:
			if( FindWindow(event.where, &window) == inMenuBar)
				menuResult = MenuSelect(event.where);
			break;
		case keyDown:
			if( event.modifiers & cmdKey )
				menuResult = MenuKey((short)event.message & charCodeMask);
			break;
		case kHighLevelEvent:
			AEProcessAppleEvent(&event);
			break;
		}

		menuID = HiWord(menuResult);
		menuItem = LoWord(menuResult);
		switch ( menuID ) {
		case mFile:
			MLDone = MLAbort = 1;
			break;
		case mApple:
			switch ( menuItem ) {
			case iAbout:
				do_about_box();
				break;
			default:
				GetMenuItemText(GetMenuHandle(mApple), menuItem, daName);
				break;
			}
			HiliteMenu(0);
		}
	}
	return MLDone;
}

#if MLINTERFACE >= 3
MLYDEFN( int, MLDefaultYielder, ( MLINK mlp, MLYieldParameters yp))
#else
MLYDEFN( devyield_result, MLDefaultYielder, ( MLINK mlp, MLYieldParameters yp))
#endif /* MLINTERFACE >= 3 */
{
	mlp = mlp; /* suppress unused warning */
#if MLINTERFACE >= 3
	return (int)_handle_user_event( MLSleepYP(yp));
#else
	return _handle_user_event( MLSleepYP(yp));
#endif /* MLINTERFACE >= 3 */
}

#endif /* (DARWIN_MATHLINK && CARBON_MPREP */

/********************************* end header *********************************/


# line 1 "/Users/vmateu/GitHub/TTbarGamma/src/mathlink.cpp"
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

# line 519 "/Users/vmateu/GitHub/TTbarGamma/src/mathlink.tm.cpp"


void ewfactors P(( int _tp1, double _tp2, double _tp3, double _tp4, double _tp5));

#if MLPROTOTYPES
static int _tr0( MLINK mlp)
#else
static int _tr0(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	double _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLNewPacket(mlp) ) goto L5;

	ewfactors(_tp1, _tp2, _tp3, _tp4, _tp5);

	res = 1;
L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr0 */


void betaQCD P(( int _tp1));

#if MLPROTOTYPES
static int _tr1( MLINK mlp)
#else
static int _tr1(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLNewPacket(mlp) ) goto L1;

	betaQCD(_tp1);

	res = 1;
L1: 
L0:	return res;
} /* _tr1 */


void gammaMassQCD P(( int _tp1));

#if MLPROTOTYPES
static int _tr2( MLINK mlp)
#else
static int _tr2(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLNewPacket(mlp) ) goto L1;

	gammaMassQCD(_tp1);

	res = 1;
L1: 
L0:	return res;
} /* _tr2 */


double alphaqcd P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9));

#if MLPROTOTYPES
static int _tr3( MLINK mlp)
#else
static int _tr3(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLNewPacket(mlp) ) goto L9;

	_rp0 = alphaqcd(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr3 */


double rhadmass P(( int _tp1, int _tp2, int _tp3, int _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12));

#if MLPROTOTYPES
static int _tr4( MLINK mlp)
#else
static int _tr4(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	int _tp3;
	int _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetInteger( mlp, &_tp3) ) goto L2;
	if ( ! MLGetInteger( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLNewPacket(mlp) ) goto L12;

	_rp0 = rhadmass(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr4 */


double rhad P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10));

#if MLPROTOTYPES
static int _tr5( MLINK mlp)
#else
static int _tr5(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLNewPacket(mlp) ) goto L10;

	_rp0 = rhad(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr5 */


double sigmaHad P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12));

#if MLPROTOTYPES
static int _tr6( MLINK mlp)
#else
static int _tr6(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLNewPacket(mlp) ) goto L12;

	_rp0 = sigmaHad(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr6 */


double sigmaRad P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15, double _tp16));

#if MLPROTOTYPES
static int _tr7( MLINK mlp)
#else
static int _tr7(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _tp16;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLGetReal( mlp, &_tp16) ) goto L15;
	if ( ! MLNewPacket(mlp) ) goto L16;

	_rp0 = sigmaRad(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15, _tp16);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L16: L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr7 */


double sigmaRadCone P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15, double _tp16, double _tp17));

#if MLPROTOTYPES
static int _tr8( MLINK mlp)
#else
static int _tr8(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _tp16;
	double _tp17;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLGetReal( mlp, &_tp16) ) goto L15;
	if ( ! MLGetReal( mlp, &_tp17) ) goto L16;
	if ( ! MLNewPacket(mlp) ) goto L17;

	_rp0 = sigmaRadCone(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15, _tp16, _tp17);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L17: L16: L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr8 */


double radiativeCone P(( double _tp1, double _tp2, double _tp3));

#if MLPROTOTYPES
static int _tr9( MLINK mlp)
#else
static int _tr9(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	double _tp1;
	double _tp2;
	double _tp3;
	double _rp0;
	if ( ! MLGetReal( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLNewPacket(mlp) ) goto L3;

	_rp0 = radiativeCone(_tp1, _tp2, _tp3);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L3: L2: L1: 
L0:	return res;
} /* _tr9 */


double radiativeKernel P(( double _tp1, double _tp2));

#if MLPROTOTYPES
static int _tr10( MLINK mlp)
#else
static int _tr10(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	double _tp1;
	double _tp2;
	double _rp0;
	if ( ! MLGetReal( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal( mlp, &_tp2) ) goto L1;
	if ( ! MLNewPacket(mlp) ) goto L2;

	_rp0 = radiativeKernel(_tp1, _tp2);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L2: L1: 
L0:	return res;
} /* _tr10 */


double sigmaMassRad P(( int _tp1, int _tp2, int _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15, double _tp16, double _tp17));

#if MLPROTOTYPES
static int _tr11( MLINK mlp)
#else
static int _tr11(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	int _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _tp16;
	double _tp17;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetInteger( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLGetReal( mlp, &_tp16) ) goto L15;
	if ( ! MLGetReal( mlp, &_tp17) ) goto L16;
	if ( ! MLNewPacket(mlp) ) goto L17;

	_rp0 = sigmaMassRad(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15, _tp16, _tp17);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L17: L16: L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr11 */


double sigmaMassRadCone P(( int _tp1, int _tp2, int _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15, double _tp16, double _tp17, double _tp18));

#if MLPROTOTYPES
static int _tr12( MLINK mlp)
#else
static int _tr12(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	int _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _tp16;
	double _tp17;
	double _tp18;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetInteger( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLGetReal( mlp, &_tp16) ) goto L15;
	if ( ! MLGetReal( mlp, &_tp17) ) goto L16;
	if ( ! MLGetReal( mlp, &_tp18) ) goto L17;
	if ( ! MLNewPacket(mlp) ) goto L18;

	_rp0 = sigmaMassRadCone(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15, _tp16, _tp17, _tp18);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L18: L17: L16: L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr12 */


double sigmaMassRadConeCum P(( int _tp1, int _tp2, int _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15, double _tp16, double _tp17, double _tp18, double _tp19));

#if MLPROTOTYPES
static int _tr13( MLINK mlp)
#else
static int _tr13(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	int _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _tp16;
	double _tp17;
	double _tp18;
	double _tp19;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetInteger( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLGetReal( mlp, &_tp16) ) goto L15;
	if ( ! MLGetReal( mlp, &_tp17) ) goto L16;
	if ( ! MLGetReal( mlp, &_tp18) ) goto L17;
	if ( ! MLGetReal( mlp, &_tp19) ) goto L18;
	if ( ! MLNewPacket(mlp) ) goto L19;

	_rp0 = sigmaMassRadConeCum(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15, _tp16, _tp17, _tp18, _tp19);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L19: L18: L17: L16: L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr13 */


double sigmaRadConeCum P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15, double _tp16, double _tp17, double _tp18));

#if MLPROTOTYPES
static int _tr14( MLINK mlp)
#else
static int _tr14(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _tp16;
	double _tp17;
	double _tp18;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLGetReal( mlp, &_tp16) ) goto L15;
	if ( ! MLGetReal( mlp, &_tp17) ) goto L16;
	if ( ! MLGetReal( mlp, &_tp18) ) goto L17;
	if ( ! MLNewPacket(mlp) ) goto L18;

	_rp0 = sigmaRadConeCum(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15, _tp16, _tp17, _tp18);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L18: L17: L16: L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr14 */


double sigmaMassRadCum P(( int _tp1, int _tp2, int _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15, double _tp16, double _tp17, double _tp18));

#if MLPROTOTYPES
static int _tr15( MLINK mlp)
#else
static int _tr15(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	int _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _tp16;
	double _tp17;
	double _tp18;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetInteger( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLGetReal( mlp, &_tp16) ) goto L15;
	if ( ! MLGetReal( mlp, &_tp17) ) goto L16;
	if ( ! MLGetReal( mlp, &_tp18) ) goto L17;
	if ( ! MLNewPacket(mlp) ) goto L18;

	_rp0 = sigmaMassRadCum(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15, _tp16, _tp17, _tp18);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L18: L17: L16: L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr15 */


double sigmaRadCum P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15, double _tp16, double _tp17));

#if MLPROTOTYPES
static int _tr16( MLINK mlp)
#else
static int _tr16(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _tp16;
	double _tp17;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLGetReal( mlp, &_tp16) ) goto L15;
	if ( ! MLGetReal( mlp, &_tp17) ) goto L16;
	if ( ! MLNewPacket(mlp) ) goto L17;

	_rp0 = sigmaRadCum(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15, _tp16, _tp17);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L17: L16: L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr16 */


double sigmaHadMass P(( int _tp1, int _tp2, int _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9, double _tp10, double _tp11, double _tp12, double _tp13, double _tp14, double _tp15));

#if MLPROTOTYPES
static int _tr17( MLINK mlp)
#else
static int _tr17(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	int _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _tp10;
	double _tp11;
	double _tp12;
	double _tp13;
	double _tp14;
	double _tp15;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetInteger( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLGetReal( mlp, &_tp10) ) goto L9;
	if ( ! MLGetReal( mlp, &_tp11) ) goto L10;
	if ( ! MLGetReal( mlp, &_tp12) ) goto L11;
	if ( ! MLGetReal( mlp, &_tp13) ) goto L12;
	if ( ! MLGetReal( mlp, &_tp14) ) goto L13;
	if ( ! MLGetReal( mlp, &_tp15) ) goto L14;
	if ( ! MLNewPacket(mlp) ) goto L15;

	_rp0 = sigmaHadMass(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9, _tp10, _tp11, _tp12, _tp13, _tp14, _tp15);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L15: L14: L13: L12: L11: L10: L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr17 */


double massqcd P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9));

#if MLPROTOTYPES
static int _tr18( MLINK mlp)
#else
static int _tr18(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLNewPacket(mlp) ) goto L9;

	_rp0 = massqcd(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr18 */


double polemass P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, double _tp8, double _tp9));

#if MLPROTOTYPES
static int _tr19( MLINK mlp)
#else
static int _tr19(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	double _tp8;
	double _tp9;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal( mlp, &_tp7) ) goto L6;
	if ( ! MLGetReal( mlp, &_tp8) ) goto L7;
	if ( ! MLGetReal( mlp, &_tp9) ) goto L8;
	if ( ! MLNewPacket(mlp) ) goto L9;

	_rp0 = polemass(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8, _tp9);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L9: L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr19 */


double alphageneric P(( int _tp1, int _tp2, double _tp3, double _tp4, double _tp5));

#if MLPROTOTYPES
static int _tr20( MLINK mlp)
#else
static int _tr20(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	int _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetInteger( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLNewPacket(mlp) ) goto L5;

	_rp0 = alphageneric(_tp1, _tp2, _tp3, _tp4, _tp5);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr20 */


double alphaQED P(( int _tp1, double _tp2, double _tp3, double _tp4, double _tp5));

#if MLPROTOTYPES
static int _tr21( MLINK mlp)
#else
static int _tr21(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	int _tp1;
	double _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _rp0;
	if ( ! MLGetInteger( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal( mlp, &_tp5) ) goto L4;
	if ( ! MLNewPacket(mlp) ) goto L5;

	_rp0 = alphaQED(_tp1, _tp2, _tp3, _tp4, _tp5);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr21 */


double diLog P(( double _tp1));

#if MLPROTOTYPES
static int _tr22( MLINK mlp)
#else
static int _tr22(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	double _tp1;
	double _rp0;
	if ( ! MLGetReal( mlp, &_tp1) ) goto L0;
	if ( ! MLNewPacket(mlp) ) goto L1;

	_rp0 = diLog(_tp1);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal( mlp, _rp0);
L1: 
L0:	return res;
} /* _tr22 */


static struct func {
	int   f_nargs;
	int   manual;
	int   (*f_func)P((MLINK));
	const char  *f_name;
	} _tramps[23] = {
		{ 5, 0, _tr0, "ewfactors" },
		{ 1, 0, _tr1, "betaQCD" },
		{ 1, 0, _tr2, "gammaMassQCD" },
		{ 9, 0, _tr3, "alphaqcd" },
		{12, 0, _tr4, "rhadmass" },
		{10, 0, _tr5, "rhad" },
		{12, 0, _tr6, "sigmaHad" },
		{16, 0, _tr7, "sigmaRad" },
		{17, 0, _tr8, "sigmaRadCone" },
		{ 3, 0, _tr9, "radiativeCone" },
		{ 2, 0, _tr10, "radiativeKernel" },
		{17, 0, _tr11, "sigmaMassRad" },
		{18, 0, _tr12, "sigmaMassRadCone" },
		{19, 0, _tr13, "sigmaMassRadConeCum" },
		{18, 0, _tr14, "sigmaRadConeCum" },
		{18, 0, _tr15, "sigmaMassRadCum" },
		{17, 0, _tr16, "sigmaRadCum" },
		{15, 0, _tr17, "sigmaHadMass" },
		{ 9, 0, _tr18, "massqcd" },
		{ 9, 0, _tr19, "polemass" },
		{ 5, 0, _tr20, "alphageneric" },
		{ 5, 0, _tr21, "alphaQED" },
		{ 1, 0, _tr22, "diLog" }
		};

static const char* evalstrs[] = {
	"BeginPackage[\"mathlinkpackage`\"]",
	(const char*)0,
	"Print[\"     Package for top production at a linear collider \"]",
	(const char*)0,
	"Print[\"     Author:            Vicent Mateu                 \"]",
	(const char*)0,
	"Print[\"     Last modification: 04 - 02 - 2016               \"]",
	(const char*)0,
	"Print[\"     Version:           1.00                         \"]",
	(const char*)0,
	"Mzdef = 91.187",
	(const char*)0,
	"mWdef = 80.385",
	(const char*)0,
	"aMzdef = 0.1184",
	(const char*)0,
	"aQEDdef = 1/127.925",
	(const char*)0,
	"aQEDdef = 0.00781751",
	(const char*)0,
	"RHad::usage=\"RHad[order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, ",
	"Q, mu] computes the total hadronic cross section normalized to t",
	"he dimuon production, ignoring mass corrections. mQ refers to th",
	"e top (nf = 6) or bottom (nf = 5), and mCharm is only used for n",
	"f < 4.\"",
	(const char*)0,
	"SigmaHad::usage=\"SigmaHad[order, nf, mW, Mz, aMz, aQED, mQ, muQ,",
	" mCharm, muCharm, Q, mu] computes the total hadronic cross secti",
	"on ignoring mass corrections. mQ refers to the top (nf = 6) or b",
	"ottom (nf = 5), and mCharm is only used for nf < 4.\"",
	(const char*)0,
	"SigmaRad::usage=\"SigmaRad[order, nf, mW, Mz, aMz, aQED, gammaZ, ",
	"sin2ThetaW, mQ, muQ, mCharm, muCharm, x, theta, Q, mu] computes ",
	"the total hadronic cross section including an ISR photon, comple",
	"tely differential in photon momentum solid angle and in x = Egam",
	"ma/Q, ignoring mass corrections. mQ refers to the top (nf = 6) o",
	"r bottom (nf = 5), and mCharm is only used for nf < 4.\"",
	(const char*)0,
	"SigmaRadCone::usage=\"SigmaRadCone[order, nf, mW, Mz, aMz, aQED, ",
	"gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x, theta, deltaThe",
	"ta, Q, mu] computes the total hadronic cross section including a",
	"n ISR photon, diffential in x = Egamma/Q and integrating inside ",
	"a cone around the photon momentum, ignoring mass corrections. mQ",
	" refers to the top (nf = 6) or bottom (nf = 5), and mCharm is on",
	"ly used for nf < 4.\"",
	(const char*)0,
	"RadiativeCone::usage=\"RadiativeCone[x, theta, deltaTheta] comput",
	"es the cone integrating kernel.\"",
	(const char*)0,
	"RadiativeKernel::usage=\"RadiativeKernel[x, theta] computes the r",
	"adiative kernel.\"",
	(const char*)0,
	"SigmaMassRad::usage=\"SigmaMassRad[scheme, order, nf, mW, Mz, aMz",
	", aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x, theta, ",
	"Q, mu] computes the total massive hadronic cross section includi",
	"ng an ISR photon, completely differential in photon momentum sol",
	"id angle and in x = Egamma/Q. mQ refers to the top (nf = 6) or b",
	"ottom (nf = 5), and mCharm is only used for nf < 4.\"",
	(const char*)0,
	"SigmaMassRadCone::usage=\"SigmaMassRadCone[scheme, order, nf, mW,",
	" Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x,",
	" theta, deltaTheta, Q, mu] computes the total massive hadronic c",
	"ross section including an ISR photon, differential x = Egamma/Q ",
	"and integrating inside a cone around the photon momentum. mQ ref",
	"ers to the top (nf = 6) or bottom (nf = 5), and mCharm is only u",
	"sed for nf < 4.\"",
	(const char*)0,
	"SigmaMassRadConeCum::usage=\"SigmaMassRadConeCum[scheme, order, n",
	"f, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCha",
	"rm, x0, x1, theta, deltaTheta, Q, eh] computes the total massive",
	" hadronic cross section including an ISR photon, integrating in ",
	"x = Egamma/Q and inside a cone around the photon momentum. mQ re",
	"fers to the top (nf = 6) or bottom (nf = 5), and mCharm is only ",
	"used for nf < 4.\"",
	(const char*)0,
	"SigmaMassRadCum::usage=\"SigmaMassRadCum[scheme, order, nf, mW, M",
	"z, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x0, ",
	"x1, theta, Q, eh] computes the total massive hadronic cross sect",
	"ion including an ISR photon, integrating in x = Egamma/Q. mQ ref",
	"ers to the top (nf = 6) or bottom (nf = 5), and mCharm is only u",
	"sed for nf < 4.\"",
	(const char*)0,
	"SigmaRadConeCum::usage=\"SigmaRadConeCum[order, nf, mW, Mz, aMz, ",
	"aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x0, x1, thet",
	"a, deltaTheta, Q, eh] computes the total massless hadronic cross",
	" section including an ISR photon, integrating in x = Egamma/Q an",
	"d inside a cone around the photon momentum. mQ refers to the top",
	" (nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4",
	".\"",
	(const char*)0,
	"SigmaRadCum::usage=\"SigmaRadCum[order, nf, mW, Mz, aMz, aQED, ga",
	"mmaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, x0, x1, theta, Q, eh",
	"] computes the total massless hadronic cross section including a",
	"n ISR photon, integrating in x = Egamma/Q. mQ refers to the top ",
	"(nf = 6) or bottom (nf = 5), and mCharm is only used for nf < 4.",
	"\"",
	(const char*)0,
	"SigmaHadMass::usage=\"SigmaHadMass[scheme, order, nf, mW, Mz, aMz",
	", aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm, muCharm, Q, mu] com",
	"putes the total hadronic cross section for a massive quark, incl",
	"uding EW factors. mQ refers to the top (nf = 6) or bottom (nf = ",
	"5), and mCharm is only used for nf < 4.\"",
	(const char*)0,
	"RHadMass::usage=\"RHadMass[scheme, current, order, nf, Mz, aMz, m",
	"Q, muQ, mCharm, muCharm, Q, mu] computes the total hadronic cros",
	"s section normalized to the dimuon production, including mass co",
	"rrections. scheme = 0, 1 for pole and MS-bar. current = 1, 2 for",
	" vector or axial-vector mQ refers to the top (nf = 6) or bottom ",
	"(nf = 5), and mCharm is only used for nf < 4.\"",
	(const char*)0,
	"AlphaQCD::usage=\"AlphaQCD[order, nf, Mz, aMz, mQ, muQ, mCharm, m",
	"uCharm, mu] computes alpha strong for nf active flavors, computi",
	"ng threshold matching. mQ refers to the top (nf = 6) or bottom (",
	"nf = 5), and mCharm is only used for nf < 4.\"",
	(const char*)0,
	"AlphaGeneric::usage=\"AlphaGeneric[order, nf, Mz, aMz, mu] comput",
	"es alpha strong for nf active flavors, no threshold matching com",
	"puted. Refrence point is alphaS(nf, Mz) = aMz.\"",
	(const char*)0,
	"AlphaQED::usage=\"AlphaQED[nf, Mw, Mz, aMz, mu] computes alphaQED",
	" for nf active flavors, threshold matching computed. Refrence po",
	"int is alphaQED(Mz) = aMz.\"",
	(const char*)0,
	"MassQCD::usage=\"MassQCD[order, nf, Mz, aMz, mQ, muQ, mCharm, muC",
	"harm, mu] computes the running of the MS-bar mass for nf active ",
	"flavors. mQ refers to the top (nf = 6) or bottom (nf = 5), and m",
	"Charm is only used for nf < 4.\"",
	(const char*)0,
	"PoleMass::usage=\"PoleMass[order, nf, Mz, aMz, mQ, muQ, mCharm, m",
	"uCharm, mu] computes the pole mass from the MS-bar for nf active",
	" flavors. mQ refers to the top (nf = 6) or bottom (nf = 5), and ",
	"mCharm is only used for nf < 4.\"",
	(const char*)0,
	"BetaQCD::usage = \"BetaQCD[nf] computes the QCD beta function\"",
	(const char*)0,
	"GammaMass::usage = \"GammaMass[nf] computes the quark anomalous d",
	"imension\"",
	(const char*)0,
	"DiLog::usage=\"DiLog[x] computes the dilogarithm\"",
	(const char*)0,
	"EWFactors::usage=\"EWFactors[nf, Q, Mz, GammaZ, sin2ThetaW] elect",
	"roweak factors\"",
	(const char*)0,
	"Begin[\"`private`\"]",
	(const char*)0,
	"End[]",
	(const char*)0,
	"EndPackage[]",
	(const char*)0,
	(const char*)0
};
#define CARDOF_EVALSTRS 36

static int _definepattern P(( MLINK, char*, char*, int));

static int _doevalstr P(( MLINK, int));

int  _MLDoCallPacket P(( MLINK, struct func[], int));


#if MLPROTOTYPES
int MLInstall( MLINK mlp)
#else
int MLInstall(mlp) MLINK mlp;
#endif
{
	int _res;
	_res = MLConnect(mlp);
	if (_res) _res = _doevalstr( mlp, 0);
	if (_res) _res = _doevalstr( mlp, 1);
	if (_res) _res = _doevalstr( mlp, 2);
	if (_res) _res = _doevalstr( mlp, 3);
	if (_res) _res = _doevalstr( mlp, 4);
	if (_res) _res = _doevalstr( mlp, 5);
	if (_res) _res = _doevalstr( mlp, 6);
	if (_res) _res = _doevalstr( mlp, 7);
	if (_res) _res = _doevalstr( mlp, 8);
	if (_res) _res = _doevalstr( mlp, 9);
	if (_res) _res = _doevalstr( mlp, 10);
	if (_res) _res = _doevalstr( mlp, 11);
	if (_res) _res = _doevalstr( mlp, 12);
	if (_res) _res = _doevalstr( mlp, 13);
	if (_res) _res = _doevalstr( mlp, 14);
	if (_res) _res = _doevalstr( mlp, 15);
	if (_res) _res = _doevalstr( mlp, 16);
	if (_res) _res = _doevalstr( mlp, 17);
	if (_res) _res = _doevalstr( mlp, 18);
	if (_res) _res = _doevalstr( mlp, 19);
	if (_res) _res = _doevalstr( mlp, 20);
	if (_res) _res = _doevalstr( mlp, 21);
	if (_res) _res = _doevalstr( mlp, 22);
	if (_res) _res = _doevalstr( mlp, 23);
	if (_res) _res = _doevalstr( mlp, 24);
	if (_res) _res = _doevalstr( mlp, 25);
	if (_res) _res = _doevalstr( mlp, 26);
	if (_res) _res = _doevalstr( mlp, 27);
	if (_res) _res = _doevalstr( mlp, 28);
	if (_res) _res = _doevalstr( mlp, 29);
	if (_res) _res = _doevalstr( mlp, 30);
	if (_res) _res = _doevalstr( mlp, 31);
	if (_res) _res = _doevalstr( mlp, 32);
	if (_res) _res = _doevalstr( mlp, 33);
	if (_res) _res = _definepattern(mlp, (char *)"EWFactors[nf_, Q_, Mz_, GammaZ_, sin2ThetaW_]", (char *)"{nf, Q, Mz, GammaZ, sin2ThetaW}", 0);
	if (_res) _res = _definepattern(mlp, (char *)"BetaQCD[nf_]", (char *)"{nf}", 1);
	if (_res) _res = _definepattern(mlp, (char *)"GammaMass[nf_]", (char *)"{nf}", 2);
	if (_res) _res = _definepattern(mlp, (char *)"AlphaQCD[order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, muCharm_, mu_]", (char *)"{order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu}", 3);
	if (_res) _res = _definepattern(mlp, (char *)"RHadMass[scheme_, current_, order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_,                 muCharm_, q_, mu_]", (char *)"{scheme, current, order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, q, mu}", 4);
	if (_res) _res = _definepattern(mlp, (char *)"RHad[order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, muCharm_, q_, mu_]", (char *)"{order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, q, mu}", 5);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaHad[order_, nf_, mW_, Mz_, aMz_, aQED_, mQ_, muQ_, mCharm_, muCharm_,                  q_,  mu_]", (char *)"{order, nf, mW, Mz, aMz, aQED, mQ, muQ, mCharm, muCharm, q, mu}", 6);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaRad[order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_, sin2ThetaW_, mQ_,                 muQ_, mCharm_, muCharm_, x_, theta_, q_, mu_]", (char *)"{order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm,                  muCharm, x, theta, q, mu}", 7);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaRadCone[order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_, sin2ThetaW_,               mQ_, muQ_, mCharm_, muCharm_, x_, theta_, deltaTheta_, q_, mu_]", (char *)"{order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm,               muCharm, x, theta, deltaTheta, q, mu}", 8);
	if (_res) _res = _definepattern(mlp, (char *)"RadiativeCone[x_, theta_, deltaTheta_]", (char *)"{x, theta, deltaTheta}", 9);
	if (_res) _res = _definepattern(mlp, (char *)"RadiativeKernel[x_, theta_]", (char *)"{x, theta}", 10);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaMassRad[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,                 sin2ThetaW_, mQ_, muQ_, mCharm_,  muCharm_, x_, theta_, q_, mu_]", (char *)"{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,                 mCharm, muCharm, x, theta, q,  mu}", 11);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaMassRadCone[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,                 sin2ThetaW_, mQ_, muQ_, mCharm_,  muCharm_, x_, theta_, deltaTheta_, q_,                 mu_]", (char *)"{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,                 mCharm, muCharm, x, theta, deltaTheta, q,  mu}", 12);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaMassRadConeCum[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,                 sin2ThetaW_, mQ_, muQ_, mCharm_,  muCharm_, x0_, x1_, theta_, deltaTheta_,                 q_, eh_]", (char *)"{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,                 mCharm, muCharm, x0, x1, theta, deltaTheta, q,  eh}", 13);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaRadConeCum[order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_, sin2ThetaW_,                 mQ_, muQ_, mCharm_,  muCharm_, x0_, x1_, theta_, deltaTheta_, q_, eh_]", (char *)"{order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm,                 muCharm, x0, x1, theta, deltaTheta, q, eh}", 14);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaMassRadCum[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,                 sin2ThetaW_, mQ_, muQ_, mCharm_,  muCharm_, x0_, x1_, theta_, q_, eh_]", (char *)"{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,                 mCharm, muCharm, x0, x1, theta, q,  eh}", 15);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaRadCum[order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_, sin2ThetaW_,                 mQ_, muQ_, mCharm_,  muCharm_, x0_, x1_, theta_, q_, eh_]", (char *)"{order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ, mCharm,                 muCharm, x0, x1, theta, q,  eh}", 16);
	if (_res) _res = _definepattern(mlp, (char *)"SigmaHadMass[scheme_, order_, nf_, mW_, Mz_, aMz_, aQED_, gammaZ_,                 sin2ThetaW_, mQ_, muQ_, mCharm_, muCharm_, q_, mu_]", (char *)"{scheme, order, nf, mW, Mz, aMz, aQED, gammaZ, sin2ThetaW, mQ, muQ,                  mCharm, muCharm, q, mu}", 17);
	if (_res) _res = _definepattern(mlp, (char *)"MassQCD[order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, muCharm_, mu_]", (char *)"{order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu}", 18);
	if (_res) _res = _definepattern(mlp, (char *)"PoleMass[order_, nf_, Mz_, aMz_, mQ_, muQ_, mCharm_, muCharm_, mu_]", (char *)"{order, nf, Mz, aMz, mQ, muQ, mCharm, muCharm, mu}", 19);
	if (_res) _res = _definepattern(mlp, (char *)"AlphaGeneric[order_, nf_, Mz_, aMz_, mu_]", (char *)"{order, nf, Mz, aMz, mu}", 20);
	if (_res) _res = _definepattern(mlp, (char *)"AlphaQED[nf_, mW_, Mz_, aMz_, mu_]", (char *)"{nf, mW, Mz, aMz, mu}", 21);
	if (_res) _res = _definepattern(mlp, (char *)"DiLog[mu_]", (char *)"{mu}", 22);
	if (_res) _res = _doevalstr( mlp, 34);
	if (_res) _res = _doevalstr( mlp, 35);
	if (_res) _res = MLPutSymbol( mlp, "End");
	if (_res) _res = MLFlush( mlp);
	return _res;
} /* MLInstall */


#if MLPROTOTYPES
int MLDoCallPacket( MLINK mlp)
#else
int MLDoCallPacket( mlp) MLINK mlp;
#endif
{
	return _MLDoCallPacket( mlp, _tramps, 23);
} /* MLDoCallPacket */

/******************************* begin trailer ********************************/

#ifndef EVALSTRS_AS_BYTESTRINGS
#	define EVALSTRS_AS_BYTESTRINGS 1
#endif

#if CARDOF_EVALSTRS
static int  _doevalstr( MLINK mlp, int n)
{
	long bytesleft, charsleft, bytesnow;
#if !EVALSTRS_AS_BYTESTRINGS
	long charsnow;
#endif
	char **s, **p;
	char *t;

	s = (char **)evalstrs;
	while( n-- > 0){
		if( *s == 0) break;
		while( *s++ != 0){}
	}
	if( *s == 0) return 0;
	bytesleft = 0;
	charsleft = 0;
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft += bytesnow;
		charsleft += bytesnow;
#if !EVALSTRS_AS_BYTESTRINGS
		t = *p;
		charsleft -= MLCharacterOffset( &t, t + bytesnow, bytesnow);
		/* assert( t == *p + bytesnow); */
#endif
		++p;
	}


	MLPutNext( mlp, MLTKSTR);
#if EVALSTRS_AS_BYTESTRINGS
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft -= bytesnow;
		MLPut8BitCharacters( mlp, bytesleft, (unsigned char*)*p, bytesnow);
		++p;
	}
#else
	MLPut7BitCount( mlp, charsleft, bytesleft);
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft -= bytesnow;
		t = *p;
		charsnow = bytesnow - MLCharacterOffset( &t, t + bytesnow, bytesnow);
		/* assert( t == *p + bytesnow); */
		charsleft -= charsnow;
		MLPut7BitCharacters(  mlp, charsleft, *p, bytesnow, charsnow);
		++p;
	}
#endif
	return MLError( mlp) == MLEOK;
}
#endif /* CARDOF_EVALSTRS */


static int  _definepattern( MLINK mlp, char* patt, char* args, int func_n)
{
	MLPutFunction( mlp, "DefineExternal", (long)3);
	  MLPutString( mlp, patt);
	  MLPutString( mlp, args);
	  MLPutInteger( mlp, func_n);
	return !MLError(mlp);
} /* _definepattern */


int _MLDoCallPacket( MLINK mlp, struct func functable[], int nfuncs)
{
#if MLINTERFACE >= 4
	int len;
#else
	long len;
#endif
	int n, res = 0;
	struct func* funcp;

	if( ! MLGetInteger( mlp, &n) ||  n < 0 ||  n >= nfuncs) goto L0;
	funcp = &functable[n];

	if( funcp->f_nargs >= 0
#if MLINTERFACE >= 4
	&& ( ! MLTestHead(mlp, "List", &len)
#else
	&& ( ! MLCheckFunction(mlp, "List", &len)
#endif
	     || ( !funcp->manual && (len != funcp->f_nargs))
	     || (  funcp->manual && (len <  funcp->f_nargs))
	   )
	) goto L0;

	stdlink = mlp;
	res = (*funcp->f_func)( mlp);

L0:	if( res == 0)
		res = MLClearError( mlp) && MLPutSymbol( mlp, "$Failed");
	return res && MLEndPacket( mlp) && MLNewPacket( mlp);
} /* _MLDoCallPacket */


mlapi_packet MLAnswer( MLINK mlp)
{
	mlapi_packet pkt = 0;
#if MLINTERFACE >= 4
	int waitResult;

	while( ! MLDone && ! MLError(mlp)
		&& (waitResult = MLWaitForLinkActivity(mlp),waitResult) &&
		waitResult == MLWAITSUCCESS && (pkt = MLNextPacket(mlp), pkt) &&
		pkt == CALLPKT)
	{
		MLAbort = 0;
		if(! MLDoCallPacket(mlp))
			pkt = 0;
	}
#else
	while( !MLDone && !MLError(mlp) && (pkt = MLNextPacket(mlp), pkt) && pkt == CALLPKT){
		MLAbort = 0;
		if( !MLDoCallPacket(mlp)) pkt = 0;
	}
#endif
	MLAbort = 0;
	return pkt;
} /* MLAnswer */



/*
	Module[ { me = $ParentLink},
		$ParentLink = contents of RESUMEPKT;
		Message[ MessageName[$ParentLink, "notfe"], me];
		me]
*/

static int refuse_to_be_a_frontend( MLINK mlp)
{
	int pkt;

	MLPutFunction( mlp, "EvaluatePacket", 1);
	  MLPutFunction( mlp, "Module", 2);
	    MLPutFunction( mlp, "List", 1);
		  MLPutFunction( mlp, "Set", 2);
		    MLPutSymbol( mlp, "me");
	        MLPutSymbol( mlp, "$ParentLink");
	  MLPutFunction( mlp, "CompoundExpression", 3);
	    MLPutFunction( mlp, "Set", 2);
	      MLPutSymbol( mlp, "$ParentLink");
	      MLTransferExpression( mlp, mlp);
	    MLPutFunction( mlp, "Message", 2);
	      MLPutFunction( mlp, "MessageName", 2);
	        MLPutSymbol( mlp, "$ParentLink");
	        MLPutString( mlp, "notfe");
	      MLPutSymbol( mlp, "me");
	    MLPutSymbol( mlp, "me");
	MLEndPacket( mlp);

	while( (pkt = MLNextPacket( mlp), pkt) && pkt != SUSPENDPKT)
		MLNewPacket( mlp);
	MLNewPacket( mlp);
	return MLError( mlp) == MLEOK;
}


int MLEvaluate( MLINK mlp, char* s)
{
	if( MLAbort) return 0;
	return MLPutFunction( mlp, "EvaluatePacket", 1L)
		&& MLPutFunction( mlp, "ToExpression", 1L)
		&& MLPutString( mlp, s)
		&& MLEndPacket( mlp);
} /* MLEvaluate */


int MLEvaluateString( MLINK mlp, char* s)
{
	int pkt;
	if( MLAbort) return 0;
	if( MLEvaluate( mlp, s)){
		while( (pkt = MLAnswer( mlp), pkt) && pkt != RETURNPKT)
			MLNewPacket( mlp);
		MLNewPacket( mlp);
	}
	return MLError( mlp) == MLEOK;
} /* MLEvaluateString */


#if MLINTERFACE >= 3
MLMDEFN( void, MLDefaultHandler, ( MLINK mlp, int message, int n))
#else
MLMDEFN( void, MLDefaultHandler, ( MLINK mlp, unsigned long message, unsigned long n))
#endif /* MLINTERFACE >= 3 */
{
	mlp = (MLINK)0; /* suppress unused warning */
	n = 0; /* suppress unused warning */

	switch (message){
	case MLTerminateMessage:
		MLDone = 1;
	case MLInterruptMessage:
	case MLAbortMessage:
		MLAbort = 1;
	default:
		return;
	}
}

#if MLINTERFACE >= 3
static int _MLMain( char **argv, char **argv_end, char *commandline)
#else
static int _MLMain( charpp_ct argv, charpp_ct argv_end, charp_ct commandline)
#endif /* MLINTERFACE >= 3 */
{
	MLINK mlp;
#if MLINTERFACE >= 3
	int err;
#else
	long err;
#endif /* MLINTERFACE >= 3 */

#if (DARWIN_MATHLINK && CARBON_MPREP)
	if( !init_macintosh()) goto R0;
#endif /* (DARWIN_MATHLINK && CARBON_MPREP) */

#if MLINTERFACE >= 4
	if( !stdenv)
		stdenv = MLInitialize( (MLEnvironmentParameter)0);
#else
	if( !stdenv)
		stdenv = MLInitialize( (MLParametersPointer)0);
#endif

	if( stdenv == (MLEnvironment)0) goto R0;

#if (DARWIN_MATHLINK && CARBON_MPREP)
#if MLINTERFACE >= 3
	if( !stdyielder)
		stdyielder = (MLYieldFunctionObject)MLDefaultYielder;
#else
	if( !stdyielder)
		stdyielder = MLCreateYieldFunction( stdenv, NewMLYielderProc( MLDefaultYielder), 0);
#endif /* MLINTERFACE >= 3 */
#endif /* (DARWIN_MATHLINK && CARBON_MPREP)*/

#if MLINTERFACE >= 3
	if( !stdhandler)
		stdhandler = (MLMessageHandlerObject)MLDefaultHandler;
#else
	if( !stdhandler)
		stdhandler = MLCreateMessageHandler( stdenv, NewMLHandlerProc( MLDefaultHandler), 0);
#endif /* MLINTERFACE >= 3 */

#if (DARWIN_MATHLINK && CARBON_MPREP)
        MLSetDialogFunction(stdenv, MLRequestToInteractFunction, NewMLRequestToInteractProc(MLDontPermit_darwin));

	mlp = commandline
		? MLOpenString( stdenv, commandline, &err)
#if MLINTERFACE >= 3
			: MLOpenArgcArgv( stdenv, (int)(argv_end - argv), argv, &err);
#else
			: MLOpenArgv( stdenv, argv, argv_end, &err);
#endif

        MLSetDialogFunction(stdenv, MLRequestToInteractFunction, NewMLRequestToInteractProc(MLPermit_darwin));

	if( mlp == (MLINK)0){
                        mlp = commandline
                                ? MLOpenString( stdenv, commandline, &err)
#if MLINTERFACE < 3
                                : MLOpenArgv( stdenv, argv, argv_end, &err);
#else
                                : MLOpenArgcArgv( stdenv, (int)(argv_end - argv), argv, &err);
#endif
        }
#else /* !(DARWIN_MATHLINK && CARBON_MPREP)*/
	mlp = commandline
		? MLOpenString( stdenv, commandline, &err)
#if MLINTERFACE < 3
		: MLOpenArgv( stdenv, argv, argv_end, &err);
#else
		: MLOpenArgcArgv( stdenv, (int)(argv_end - argv), argv, &err);
#endif
#endif /* (DARWIN_MATHLINK && CARBON_MPREP)*/

	if( mlp == (MLINK)0){
		MLAlert( stdenv, MLErrorString( stdenv, err));
		goto R1;
	}

	if( stdyielder) MLSetYieldFunction( mlp, stdyielder);
	if( stdhandler) MLSetMessageHandler( mlp, stdhandler);

	if( MLInstall( mlp))
		while( MLAnswer( mlp) == RESUMEPKT){
			if( ! refuse_to_be_a_frontend( mlp)) break;
		}

	MLClose( mlp);
R1:	MLDeinitialize( stdenv);
	stdenv = (MLEnvironment)0;
R0:	return !MLDone;
} /* _MLMain */


#if MLINTERFACE >= 3
int MLMainString( char *commandline)
#else
int MLMainString( charp_ct commandline)
#endif /* MLINTERFACE >= 3 */
{
#if MLINTERFACE >= 3
	return _MLMain( (char **)0, (char **)0, commandline);
#else
	return _MLMain( (charpp_ct)0, (charpp_ct)0, commandline);
#endif /* MLINTERFACE >= 3 */
}

int MLMainArgv( char** argv, char** argv_end) /* note not FAR pointers */
{   
	static char FAR * far_argv[128];
	int count = 0;
	
	while(argv < argv_end)
		far_argv[count++] = *argv++;
		 
	return _MLMain( far_argv, far_argv + count, (charp_ct)0);

}

#if MLINTERFACE >= 3
int MLMain( int argc, char ** argv)
#else
int MLMain( int argc, charpp_ct argv)
#endif /* MLINTERFACE >= 3 */
{
#if MLINTERFACE >= 3
 	return _MLMain( argv, argv + argc, (char *)0);
#else
 	return _MLMain( argv, argv + argc, (charp_ct)0);
#endif /* MLINTERFACE >= 3 */
}
