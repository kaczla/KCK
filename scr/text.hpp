#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "include_SDL.hpp"
#include "include_SDL_ttf.hpp"
#include "include_SDL_opengl.hpp"
#include <iostream>

class Text{
public:
	Text();
	~Text();
	static bool InitText();
	static void Clear();
	void RenderText( std::string text );
	static void RenderTextNow( std::string text );
	void SetColor( Uint8 r, Uint8 g, Uint8 b);
private:
	static bool IsInit;
	static TTF_Font *Font;
	//static SDL_Color TextColorBasic;
	GLuint ImageID;
	SDL_Color TextColor;
};

#endif
