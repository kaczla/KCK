#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "include_SDL.hpp"
#include "include_SDL_ttf.hpp"
#include "include_SDL_opengl.hpp"
#include <iostream>
#include "log_game.hpp"

class Text{
public:
	Text();
	~Text();
	static bool InitText();
	static void Clear();
	void RenderText( std::string text );
	static void RenderTextNow( std::string text );
	void SetColor( Uint8 r, Uint8 g, Uint8 b);
	static void SetMaxLength( float max );
private:
	static bool IsInit;
	static TTF_Font *Font;
	static SDL_Color TextColorBlack;
	static SDL_Color TextColorWhite;
	static SDL_Color TextColorRed;
	static SDL_Color TextColorGreen;
	static SDL_Color TextColorBlue;
	static int FontSize;
	static unsigned int MaxLength;
	GLuint ImageID;
	SDL_Color TextColor;
};

#endif
