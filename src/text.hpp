#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "include_SDL.hpp"
#include "include_SDL_ttf.hpp"
#include "include_SDL_opengl.hpp"
#include <iostream>
#include <vector>
#include "log_game.hpp"

typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;

class Text{
public:
	Text();
	~Text();
	static bool InitText();
	static void Clear();
	void RenderText( std::string text );
	void RenderText( u16string text );
	void SetColor( Uint8 r, Uint8 g, Uint8 b);
	void SetMaxLength( float max );
	void SetNextLine( float line );
	void Draw();
	void DrawPlusAngle();
private:
	static bool IsInit;
	static TTF_Font *Font;
	static SDL_Color TextColorBlack;
	static SDL_Color TextColorWhite;
	static SDL_Color TextColorRed;
	static SDL_Color TextColorGreen;
	static SDL_Color TextColorBlue;
	static int FontSize;
	unsigned int MaxLength;
	float NextLine;
	std::vector <GLuint> ImageID;
	std::vector <GLint> Width;
	std::vector <GLint> Height;
	SDL_Color TextColor;
};

#endif
