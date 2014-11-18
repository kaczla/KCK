#include "map.hpp"

Map::Map(){
	this->Width = 50;
	this->Height = 50;
	this->Success = false;
	this->SuccessVarMap = false;
	//this->SetVector();

	this->PlayerX = 1;
	this->PlayerY = 25;
	this->Error_Map = "nie zainicjalizawano mapy ( void SetValue(int height, int width); )";
}

Map::Map(int height, int width){
	this->Width = width;
	this->Height = height;
	this->Success = false;
	this->SuccessVarMap = false;
	this->SetVector();

	//INNA LOSOWA!!!
	this->PlayerX = 1;
	this->PlayerY = 25;
}

bool Map::ReturnSuccess(){
	return this->Success;
}

void Map::SetValue(int height, int width){
	this->Width = width;
	this->Height = height;
	if( this->Pelne.size() == 0 or this->TrawaPiach.size() == 0 or this->WodaPiach.size() == 0 or this->WodaTrawa.size() == 0 ){
		this->Success = false;
		this->Error_Map = "nie zainicjalizowano zmiennych mapy odpowiedzialnych za wyświetlanie grafiki ( void SetVarMap( std::vector <Img> img, std::vector <Anim> anim); )";
	}
	else if( ! this->SuccessVarMap ){
		this->Success = false;
		this->Error_Map = "nie zainicjalizowano zmiennych mapy odpowiedzialnych za wyświetlanie grafiki ( void SetVarMap( std::vector <Img> img, std::vector <Anim> anim); )";
	}
	else{
		this->SetVector();
		//PODŁOŻE
		for( int i=0; i<this->Height; i++ ){
			this->Map2D[0][i] = 1;
			this->Map2D[i][0] = 1;

			this->Map2D[this->Height-1][i] = 1;
			this->Map2D[i][this->Width-1] = 1;
		}
		for( int i=1; i<this->Height-1; i++ ){
			for( int j=1; j<this->Width-1; j++ ){
				this->Map2D[i][j]=2;//rand()%14+1;
			}
		}

		//OBIEKTY


		this->Error_Map = " ";
		this->Success = true;
	}
}

int Map::ReturnValueMap(int x, int y){
	//std::cout<<"map x="<<x<<" y="<<y<<" :"<<this->Map2D[x][y]
    //         <<" Width="<<this->Width<<" Height="<<this->Height<<"\n";
	if( x<0 or x>=this->Width ){
		return this->Pelne[0].ReturnImageID();
	}
	else if( y<0 or y>=this->Height ){
		return this->Pelne[0].ReturnImageID();
	}
	else{
		return this->Map2D[x][y];
	}
}

int Map::ReturnValueMapObj(int x, int y){
	if( x<0 or x>=this->Width ){
		return 0;
	}
	else if( y<0 or y>=this->Height ){
		return 0;
	}
	else{
		return this->Map2D_obj[x][y];
	}
}

std::string Map::ReturnError(){
	return this->Error_Map;
}

int Map::ReturnWidth(){
	return this->Width;
}

int Map::ReturnHeight(){
	return this->Height;
}

void Map::SaveToFile(){
	std::cout<<"MAP:\n";
	for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			std::cout<<this->Map2D[i][j]<<" ";
		}
		std::cout<<"\n";
	}
	std::cout<<"OBJ:\n";
	for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			std::cout<<this->Map2D_obj[i][j]<<" ";
		}
		std::cout<<"\n";
	}

	std::cout<<"Pelne.size() = "<<Pelne.size()<<" ";
	for( unsigned int j=0; j<this->Pelne.size(); j++ ){
		std::cout<<j<<";LocalName="<<this->Pelne[j].ReturnLocalName()<<";ImageID="<<this->Pelne[j].ReturnImageID()<<" ";
	}
	std::cout<<"\n";

	for( unsigned int j=0; j<this->TrawaPiach.size(); j++ ){
		std::cout<<j<<";LocalName="<<this->TrawaPiach[j].ReturnLocalName()<<";ImageID="<<this->TrawaPiach[j].ReturnImageID()<<" ";
	}
	std::cout<<"\n";
	for( unsigned int j=0; j<this->WodaPiach.size(); j++ ){
		std::cout<<j<<";LocalName="<<this->WodaPiach[j].ReturnLocalName()<<";ImageID="<<this->WodaPiach[j].ReturnImageID()<<" ";
	}
	std::cout<<"\n";
	for( unsigned int j=0; j<this->WodaTrawa.size(); j++ ){
		std::cout<<j<<";LocalName="<<this->WodaTrawa[j].ReturnLocalName()<<";ImageID="<<this->WodaTrawa[j].ReturnImageID()<<" ";
	}
	std::cout<<"\n";

}

void Map::SetVector(){
	this->Map2D.resize(this->Height);	//this->map.clear();
	for( int i=0; i<this->Height; i++){
		this->Map2D[i].resize(this->Width);		//this->map[i].clear();
	}
	this->Map2D_obj.resize(this->Height);
	for( int i=0; i<this->Height; i++){
		this->Map2D_obj[i].resize(this->Width);
	}

	for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			this->Map2D[i][j] = 0;
		}
	}
	for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			this->Map2D_obj[i][j] = 0;
		}
	}
}

Map::~Map(){

}

void Map::SetVarMap( std::vector <Img> img, std::vector <Anim> anim){
	this->Pelne.resize( 3 );
	this->Pelne[0].SetLocalName( "fullwoda" );
	this->Pelne[1].SetLocalName( "fulltrawa" );
	this->Pelne[2].SetLocalName( "fullpiach" );

	this->TrawaPiach.resize( 12 );
	this->TrawaPiach[0].SetLocalName( "GD_piachtrawa" );
	this->TrawaPiach[1].SetLocalName( "GD_trawapiach" );
	this->TrawaPiach[2].SetLocalName( "LD1_GP3_piachtrawa" );
	this->TrawaPiach[3].SetLocalName( "LD1_GP3_trawapiach" );
	this->TrawaPiach[4].SetLocalName( "LD3_GP1_piachtrawa" );
	this->TrawaPiach[5].SetLocalName( "LD3_GP1_trawapiach" );
	this->TrawaPiach[6].SetLocalName( "LG1_PD3_piachtrawa" );
	this->TrawaPiach[7].SetLocalName( "LG1_PD3_trawapiach" );
	this->TrawaPiach[8].SetLocalName( "LG3_PD1_piachtrawa" );
	this->TrawaPiach[9].SetLocalName( "LG3_PD1_trawapiach" );
	this->TrawaPiach[10].SetLocalName( "LP_piachtrawa" );
	this->TrawaPiach[11].SetLocalName( "LP_trawapiach" );

	this->WodaPiach.resize( 12 );
	this->WodaPiach[0].SetLocalName( "GD_piachwoda" );
	this->WodaPiach[1].SetLocalName( "GD_wodapiach" );
	this->WodaPiach[2].SetLocalName( "LD1_GP3_piachwoda" );
	this->WodaPiach[3].SetLocalName( "LD1_GP3_wodapiach" );
	this->WodaPiach[4].SetLocalName( "LD3_PG1_piachwoda" );
	this->WodaPiach[5].SetLocalName( "LD3_PG1_wodapiach" );
	this->WodaPiach[6].SetLocalName( "LG1_PD3_piachwoda" );
	this->WodaPiach[7].SetLocalName( "LG1_PD3_wodapiach" );
	this->WodaPiach[8].SetLocalName( "LG3_PD1_piachwoda" );
	this->WodaPiach[9].SetLocalName( "LG3_PD1_wodapiach" );
	this->WodaPiach[10].SetLocalName( "LP_piachwoda" );
	this->WodaPiach[11].SetLocalName( "LP_wodapiach" );

	this->WodaTrawa.resize( 12 );
	this->WodaTrawa[0].SetLocalName( "GD_trawawoda" );
	this->WodaTrawa[1].SetLocalName( "GD_wodatrawa" );
	this->WodaTrawa[2].SetLocalName( "LD1_PG3_trawawoda" );
	this->WodaTrawa[3].SetLocalName( "LD1_PG3_wodatrawa" );
	this->WodaTrawa[4].SetLocalName( "LD3_PG1_trawawoda" );
	this->WodaTrawa[5].SetLocalName( "LD3_PG1_wodatrawa" );
	this->WodaTrawa[6].SetLocalName( "LG1_PD3_wodatrawa" );
	this->WodaTrawa[7].SetLocalName( "LG1_PD3_trawawoda" );
	this->WodaTrawa[8].SetLocalName( "LG3_PD1_trawawoda" );
	this->WodaTrawa[9].SetLocalName( "LG3_PD1_wodatrawa" );
	this->WodaTrawa[10].SetLocalName( "LP_trawawoda" );
	this->WodaTrawa[11].SetLocalName( "LP_wodatrawa" );

	bool equal_size = false;
	if( this->TrawaPiach.size() == this->WodaPiach.size() and this->TrawaPiach.size() == this->WodaTrawa.size() ){
		equal_size = true;
	}
	else{
		equal_size = false;
	}

	bool not_found = true;
	for( unsigned int i=0; i<img.size(); i++ ){
		for( unsigned int j=0; j<this->Pelne.size(); j++ ){
			if( not_found && this->Pelne[j].ReturnLocalName() == img[i].ReturnName() ){
				this->Pelne[j].SetImageID( img[i].ReturnImageID() );
				not_found = false;
				break;
			}
		}
		if( equal_size ){
			for( unsigned int j=0; j<this->TrawaPiach.size(); j++ ){
				if( not_found && this->TrawaPiach[j].ReturnLocalName() == img[i].ReturnName() ){
					this->TrawaPiach[j].SetImageID( img[i].ReturnImageID() );
					not_found = false;
					break;
				}
				else if( not_found && this->WodaPiach[j].ReturnLocalName() == img[i].ReturnName() ){
					this->WodaPiach[j].SetImageID( img[i].ReturnImageID() );
					not_found = false;
					break;
				}
				else if( not_found && this->WodaTrawa[j].ReturnLocalName() == img[i].ReturnName() ){
					this->WodaTrawa[j].SetImageID( img[i].ReturnImageID() );
					not_found = false;
					break;
				}
			}
		}
		else{
			for( unsigned int j=0; j<this->TrawaPiach.size(); j++ ){
				if( not_found && this->TrawaPiach[j].ReturnLocalName() == img[i].ReturnName() ){
					this->TrawaPiach[j].SetImageID( img[i].ReturnImageID() );
					not_found = false;
					break;
				}
			}
			for( unsigned int j=0; j<this->WodaPiach.size(); j++ ){
				if( not_found && this->WodaPiach[j].ReturnLocalName() == img[i].ReturnName() ){
					this->WodaPiach[j].SetImageID( img[i].ReturnImageID() );
					not_found = false;
					break;
				}
			}
			for( unsigned int j=0; j<this->WodaTrawa.size(); j++ ){
				if( not_found && this->WodaTrawa[j].ReturnLocalName() == img[i].ReturnName() ){
					this->WodaTrawa[j].SetImageID( img[i].ReturnImageID() );
					not_found = false;
					break;
				}
			}
		}
		not_found = true;
	}

	//SPRAWDZENIE
	int ile = 0;
	std::string error_tmp = "";
	for( unsigned int j=0; j<this->Pelne.size(); j++ ){
		if(  this->Pelne[j].ReturnImageID() == 0 ){
			ile++;
			error_tmp+= this->Pelne[j].ReturnLocalName() + "; ";
		}
	}
	if( equal_size ){
		for( unsigned int j=0; j<this->TrawaPiach.size(); j++ ){
			if( this->TrawaPiach[j].ReturnImageID() == 0 ){
				ile++;
				error_tmp+= this->TrawaPiach[j].ReturnLocalName() + "; ";
			}
			if( this->WodaPiach[j].ReturnImageID() == 0 ){
				ile++;
				error_tmp+= this->WodaPiach[j].ReturnLocalName() + "; ";
			}
			if( this->WodaTrawa[j].ReturnImageID() == 0 ){
				ile++;
				error_tmp+= this->WodaTrawa[j].ReturnLocalName() + "; ";
			}
		}
	}
	else{
		for( unsigned int j=0; j<this->TrawaPiach.size(); j++ ){
			if( this->TrawaPiach[j].ReturnImageID() == 0 ){
				ile++;
				error_tmp+= this->TrawaPiach[j].ReturnLocalName() + "; ";
			}
		}
		for( unsigned int j=0; j<this->WodaPiach.size(); j++ ){
			if( this->WodaPiach[j].ReturnImageID() == 0 ){
				ile++;
				error_tmp+= this->WodaPiach[j].ReturnLocalName() + "; ";
			}
		}
		for( unsigned int j=0; j<this->WodaTrawa.size(); j++ ){
			if( this->WodaTrawa[j].ReturnImageID() == 0 ){
				ile++;
				error_tmp+= this->WodaTrawa[j].ReturnLocalName() + "; ";
			}
		}
	}

	if( ile != 0 ){
		std::cerr<<SDL_GetTicks()<<": Liczba zmiennych mapy odpowiedzialnych za wyświetlanie grafiki, które nie zostały zinicjalizowane to: "<<ile<<"\n";
		std::cerr<<SDL_GetTicks()<<": Nazwy zmiennych: "<<error_tmp<<"\n";
	}
	this->SuccessVarMap = true;

}






