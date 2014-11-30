#include "game.hpp"

Game::Game(){
	this->game_start = true;
	if( ! logGame.ReturnLogGame() ){
		this->game_start = false;
		std::cout<<"Nie można utworzyć pliku \"log.txt\"\n";
	}
	else{
		this->DateToFile();
	}
//AIML
	if( ! bot.InitBot() ){
		this->game_start = false;
	}
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
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": Inicjalizowanie gry\n" );
//Grafika
	this->ReadImages();
//ANIMACJE
	this->ReadAnim();
//ERROR IMAGE
	this->error_img.resize( 1 );
	this->error_img.clear();
	this->error_img.push_back( Img( 0, "error", "bin/img/error.png" ) );
	if( ! this->error_img[0].ReturnSuccess() ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Brak pliku bin/img/error.png !\n" );
		this->game_start = false;
	}
//BACKGROUND
	this->backgroud.resize( 2 );
	this->backgroud.clear();
	this->backgroud.push_back( Img( 100, "background_bottom", "bin/img/background_bottom.png" ) );
	if( ! this->backgroud[0].ReturnSuccess() ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Brak pliku bin/img/background_bottom.png !\n" );
		this->game_start = false;
	}
	this->backgroud.push_back( Img( 101, "background_right", "bin/img/background_right.png" ) );
	if( ! this->backgroud[1].ReturnSuccess() ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Brak pliku bin/img/background_right.png !\n" );
		this->game_start = false;
	}
//TEXT LOAD TO BIT MAP

//MAPA
	this->map2D.SetVarMap( this->images, this->anim );
	this->map2D.SetValue( 50, 50 );
	if( ! this->map2D.ReturnSuccess() ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Nie utworzono mapy gry! Błąd: " );
		LogGame::Write( this->map2D.ReturnError() );
		LogGame::NewLine();
		this->game_start = false;
	}
	this->CurrentPlayerX = this->map2D.ReturnPlayerX();
	this->CurrentPlayerY = this->map2D.ReturnPlayerY();
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
	this->InputPositionX =  this->Height_percent + this->init.SCREEN_WIDTH * 0.085;
	this->InputPositionY =  this->init.SCREEN_HEIGHT * 0.1;
	this->BotMessage = "";
	this->BotMessagePositionX = this->init.SCREEN_WIDTH * 0.09;
	this->BotMessagePositionY = this->init.SCREEN_HEIGHT * 0.105;

	this->KeyEvent = SDLK_UNKNOWN;
	this->KeyEventState = KMOD_NONE;
}

Game::~Game(){
	this->settings.SaveSettings();
	Text::Clear();
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": Niszczenie obiektów\n" );
	this->init.clean_up();
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
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": Uruchamianie gry\n" );
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
					case SDLK_COMMA: // .
						//SDL_GL_SwapBuffers();

						break;
						//this->map2D.SaveToFile();
					case SDLK_ESCAPE: // ESC
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
					case SDLK_SPACE: // SPACE
						if( this->Input.size() > 0 ){
							if( this->Input[this->Input.size()-1] != ' ' ){
								this->Input += ' ';
							}
						}
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
							this->KeyEventState = SDL_GetModState();
							if( this->KeyEventState & KMOD_SHIFT ){
								this->Input.clear();
							}
							else{
								this->Input.erase( this->Input.end()-1, this->Input.end() );
							}
						}
						break;
					case SDLK_RETURN:
						this->BotMessage = this->bot.ReturnAnswer( this->Input );
						break;
					default:
						this->ReadKey();
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
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );
	LogGame::Write( ": KONIEC GRY\n" );
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
	this->CurrentPlayerX = this->map2D.ReturnPlayerX();
	this->CurrentPlayerY = this->map2D.ReturnPlayerY();
	glClear( GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	for( int i=this->CurrentPlayerY-this->Square_length; i<=this->CurrentPlayerY+this->Square_length; i++ ){
		for( int j=this->CurrentPlayerX-this->Square_length; j<=this->CurrentPlayerX+this->Square_length; j++ ){
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
					if( this->CurrentMapObj > (int)this->images.size() ){
						glBindTexture( GL_TEXTURE_2D, this->anim[this->CurrentMapObj-this->EndImages-1].ReturnImageID() );
						this->Draw_Square();
					}
				}
			}
			else{
				glBindTexture( GL_TEXTURE_2D, this->images[this->CurrentMap-1].ReturnImageID() );
				this->Draw_Square();
				if( this->CurrentMapObj != 0){
					if( this->CurrentMapObj > (int)this->images.size() ){
						glBindTexture( GL_TEXTURE_2D, this->anim[this->CurrentMapObj-this->EndImages-1].ReturnImageID() );
						this->Draw_Square();
					}
				}
			}
			//PLAYER
			if( this->CurrentPlayerY == i && this->CurrentPlayerX == j ){
				this->CurrentMapObj = this->map2D.ReturnPlayer();
				glBindTexture( GL_TEXTURE_2D, this->images[this->CurrentMapObj-1].ReturnImageID() );
				this->Draw_Square();
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
//RIGHT BACKGROUD
	glTranslatef( this->Height_percent, -this->Height_percent, 0.0 );
	glBindTexture( GL_TEXTURE_2D, this->backgroud[1].ReturnImageID() );
	glBegin( GL_QUADS );
		glTexCoord2f( 0.0, 0.0 ); glVertex2f( 0.0, 0.0 );
		glTexCoord2f( 1.0, 0.0 ); glVertex2f( this->Width_percent, 0.0 );
		glTexCoord2f( 1.0, 1.0 ); glVertex2f( this->Width_percent, this->init.SCREEN_HEIGHT );
		glTexCoord2f( 0.0, 1.0 ); glVertex2f( 0.0, this->init.SCREEN_HEIGHT );
	glEnd();

	//BOT MESSAGE
	//57 51
	glTranslatef( this->BotMessagePositionX, this->BotMessagePositionY, 0.0 );
	if( this->BotMessage != "" ){
		this->text.RenderText( this->BotMessage );
	}

	//INPUT
	glLoadIdentity();
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

void Game::ReadImages(){
	std::fstream file_img;
	int tmp_ile_img, tmp1_id, tmp_wczytano=0;
	std::string tmp_name, tmp_file_name;
	file_img.open( "bin/img.txt", std::ios::in );
	if( file_img.good() ){
		file_img>>tmp_ile_img;
		this->images.resize( tmp_ile_img );
		this->images.clear();
		for( int i=0; i<tmp_ile_img; i++ ){
			if( file_img.good() ){
				file_img>>tmp1_id;
				file_img>>tmp_name;
				file_img>>tmp_file_name;
				this->images.push_back( Img( tmp1_id, tmp_name, tmp_file_name ) );
				if( this->images[i].ReturnSuccess() ){
					tmp_wczytano++;
				}
				//std::cout<<"for:i="<<i<<" tmp1_id="<<tmp1_id<<" tmp_name="<<tmp_name<<" tmp_file_name="<<tmp_file_name<<" images.size()="<<this->images.size()<<"\n";
			}
		}

		if( tmp_wczytano == tmp_ile_img ){
			LogGame::Write( "[LOG] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": Wczytano grafikę w liczbie " );
			LogGame::Write( this->images.size() );
			LogGame::NewLine();
		}
		else{
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": Wczytano " );
			LogGame::Write( tmp_wczytano );
			LogGame::Write( " grafik z " );
			LogGame::Write( tmp_ile_img );
			LogGame::NewLine();
		}

		file_img.close();
	}
	else{
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Brak pliku bin/img.txt !\n" );
		this->game_start = false;
	}
}

void Game::ReadAnim(){
	std::fstream file_anim;
	int tmp_ile_anim, tmp1_id, tmp_wczytano=0;
	std::string tmp_global_name, tmp_name, tmp_file_name;
	file_anim.open( "bin/anim.txt", std::ios::in );
	if( file_anim.good() ){
		file_anim>>tmp_ile_anim;
		this->anim.resize(tmp_ile_anim);
		this->anim.clear();
		Uint32 tmp_time;
		int ile_img;
		std::vector <std::string> tmp_name_anim;
		std::vector <std::string> tmp_file_name_anim;
		for( int i=0 ; i<tmp_ile_anim; i++ ){
			tmp_name_anim.clear();
			tmp_file_name_anim.clear();
			file_anim>>tmp1_id;
			file_anim>>tmp_global_name;
			file_anim>>tmp_time;
			file_anim>>ile_img;
			//std::cout<<"for:i="<<i<<" tmp1_id="<<tmp1_id<<" tmp_global_name="<<tmp_global_name<<" tmp_time="<<tmp_time<<" ile_img="<<ile_img<<"\n";
			for( int j=0; j<ile_img; j++ ){
				file_anim>>tmp_name;
				file_anim>>tmp_file_name;
				tmp_name_anim.push_back( tmp_name );
				tmp_file_name_anim.push_back( tmp_file_name );
				//std::cout<<"\tfor:j="<<j<<" tmp_name="<<tmp_name<<" tmp_file_name="<<tmp_file_name<<"\n";
			}
			this->anim.push_back( Anim( tmp1_id, tmp_global_name, ile_img, tmp_time, tmp_name_anim, tmp_file_name_anim ) );
			if( this->anim[i].ReturnSuccess() ){
				tmp_wczytano++;
			}
		}

		if(tmp_wczytano==tmp_ile_anim){
			LogGame::Write( "[LOG] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": Wczytano animacje w liczbie " );
			LogGame::Write( this->anim.size() );
			LogGame::NewLine();
		}
		else{
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": Wczytano " );
			LogGame::Write( tmp_wczytano );
			LogGame::Write( " animacji z " );
			LogGame::Write( tmp_ile_anim );
			LogGame::NewLine();
		}
		file_anim.close();
	}
	else{
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Brak pliku bin/anim.txt !\n" );
		this->game_start = false;
	}
}

void Game::DateToFile(){
	time_t time_tmp = time( NULL );
	struct tm *date_tmp = localtime( &time_tmp );
	LogGame::Write( "[LOG] Utworzenie pliku log.txt: " );
	LogGame::Write( asctime( date_tmp ) );
}

void Game::ReadKey(){
	if( this->KeyEvent >= 97 && this->KeyEvent <= 122 ){
		this->KeyEventState = SDL_GetModState();
		if( ( this->KeyEventState & KMOD_SHIFT ) and ( this->KeyEventState & KMOD_ALT ) ){
			switch( this->KeyEvent ){
			case SDLK_a:
				this->Input += "Ą";
				break;
			case SDLK_s:
				this->Input += "Ś";
				break;
			case SDLK_c:
				this->Input += "Ć";
				break;
			case SDLK_e:
				this->Input += "Ę";
				break;
			case SDLK_o:
				this->Input += "Ó";
				break;
			case SDLK_l:
				this->Input += "Ł";
				break;
			case SDLK_n:
				this->Input += "Ń";
				break;
			case SDLK_z:
				this->Input += "Ż";
				break;
			case SDLK_x:
				this->Input += "Ź";
				break;
			default:
				break;
			}
		}
		else if( ( this->KeyEventState & KMOD_SHIFT ) or ( this->KeyEventState & KMOD_CAPS ) ){
			this->Input += (char)this->KeyEvent - 32;
		}
		else if( this->KeyEventState & KMOD_ALT ){
			switch( this->KeyEvent ){
			case SDLK_a:
				this->Input += "ą";
				break;
			case SDLK_s:
				this->Input += "ś";
				break;
			case SDLK_c:
				this->Input += "ć";
				break;
			case SDLK_e:
				this->Input += "ę";
				break;
			case SDLK_o:
				this->Input += "ó";
				break;
			case SDLK_l:
				this->Input += "ł";
				break;
			case SDLK_n:
				this->Input += "ń";
				break;
			case SDLK_z:
				this->Input += "ż";
				break;
			case SDLK_x:
				this->Input += "ź";
				break;
			default:
				break;
			}
		}
		else{
			this->Input += (char)this->KeyEvent;
		}
	}
}
