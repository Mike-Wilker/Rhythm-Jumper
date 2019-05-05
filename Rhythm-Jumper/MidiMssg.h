#pragma once
#ifndef _MIDIMSSG_H_INCLUDED
#define _MIDIMSSG_H_INCLUDED
#include <vector>
#include <string>

namespace smf 
{
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

class MidiMssg : public std::vector<uchar>
{
	public:
		MidiMssg(void);
		MidiMssg(int command);
		MidiMssg(int command, int p1);
		MidiMssg(int command, int p1, int p2);
		MidiMssg(const MidiMssg& message);
		MidiMssg(const std::vector<uchar>& message);
		MidiMssg(const std::vector<char>& message);
		MidiMssg(const std::vector<int>& message);
		MidiMssg();

		MidiMssg& operator= (const MidiMssg& message);
		MidiMssg& operator= (const std::vector<uchar>& bytes);
		MidiMssg& operator= (const std::vector<char>& bytes);
		MidiMssg& operator= (const std::vector<int>& bytes);

		void sortTrack(void);
		void sortTrackWithSequence(void);
		int getP0(void) const;
		int getP1(void) const;
		int getP2(void) const;
		int getP3(void) const;
		void setP0(int value);
		void setP1(int value);
		void setP2(int value);
		void setP3(int value);
		int  getSize(void) const;
		void setSize(int asize);
		int setSizeToCommand(void);
		int resizeToCommand(void);
		int getKeyNumber(void) const;
		int getVelocity(void) const;
		void setKeyNumber(int value);
		void setVelocity(int value);
		void setSpelling(int base7, int accidental);
		void getSpelling(int& base7, int& accidental);
		int  getControllerNumber(void) const;
		int  getControllerValue(void) const;
		int  getCommandNibble(void) const;
		int  getCommandByte(void) const;
		int  getChannelNibble(void) const;
		int  getChannel(void) const;
		void setCommandByte(int value);
		void setCommand(int value);
		void setCommand(int value, int p1);
		void setCommand(int value, int p1, int p2);
		void setCommandNibble(int value);
		void setChannelNibble(int value);
		void setChannel(int value);
		void setParameters(int p1, int p2);
		void setParameters(int p1);
		void setMessage(const std::vector<uchar>& message);
		void setMessage(const std::vector<char>& message);
		void setMessage(const std::vector<int>& message);
		bool isMetaMessage(void) const;
		bool isMeta(void) const;
		bool isNote(void) const;
		bool isNoteOff(void) const;
		bool isNoteOn(void) const;
		bool isAftertouch(void) const;
		bool isController(void) const;
		bool isSustain(void) const;
		bool isSustainOn(void) const;
		bool isSustainOff(void) const;
		bool isSoft(void) const;
		bool isSoftOn(void) const;
		bool isSoftOff(void) const;
		bool isPatchChange(void) const;
		bool isTimbre(void) const;
		bool isPressure(void) const;
		bool isPitchbend(void) const;
		bool isEmpty(void) const;
		void makeNoteOn(int channel, int key, int velocity);
		void makeNoteOff(int channel, int key, int velocity);
		void makeNoteOff(int channel, int key);
		void makeNoteOff(void);
		void makePatchChange(int channel, int patchnum);
		void makeTimbre(int channel, int patchnum);
		void makeController(int channel, int num, int value);
		void makeSustain(int channel, int value);
		void makeSustainPedal(int channel, int value);
		void makeSustainOn(int channel);
		void makeSustainPedalOn(int channel);
		void makeSustainOff(int channel);
		void makeSustainPedalOff(int channel);
		void makeMetaMessage(int mnum, const std::string& data);
		void makeText(const std::string& name);
		void makeCopyright(const std::string& text);
		void makeTrackName(const std::string& name);
		void makeInstrumentName(const std::string& name);
		void makeLyric(const std::string& text);
		void makeMarker(const std::string& text);
		void makeCue(const std::string& text);
		void makeTimeSignature(int top, int bottom,int clocksPerClick = 24, int num32dsPerQuarter = 8);
		void makeTempo(double tempo) { setTempo(tempo); }
		int getTempoMicro(void) const;
		int getTempoMicroseconds(void) const;
		double getTempoSeconds(void) const;
		double getTempoBPM(void) const;
		double getTempoTPS(int tpq) const;
		double getTempoSPT(int tpq) const;
		int getMetaType(void) const;
		bool isText(void) const;
		bool isCopyright(void) const;
		bool isTrackName(void) const;
		bool isInstrumentName(void) const;
		bool isLyricText(void) const;
		bool isMarkerText(void) const;
		bool isTempo(void) const;
		bool isTimeSignature(void) const;
		bool isKeySignature(void) const;
		bool isEndOfTrack(void) const;
		std::string getMetaContent(void);
		void setMetaContent(const std::string& content);
		void setTempo(double tempo);
		void setTempoMicroseconds(int microseconds);
		void setMetaTempo(double tempo);
};
}
#endif