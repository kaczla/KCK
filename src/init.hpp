#ifndef INIT_HPP_
#define INIT_HPP_
#include "include_SDL.hpp"
#include "include_SDL_opengl.hpp"
#include "include_SDL_main.hpp"
#include "include_IL.hpp"
#include <iostream>
#include "log_game.hpp"


/*
#ifndef SET_GLOBAL_GAME
#define SET_GLOBAL_GAME
	//const
	int SCREEN_WIDTH;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;
#endif
*/

class Init{
public:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int SCREEN_BPP;
	Init();
	~Init();
	bool init();
	void set_Screen(int Height, int Width, int BPP);
	void clean_up();
private:
	bool init_SDL();
	bool init_GL();
	bool init_IL();
};

#endif
