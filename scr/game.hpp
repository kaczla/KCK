#ifndef GAME_HPP_
#define GAME_HPP_
#include <vector>
#include "init.hpp"
#include "settings.hpp"
#include "img.hpp"
#include "anim.hpp"
#include "map.hpp"
#include "text.hpp"

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
	std::vector <Img> backgroud;
	//std::vector <Img>::iterator imagesIt;
	Map map2D;
	bool game_start;
	SDL_Event event;
	int playerx,playery;
	int StartImages, EndImages, StartAnim, EndAnim;
	int CurrentMap, CurrentMapObj;
	//int tmp_update,tmp_update2;

	GLfloat Percent, Height_percent, Width_percent;

	//wyswietlanie mapy
	GLfloat Square_size, Square_length ;

	//wyswietlenie tla
	GLfloat Background_bottom_length_x, Background_bottom_length_y;
	//clock
	Uint32 StartTime, StopEnd;
	int fps;
	//TEXT
	Text text;


};

#endif
