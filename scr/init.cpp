#include "init.hpp"

bool Init::init(){
	if( ! init_SDL() ){
		clean_up();
		return false;
	}
	return true;
}

bool Init::init_SDL(){
	std::cout<<SDL_GetTicks()<<": SDL - Inicjalizowanie\n";
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
		std::cerr<<SDL_GetTicks()<<": SDL - Problem z inicjalizacją \"SDL_Init\" ! "<<SDL_GetError()<<"\n";
		return false;
	}
	if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL | SDL_HWSURFACE ) == NULL  ){
		std::cerr<<SDL_GetTicks()<<": SDL - Problem z tworzeniem okna \"SDL_SetVideoMode\" ! "<<SDL_GetError()<<"\n";
		return false;
	}
	SDL_EnableUNICODE( SDL_TRUE );
	SDL_WM_SetCaption( "KCK", NULL );
	std::cout<<SDL_GetTicks()<<": SDL - Inicjalizacja przebiegła pomyślnie\n";
	if( ! init_GL() ){
		return false;
	}
	if( ! init_IL() ){
		return false;
	}

	return true;
}

bool Init::init_GL(){
	std::cout<<SDL_GetTicks()<<": OpenGL - Inicjalizowanie\n";
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
		std::cerr<<SDL_GetTicks()<<": OpenGL - Problem z inicjalizacją: "<<gluErrorString( errorGL )<<"\n";
		return false;
	}
	std::cout<<SDL_GetTicks()<<": OpenGL - Inicjalizacja przebiegła pomyślnie\n";
	return true;
}

bool Init::init_IL(){
	std::cout<<SDL_GetTicks()<<": DevIL - Inicjalizowanie\n";
	if( ilGetInteger( IL_VERSION_NUM ) < IL_VERSION ){
		std::cerr<<SDL_GetTicks()<<": DevIL - Zła wersja DevIL!\n";
		return false;
	}
	ilInit();
	ILenum errorIL = ilGetError();
	if( errorIL != IL_NO_ERROR ){
		std::cerr<<SDL_GetTicks()<<": DevIL - Problem z inicjalizacją: "<<errorIL<<"\n";
		return false;
	}
	std::cout<<SDL_GetTicks()<<": DevIL - Inicjalizacja przebiegła pomyślnie\n";
	return true;
}

void Init::set_Screen(int Width, int Height, int BPP){
	this->SCREEN_WIDTH = Width;
	this->SCREEN_HEIGHT = Height;
	this->SCREEN_BPP = BPP;
}

bool Init::init_Img(){

	return true;
}

void Init::clean_up(){
	std::cout<<SDL_GetTicks()<<": Czyszczenie:\n";
	//clear memory!
	std::cout<<SDL_GetTicks()<<": SDL QUIT\n";
	SDL_Quit();
}

