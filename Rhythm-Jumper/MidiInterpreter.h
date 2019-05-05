#pragma once
#include "Barrier.h"
#include <string>
#include "MidiFile.h"
#include "MidiOptions.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

class MidiInterpreter
{
private:

public:
	MidiInterpreter()
	{

	}
	std::list<Barrier*> InterpretMidi(std::string fileName)
	{
		std::list<Barrier*> barriers;
		return barriers;
	}
	~MidiInterpreter()
	{

	}
};

int MidiInterpreter::readMidi(int argc, char** argv)
{
	Options options;
	options.process(argc, argv);
	MidiFile midifile;
	if (options.getArgCount() == 0) midifile.read(cin);
	else midifile.read(options.getArg(1));
	midifile.doTimeAnalysis();
	midifile.linkNotePairs();

	int tracks = midifile.getTrackCount();
	cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
	if (tracks > 1) cout << "TRACKS: " << tracks << endl;
	for (int track = 0; track<tracks; track++)
	{
		if (tracks > 1) cout << "\nTrack " << track << endl;
		cout << "Tick\tSeconds\tDur\tMessage" << endl;
		for (int event = 0; event<midifile[track].size(); event++) {
			cout << dec << midifile[track][event].tick;
			cout << '\t' << dec << midifile[track][event].seconds;
			cout << '\t';
			if (midifile[track][event].isNoteOn())
				cout << midifile[track][event].getDurationInSeconds();
			cout << '\t' << hex;
			for (int i = 0; i<midifile[track][event].size(); i++)
				cout << (int)midifile[track][event][i] << ' ';
			cout << endl;
		}
	}
}

void MidiInterpreter::playMidi()
{
	//Initialize sound 
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_VolumeMusic(100);
	//Load song 
	string midiFile = LIB_AUDIO + "redlottery.mid";
	Mix_Music *song = Mix_LoadMUS(midiFile.c_str());
	//Play song
	Mix_PlayMusic(song, 1);
}
