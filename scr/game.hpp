#ifndef GAME_HPP_
#define GAME_HPP_
#include "init.hpp"
#include "settings.hpp"
#include "img.hpp"
#include "anim.hpp"
#include "map.hpp"
#include <vector>
//#include <ft2build.h>
//#include FT_FREETYPE_H

class Game{
public:
	Game();
	~Game();
	void Start();
private:
	void Update();
	void Save();
	void Load();
	inline void Draw_Square();
	Settings settings;
	Init init;
	std::vector <Img> images;
	std::vector <Anim> anim;
	std::vector <Img> error_img;
	//std::vector <Img>::iterator imagesIt;
	Map map2D;
	bool game_start;
	SDL_Event event;
	//int map[50][50];
	int playerx,playery;
	int Zmiana_img_na_anim;
	int tmp_update,tmp_update2;

	//wyswietlanie mapy
	GLfloat Square_size, Square_length ;

	//clock
	Uint32 StartTime, StopEnd;
	int fps;
};


#endif
