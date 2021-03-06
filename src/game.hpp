#ifndef GAME_HPP_
#define GAME_HPP_
#include <vector>
#include "init.hpp"
#include <time.h>
#include "settings.hpp"
#include "img.hpp"
#include "anim.hpp"
#include "map.hpp"
#include "text.hpp"
#include "log_game.hpp"
#include "bot.hpp"
#include <cstdlib>
#include <pthread.h>

typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;

/**
 * Główna klasa gry, która zarządza wszystkimi elementami.
 */
class Game{
public:
	Game();
	~Game();
	/**
	 * Uruchomienie gry
	 */
	void Start();
private:
	void Update();
	void Save();
	void Load();
	inline void Draw_Square();
	Settings settings;
	Init init;
	//LOGI
	inline void DateToFile();
	LogGame logGame;
	//GRAFIKA
	std::vector <Img> images;
	std::vector <Anim> anim;
	std::vector <Img> error_img;
	std::vector <Img> backgroud;
	std::vector <Img> other;
	inline void ReadImages();
	inline void ReadAnim();
	Img *MenuFood, *MenuWood, *MenuStone, *MenuBar[4];
	Img *ScreenStart, *Working;
	Img *Hungry[3];
	inline void DrawMenu();
	//MAPA GRY
	Map map2D;
	bool game_start;
	//KEY EVENT
	SDL_Event event;
	SDLKey KeyEvent;
	SDLMod KeyEventState;
	inline void ReadKey();
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
	bool CheckAddChar;
	Text TextInput;
	u16string Input;
	u16string InputBackUp;
	GLfloat InputPositionX, InputPositionY;
	GLfloat InputPositionLengthMax;
	void DrawInput();
	unsigned int LastInput, NextInput;
	Text TextBotMessage;
	std::string BotMessage;
	GLfloat BotMessagePositionX, BotMessagePositionY;
	GLfloat BotMessagePositionLengthMax;
	void DrawBotMessage();
	std::string Speak, SpeakThread;
	//AIML
	Bot bot;
	//thread
	pthread_t Thread;
};

void *SpeakText( void * In );

#endif
