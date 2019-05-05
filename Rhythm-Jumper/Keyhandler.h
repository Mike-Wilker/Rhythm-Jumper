#pragma once
class KeyHandler
{
private:
	std::list<SDL_Keycode> heldKeys;
	SDL_mutex* mutex;
public:
	KeyHandler()
	{
		mutex = SDL_CreateMutex();
	}
	void pollKeys()
	{
		SDL_LockMutex(mutex);
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				heldKeys.emplace_front(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				heldKeys.remove(event.key.keysym.sym);
				break;
			}
		}
		SDL_UnlockMutex(mutex);
	}
	std::list<SDL_Keycode> getHeldKeys()
	{
		SDL_LockMutex(mutex);
		SDL_UnlockMutex(mutex);
		return heldKeys;
	}
	~KeyHandler()
	{
		SDL_DestroyMutex(mutex);
	}
};