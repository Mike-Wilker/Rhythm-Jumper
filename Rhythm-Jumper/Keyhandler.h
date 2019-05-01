#pragma once
class KeyHandler
{
private:
	std::vector<char> heldKeys;
public:
	KeyHandler()
	{

	}
	void pollKeys()
	{

	}
	std::vector<char> getPressedKeys()
	{
		return heldKeys;
	}
	~KeyHandler()
	{

	}
};