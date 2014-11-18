#ifndef INIT_HPP_
#define INIT_HPP_
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <SDL\SDL_main.h>
#include <IL\il.h>
#include <iostream>


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
	Init(){
		this->SCREEN_BPP=32;
		this->SCREEN_HEIGHT=480;
		this->SCREEN_WIDTH=640;
	}
	~Init(){
		this->clean_up();
	}
	bool init();
	void set_Screen(int Height, int Width, int BPP);
private:
	bool init_SDL();
	bool init_GL();
	bool init_IL();
	void clean_up();
};

#endif
