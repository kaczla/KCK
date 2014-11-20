#include "text.hpp"

bool Text::IsInit = false;
TTF_Font *Text::Font = NULL;

Text::Text(){
	this->SetColor( 255, 255, 255 );
	this->ImageID = 0;
}

Text::~Text(){
	glDeleteTextures(1, &this->ImageID);
}

bool Text::InitText(){
	if( ! Text::IsInit ){
		std::cout<<SDL_GetTicks()<<": Freetype - Inicjalizowanie\n";
		if( TTF_Init() == -1 ){
			std::cerr<<SDL_GetTicks()<<": FreeType - Błąd: Niepowodzenie TTF_Init !\n";
			return false;
		}
		Text::Font = TTF_OpenFont( "bin/font.ttf", 14 );
		if( Text::Font == NULL ){
			std::cerr<<SDL_GetTicks()<<": FreeType - Błąd: Niepowodzenie TTF_OpenFont !\n";
			return false;
		}
		TTF_SetFontStyle( Text::Font, TTF_STYLE_BOLD );
		Text::IsInit = true;
		std::cout<<SDL_GetTicks()<<": Freetype - Inicjalizacja przebiegła pomyślnie\n";
	}
	return true;
}

void Text::Clear(){
	if( Text::IsInit ){
		TTF_Quit();
	}
}

void Text::SetColor( Uint8 r, Uint8 g, Uint8 b){
	this->TextColor.r = r;
	this->TextColor.g = g;
	this->TextColor.b = b;
}


void Text::RenderText( std::string text ){
	if( ! Text::IsInit ){
		TTF_CloseFont( Text::Font );
		Text::InitText();
	}

	SDL_Surface *Message = TTF_RenderUTF8_Blended( Text::Font, text.c_str(), this->TextColor);
	glGenTextures( 1, &this->ImageID );
	glBindTexture( GL_TEXTURE_2D, this->ImageID );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels );
	glBegin( GL_QUADS );
		glTexCoord2d( 0.0, 0.0 ); glVertex2d( 0.0, 0.0 );
		glTexCoord2d( 1.0, 0.0 ); glVertex2d( Message->w, 0.0 );
		glTexCoord2d( 1.0, 1.0 ); glVertex2d( Message->w, Message->h );
		glTexCoord2d( 0.0, 1.0 ); glVertex2d( 0.0, Message->h );
	glEnd();

	SDL_FreeSurface(Message);
}

void Text::RenderTextNow( std::string text ){
	SDL_Color TextColorBasic;
	TextColorBasic.r = 0;
	TextColorBasic.g = 0;
	TextColorBasic.b = 0;
	SDL_Surface *Message = TTF_RenderUTF8_Blended( Text::Font, text.c_str(), TextColorBasic );
	GLuint ImageID_tmp;
	glGenTextures( 1, &ImageID_tmp );
	glBindTexture( GL_TEXTURE_2D, ImageID_tmp );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels );
	glBegin( GL_QUADS );
		glTexCoord2d( 0.0, 0.0 ); glVertex2d( 0.0, 0.0 );
		glTexCoord2d( 1.0, 0.0 ); glVertex2d( Message->w, 0.0 );
		glTexCoord2d( 1.0, 1.0 ); glVertex2d( Message->w, Message->h );
		glTexCoord2d( 0.0, 1.0 ); glVertex2d( 0.0, Message->h );
	glEnd();
	glDeleteTextures(1, &ImageID_tmp);
	SDL_FreeSurface(Message);

}
