#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_
#include <fstream>
#include <iostream>
#include "log_game.hpp"

/**
 * Ładowanie i zapis ustawień dla gry.
 */
class Settings{
public:
	Settings();
	~Settings();
	/**
	 * Inicjalizacja ustawień gry
	 */
	void init_Settings();
	/**
	 * Zapisanie ustawień gry do pliku
	 */
	void SaveSettings();
	/**
	 *
	 * @return wartość pełnego ekranu
	 */
	bool ReturnFullscreen();
	/**
	 *
	 * @return szerokość ekranu
	 */
	int ReturnWidth();
	/**
	 *
	 * @return wysokość ekranu
	 */
	int ReturnHeight();
	/**
	 *
	 * @return wartość bitów na pixel
	 */
	int ReturnBpp();
private:
	bool fullscreen;
	int width;
	int height;
	int bpp;
	void SetValue(std::string name, int value);
};

#endif
