#pragma once
/*
class MidiInterpreter
{
private:
	MidiFile* file;
public:
	MidiInterpreter(std::string fileName)
	{
		file = new MidiFile(fileName);
	}
	std::list<Barrier*> getBarriers(SDL_Renderer* renderer)
	{
		std::list<Barrier*> barriers;
		int bpm = file->getTicksPerQuarterNote();
		for (int x = 0; x < file->getNumTracks(); x++)
		{
			for (int y = 0; y < file->getNumEvents(x); y++)
			{
				if (file->getEvent(x, y).isNoteOn())
				{
					barriers.emplace_back(new Fence(renderer, file->getEvent(x, y).tick));
				}
			}
		}
		return barriers;
	}
	~MidiInterpreter()
	{

	}
	
};*/