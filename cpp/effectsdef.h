#ifndef EFFECTSDEF_H
#define EFFECTSDEF_H
#include "effects.h"
#include "effectgui.h"
#include "graphics.h"

///Definicje efektów
///Zeby efekt działał wystarczy zrobić 3 rzeczy:
///1. Napisać klase z definicją efektów bazując na EffectGUI (tu patrz PlayBuf) lub EffectAutoGUI. Zalecane jest użycie makra EFFECT_BODY (patrz poniższe implementacje)
///2. dodać linijkę 'REGISTER_EFFECT(<tu nazwa efektu>, <nazwa grupy>);' lub 'REGISTER_EFFECT_EX(<tu nazwa efektu>, <nazwa grupy>, <nazwa podgrupy>);' (w przypadku podgrupy) do funkcji registerEffects()
///3. dodać linijkę 'EFFECT_BY_NAME(<tu nazwa efektu>);' do funkcji getEffect()

	
#define EFFECT_START(FULL_NAME, SC_NAME) \
class FULL_NAME : public EffectAutoGUI { \
	private:\
		std::vector<EffectArgument> args;\
		std::vector<ArgVis> argsVis;\
	public:\
		static constexpr const char* registration_name = #SC_NAME; \
		static constexpr const char* registration_fullname = #FULL_NAME; \
		std::vector<EffectArgument>& getArgs() {return args;}\
		int getArgsCount() const {return args.size();}\
		std::vector<ArgVis>& getArgumentVisuals() {return argsVis;}\
	FULL_NAME(int X, int Y): EffectAutoGUI(#SC_NAME, #FULL_NAME),
	
#define EFFECT_END(FULL_NAME) \
	~FULL_NAME() {quitGUI();} \
};
	
EFFECT_START(DistEcho, eff_distecho)
	args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f), EffectArgument("delay", 0.15f)}),
	argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
	{sendInstance(); initGUI(X, Y);}
EFFECT_END(DistEcho)
	
EFFECT_START(ShiftEcho, eff_shiftecho)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 0.0f), EffectArgument("phase", 0.0f), EffectArgument("feedback", 0.1f), EffectArgument("delay", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, -100.0f, 100.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(ShiftEcho)
	
EFFECT_START(GenEcho, eff_genecho)
		args({EffectArgument("feedback_input", OSCConn::getFreeBus()), EffectArgument("feedback_output", OSCConn::getFreeBus()), EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("feedback", 0.1f), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_FEEDBACK_INBUS), ArgVis(VT_FEEDBACK_OUTBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, 45, 40);}
EFFECT_END(GenEcho)
	
EFFECT_START(DubEcho, eff_dubecho)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("length", 0.5f), EffectArgument("feedback", 0.1f), EffectArgument("sep", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 10.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(DubEcho)
	
EFFECT_START(FBamFX, eff_fbamfx)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FBamFX)
	
EFFECT_START(FBamFXVD, eff_fbamfx_variable_delay)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FBamFXVD)
	
EFFECT_START(Brassage, eff_brassage)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Brassage)
	
EFFECT_START(BrassageOSC, eff_brassage_sin)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BrassageOSC)
	
EFFECT_START(BrassagePlus, eff_brassage_plus)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("amp", 0.5f), EffectArgument("delay", 1.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 15.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BrassagePlus)
	
EFFECT_START(RMChorus, eff_rmchorus)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 20.0f), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 100.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(RMChorus)
	
EFFECT_START(RMChorus2, eff_rmchorus2)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(RMChorus2)
	
EFFECT_START(RMDelay, eff_rmdelay)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(RMDelay)
	
EFFECT_START(RMDelayRec, eff_rmdelayrec)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("delay", 0.15f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 2.0f)})
		{sendInstance(); initGUI(X, Y, 17, 17);}
EFFECT_END(RMDelayRec)
	
EFFECT_START(WSDistortion, eff_wsdistortion)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("gain", 2.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y, 17, 17);}
EFFECT_END(WSDistortion)
	
EFFECT_START(MixWithSquare, eff_mix_with_square)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
EFFECT_END(MixWithSquare)
	
EFFECT_START(MobilePhoneLag, eff_mobile_phone_lag)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
EFFECT_END(MobilePhoneLag)
	
EFFECT_START(MobilePhoneLag2, eff_mobile_phone_lag2)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
EFFECT_END(MobilePhoneLag2)
	
EFFECT_START(MobilePhoneLag3, eff_mobile_phone_lag3)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5.0f), EffectArgument("width", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
EFFECT_END(MobilePhoneLag3)
	
EFFECT_START(FreqShift, eff_freqshift)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, -100.0f, 100.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FreqShift)
	
EFFECT_START(FreqShiftFromBus, eff_freq_shift)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FreqShiftFromBus)
	
EFFECT_START(PitchShift, eff_pitchshift)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("semitones", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, -5.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(PitchShift)
	
EFFECT_START(RandomPitchShift, eff_rand_pitchshift)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y, 30, 30);}
EFFECT_END(RandomPitchShift)
	
EFFECT_START(Gain, eff_mul)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Gain)
	
EFFECT_START(Clipper4, eff_Clipper4)
			args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("lo", 0.0f), EffectArgument("hi", 1.0f)}),
			argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
			{sendInstance(); initGUI(X, Y);}
EFFECT_END(Clipper4)
	
EFFECT_START(Clipper8, eff_Clipper8)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("lo", 0.0f), EffectArgument("hi", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Clipper8)
	
EFFECT_START(Clipper32, eff_Clipper32)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("lo", 0.0f), EffectArgument("hi", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Clipper32)

EFFECT_START(SoftClipAmp, eff_SoftClipAmp)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("pregain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(SoftClipAmp)
	
EFFECT_START(SoftClipAmp4, eff_SoftClipAmp4)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("pregain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(SoftClipAmp4)
	
EFFECT_START(SoftClipAmp8, eff_SoftClipAmp8)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("pregain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(SoftClipAmp8)
	
EFFECT_START(SoftClipper4,eff_SoftClipper4)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
EFFECT_END(SoftClipper4)
	
EFFECT_START(SoftClipper8, eff_SoftClipper8)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
EFFECT_END(SoftClipper8)
	
EFFECT_START(AYSimple, eff_ay_simple)
		args({EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("amp_bus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_FREQ_INBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y, 30);}
EFFECT_END(AYSimple)
	
EFFECT_START(YMSimple, eff_ym_simple)
		args({EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("amp_bus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_FREQ_INBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 25.0f)})
		{sendInstance(); initGUI(X, Y, 30);}
EFFECT_END(YMSimple)
	
EFFECT_START(Limiter, eff_limiter)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("level", 1.0f), EffectArgument("dur", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.01f, 0.1f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Limiter)
	
EFFECT_START(Normalizer, eff_normalizer)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("level", 1.0f), EffectArgument("dur", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.01f, 0.1f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Normalizer)
	
EFFECT_START(BLowPass, eff_BLowPass)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BLowPass)
	
EFFECT_START(BLowPass4, eff_BLowPass4)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BLowPass4)
	
EFFECT_START(BHiPass, eff_BHiPass)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BHiPass)
	
EFFECT_START(BHiPass4, eff_BHiPass4)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BHiPass4)
	
EFFECT_START(BPeakEQ, eff_BPeakEQ)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BPeakEQ)
	
EFFECT_START(BHiShelf, eff_BHiShelf)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rs", 1.0f), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BHiShelf)
	
EFFECT_START(BLowShelf, eff_BLowShelf)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rs", 1.0f), EffectArgument("gain", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BLowShelf)
	
EFFECT_START(BAllPass, eff_BAllPass)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 5000.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BAllPass)
	
EFFECT_START(BBandPass, eff_BBandPass)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 1000.0f), EffectArgument("bw", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BBandPass)
	
EFFECT_START(ButterworthLPF, eff_LPF)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(ButterworthLPF)
	
EFFECT_START(ButterworthHPF, eff_HPF)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(ButterworthHPF)
	
EFFECT_START(ButterworthBRF, eff_BRF)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(ButterworthBRF)
	
EFFECT_START(ButterworthBPF, eff_BPF)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 100.0f), EffectArgument("rq", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 22000.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(ButterworthBPF)
	
EFFECT_START(OctaveUp, eff_octave_up)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
EFFECT_END(OctaveUp)
	
EFFECT_START(OctaveDown, eff_octave_down)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
EFFECT_END(OctaveDown)
	
EFFECT_START(FormantFilter, eff_formant_filter)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_mul", 0.5f), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(21, 0.5f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f)), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FormantFilter)
	
EFFECT_START(FormantFilterFreq, eff_octave_down)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("freq_mul", 0.5f), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(21, 0.5f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f)), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
EFFECT_END(FormantFilterFreq)
	
EFFECT_START(Amplitude, eff_amplitude)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("attackTime", 0.01f), EffectArgument("releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_AMP_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Amplitude)
	
EFFECT_START(ShepardCycleTone, eff_shepard_cycle_tone)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("amp_bus", OSCConn::getFreeBus()), EffectArgument("amp", 0.5f)}),
		argsVis({ArgVis(VT_OUTBUS), ArgVis(VT_FREQ_INBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y, 30, 30);}
EFFECT_END(ShepardCycleTone)
	
EFFECT_START(Pitch, eff_pitch)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Pitch)
	
EFFECT_START(TartiniPitch, eff_tartini_pitch)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("cutoff", 0.45f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, 17, 17);}
EFFECT_END(TartiniPitch)
	
EFFECT_START(QitchPitch, eff_qitch_pitch)
		
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("ampThreshold", 0.01f), EffectArgument("minfreq", 0.0f), EffectArgument("maxfreq", 2500.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2500.0f), ArgVis(VT_SLIDER, 0.0f, 2500.0f)})
		{sendInstance(); initGUI(X, Y, 17, 17);}
EFFECT_END(QitchPitch)
	
EFFECT_START(Goetzel, eff_goetzel)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("freq_outbus", OSCConn::getFreeBus()), EffectArgument("amp_outbus", OSCConn::getFreeBus()), EffectArgument("freq", 440.0f), EffectArgument("overlap", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_AMP_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 8000.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, EffectAutoGUI::left_padding, 30);}
EFFECT_END(Goetzel)
	
EFFECT_START(SampleDecrease, eff_sample_decrese)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("samplerate", 20000.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 48000.0f)})
		{sendInstance(); initGUI(X, Y, 25, 25);}
EFFECT_END(SampleDecrease)
	
EFFECT_START(BitCrush, eff_bitcrush)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("bitSize", 16.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, 1, 32)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(BitCrush)
	
EFFECT_START(Mix, eff_mix)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Mix)
	
EFFECT_START(MixAmp, eff_mix)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("max_amp1", 0.5f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(MixAmp)
	
EFFECT_START(Mix3, eff_mix3)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Mix3)
	
EFFECT_START(Mix3Amp, eff_mix3)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), 
		EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("max_amp1", 0.3333f), EffectArgument("max_amp2", 0.3333f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)}),
		valueSlider1(0.3333f), valueSlider2(0.3333f)
		{sendInstance(); initGUI(X, Y, 25);}
		float valueSlider1, valueSlider2;
		void doSomething()
		{
			if(((Slider*)drawables[4].drawable)->getValue()!=valueSlider1)
			{
				valueSlider1=((Slider*)drawables[4].drawable)->getValue();
				valueSlider2=((Slider*)drawables[5].drawable)->getValue();
				if(valueSlider1+valueSlider2>1.0f)
				{
					valueSlider2=1.0f-valueSlider1;
					((Slider*)drawables[5].drawable)->setValue(valueSlider2);
				}
				
			}
			else
			if(((Slider*)drawables[5].drawable)->getValue()!=valueSlider2)
			{
				valueSlider1=((Slider*)drawables[4].drawable)->getValue();
				valueSlider2=((Slider*)drawables[5].drawable)->getValue();
				if(valueSlider1+valueSlider2>1.0f)
				{
					valueSlider1=1.0f-valueSlider2;
					((Slider*)drawables[4].drawable)->setValue(valueSlider1);
				}
			}
		}
EFFECT_END(Mix3Amp)
	
EFFECT_START(Gramophone, eff_gramophone)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("noise_amp", 0.2f), EffectArgument("rq", 1.0f),
		EffectArgument("freq", 1000.0f), EffectArgument("imp_freq", 5.0f), EffectArgument("blip_freq", 3.0f), EffectArgument("gain", 2.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 5.0f), ArgVis(VT_SLIDER, 0.1f, 10.0f),
		ArgVis(VT_SLIDER, 1.0f, 15000.0f), ArgVis(VT_SLIDER, 0.0f, 30.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 5.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Gramophone)
	
EFFECT_START(Harmonizer4, eff_harmonizer_4)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Harmonizer4)
	
EFFECT_START(Harmonizer5, eff_harmonizer_5)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f),
		EffectArgument("semitones5", 0.0f), EffectArgument("amp5", 0.0f), EffectArgument("amp_threshold5", 0.02f), EffectArgument("ampmax5", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Harmonizer5)
	
EFFECT_START(Harmonizer6, eff_harmonizer_6)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f),
		EffectArgument("semitones5", 0.0f), EffectArgument("amp5", 0.0f), EffectArgument("amp_threshold5", 0.02f), EffectArgument("ampmax5", 0.06f),
		EffectArgument("semitones6", 0.0f), EffectArgument("amp6", 0.0f), EffectArgument("amp_threshold6", 0.02f), EffectArgument("ampmax6", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Harmonizer6)
	
EFFECT_START(Harmonizer7, eff_harmonizer_7)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f),
		EffectArgument("semitones5", 0.0f), EffectArgument("amp5", 0.0f), EffectArgument("amp_threshold5", 0.02f), EffectArgument("ampmax5", 0.06f),
		EffectArgument("semitones6", 0.0f), EffectArgument("amp6", 0.0f), EffectArgument("amp_threshold6", 0.02f), EffectArgument("ampmax6", 0.06f),
		EffectArgument("semitones7", 0.0f), EffectArgument("amp7", 0.0f), EffectArgument("amp_threshold7", 0.02f), EffectArgument("ampmax7", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Harmonizer7)
	
EFFECT_START(Harmonizer8, eff_harmonizer_8)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("amp_attack", 0.02f), EffectArgument("amp_release", 0.5f),
		EffectArgument("semitones1", 0.0f), EffectArgument("amp1", 0.0f), EffectArgument("amp_threshold1", 0.02f), EffectArgument("ampmax1", 0.06f),
		EffectArgument("semitones2", 0.0f), EffectArgument("amp2", 0.0f), EffectArgument("amp_threshold2", 0.02f), EffectArgument("ampmax2", 0.06f),
		EffectArgument("semitones3", 0.0f), EffectArgument("amp3", 0.0f), EffectArgument("amp_threshold3", 0.02f), EffectArgument("ampmax3", 0.06f),
		EffectArgument("semitones4", 0.0f), EffectArgument("amp4", 0.0f), EffectArgument("amp_threshold4", 0.02f), EffectArgument("ampmax4", 0.06f),
		EffectArgument("semitones5", 0.0f), EffectArgument("amp5", 0.0f), EffectArgument("amp_threshold5", 0.02f), EffectArgument("ampmax5", 0.06f),
		EffectArgument("semitones6", 0.0f), EffectArgument("amp6", 0.0f), EffectArgument("amp_threshold6", 0.02f), EffectArgument("ampmax6", 0.06f),
		EffectArgument("semitones7", 0.0f), EffectArgument("amp7", 0.0f), EffectArgument("amp_threshold7", 0.02f), EffectArgument("ampmax7", 0.06f),
		EffectArgument("semitones8", 0.0f), EffectArgument("amp8", 0.0f), EffectArgument("amp_threshold8", 0.02f), EffectArgument("ampmax8", 0.06f)
		}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS),
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15),
		ArgVis(VT_SLIDER, -12.0f, 12.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15), ArgVis(VT_SLIDER, 0.0f, 1.0f, 15)
		})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Harmonizer8)
	
	
	class Playbuf : public EffectGUI
	{
		private:
			int bufnum=-1;
			
			std::vector<EffectArgument> args;
			std::vector<ArgVis> argsVis;
			
			std::vector<int_pair> visualPositions;
			
			char playbufFileName[MAX_PATH];
			
			void constructor(int X, int Y, int bn=-1)
			{
				if(bn==-1)
				{
					FILE* file=fopen(playbufFileName, "r");
					
					if(file==NULL) 
					{
						fprintf(stderr, "Error: File '%s' not exists\n", playbufFileName);
						strcpy(playbufFileName, "/file/unknown");
					}
					
					fclose(file);
					
					fprintf(stderr, "Loading buffer from file: %s\n", playbufFileName);
					bufnum=OSCConn::loadBuffer(playbufFileName);
				}
				else
				{
					bufnum=bn;
				}
				
				
				args[0].set(bufnum);
				*(std::string*)(argsVis[0].data)=OSCConn::getBufferFileById(bufnum);
				
				if(bn==-1)
				{
					int lastSlash=0;
					
					for(int i=1;playbufFileName[i]!='\0';++i)
					{
						if((playbufFileName[i]=='/' || playbufFileName[i]=='\\') && playbufFileName[i-1]!='\\')
						{
							lastSlash=i;
						}
					}
					
					(*(std::string*)(argsVis[0].data)).erase(0, lastSlash+1);
				}
				
				sendInstance(true); 
				
				initGUI(X, Y);
				
				int w, h;
				SDL_QueryTexture(drawables[0].nameTex, NULL, NULL, &w, &h);
				
				w=std::max(100, w);
				
				visualPositions[0].first=EffectAutoGUI::slider_period + w/2;
				visualPositions[1].first=EffectAutoGUI::slider_period + w + EffectAutoGUI::slider_period;
				
				width=visualPositions[1].first + Bus::size + EffectAutoGUI::slider_period;
				height=visualPositions[1].second + Bus::size + EffectAutoGUI::bottom_padding+h-10 + EffectAutoGUI::slider_period;
				
				visualPositions[2].first=EffectAutoGUI::slider_period*2;
				visualPositions[2].second=visualPositions[1].second + h - 10 + EffectAutoGUI::slider_period;
				
				visualPositions[3].first=visualPositions[2].first+EffectAutoGUI::slider_period*2 + Bus::size;
				visualPositions[3].second=visualPositions[1].second + h - 10 + EffectAutoGUI::slider_period;
				
				updateDrawablePositions();
			}
			
			
		public:
			static constexpr const char* registration_name = "eff_playbuf";
			static constexpr const char* registration_fullname = "Playbuf";
			std::vector<EffectArgument>& getArgs() {return args;}
			int getArgsCount() const {return args.size();}
			std::vector<ArgVis>& getArgumentVisuals() {return argsVis;}
			std::vector<int_pair>& getVisualPositions() {return visualPositions;}
			
			Playbuf(int X, int Y): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("trigger", 1.0f), EffectArgument("loop", 0.0f)}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS), ArgVis(VT_SWITCHBUTTON, 1.0f, -1.0f, 3, 2, true), ArgVis(VT_SWITCHBUTTON, 0.0f, 1.0f, 3, 2, false)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding), int_pair(0, 0), int_pair(0, 0)})
			{
				getOpenFile(playbufFileName, MAX_PATH);
				constructor(X, Y);
			}
			
			Playbuf(int X, int Y, int bufnum): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("trigger", 1.0f), EffectArgument("loop", 0.0f)}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS), ArgVis(VT_SWITCHBUTTON, 1.0f, -1.0f, 3, 2, true), ArgVis(VT_SWITCHBUTTON, 0.0f, 1.0f, 3, 2, false)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding), int_pair(0, 0), int_pair(0, 0)})
			{
				constructor(X, Y, bufnum);
			}
			
			Playbuf(const char* data): args({EffectArgument("bufnum", 0), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("trigger", 1.0f), EffectArgument("loop", 0.0f)}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_OUTBUS), ArgVis(VT_SWITCHBUTTON, 1.0f, -1.0f, 3, 2, true), ArgVis(VT_SWITCHBUTTON, 0.0f, 1.0f, 3, 2, false)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding), int_pair(0, 0), int_pair(0, 0)})
			{
				std::stringstream ss;
				ss<<data;
				int X, Y;
				bool loopStatus;
				ss>>X>>Y>>loopStatus;
				
				ss.ignore(1, ' ');
				ss.getline(playbufFileName, MAX_PATH);
				
				constructor(X, Y);
				
				((SwitchButton*)drawables[3].drawable)->setStatus(loopStatus);
			}
			
			
			void saveData(FILE* file) 
			{
				fprintf(file, "%d %d %d %s ", posX, posY, int(((SwitchButton*)drawables[3].drawable)->getStatus()), playbufFileName);
			}
			~Playbuf() {quitGUI(); OSCConn::deleteBuffer(bufnum);}
	};
	
	
	class Recordbuf : public EffectGUI
	{
		private:
			static constexpr float buffer_size=60.0f; //jedna minuta
		
			int bufnum=-1;
			
			std::vector<EffectArgument> args;
			std::vector<ArgVis> argsVis;
			
			std::vector<int_pair> visualPositions;
			
			void constructor(int X, int Y)
			{
				bufnum=OSCConn::allocBuffer(buffer_size);
				
				args[0].set(bufnum);
				*(std::string*)(argsVis[0].data)=OSCConn::getBufferFileById(bufnum);
				
				sendInstance(true); 
				
				initGUI(X, Y);
				
				int w, h;
				SDL_QueryTexture(drawables[0].nameTex, NULL, NULL, &w, &h);
				
				w=std::max(100, w);
				
				visualPositions[0].first=EffectAutoGUI::slider_period + Bus::size + EffectAutoGUI::slider_period + w/2;
				visualPositions[1].first=EffectAutoGUI::slider_period;
				
				width=visualPositions[1].first + Bus::size + EffectAutoGUI::slider_period*2 + w;
				height=visualPositions[1].second + Bus::size + EffectAutoGUI::bottom_padding+h-10 + EffectAutoGUI::slider_period;
				
				visualPositions[3].first=width - EffectAutoGUI::slider_period*2;
				visualPositions[3].second=visualPositions[1].second + h - 10 + EffectAutoGUI::slider_period;
				
				visualPositions[2].first=visualPositions[3].first - EffectAutoGUI::slider_period*2 - Bus::size;
				visualPositions[2].second=visualPositions[1].second + h - 10 + EffectAutoGUI::slider_period;
				
				updateDrawablePositions();
				new Playbuf(X, Y+height, bufnum);
			}
			
			
		public:
			static constexpr const char* registration_name = "eff_recordbuf";
			static constexpr const char* registration_fullname = "Recordbuf";
			std::vector<EffectArgument>& getArgs() {return args;}
			int getArgsCount() const {return args.size();}
			std::vector<ArgVis>& getArgumentVisuals() {return argsVis;}
			std::vector<int_pair>& getVisualPositions() {return visualPositions;}
			
			Recordbuf(int X, int Y): args({EffectArgument("bufnum", 0), EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("trigger", 1.0f), EffectArgument("loop", 0.0f)}),
			argsVis({ArgVis(VT_TEXT, std::string("")), ArgVis(VT_INBUS), ArgVis(VT_SWITCHBUTTON, 1.0f, -1.0f, 3, 2, true), ArgVis(VT_SWITCHBUTTON, 0.0f, 1.0f, 3, 2, false)}),
			visualPositions({int_pair(0, EffectAutoGUI::top_padding), int_pair(0, EffectAutoGUI::top_padding), int_pair(0, 0), int_pair(0, 0)})
			{
				constructor(X, Y);
			}
			
			//loadData
			
			void saveData(FILE* file) 
			{
				fprintf(file, "%d %d %d ", posX, posY, int(((SwitchButton*)drawables[3].drawable)->getStatus()));
			}
			~Recordbuf() {quitGUI(); OSCConn::deleteBuffer(bufnum);}
	};
	
EFFECT_START(Input, eff_input)
	args({EffectArgument("outbus", OSCConn::getFreeBus())}),
	argsVis({ArgVis(VT_OUTBUS)})
	{sendInstance(); initGUI(X, Y);}
EFFECT_END(Input)
	
EFFECT_START(InputExtended, eff_input_extended)
		args({EffectArgument("outbus1", OSCConn::getFreeBus()), EffectArgument("outbus2", OSCConn::getFreeBus()), EffectArgument("outbus3", OSCConn::getFreeBus()), EffectArgument("outbus4", OSCConn::getFreeBus()),
			    EffectArgument("outbus5", OSCConn::getFreeBus()), EffectArgument("outbus6", OSCConn::getFreeBus()), EffectArgument("outbus7", OSCConn::getFreeBus()), EffectArgument("outbus8", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y, 30, 30);}
EFFECT_END(InputExtended)
	
EFFECT_START(Output, eff_output)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Output)
	
EFFECT_START(OutputExtended, eff_output_extended)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("inbus4", OSCConn::getFreeBus()),
				  EffectArgument("inbus5", OSCConn::getFreeBus()), EffectArgument("inbus6", OSCConn::getFreeBus()), EffectArgument("inbus7", OSCConn::getFreeBus()), EffectArgument("inbus8", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS)})
		{sendInstance(); initGUI(X, Y, 30, 30);}
EFFECT_END(OutputExtended)
	
EFFECT_START(AFM1, eff_afm1)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mod_index", 1.0f), EffectArgument("c", 1.0f), EffectArgument("m", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.01f, 10.0f), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_GRADUALSLIDER, 1, 20)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(AFM1)
	
EFFECT_START(AFM1Env, eff_afm1env)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mod_index_mul", 1.0f), 
		EffectArgument("c", 1.0f), EffectArgument("m", 1.0f), EffectArgument("amp_attackTime", 0.01f), EffectArgument("amp_releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.01f, 6.0f), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
EFFECT_END(AFM1Env)
	
EFFECT_START(AFM2, eff_afm2)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mod_index", 1.0f), EffectArgument("c", 1.0f), EffectArgument("m", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.01f, 10.0f), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_GRADUALSLIDER, 1, 20)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(AFM2)
	
EFFECT_START(AFM2Env, eff_afm2env)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("mod_index_mul", 1.0f), 
		EffectArgument("c", 1.0f), EffectArgument("m", 1.0f), EffectArgument("amp_attackTime", 0.01f), EffectArgument("amp_releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.01f, 6.0f), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_GRADUALSLIDER, 1, 20), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, 20);}
EFFECT_END(AFM2Env)
	
EFFECT_START(Hadamard, eff_hadamard_first)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("hadamard_cut", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, 0, 64)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Hadamard)
	
EFFECT_START(Hadamard2, eff_hadamard_last)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("hadamard_cut", 64.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, 0, 64)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Hadamard2)
	
EFFECT_START(Pipe, eff_pipe)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Pipe)
	
EFFECT_START(GoetzelSinus, eff_goetzel_sinus)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 440.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 20000.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(GoetzelSinus)
	
EFFECT_START(Select2, eff_select2)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("which", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(2, 1.0f, 0.0f))})
		{sendInstance(); initGUI(X, Y, 25);}
EFFECT_END(Select2)
	
EFFECT_START(Select3, eff_select3)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("which", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(3, 2.0f, 1.0f, 0.0f))})
		{sendInstance(); initGUI(X, Y, 25);}
EFFECT_END(Select3)
	
EFFECT_START(Select4, eff_select4)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("inbus4", OSCConn::getFreeBus()),
		EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("which", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(4, 3.0f, 2.0f, 1.0f, 0.0f))})
		{sendInstance(); initGUI(X, Y, 25);}
EFFECT_END(Select4)
	
EFFECT_START(Select5, eff_select5)
		args({EffectArgument("inbus1", OSCConn::getFreeBus()), EffectArgument("inbus2", OSCConn::getFreeBus()), EffectArgument("inbus3", OSCConn::getFreeBus()), EffectArgument("inbus4", OSCConn::getFreeBus()),
		EffectArgument("inbus5", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("which", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_GRADUALSLIDER, FloatArray(5, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f))})
		{sendInstance(); initGUI(X, Y, 25);}
EFFECT_END(Select5)
	
EFFECT_START(Compander, eff_compander)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("thresh", 0.5f), 
		EffectArgument("slopeBelow", 1.0f), EffectArgument("slopeAbove", 1.0f), EffectArgument("clampTime", 0.01f), EffectArgument("relaxTime", 0.1f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 3.0f), ArgVis(VT_SLIDER, 0.0f, 3.0f), ArgVis(VT_SLIDER, 0.0f, 0.1f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Compander)
	
EFFECT_START(WarmChorus, eff_warm_chorus)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("amp_attack", 0.02f), 
		EffectArgument("amp_release", 0.5f), EffectArgument("max_delay", 0.2f), EffectArgument("hadamard_cut", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.01f, 0.5f), ArgVis(VT_GRADUALSLIDER, 0, 25)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(WarmChorus)
	
EFFECT_START(ParamToFreqency, eff_param_to_bus)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("param", 440.0f)}),
		argsVis({ArgVis(VT_FREQ_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 20000.0f)})
		{sendInstance(); initGUI(X, Y, EffectAutoGUI::left_padding, 25);}
EFFECT_END(ParamToFreqency)
	
EFFECT_START(ParamToAmplitude, eff_param_to_bus)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("param", 1.0f)}),
		argsVis({ArgVis(VT_AMP_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, EffectAutoGUI::left_padding, 25);}
EFFECT_END(ParamToAmplitude)
	
EFFECT_START(Sinus, eff_sinus)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq", 440.0f), EffectArgument("amp", 1.0f)}),
		argsVis({ArgVis(VT_OUTBUS),  ArgVis(VT_SLIDER, 0.0f, 20000.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(Sinus)
	
EFFECT_START(FreqHalfToneBucketing, eff_freq_bucketing_halftone)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_AMP_OUTBUS), ArgVis(VT_AMP_INBUS)})
		{sendInstance(); initGUI(X, Y, 35, 35);}
EFFECT_END(FreqHalfToneBucketing)
	
EFFECT_START(FreqQuaterToneBucketing, eff_freq_bucketing_quater_tone)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus())}),
		argsVis({ArgVis(VT_AMP_OUTBUS), ArgVis(VT_AMP_INBUS)})
		{sendInstance(); initGUI(X, Y, 40, 40);}
EFFECT_END(FreqQuaterToneBucketing)
	
EFFECT_START(FreqBucketing, eff_freq_bucketing)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("halftones", 1.0f)}),
		argsVis({ArgVis(VT_AMP_OUTBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y, 20, 20);}
EFFECT_END(FreqBucketing)
	
EFFECT_START(WSDistortionWetDry, eff_wsdistortionwetDry)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("freq", 5.0f), EffectArgument("gain", 1.0f), EffectArgument("sin_amp", 0.1f), EffectArgument("noise_amp", 0.2f), EffectArgument("const_amp", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), 
		ArgVis(VT_SLIDER, 0.0f, 100.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(WSDistortionWetDry)
	
EFFECT_START(RLPFD, eff_RLPFD)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), 
		EffectArgument("cutoff_freq", 250.0f), EffectArgument("resonance", 1.0f), EffectArgument("distortion", 0.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), 
		ArgVis(VT_SLIDER, 0.0f, 2000.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(RLPFD)
	
EFFECT_START(FBam, eff_fbam)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FBam)
	
EFFECT_START(FBamEnv, eff_fbam_env)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()),
		EffectArgument("freq", 440.0f), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f), EffectArgument("amp_attackTime", 0.01f), EffectArgument("amp_releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), 
		ArgVis(VT_SLIDER, 20.0f, 2000.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FBamEnv)
	
EFFECT_START(FBamEnvFreq, eff_fbam_env1)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()),
		EffectArgument("freq_bus", 440.0f), EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f), EffectArgument("amp_attackTime", 0.01f), EffectArgument("amp_releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), 
		ArgVis(VT_FREQ_INBUS), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FBamEnvFreq)
	
EFFECT_START(FBamFiddle, eff_fbam_fiddle)
		args({EffectArgument("inbus", OSCConn::getFreeBus()), EffectArgument("outbus", OSCConn::getFreeBus()),
		EffectArgument("feedback", 0.1f), EffectArgument("amp", 1.0f), EffectArgument("amp_attackTime", 0.01f), EffectArgument("amp_releaseTime", 0.01f)}),
		argsVis({ArgVis(VT_INBUS), ArgVis(VT_OUTBUS), 
		ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 2.5f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f)})
		{sendInstance(); initGUI(X, Y);}
EFFECT_END(FBamFiddle)
	
EFFECT_START(Concat, eff_concat)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("control_bus", OSCConn::getFreeBus()), EffectArgument("source_bus", OSCConn::getFreeBus()), 
		EffectArgument("seektime", 10.0f), EffectArgument("seekdur", 10.0f), EffectArgument("matchlength", 0.05f),
		EffectArgument("freezestore", 0.0f), EffectArgument("zcr", 0.5f), EffectArgument("lms", 0.1f), EffectArgument("sc", 1.0f), EffectArgument("st", 1.0f), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_OUTBUS), ArgVis(VT_INBUS), ArgVis(VT_INBUS), 
		ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f),
		ArgVis(VT_GRADUALSLIDER, 0, 1), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y, 35);}
EFFECT_END(Concat)
	
EFFECT_START(ConcatSinus, eff_concat_sinus)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("source_bus", OSCConn::getFreeBus()), 
		EffectArgument("freq", 440.0f), EffectArgument("amp", 1.0f), EffectArgument("seektime", 10.0f), EffectArgument("seekdur", 10.0f), EffectArgument("matchlength", 0.05f),
		EffectArgument("freezestore", 0.0f), EffectArgument("zcr", 0.5f), EffectArgument("lms", 0.1f), EffectArgument("sc", 1.0f), EffectArgument("st", 1.0f), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_OUTBUS), ArgVis(VT_INBUS), 
		ArgVis(VT_SLIDER, 20.0f, 2000.0f), ArgVis(VT_SLIDER, 0.0f, 1.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f),
		ArgVis(VT_GRADUALSLIDER, 0, 1), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y, 35);}
EFFECT_END(ConcatSinus)
	
EFFECT_START(ConcatSinusBus, eff_concat_sinus_from_bus)
		args({EffectArgument("outbus", OSCConn::getFreeBus()), EffectArgument("source_bus", OSCConn::getFreeBus()), 
		EffectArgument("freq_bus", OSCConn::getFreeBus()), EffectArgument("amp_bus", OSCConn::getFreeBus()), EffectArgument("seektime", 10.0f), EffectArgument("seekdur", 10.0f), EffectArgument("matchlength", 0.05f),
		EffectArgument("freezestore", 0.0f), EffectArgument("zcr", 0.5f), EffectArgument("lms", 0.1f), EffectArgument("sc", 1.0f), EffectArgument("st", 1.0f), EffectArgument("mul", 1.0f)}),
		argsVis({ArgVis(VT_OUTBUS), ArgVis(VT_INBUS), 
		ArgVis(VT_FREQ_INBUS), ArgVis(VT_AMP_INBUS), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 20.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f),
		ArgVis(VT_GRADUALSLIDER, 0, 1), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 2.0f), ArgVis(VT_SLIDER, 0.0f, 10.0f)})
		{sendInstance(); initGUI(X, Y, 35);}
EFFECT_END(ConcatSinusBus)
	
	
	void registerEffects();
	
	Effect* getEffect(std::string name, int X=0, int Y=0);
	
#endif
