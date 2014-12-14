#include "map.hpp"

Map::Map(){
	this->Width = 50;
	this->Height = 50;
	this->Success = false;
	this->SuccessVarMap = false;
	this->Animation = true;

	this->PlayerX = 1;
	this->PlayerY = 25;
	this->Error_Map = "nie zainicjalizawano mapy ( void SetValue(int height, int width); )";
}

Map::Map(int height, int width){
	this->Width = width;
	this->Height = height;
	this->Success = false;
	this->SuccessVarMap = false;
	this->Animation = true;
	this->SetVector();

	//INNA LOSOWA!!!
	this->PlayerX = 1;
	this->PlayerY = width / 2;
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
		//WODA
		for( int i=0; i<this->Height; i++ ){
			this->Map2D[0][i] = this->Pelne[0].ReturnImageID();
			this->Map2D[i][0] = this->Pelne[0].ReturnImageID();

			this->Map2D[this->Height-1][i] = this->Pelne[0].ReturnImageID();
			this->Map2D[i][this->Width-1] = this->Pelne[0].ReturnImageID();
		}
		//PLAZA
		for( int i=2; i<this->Height-2; i++ ){
			this->Map2D[1][i] = this->WodaPiach[1].ReturnImageID();
			this->Map2D[2][i] = this->Pelne[2].ReturnImageID();
			this->Map2D[i][1] = this->WodaPiach[11].ReturnImageID();
			this->Map2D[i][2] = this->Pelne[2].ReturnImageID();

			this->Map2D[this->Height-3][i] = this->Pelne[2].ReturnImageID();
			this->Map2D[this->Height-2][i] = this->WodaPiach[0].ReturnImageID();
			this->Map2D[i][this->Width-3] = this->Pelne[2].ReturnImageID();
			this->Map2D[i][this->Width-2] = this->WodaPiach[10].ReturnImageID();
		}
		//NAROZNIKI
		this->Map2D[1][1] = this->WodaPiach[9].ReturnImageID();
		this->Map2D[this->Height-2][1] = this->WodaPiach[5].ReturnImageID();
		this->Map2D[1][this->Width-2] = this->WodaPiach[2].ReturnImageID();
		this->Map2D[this->Height-2][this->Width-2] = this->WodaPiach[6].ReturnImageID();

		for( int i=4; i<this->Height-4; i++ ){
			this->Map2D[3][i] = this->TrawaPiach[0].ReturnImageID();
			this->Map2D[i][3] = this->TrawaPiach[10].ReturnImageID();

			this->Map2D[this->Width-4][i] = this->TrawaPiach[1].ReturnImageID();
			this->Map2D[i][this->Width-4] = this->TrawaPiach[11].ReturnImageID();
		}
		this->Map2D[3][3] = this->TrawaPiach[8].ReturnImageID();
		this->Map2D[this->Height-4][3] = this->TrawaPiach[4].ReturnImageID();
		this->Map2D[3][this->Width-4] = this->TrawaPiach[3].ReturnImageID();
		this->Map2D[this->Height-4][this->Width-4] = this->TrawaPiach[7].ReturnImageID();

		//TRAWA
		for( int i=4; i<this->Height-4; i++ ){
			for( int j=4; j<this->Width-4; j++ ){
				this->Map2D[i][j] = this->Pelne[1].ReturnImageID();
			}
		}

		//BIOMY
		srand( time( NULL ));
		int randombiomcount;
		bool range = true;
		randombiomcount=(std::rand() % 8) +26; //od 26 do 34
		for(int i=0;i<randombiomcount; i++){
			//range = false;
			int bioms[50][50];
			int x = (std::rand() % (this->Width-11)) + 5; // <5;44>
			int y = (std::rand() % (this->Height-11)) + 5;

			//zerowanie tablicy
			for(int p=0;p<50;p++)
			{
				for(int l=0;l<50;l++)
				{
					bioms[p][l]=0;
				}
			}
			//sprawdzenie odleglosci wylosowanych juz biomow
////////////////////////////////// NIESKONCZONE
			/*for(int q=0;q<50;q++)
			{
				for(int w=0;w<50;w++)
				{
					if( sqrt( (x-q) * (x-q) + (y-w) * (y-w)  ) < 8 && bioms[q][w]==1)
						{
							i--;
						}
							else
						{
							bioms[x][y]=1;
							range=true;
						}
				}
				if(range==true)
				{
					break;
				}

			}*/
////////////////////////////////
			if(range==true)
			{
				int randombiom = (std::rand() % 3) + 0;
				int randomshape;
				this->Map2D[x][y] = this->Pelne[randombiom].ReturnImageID(); //punkt bezwzgledny (czerwona kropka)
					//trzeba tutaj wstawic cos co na chwile zatrzyma program
				for(int lol=0;lol<10000;lol++)
				{
					;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
				}
					randomshape = (std::rand() % 12) + 0;
					//randomshape = 11; //do testowania
					/*
					 * 0 niepelny prostokat
					 * 1 kwadrat
					 * 2 pieseł
					 * 3 .|.
					 * 4 maly kwadrat
					 * 5 to co w 0 ale odwrocony
					 * 6 gwiazda
					 * 7 krzyz lotniczy
					 * 8 pacman w prawo
					 * 9 pacman w lewo
					 * 10 pacman w gore
					 * 11 pacman w dol
					 */
					switch (randomshape)
					{
					default: break;
					case 0:
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y+1] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 1:
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y+1] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 2:
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 3:
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 4:
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 5:
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y-1] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 6:
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+2] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 7:
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 8:
						this->Map2D[x-2][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y+2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y+2] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 9:
						this->Map2D[x-2][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 10:
						this->Map2D[x-2][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-2][y+2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y+2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						break;
					case 11:
						this->Map2D[x-1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x-1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y-2] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+2][y+2] = this->Pelne[randombiom].ReturnImageID();
						break;
				}
			}
		}



		//OBIEKTY
		this->Map2D_obj[this->PlayerY][this->PlayerX+3] = this->Drzewo[0].ReturnImageID();
		this->Map2D_obj[this->PlayerY+1][this->PlayerX+3] = this->Drzewo[1].ReturnImageID();
		this->Map2D_obj[this->PlayerY+2][this->PlayerX+3] = this->Drzewo[2].ReturnImageID();

		this->Error_Map = " ";
		this->Success = true;
	}
}

int Map::ReturnValueMap(int x, int y){
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
	LogGame::Write( "[LOG] MAP:\n" );
	for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			LogGame::Write( this->Map2D[i][j] );
			LogGame::Write( " " );
		}
		LogGame::NewLine();
	}
	LogGame::Write( "[LOG] OBJ:\n" );
	for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			LogGame::Write( this->Map2D_obj[i][j] );
			LogGame::Write( " " );
		}
		LogGame::NewLine();
	}

	LogGame::Write( "[LOG] Pelne.size() = " );
	LogGame::Write( Pelne.size() );
	LogGame::Write( " " );
	for( unsigned int j=0; j<this->Pelne.size(); j++ ){
		LogGame::Write( j );
		LogGame::Write( ";LocalName=" );
		LogGame::Write( this->Pelne[j].ReturnLocalName() );
		LogGame::Write( ";ImageID=" );
		LogGame::Write( this->Pelne[j].ReturnImageID() );
	}
	LogGame::NewLine();

	LogGame::Write( "[LOG] TrawaPiach.size() = " );
	LogGame::Write( TrawaPiach.size() );
	LogGame::Write( " " );
	for( unsigned int j=0; j<this->TrawaPiach.size(); j++ ){
		LogGame::Write( j );
		LogGame::Write( ";LocalName=" );
		LogGame::Write( this->TrawaPiach[j].ReturnLocalName() );
		LogGame::Write( ";ImageID=" );
		LogGame::Write( this->TrawaPiach[j].ReturnImageID() );
	}
	LogGame::NewLine();

	LogGame::Write( "[LOG] WodaPiach.size() = " );
	LogGame::Write( WodaPiach.size() );
	LogGame::Write( " " );
	for( unsigned int j=0; j<this->WodaPiach.size(); j++ ){
		LogGame::Write( j );
		LogGame::Write( ";LocalName=" );
		LogGame::Write( this->WodaPiach[j].ReturnLocalName() );
		LogGame::Write( ";ImageID=" );
		LogGame::Write( this->WodaPiach[j].ReturnImageID() );
	}
	LogGame::NewLine();

	LogGame::Write( "[LOG] WodaTrawa.size() = " );
	LogGame::Write( WodaTrawa.size() );
	LogGame::Write( " " );
	for( unsigned int j=0; j<this->WodaTrawa.size(); j++ ){
		LogGame::Write( j );
		LogGame::Write( ";LocalName=" );
		LogGame::Write( this->WodaTrawa[j].ReturnLocalName() );
		LogGame::Write( ";ImageID=" );
		LogGame::Write( this->WodaTrawa[j].ReturnImageID() );
	}
	LogGame::NewLine();

	LogGame::Write( "[LOG] Player.size() = " );
	LogGame::Write( Player.size() );
	LogGame::Write( " " );
	for( unsigned int j=0; j<this->Player.size(); j++ ){
		LogGame::Write( j );
		LogGame::Write( ";LocalName=" );
		LogGame::Write( this->Player[j].ReturnLocalName() );
		LogGame::Write( ";ImageID=" );
		LogGame::Write( this->Player[j].ReturnImageID() );
	}
	LogGame::NewLine();
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
			this->Map2D[i][j] = -1;
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
	if( anim.size() == 0 ){
		this->Animation = false;
	}

	this->Player.resize( 4 );
	this->Player[0].SetLocalName( "PlayerUp" );
	this->Player[1].SetLocalName( "PlayerLeft" );
	this->Player[2].SetLocalName( "PlayerRight" );
	this->Player[3].SetLocalName( "PlayerDown" );

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

	this->Drzewo.resize( 3 );
	this->Drzewo[0].SetLocalName( "tree1" );
	this->Drzewo[1].SetLocalName( "tree2" );
	this->Drzewo[2].SetLocalName( "tree3" );

	this->Ognisko.resize( 3 );
	this->Ognisko[0].SetLocalName( "ognichoready" );
	this->Ognisko[1].SetLocalName( "ognichofire" );
	this->Ognisko[2].SetLocalName( "ognichospalone" );

	this->Kamien.resize( 3 );
	this->Kamien[0].SetLocalName( "stone1" );
	this->Kamien[1].SetLocalName( "stone2" );
	this->Kamien[2].SetLocalName( "stone3" );

	bool equal_size = false;
	if( this->TrawaPiach.size() == this->WodaPiach.size() and this->TrawaPiach.size() == this->WodaTrawa.size() ){
		equal_size = true;
	}
	else{
		equal_size = false;
	}

	unsigned int i,j;
	//Grafika
	bool not_found = true;
	for( i=0; i<img.size(); i++ ){
		for( j=0; j<this->Player.size(); j++ ){
			if( not_found && this->Player[j].ReturnLocalName() == img[i].ReturnName() ){
				this->Player[j].SetImageID( i );
				not_found = false;
				break;
			}
		}
		for( j=0; j<this->Pelne.size(); j++ ){
			if( not_found && this->Pelne[j].ReturnLocalName() == img[i].ReturnName() ){
				this->Pelne[j].SetImageID( i );
				not_found = false;
				break;
			}
		}
		if( equal_size ){
			for( j=0; j<this->TrawaPiach.size(); j++ ){
				if( not_found && this->TrawaPiach[j].ReturnLocalName() == img[i].ReturnName() ){
					this->TrawaPiach[j].SetImageID( i );
					not_found = false;
					break;
				}
				else if( not_found && this->WodaPiach[j].ReturnLocalName() == img[i].ReturnName() ){
					this->WodaPiach[j].SetImageID( i );
					not_found = false;
					break;
				}
				else if( not_found && this->WodaTrawa[j].ReturnLocalName() == img[i].ReturnName() ){
					this->WodaTrawa[j].SetImageID( i );
					not_found = false;
					break;
				}
			}
		}
		else{
			for( j=0; j<this->TrawaPiach.size(); j++ ){
				if( not_found && this->TrawaPiach[j].ReturnLocalName() == img[i].ReturnName() ){
					this->TrawaPiach[j].SetImageID( i );
					not_found = false;
					break;
				}
			}
			for( j=0; j<this->WodaPiach.size(); j++ ){
				if( not_found && this->WodaPiach[j].ReturnLocalName() == img[i].ReturnName() ){
					this->WodaPiach[j].SetImageID( i );
					not_found = false;
					break;
				}
			}
			for( j=0; j<this->WodaTrawa.size(); j++ ){
				if( not_found && this->WodaTrawa[j].ReturnLocalName() == img[i].ReturnName() ){
					this->WodaTrawa[j].SetImageID( i );
					not_found = false;
					break;
				}
			}
		}
		if( not_found && this->Ognisko[0].ReturnLocalName() == img[i].ReturnName() ){
			this->Ognisko[0].SetImageID( i );
			not_found = false;
		}
		for( j=0; j<this->Kamien.size(); j++ ){
			if( not_found && this->Kamien[j].ReturnLocalName() == img[i].ReturnName() ){
				this->Kamien[j].SetImageID( i );
				not_found = false;
				break;
			}
		}
		if( not_found && ( ! this->Animation ) ){
			for( j=1; j<this->Ognisko.size(); j++ ){
				if( not_found && this->Ognisko[j].ReturnLocalName() == img[i].ReturnName() ){
					this->Ognisko[j].SetImageID( i );
					not_found = false;
					break;
				}
			}
			for( j=0; j<this->Drzewo.size(); j++ ){
				if( not_found && this->Drzewo[j].ReturnLocalName() == img[i].ReturnName() ){
					this->Drzewo[j].SetImageID( i );
					not_found = false;
					break;
				}
			}
		}
		not_found = true;
	}
	//Animacje
	if( this->Animation ){
		not_found = true;
		for( i=0; i<anim.size(); i++ ){
			if( not_found ){
				for( j=0; j<this->Ognisko.size(); j++ ){
					if( not_found && this->Ognisko[j].ReturnLocalName() == anim[i].ReturnName() ){
						this->Ognisko[j].SetImageID( img.size()+i );
						not_found = false;
						break;
					}
				}
			}
			if( not_found ){
				for( j=0; j<this->Drzewo.size(); j++ ){
					if( not_found && this->Drzewo[j].ReturnLocalName() == anim[i].ReturnName() ){
						this->Drzewo[j].SetImageID( img.size()+i );
						not_found = false;
						break;
					}
				}
			}
			not_found = true;
		}
	}

	//SPRAWDZENIE
	int ile = 0;
	std::string error_tmp = "";
	for( j=0; j<this->Player.size(); j++ ){
		if(  this->Player[j].ReturnImageID() == -1 ){
			ile++;
			error_tmp+= this->Player[j].ReturnLocalName() + "; ";
		}
	}
	for( j=0; j<this->Pelne.size(); j++ ){
		if(  this->Pelne[j].ReturnImageID() == -1 ){
			ile++;
			error_tmp+= this->Pelne[j].ReturnLocalName() + "; ";
		}
	}
	if( equal_size ){
		for( j=0; j<this->TrawaPiach.size(); j++ ){
			if( this->TrawaPiach[j].ReturnImageID() == -1 ){
				ile++;
				error_tmp+= this->TrawaPiach[j].ReturnLocalName() + "; ";
			}
			if( this->WodaPiach[j].ReturnImageID() == -1 ){
				ile++;
				error_tmp+= this->WodaPiach[j].ReturnLocalName() + "; ";
			}
			if( this->WodaTrawa[j].ReturnImageID() == -1 ){
				ile++;
				error_tmp+= this->WodaTrawa[j].ReturnLocalName() + "; ";
			}
		}
	}
	else{
		for( j=0; j<this->TrawaPiach.size(); j++ ){
			if( this->TrawaPiach[j].ReturnImageID() == -1 ){
				ile++;
				error_tmp+= this->TrawaPiach[j].ReturnLocalName() + "; ";
			}
		}
		for( j=0; j<this->WodaPiach.size(); j++ ){
			if( this->WodaPiach[j].ReturnImageID() == -1 ){
				ile++;
				error_tmp+= this->WodaPiach[j].ReturnLocalName() + "; ";
			}
		}
		for( j=0; j<this->WodaTrawa.size(); j++ ){
			if( this->WodaTrawa[j].ReturnImageID() == -1 ){
				ile++;
				error_tmp+= this->WodaTrawa[j].ReturnLocalName() + "; ";
			}
		}
	}

	for( j=0; j<this->Drzewo.size(); j++ ){
		if( this->Drzewo[j].ReturnImageID() == -1 ){
			ile++;
			error_tmp+= this->Drzewo[j].ReturnLocalName() + "; ";
		}
	}
	for( j=0; j<this->Ognisko.size(); j++ ){
		if( this->Ognisko[j].ReturnImageID() == -1 ){
			ile++;
			error_tmp+= this->Ognisko[j].ReturnLocalName() + "; ";
		}
	}
	for( j=0; j<this->Kamien.size(); j++ ){
		if( this->Kamien[j].ReturnImageID() == -1 ){
			ile++;
			error_tmp+= this->Kamien[j].ReturnLocalName() + "; ";
		}
	}

	if( ile != 0 ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Liczba zmiennych mapy odpowiedzialnych za wyświetlanie grafiki, które nie zostały zinicjalizowane to: " );
		LogGame::Write( ile );
		LogGame::NewLine();

		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Nazwy zmiennych: " );
		LogGame::Write( error_tmp );
		LogGame::NewLine();
	}
	this->SuccessVarMap = true;

}

int Map::ReturnPlayerX(){
	return this->PlayerX;
}

int Map::ReturnPlayerY(){
	return this->PlayerY;
}

int Map::ReturnPlayer(){
	return this->Player[0].ReturnImageID();
}

std::string Map::Operation( std::string text ){
	//REMOVE SPACE CHAR
	std::string tmp = text;
	text.clear();
	for( unsigned int i=0; i<tmp.size(); i++ ){
		if( tmp[i] != ' ' ){
			text += tmp[i];
		}
	}

	if( text[1] == 'g' ){
		//GO
		if( text[2] == 'u' ){
			//UP
			if( text[3] == '3' ){


			}
			text = "Pokonałem krótki odcinek na północ";
		}
		else if( text[2] == 'd' ){
			//DOWN

			text = "Pokonałem krótki odcinek na południe";
		}
		else if( text[2] == 'l' ){
			//LEFT

			text = "Pokonałem krótki odcinek na zachód";
		}
		else if( text[2] == 'r' ){
			//RIGHT

			text = "Pokonałem krótki odcinek na wschód";
		}
		else{
			text = "Nie wiem co mam zrobić!";
		}
	}
	return text;
}



void Map::TurnOnAnimation( bool value ){
	if( value ){
		this->Animation = true;
	}
	else{
		this->Animation = false;
	}
}
