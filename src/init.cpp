#include "init.hpp"

Init::Init(){
	this->SCREEN_BPP=32;
	this->SCREEN_HEIGHT=480;
	this->SCREEN_WIDTH=640;
}

Init::~Init(){
	this->clean_up();
}

bool Init::init(){
	if( ! init_SDL() ){
		this->clean_up();
		return false;
	}
	return true;
}

bool Init::init_SDL(){
	LogGame::Write( "[LOG] " );
	LogGame::Write( 0 );
	LogGame::Write( ": SDL - Inicjalizowanie\n" );
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": SDL - Problem z inicjalizacją \"SDL_Init\" ! " );
		LogGame::Write( SDL_GetError() );
		LogGame::NewLine();
		return false;
	}
	if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL | SDL_HWSURFACE ) == NULL  ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": SDL - Problem z tworzeniem okna \"SDL_SetVideoMode\" ! " );
		LogGame::Write( SDL_GetError() );
		LogGame::NewLine();
		return false;
	}
	SDL_EnableUNICODE( SDL_TRUE );
	SDL_WM_SetCaption( "Komunikacja Człowiek-Komputer", NULL );
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": SDL - Inicjalizacja przebiegła pomyślnie\n" );
	if( ! init_GL() ){
		return false;
	}
	if( ! init_IL() ){
		return false;
	}

	return true;
}

bool Init::init_GL(){
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": OpenGL - Inicjalizowanie\n" );
	glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
	glEnable( GL_TEXTURE_2D );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 0.0, 100.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT );
	//
	glEnable( GL_BLEND );
	glDisable( GL_DEPTH_TEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	GLenum errorGL = glGetError();
	if( errorGL != GL_NO_ERROR ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": OpenGL - Problem z inicjalizacją: " );
		LogGame::Write( errorGL );
		LogGame::NewLine();
		return false;
	}
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": OpenGL - Inicjalizacja przebiegła pomyślnie\n" );
	return true;
}

bool Init::init_IL(){
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": DevIL - Inicjalizowanie\n" );
	if( ilGetInteger( IL_VERSION_NUM ) < IL_VERSION ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": DevIL - Zła wersja DevIL!\n" );
		return false;
	}
	ilInit();
	ILenum errorIL = ilGetError();
	if( errorIL != IL_NO_ERROR ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": DevIL - Problem z inicjalizacją: " );
		LogGame::Write( errorIL );
		LogGame::NewLine();
		return false;
	}
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": DevIL - Inicjalizacja przebiegła pomyślnie\n" );
	return true;
}

void Init::set_Screen(int Width, int Height, int BPP){
	this->SCREEN_WIDTH = Width;
	this->SCREEN_HEIGHT = Height;
	this->SCREEN_BPP = BPP;
}

void Init::clean_up(){
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": Czyszczenie:\n" );
	//clear memory!
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": SDL QUIT\n" );
	SDL_Quit();
}

