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

/**
 * Ładowanie ustawień gry i inicjalizowanie podstawowych bibliotek.
 */
class Init{
public:
	/**
	 * Szerokość ekranu
	 */
	int SCREEN_WIDTH;
	/**
	 * Wysokość ekranu
	 */
	int SCREEN_HEIGHT;
	/**
	 * Bity na pixel
	 */
	int SCREEN_BPP;
	Init();
	~Init();
	/**
	 * Inicjalizuje podstawowe biblioteki
	 * @return kod błędu
	 */
	bool init();
	/**
	 * Ustawia wielkość okna gry
	 * @param Height - wysokość
	 * @param Width - szerokość
	 * @param BPP - bity na pixel
	 */
	void set_Screen(int Height, int Width, int BPP);
	/**
	 * Zwalnia pamięć
	 */
	void clean_up();
private:
	bool init_SDL();
	bool init_GL();
	bool init_IL();
};

#endif
