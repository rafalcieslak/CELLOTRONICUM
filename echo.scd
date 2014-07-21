////DIST ECHO
SynthDef.new(\eff_distecho, {
	arg inbus=8, outbus=0, amp=0.5, delay=0.5, decay=0.5;
	var in = In.ar(inbus,1);
	var pom = in/(in.abs+1);
	var delayed = CombC.ar(pom,delay,delay,decay,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_distecho, [\inbus, 8, \outbus, 0, \amp, 1.0, \delay, 0.5, \decay, 2]);

x.set(\delay,0.04);
x.set(\freq,200);
*/

//SHIFT ECHO (działa)
SynthDef.new(\eff_shiftecho, {
	arg inbus=8, outbus=0, freq=1, phase=0, delay=0.5, decay=0.5;
	var in = In.ar(inbus,1);
	var pom = FreqShift.ar(in,freq,phase);
	var delayed = CombC.ar(pom,delay,delay,decay,1,in);
	Out.ar(outbus,delayed);
}).add;

/*/TESTS
x = Synth.new(\eff_shiftecho, [\inbus, 8, \outbus, 0, \delay, 0.5, \decay, 0.9, \freq, 10]);
*/

//ECHO WITH CUSTOMIZED FEEDBACK?
SynthDef.new(\eff_genecho, {
	arg inbus=8, outbus=0, feedback_input=99, feedback_output=99, delay=0, decay=0; //.zobaczyć, czy ten feedback output jest potrzebny!
	var input = In.ar(inbus,1)+InFeedback.ar(feedback_input);
	OffsetOut.ar(feedback_output, DelayC.ar(decay*input, delay, delay - ControlRate.ir.reciprocal)); // subtract block size
	Out.ar(outbus,input);
}).add;

/*/TEST
x = Synth.new(\eff_genecho, [\inbus, 8, \outbus, 0, \delay, 0.5, \decay, 0.7]);
*/

SynthDef.new(\gramophone, {
	arg inbus=8, outbus=0, noise_amp = 0.2, rq=1, freq=1000, imp_freq=5, blip_freq=3, gain = 2;
	var input = gain* In.ar(inbus,1);
	var filtered = BBandPass.ar(WhiteNoise.ar(noise_amp/300),freq,rq);
	var sig = Impulse.kr(imp_freq,0,WhiteNoise.kr(noise_amp)) + Impulse.kr(imp_freq/2,0.1,WhiteNoise.kr(noise_amp)) + Impulse.kr(imp_freq/3,0.1,WhiteNoise.kr(noise_amp/2));
	var impulses = Blip.ar(blip_freq,300,sig*2);
	var res = input/(input.abs+1);
	var noises = (0.98*impulses) + filtered  + GrayNoise.ar(noise_amp/100) + WhiteNoise.ar(noise_amp/1000);
	var filtr = MidEQ.ar(res,750,1,0.9);
	var mid = BLowPass.ar(BHiPass.ar(filtr,168,0.5),2000,0.5);
	var comp = Compander.ar(mid,mid,0.1,2,0.5,0.01,0.02);
	Out.ar(outbus, comp+noises);
}).add;

/* TEST - nagrywanie do pliku

SynthDef(\recordTone, { |buffer|
    RecordBuf.ar(In.ar(0), buffer, loop: 0, doneAction: 2);
}).add;

b = Buffer.read(s, ~p +/+ "zBrody4.wav");
b.bufnum.postln;
Routine({
    var recordfn =
	 {  var server = Server.local;
		var buffer = Buffer.alloc(s, b.numFrames, b.numChannels,2);
        server.sync;
        server.makeBundle(func: {
			var recorder = Synth.tail(s, \recordTone, [\buffer, buffer]);
            var x = Synth.new(\gramophone, [\inbus, 16, \outbus, 0, \noise_amp, 1.0]);
			var y = Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 5]);
        });
        (b.numFrames/s.sampleRate).wait;
        buffer.write( ~p +/+ "test1.wav", "WAVE", "int16", completionMessage: ["/b_free", buffer]);
    };
    recordfn.value;
}).next;

//TEST 2 - nagrywanie w locie
b = Buffer.read(s, ~p +/+ "zBrody4.wav");
b.bufnum.postln;
a = Buffer.alloc(s, b.numFrames, b.numChannels,2);
Synth.new(\gramophone, [\inbus, 16, \outbus, 0, \noise_amp, 1.0]);
Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 5]);
Synth.tail(s, \recordTone, [\buffer, a]);

a.write( ~p +/+ "test1.wav", "WAVE", "int16", completionMessage: ["/b_free", a]);

//TEST 3 - nagrywanie przez server
s.prepareForRecord(~p +/+ "server_record.aiff");

Synth.new(\gramophone, [\inbus, 16, \outbus, 0, \noise_amp, 1.0]);
Synth.new(\eff_playbuf, [\outbus, 16, \bufnum, 5]);
s.record;

s.stopRecording;
//jest jeszze s.pauseRecording
*/
/*//TEST
/*
x = Synth.new(\gramophone, [\inbus, 8, \outbus, 0, \noise_amp, 0.8]);
x.set(\noise_amp, 0.5);
x.set(\imp_freq, 5);
x.set(\blip_freq, 3);
x.set(\gain, 2);
x.set(\freq,1200);*/
*/