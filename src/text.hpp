#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "include_SDL.hpp"
#include "include_SDL_ttf.hpp"
#include "include_SDL_opengl.hpp"
#include <iostream>
#include <vector>
#include "log_game.hpp"

typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;

/**
 * Przetwarzanie podanego tekstu do bitmapy i wyświetlenie na ekranie.
 */
class Text{
public:
	Text();
	~Text();
	/**
	 * Uruchomienie biblioteki SDL_TTF
	 * @return kod błędu
	 */
	static bool InitText();
	/**
	 * Zamknięcie biblioteki SDL_TTF
	 */
	static void Clear();
	/**
	 * Rysowanie tekstu do bit mapy
	 * @param text - tekst do przetworzenia
	 */
	void RenderText( std::string text );
	/**
	 * Rysowanie tekstu do bit mapy
	 * @param text tekst do przetworzenia ( utf16 )
	 */
	void RenderText( u16string text );
	/**
	 * Ustawienie koloru tekstu
	 * @param r - czerwony
	 * @param g - zielony
	 * @param b - niebieski
	 */
	void SetColor( Uint8 r, Uint8 g, Uint8 b);
	/**
	 * Ustawienie maksymalnej ilości znaków w jednej linii
	 * @param max - ilośc znaków
	 */
	void SetMaxLength( float max );
	/**
	 * Ustawia odstęp pomiędzy wierszami
	 * @param line - odstęp wierszy w punktach
	 */
	void SetNextLine( float line );
	/**
	 * Rysowanie przetworzonego tekstu
	 */
	void Draw();
	/**
	 * Rysowanie przetworzonego tekstu pod kątem 5 stopni
	 */
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
