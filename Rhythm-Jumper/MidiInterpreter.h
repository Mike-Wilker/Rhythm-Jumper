#pragma once
#include "Barrier.h"
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