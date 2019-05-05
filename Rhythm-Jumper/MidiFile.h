#pragma once
#ifndef _MIDIFILE_H_INCLUDED
#define _MIDIFILE_H_INCLUDED
#include "MidiEventList.h"
#include <vector>
#include <string>
#include <istream>
#include <fstream>
#define TIME_STATE_DELTA       0
#define TIME_STATE_ABSOLUTE    1
#define TRACK_STATE_SPLIT      0
#define TRACK_STATE_JOINED     1

namespace smf
{
	class _TickTime
	{
	public:
		int tick;
		double seconds;
	};

	class MidiFile
	{
	public:
		MidiFile(void);
		MidiFile(const std::string& filename);
		MidiFile(std::istream& input);
		MidiFile(const MidiFile& other);
		MidiFile(MidiFile&& other);
		~MidiFile();

		MidiFile& operator= (const MidiFile& other);
		MidiFile& operator= (MidiFile&& other);

		bool read(const std::string& filename);
		bool read(std::istream& instream);
		bool write(const std::string& filename);
		bool write(std::ostream& out);
		bool writeHex(const std::string& filename, int width = 25);
		bool writeHex(std::ostream& out, int width = 25);
		bool writeBinasc(const std::string& filename);
		bool writeBinasc(std::ostream& out);
		bool writeBinascWithComments(const std::string& filename);
		bool writeBinascWithComments(std::ostream& out);
		bool status(void) const;
		const MidiEventList& operator[] (int aTrack) const;
		MidiEventList& operator[] (int aTrack);
		int getTrackCount(void) const;
		int getNumTracks(void) const;
		int size(void) const;
		void removeEmpties(void);
		void makeDeltaTicks(void);
		void deltaTicks(void);
		void makeAbsoluteTicks(void);
		void absoluteTicks(void);
		int getTickState(void) const;
		bool isDeltaTicks(void) const;
		bool isAbsoluteTicks(void) const;
		void joinTracks(void);
		void splitTracks(void);
		void splitTracksByChannel(void);
		int getTrackState(void) const;
		int hasJoinedTracks(void) const;
		int hasSplitTracks(void) const;
		int getSplitTrack(int track, int index) const;
		int getSplitTrack(int index) const;
		void sortTrack(int track);
		void sortTracks(void);
		void markSequence(void);
		void markSequence(int track, int sequence = 1);
		void clearSequence(void);
		void clearSequence(int track);
		int addTrack(void);
		int addTrack(int count);
		int addTracks(int count);
		void deleteTrack(int aTrack);
		void mergeTracks(int aTrack1, int aTrack2);
		int getTrackCountAsType1(void);
		void setMillisecondTicks(void);
		int getTicksPerQuarterNote(void) const;
		int getTPQ(void) const;
		void setTicksPerQuarterNote(int ticks);
		void setTPQ(int ticks);
		void doTimeAnalysis(void);
		double getTimeInSeconds(int aTrack, int anIndex);
		double getTimeInSeconds(int tickvalue);
		double getAbsoluteTickTime(double starttime);
		int getFileDurationInTicks(void);
		double getFileDurationInQuarters(void);
		double getFileDurationInSeconds(void);
		int linkNotePairs(void);
		int linkEventPairs(void);
		void clearLinks(void);
		void setFilename(const std::string& aname);
		const char* getFilename(void) const;
		MidiEvent* addEvent(int aTrack, int aTick, std::vector<uchar>& midiData);
		MidiEvent* addEvent(MidiEvent& mfevent);
		MidiEvent* addEvent(int aTrack, MidiEvent& mfevent);
		MidiEvent& getEvent(int aTrack, int anIndex);
		const MidiEvent& getEvent(int aTrack, int anIndex) const;
		int getEventCount(int aTrack) const;
		int getNumEvents(int aTrack) const;
		void allocateEvents(int track, int aSize);
		void erase(void);
		void clear(void);
		void clear_no_deallocate(void);
		MidiEvent* addNoteOn(int aTrack, int aTick, int aChannel, int key, int vel);
		MidiEvent* addNoteOff(int aTrack, int aTick, int aChannel, int key, int vel);
		MidiEvent* addNoteOff(int aTrack, int aTick, int aChannel, int key);
		MidiEvent* addController(int aTrack, int aTick, int aChannel, int num, int value);
		MidiEvent* addPatchChange(int aTrack, int aTick, int aChannel, int patchnum);
		MidiEvent* addTimbre(int aTrack, int aTick, int aChannel, int patchnum);
		MidiEvent* addPitchBend(int aTrack, int aTick, int aChannel, double amount);
		MidiEvent* addSustain(int aTrack, int aTick, int aChannel, int value);
		MidiEvent* addSustainPedal(int aTrack, int aTick, int aChannel, int value);
		MidiEvent* addSustainOn(int aTrack, int aTick, int aChannel);
		MidiEvent* addSustainPedalOn(int aTrack, int aTick, int aChannel);
		MidiEvent* addSustainOff(int aTrack, int aTick, int aChannel);
		MidiEvent* addSustainPedalOff(int aTrack, int aTick, int aChannel);
		MidiEvent* addMetaEvent(int aTrack, int aTick, int aType, std::vector<uchar>& metaData);
		MidiEvent* addMetaEvent(int aTrack, int aTick, int aType, const std::string& metaData);
		MidiEvent* addText(int aTrack, int aTick, const std::string& text);
		MidiEvent* addCopyright(int aTrack, int aTick, const std::string& text);
		MidiEvent* addTrackName(int aTrack, int aTick, const std::string& name);
		MidiEvent* addInstrumentName(int aTrack, int aTick, const std::string& name);
		MidiEvent* addLyric(int aTrack, int aTick, const std::string& text);
		MidiEvent* addMarker(int aTrack, int aTick, const std::string& text);
		MidiEvent* addCue(int aTrack, int aTick, const std::string& text);
		MidiEvent* addTempo(int aTrack, int aTick, double aTempo);
		MidiEvent* addTimeSignature(int aTrack, int aTick, int top, int bottom, int clocksPerClick = 24, int num32dsPerQuarter = 8);
		MidiEvent* addCompoundTimeSignature(int aTrack, int aTick, int top, int bottom, int clocksPerClick = 36, int num32dsPerQuarter = 8);
		uchar readByte(std::istream& input);
		static ushort readLittleEndian2Bytes(std::istream& input);
		static ulong readLittleEndian4Bytes(std::istream& input);
		static std::ostream& writeLittleEndianUShort(std::ostream& out, ushort value);
		static std::ostream& writeBigEndianUShort(std::ostream& out, ushort value);
		static std::ostream& writeLittleEndianShort(std::ostream& out, short value);
		static std::ostream& writeBigEndianShort(std::ostream& out, short value);
		static std::ostream& writeLittleEndianULong(std::ostream& out, ulong value);
		static std::ostream& writeBigEndianULong(std::ostream& out, ulong value);
		static std::ostream& writeLittleEndianLong(std::ostream& out, long value);
		static std::ostream& writeBigEndianLong(std::ostream& out, long value);
		static std::ostream& writeLittleEndianFloat(std::ostream& out, float value);
		static std::ostream& writeBigEndianFloat(std::ostream& out, float value);
		static std::ostream& writeLittleEndianDouble(std::ostream& out, double value);
		static std::ostream& writeBigEndianDouble(std::ostream& out, double value);

	protected:
		std::vector<MidiEventList*> m_events;
		int m_ticksPerQuarterNote = 120;
		int m_trackCount = 1;
		int m_theTrackState = TRACK_STATE_SPLIT;
		int m_theTimeState = TIME_STATE_ABSOLUTE;
		std::string m_readFileName;
		bool m_timemapvalid = false;
		std::vector<_TickTime> m_timemap;
		bool m_rwstatus = true;
		bool m_linkedEventsQ = false;
	private:
		int extractMidiData(std::istream& inputfile, std::vector<uchar>& array, uchar& runningCommand);
		ulong readVLValue(std::istream& inputfile);
		ulong unpackVLV(uchar a = 0, uchar b = 0, uchar c = 0, uchar d = 0, uchar e = 0);
		void writeVLValue(long aValue, std::vector<uchar>& data);
		int makeVLV(uchar *buffer, int number);
		static int ticksearch(const void* A, const void* B);
		static int secondsearch(const void* A, const void* B);
		void buildTimeMap(void);
		double linearTickInterpolationAtSecond(double seconds);
		double linearSecondInterpolationAtTick(int ticktime);
	};
}
std::ostream& operator<<(std::ostream& out, smf::MidiFile& aMidiFile);
#endif 
