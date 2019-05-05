#pragma once
#ifndef _MIDIEVENT_H_INCLUDED
#define _MIDIEVENT_H_INCLUDED
#include "MidiMssg.h"
#include <vector>

namespace smf
{
	class MidiEvent : public MidiMssg
	{
	public:
		MidiEvent(void);
		MidiEvent(int command);
		MidiEvent(int command, int param1);
		MidiEvent(int command, int param1, int param2);
		MidiEvent(const MidiMssg& message);
		MidiEvent(const MidiEvent& mfevent);
		MidiEvent(int aTime, int aTrack, std::vector<uchar>& message);
		~MidiEvent();

		MidiEvent& operator=(const MidiEvent& mfevent);
		MidiEvent& operator=(const MidiMssg& message);
		MidiEvent& operator=(const std::vector<uchar>& bytes);
		MidiEvent& operator=(const std::vector<char>& bytes);
		MidiEvent& operator=(const std::vector<int>& bytes);

		void clearVariables(void);
		void unlinkEvent(void);
		void unlinkEvents(void);
		void linkEvent(MidiEvent* mev);
		void linkEvents(MidiEvent* mev);
		void linkEvent(MidiEvent& mev);
		void linkEvents(MidiEvent& mev);
		int isLinked(void) const;
		MidiEvent* getLinkedEvent(void);
		const MidiEvent* getLinkedEvent(void) const;
		int getTickDuration(void) const;
		double getDurationInSeconds(void) const;
		int tick;
		int track;
		double seconds;
		int seq;
	private:
		MidiEvent* m_eventlink;
	};

	class MidiEventList
	{
	public:
		MidiEventList(void);
		MidiEventList(const MidiEventList& other);
		MidiEventList(MidiEventList&& other);
		~MidiEventList();

		MidiEventList&   operator=(MidiEventList& other);
		MidiEvent& operator[] (int index);
		const MidiEvent& operator[] (int index) const;
		MidiEvent& back(void);
		const MidiEvent& back(void) const;
		MidiEvent& last(void);
		const MidiEvent& last(void) const;
		MidiEvent& getEvent(int index);
		const MidiEvent& getEvent(int index) const;
		void clear(void);
		void  reserve(int rsize);
		int getEventCount(void) const;
		int getSize(void) const;
		int size(void) const;
		void removeEmpties(void);
		int linkNotePairs(void);
		int linkEventPairs(void);
		void clearLinks(void);
		void clearSequence(void);
		int markSequence(int sequence = 1);
		int push(MidiEvent& event);
		int push_back(MidiEvent& event);
		int append(MidiEvent& event);
		void detach(void);
		int push_back_no_copy(MidiEvent* event);
		MidiEvent** data(void);
	protected:
		std::vector<MidiEvent*> list;
	private:
		void sort(void);
		friend class MidiFile;
	};
	int eventcompare(const void* a, const void* b);

}
#endif