#include "text.hpp"

bool Text::IsInit = false;
TTF_Font *Text::Font = NULL;
SDL_Color Text::TextColorBlack = { 0, 0, 0 };
SDL_Color Text::TextColorWhite = { 255, 255, 255 };
SDL_Color Text::TextColorRed = { 255, 0, 0 };
SDL_Color Text::TextColorGreen = { 0, 255, 0 };
SDL_Color Text::TextColorBlue = { 0, 0, 255 };
int Text::FontSize = 14;
unsigned int Text::MaxLength = 17;

Text::Text(){
	this->SetColor( 255, 255, 255 );
	this->ImageID = 0;
}

Text::~Text(){
	glDeleteTextures(1, &this->ImageID);
}

bool Text::InitText(){
	if( ! Text::IsInit ){
		LogGame::Write( "[LOG] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Freetype - Inicjalizowanie\n" );
		if( TTF_Init() == -1 ){
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": FreeType - Błąd: Niepowodzenie TTF_Init !\n" );
			return false;
		}
		if( Text::FontSize < 14 or Text::FontSize > 18 ){
			Text::FontSize = 14;
		}
		Text::Font = TTF_OpenFont( "bin/font.ttf", Text::FontSize );
		if( Text::Font == NULL ){
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": FreeType - Błąd: Niepowodzenie TTF_OpenFont !\n" );
			return false;
		}
		TTF_SetFontStyle( Text::Font, TTF_STYLE_BOLD );
		Text::IsInit = true;
		LogGame::Write( "[LOG] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Freetype - Inicjalizacja przebiegła pomyślnie\n" );
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

	SDL_Surface *Message = TTF_RenderUTF8_Blended( Text::Font, text.c_str(), Text::TextColorBlack );
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
		SDL_Surface *Message = TTF_RenderUTF8_Blended( Text::Font, text.c_str(), Text::TextColorBlack );
		GLuint ImageID_tmp;
		glGenTextures( 1, &ImageID_tmp );
		glBindTexture( GL_TEXTURE_2D, ImageID_tmp );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels );
		glRotatef( -5.0, 0.0, 0.0, 1.0 );
		glBegin( GL_QUADS );
			glTexCoord2d( 0.0, 0.0 ); glVertex2d( 0.0, 0.0 );
			glTexCoord2d( 1.0, 0.0 ); glVertex2d( Message->w, 0.0 );
			glTexCoord2d( 1.0, 1.0 ); glVertex2d( Message->w, Message->h );
			glTexCoord2d( 0.0, 1.0 ); glVertex2d( 0.0, Message->h );
		glEnd();
		glDeleteTextures(1, &ImageID_tmp);
		SDL_FreeSurface(Message);
}

void Text::SetMaxLength( float max ){
	if( max<17.0 or max>100 ){
		max = 17.0;
	}
	Text::MaxLength = (unsigned int)max;
}
