#include "game.hpp"

Game::Game(){
	this->settings.init_Settings();
	this->init.set_Screen( this->settings.ReturnWidth(), this->settings.ReturnHeight(), this->settings.ReturnBpp() );
	if( ! this->init.init() ){
		this->game_start = false;
	}
	std::cout<<SDL_GetTicks()<<": Inicjalizowanie gry\n";

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
	this->error_img.push_back( Img( 99, "error", "bin/img/error.png" ) );
	if( ! this->error_img[0].ReturnSuccess() ){
		std::cerr<<SDL_GetTicks()<<": Brak pliku bin/img/error.png !\n";
		this->game_start = false;
	}
//MAPA
	this->map2D.SetValue( 50, 50 );
	if( ! this->map2D.ReturnSuccess() ){
		std::cerr<<SDL_GetTicks()<<": Nie utworzono mapy gry!\n";
		this->game_start = false;
	}
//
	this->Square_length = 2;
	this->Square_size = (this->init.SCREEN_HEIGHT*0.8) / (2*this->Square_length+1);
	std::cout<<"this->Square_length = "<<this->Square_length<<"\tthis->Square_size = "<<this->Square_size<<"\n";
	///
	playerx=25;
	playery=25;
	Zmiana_img_na_anim = 0;
	tmp_update = 0;
	tmp_update2 = 0;
	this->fps = 0;
	this->StartTime = 0;
	this->StopEnd = 0;
	this->game_start = true;
}

Game::~Game(){
	this->settings.SaveSettings();
	std::cout<<SDL_GetTicks()<<": Niszczenie obiektów\n";
}

void Game::Start(){
	std::cout<<SDL_GetTicks()<<": Uruchamianie gry\n";
	//this->map2D.SaveToFile();
	//std::cout<<"player x="<<playerx<<" y="<<playery<<" \n";//<<this->map2D.ReturnValueMap( playerx, playery )<<"\n";
	Zmiana_img_na_anim=anim[0].ReturnImageID();
	//std::cout<<"od ilu animacje: "<<Zmiana_img_na_anim<<"\n";
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
			while( SDL_PollEvent( &this->event )  ){
				if( this->event.type == SDL_QUIT ){
					this->game_start = false;
				}
				else if( this->event.type == SDL_KEYDOWN ){
					switch(event.key.keysym.sym){
					case SDLK_q:
						//SDL_GL_SwapBuffers();
							playerx=rand()%40+5;
							playery=rand()%40+5;
							//std::cout<<"x="<<playerx<<" y="<<playery<<" :"<<this->map2D.ReturnValueMap( playerx, playery )<<"\n";
						break;
					case SDLK_w:
						//this->map2D.SaveToFile();
						break;
					case SDLK_ESCAPE:
						this->game_start = false;
						break;
					case SDLK_KP_MINUS:
						this->Square_length+=2;
						this->Square_size = (this->init.SCREEN_HEIGHT*0.8) / (2*this->Square_length+1);
						break;
					case SDLK_KP_PLUS:
						this->Square_length-=2;
						this->Square_size = (this->init.SCREEN_HEIGHT*0.8) / (2*this->Square_length+1);
						break;
					default:
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
			this->tmp_update = this->map2D.ReturnValueMap( i, j );
			//this->tmp_update2 = this->map2D.ReturnValueMapObj( i, j );
			if( this->tmp_update == -1 or this->tmp_update == 0 ){
				glBindTexture( GL_TEXTURE_2D, this->error_img[0].ReturnImageID() );
				this->Draw_Square();
			}
			else if( this->tmp_update >= Zmiana_img_na_anim ){
				//std::cout<<" tmp_update >= Zmiana_img_na_anim\n";
				glBindTexture( GL_TEXTURE_2D, this->anim[this->tmp_update-Zmiana_img_na_anim].ReturnImageID() );
				this->Draw_Square();
				if( this->tmp_update2 != 0){
					glBindTexture( GL_TEXTURE_2D, this->anim[this->tmp_update2-Zmiana_img_na_anim].ReturnImageID() );
					this->Draw_Square();
				}
			}
			else{
				//std::cout<<"tmp_update="<<this->tmp_update<<" Zmiana_img_na_anim="<<Zmiana_img_na_anim<<" images[this->tmp_update-1].ReturnImageID()="<<images[this->tmp_update-1].ReturnImageID()<<"\n";
				glBindTexture( GL_TEXTURE_2D, this->images[this->tmp_update-1].ReturnImageID() );
				this->Draw_Square();
				if( this->tmp_update2 != 0){
					glBindTexture( GL_TEXTURE_2D, this->anim[this->tmp_update2-Zmiana_img_na_anim].ReturnImageID() );
					this->Draw_Square();
				}
			}
			glTranslatef( this->Square_size, 0.0, 0.0 );
		}
		glTranslatef( -2*(this->Square_size*this->Square_length)-this->Square_size, this->Square_size, 0.0 );
	}
	//END
}

void Game::Load(){

}

void Game::Save(){

}

