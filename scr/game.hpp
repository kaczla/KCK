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
	//GRAFIKA
	std::vector <Img> images;
	std::vector <Anim> anim;
	std::vector <Img> error_img;
	std::vector <Img> backgroud;
	inline void ReadImages();
	inline void ReadAnim();
	//MAPA GRY
	Map map2D;
	bool game_start;
	//KEY EVENT
	SDL_Event event;
	SDLKey KeyEvent;
	//WYŚWIETLANIE MAPY
	GLfloat Percent, Height_percent, Width_percent;
	GLfloat Square_size, Square_length ;
	inline void ZoomIN();
	inline void ZoomOut();
	int StartImages, EndImages, StartAnim, EndAnim;
	int CurrentMap, CurrentMapObj;
	int CurrentPlayerX, CurrentPlayerY;
	//WYŚWIETLANIE TŁA
	GLfloat Background_bottom_length_x, Background_bottom_length_y;
	//ZEGAR CPU
	Uint32 StartTime, StopEnd;
	int fps;
	//TEXT
	Text text;
	std::string Input;
	GLfloat InputPositionX, InputPositionY;
	std::string BotMessage;
	GLfloat BotMessagePositionX, BotMessagePositionY;
};

#endif
