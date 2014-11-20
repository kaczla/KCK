#include "game.hpp"

Game::Game(){
	this->game_start = true;
	//SETTINGS
	this->settings.init_Settings();
	//INIT SDL, OPENGL, DevIL
	this->init.set_Screen( this->settings.ReturnWidth(), this->settings.ReturnHeight(), this->settings.ReturnBpp() );
	if( ! this->init.init() ){
		this->game_start = false;
	}
	//FREE TYPE
	if( ! text.InitText() ){
		this->game_start = false;
	}
	//GAME
	std::cout<<SDL_GetTicks()<<": Inicjalizowanie gry\n";
	//VAR TO LOAD
	int tmp_ile, tmp1_id, tmp_wczytano=0;
	std::string tmp_name, tmp_file_name;
	std::fstream file;
//Grafika
	file.open( "bin/img.txt", std::ios::in );
	if( file.good() ){
		file>>tmp_ile;
		this->images.resize(tmp_ile);
		this->images.clear();
		for( int i=0; i<tmp_ile; i++ ){
			if( file.good() ){
				file>>tmp1_id;
				file>>tmp_name;
				file>>tmp_file_name;
				this->images.push_back( Img( tmp1_id, tmp_name, tmp_file_name ) );
				if( this->images[i].ReturnSuccess() ){
					tmp_wczytano++;
				}
				//std::cout<<"for:i="<<i<<" tmp1_id="<<tmp1_id<<" tmp_name="<<tmp_name<<" tmp_file_name="<<tmp_file_name<<" images.size()="<<this->images.size()<<"\n";
			}
		}

		if(tmp_wczytano==tmp_ile){
			std::cout<<SDL_GetTicks()<<": Wczytano grafikę w liczbie "<<this->images.size()<<"\n";
		}
		else{
			std::cerr<<SDL_GetTicks()<<": Wczytano "<<tmp_wczytano<<" grafik z "<<tmp_ile<<"!\n";
		}

		file.close();
	}
	else{
		std::cerr<<SDL_GetTicks()<<": Brak pliku bin/img.txt !\n";
		this->game_start = false;
	}
//ANIMACJE
	file.open( "bin/anim.txt", std::ios::in );
	if( file.good() ){
		tmp_wczytano=0;
		file>>tmp_ile;
		this->anim.resize(tmp_ile);
		this->anim.clear();
		Uint32 tmp_time;
		int ile_img;
		std::vector <std::string> tmp_name_anim;
		std::vector <std::string> tmp_file_name_anim;
		for( int i=0; i<tmp_ile; i++ ){
			tmp_name_anim.clear();
			tmp_file_name_anim.clear();
			file>>tmp1_id;
			file>>tmp_time;
			file>>ile_img;
			for( int j=0; j<ile_img; j++ ){
				file>>tmp_name;
				file>>tmp_file_name;
				tmp_name_anim.push_back( tmp_name );
				tmp_file_name_anim.push_back( tmp_file_name );
			}
			this->anim.push_back( Anim( tmp1_id, ile_img, tmp_time, tmp_name_anim, tmp_file_name_anim ) );
			if( this->anim[i].ReturnSuccess() ){
				tmp_wczytano++;
			}
		}

		if(tmp_wczytano==tmp_ile){
			std::cout<<SDL_GetTicks()<<": Wczytano animacje w liczbie "<<this->anim.size()<<"\n";
		}
		else{
			std::cerr<<SDL_GetTicks()<<": Wczytano "<<tmp_wczytano<<" animacji z "<<tmp_ile<<"!\n";
		}
		file.close();
	}
	else{
		std::cerr<<SDL_GetTicks()<<": Brak pliku bin/anim.txt !\n";
		this->game_start = false;
	}
//ERROR IMAGE
	this->error_img.resize( 1 );
	this->error_img.clear();
	this->error_img.push_back( Img( 0, "error", "bin/img/error.png" ) );
	if( ! this->error_img[0].ReturnSuccess() ){
		std::cerr<<SDL_GetTicks()<<": Brak pliku bin/img/error.png !\n";
		this->game_start = false;
	}
//BACKGROUND
	this->backgroud.resize( 2 );
	this->backgroud.clear();
	this->backgroud.push_back( Img( 100, "background_bottom", "bin/img/background_bottom.png" ) );
	if( ! this->backgroud[0].ReturnSuccess() ){
		std::cerr<<SDL_GetTicks()<<": Brak pliku bin/img/background_bottom.png !\n";
		this->game_start = false;
	}
	this->backgroud.push_back( Img( 101, "background_right", "bin/img/background_right.png" ) );
	if( ! this->backgroud[1].ReturnSuccess() ){
		std::cerr<<SDL_GetTicks()<<": Brak pliku bin/img/background_right.png !\n";
		this->game_start = false;
	}
//TEXT LOAD TO BIT MAP

//MAPA
	this->map2D.SetVarMap( this->images, this->anim );
	this->map2D.SetValue( 50, 50 );
	if( ! this->map2D.ReturnSuccess() ){
		std::cerr<<SDL_GetTicks()<<": Nie utworzono mapy gry! Błąd: "<<this->map2D.ReturnError()<<" !\n";
		this->game_start = false;
	}
//Wielkosc obiektow
	this->Percent = 0.8;
	this->Height_percent = this->init.SCREEN_HEIGHT * this->Percent;
	this->Width_percent = this->init.SCREEN_WIDTH - this->Height_percent;
	this->Square_length = 4;
/*
	Ilość kwadratów:				 2, 3, 4, 5,  6
	Liczba wyświetlanych kwadratów:  5, 7, 9, 11, 13
	^ Ilość kwadratów x2 + 1 środkowy
*/
	this->Square_size = this->Height_percent / (2*this->Square_length+1);
	//std::cout<<"this->Square_length = "<<this->Square_length<<"\tthis->Square_size = "<<this->Square_size<<"\n";
	this->Background_bottom_length_x = this->Height_percent;
	this->Background_bottom_length_y = this->init.SCREEN_HEIGHT - this->Height_percent;
	///
	playerx=25;
	playery=25;
	this->StartImages = this->images[0].ReturnImageID();
	this->EndImages = this->images[this->images.size()-1].ReturnImageID();
	this->StartAnim = this->anim[0].ReturnImageID();
	this->EndAnim = this->anim[this->anim.size()-1].ReturnImageID();
	//std::cout<<"this->EndImages="<<this->EndImages<<" this->EndAnim="<<this->EndAnim<<"\n";
	this->CurrentMap = 0;
	this->CurrentMapObj = 0;
	this->fps = 0;
	this->StartTime = 0;
	this->StopEnd = 0;
	//TEXT
	this->Input = "";
	this->InputPositionX = this->init.SCREEN_WIDTH * 0.10;
	this->InputPositionY = this->init.SCREEN_HEIGHT * 0.11;
	this->BotMessage = "";
	this->BotMessagePositionX = this->init.SCREEN_WIDTH * 0.11;
	this->BotMessagePositionY = this->init.SCREEN_HEIGHT * 0.11;

	this->KeyEvent = SDLK_UNKNOWN;
}

Game::~Game(){
	this->settings.SaveSettings();
	Text::Clear();
	std::cout<<SDL_GetTicks()<<": Niszczenie obiektów\n";
}

void Game::ZoomIN(){
	if( this->Square_length > 6 ){
		this->Square_length = 4;
		this->Square_size = this->Height_percent / (2*this->Square_length+1);
	}
	else if( this->Square_length > 2 ){
		this->Square_length -= 1;
		this->Square_size = this->Height_percent / (2*this->Square_length+1);
	}
	else if( this->Square_length < 2 ){
		this->Square_length = 4;
		this->Square_size = this->Height_percent / (2*this->Square_length+1);
	}
}

void Game::ZoomOut(){
	if( this->Square_length < 6 ){
		this->Square_length += 1;
		this->Square_size = this->Height_percent / (2*this->Square_length+1);
	}
	else if( this->Square_length > 6 ){
		this->Square_length = 4;
		this->Square_size = this->Height_percent / (2*this->Square_length+1);
	}
}

void Game::Start(){
	std::cout<<SDL_GetTicks()<<": Uruchamianie gry\n";
	//std::cout<<"player x="<<playerx<<" y="<<playery<<" \n";//<<this->map2D.ReturnValueMap( playerx, playery )<<"\n";
	//this->map2D.SaveToFile();
	if( this->game_start ){
		while( this->game_start ){
			//CLOCK////////////////
			/*
			this->StartTime = SDL_GetTicks();
			if( this->StartTime >= this->StopEnd ){
				std::cout<<this->fps<<"\n";
				this->StopEnd = this->StartTime + 1000;
				fps=0;
			}
			*/
			/////////////////////
			while( SDL_PollEvent( &this->event ) ){
				if( this->event.type == SDL_QUIT ){
					this->game_start = false;
				}
				else if( this->event.type == SDL_KEYDOWN ){
					this->KeyEvent = event.key.keysym.sym;
					switch( this->KeyEvent ){
					case SDLK_COMMA:
						//SDL_GL_SwapBuffers();
							playerx = rand()%40+5;
							playery = rand()%40+5;
							//std::cout<<"x="<<playerx<<" y="<<playery<<" :"<<this->map2D.ReturnValueMap( playerx, playery )<<"\n";
						break;
						//this->map2D.SaveToFile();
					case SDLK_ESCAPE: //ESC
						this->game_start = false;
						break;
					case SDLK_LEFTBRACKET: // [
					case SDLK_KP_MINUS: // NUM -
						this->ZoomOut();
						break;
					case SDLK_RIGHTBRACKET: // ]
					case SDLK_KP_PLUS: // NUM +
						this->ZoomIN();
						break;
					case SDLK_BACKQUOTE: // `
						//ALL MAP
						if( this->map2D.ReturnWidth() > this->map2D.ReturnHeight() ){
							this->Square_length = (float)this->map2D.ReturnWidth() / 2.0;
						}
						else{
							this->Square_length = (float)this->map2D.ReturnHeight() / 2.0;
						}
						this->Square_size = this->Height_percent / (2*this->Square_length+1);
						break;
					case SDLK_BACKSPACE: //BACKSPACE
						if( this->Input.size() != 0 ){
							this->Input.erase( this->Input.end()-1, this->Input.end() );
						}
						break;
					default:
						if( this->KeyEvent >= 97 && this->KeyEvent <= 122 ){
							this->Input += (char)this->KeyEvent;
						}
						break;
					}
				}
			}
			this->Update();
			SDL_GL_SwapBuffers();
			//CLOCK////////////////
			/*
			fps++;
			*/
			/////////////////////
		}
	}
	std::cout<<SDL_GetTicks()<<": KONIEC GRY\n";
}

void Game::Draw_Square(){
	glBegin( GL_QUADS );
		glTexCoord2f( 0.0, 0.0 ); glVertex2f( 0.0, 0.0 );
		glTexCoord2f( 1.0, 0.0 ); glVertex2f( this->Square_size, 0.0 );
		glTexCoord2f( 1.0, 1.0 ); glVertex2f( this->Square_size, this->Square_size );
		glTexCoord2f( 0.0, 1.0 ); glVertex2f( 0.0, this->Square_size );
	glEnd();
}

void Game::Update(){

	glClear( GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	for( int i=playery-this->Square_length; i<=playery+this->Square_length; i++ ){
		for( int j=playerx-this->Square_length; j<=playerx+this->Square_length; j++ ){
			this->CurrentMap = this->map2D.ReturnValueMap( i, j );
			this->CurrentMapObj = this->map2D.ReturnValueMapObj( i, j );
			if( this->CurrentMap == 0 or this->CurrentMap == -1 ){
				glBindTexture( GL_TEXTURE_2D, this->error_img[0].ReturnImageID() );
				this->Draw_Square();
			}
			else if( this->CurrentMap > this->EndImages ){
				glBindTexture( GL_TEXTURE_2D, this->anim[this->CurrentMap-this->EndImages-1].ReturnImageID() );
				this->Draw_Square();
				if( this->CurrentMapObj != 0){
					glBindTexture( GL_TEXTURE_2D, this->anim[this->CurrentMapObj-this->EndImages-1].ReturnImageID() );
					this->Draw_Square();
				}
			}
			else{
				glBindTexture( GL_TEXTURE_2D, this->images[this->CurrentMap-1].ReturnImageID() );
				this->Draw_Square();
				if( this->CurrentMapObj != 0){
					glBindTexture( GL_TEXTURE_2D, this->anim[this->CurrentMapObj-this->EndImages-1].ReturnImageID() );
					this->Draw_Square();
				}
			}
			glTranslatef( this->Square_size, 0.0, 0.0 );
		}
		glTranslatef( -this->Height_percent, this->Square_size, 0.0 );	//glTranslatef( -2*(this->Square_size*this->Square_length)-this->Square_size, this->Square_size, 0.0 );
	}
	//END MAP
//BOTTOM BACKGROUND
	glBindTexture( GL_TEXTURE_2D, this->backgroud[0].ReturnImageID() );
	glBegin( GL_QUADS );
		glTexCoord2f( 0.0, 0.0 ); glVertex2f( 0.0, 0.0 );
		glTexCoord2f( 1.0, 0.0 ); glVertex2f( this->Background_bottom_length_x, 0.0 );
		glTexCoord2f( 1.0, 1.0 ); glVertex2f( this->Background_bottom_length_x, this->Background_bottom_length_y );
		glTexCoord2f( 0.0, 1.0 ); glVertex2f( 0.0, this->Background_bottom_length_y );
	glEnd();
	glTranslatef( this->Height_percent, -this->Height_percent, 0.0 );
//RIGHT BACKGROUD
	glBindTexture( GL_TEXTURE_2D, this->backgroud[1].ReturnImageID() );
	glBegin( GL_QUADS );
		glTexCoord2f( 0.0, 0.0 ); glVertex2f( 0.0, 0.0 );
		glTexCoord2f( 1.0, 0.0 ); glVertex2f( this->Width_percent, 0.0 );
		glTexCoord2f( 1.0, 1.0 ); glVertex2f( this->Width_percent, this->init.SCREEN_HEIGHT );
		glTexCoord2f( 0.0, 1.0 ); glVertex2f( 0.0, this->init.SCREEN_HEIGHT );
	glEnd();
	//this->text.RenderText( "Ala ma kota, ą ę ć ł ó ź ż ń" );
	glTranslatef( this->InputPositionX, 7*this->InputPositionY, 0.0 );

	if( this->Input != "" ){
		Text::RenderTextNow( this->Input );
	}
	//glTranslatef( 0.0, this->InputPositionY, 0.0 );
}

void Game::Load(){

}

void Game::Save(){

}



