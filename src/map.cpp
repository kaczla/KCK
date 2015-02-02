#include "map.hpp"

Map::Map(){
	this->Width = 50;
	this->Height = 50;
	this->Success = false;
	this->SuccessVarMap = false;
	this->Animation = true;

	this->PlayerX = 1;
	this->PlayerY = 25;
	this->LastOperation = 0;
	this->NextOperation = 0;
	this->TextOperation.clear();
	this->Answer.clear();
	this->PlayerDirection = 'r';
	this->ToDeleteAnswer = false;
	this->Busy = false;
	this->Builds = false;

	this->Food = 0;
	this->Wood = 0;
	this->Stone = 0;
	this->Hungry = 5;

	this->MaxRange = 13;
	this->PathBool = false;
	this->PathBoolEnd = false;
	this->OtherBool = false;

	this->Cheats = false;

	this->Error_Map = "nie zainicjalizawano mapy ( void SetValue(int height, int width); )";
}

Map::Map(int height, int width){
	this->Width = width;
	this->Height = height;
	this->Success = false;
	this->SuccessVarMap = false;
	this->Animation = true;
	this->SetVector();

	this->PlayerX = 1;
	this->PlayerY = width / 2;

	this->LastOperation = 0;
	this->NextOperation = 0;
	this->TextOperation.clear();
	this->Answer.clear();
	this->PlayerDirection = 'r';
	this->ToDeleteAnswer = false;
	this->Busy = false;
	this->Builds = false;

	this->Food = 0;
	this->Wood = 0;
	this->Stone = 0;
	this->Hungry = 5;

	this->MaxRange = 13;
	this->PathBool = false;
	this->PathBoolEnd = false;
	this->OtherBool = false;

	this->Cheats = false;
}

bool Map::ReturnSuccess(){
	return this->Success;
}

void Map::SetValue( int height, int width ){
	remap:
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
		int randomcount=0;
		int randombiomcount;
		randombiomcount=(std::rand() % 8) +12; //od 36 do 46
		for(int i=0;i<randombiomcount; i++){
			drawxyagain:  //ponowne losowanie x i y punktu do ksztaltow
			randomcount++; //ilosc losowan x i y
			if(randomcount>100)
			{
				goto remap; //ponowne wygenerowanie mapy
			}

			int x = (std::rand() % (this->Width-11)) + 5; // <5;44>
			int y = (std::rand() % (this->Height-11)) + 5;



			//@@@@@@@@@@@@@@@@@@
				drawrandombiomagain: //pozbycie sie jedynki z losowan
				int randombiom = (std::rand() % 3) + 0;
				if(randombiom==1)
				{
					goto drawrandombiomagain;
				}
			//@@@@@@@@@@@@@@@@@@


					for(int xx = x-4 ;xx<=x+4 ;xx++){ //wolne pole wokol punktu
						for(int yy = y-4 ;yy<=y+4 ;yy++)
						{
							if(this->Map2D[xx][yy] != this->Pelne[1].ReturnImageID())
							{
								goto drawxyagain; //ponownie losuj jezeli zajete
							}
						}
					}

					int randomshape;
					this->Map2D[x][y] = this->Pelne[randombiom].ReturnImageID(); //punkt bezwzgledny (czerwona kropka)
					randomshape = (std::rand() % 12) + 0;
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
						if(randombiom==2)
						{
							this->Map2D[x-3][y-1] = this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-3][y] = this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+2]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-2][y-1]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x-2][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x-1][y-1]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+2][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y-0]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+2]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-3][y-1] = this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-3][y] = this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+2]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-2][y-1]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x-2][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x-1][y-1]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+2][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y-0]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+2]=this->WodaTrawa[6].ReturnImageID();
						}
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
						if(randombiom==2) //piach
						{
							this->Map2D[x-2][y-2] = this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-2][y-1] = this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y] = this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y+1] = this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y+2] = this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-1][y-2] = this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x-1][y+2] = this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x][y-2] = this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+2] = this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-2] = this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+1][y+2] = this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+2][y-2] = this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-1] = this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y] = this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+1] = this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+2] = this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0) //woda
						{
							this->Map2D[x-2][y-2] = this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-2][y-1] = this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y] = this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y+1] = this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y+2] = this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-1][y-2] = this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x-1][y+2] = this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x][y-2] = this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+2] = this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-2] = this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+1][y+2] = this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+2][y-2] = this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-1] = this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y] = this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+1] = this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+2] = this->WodaTrawa[6].ReturnImageID();
						}

						break;
					case 2:
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y+1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						if(randombiom==2)
						{
							this->Map2D[x-2][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y-1]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-2][y+1]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-1][y-1]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-1][y+1]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+2][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+2]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-2][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y-1]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-2][y+1]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-1][y-1]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-1][y+1]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+2][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+2]=this->WodaTrawa[6].ReturnImageID();
						}
						break;
					case 3:
						this->Map2D[x-1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x][y+1] = this->Pelne[randombiom].ReturnImageID();
						if(randombiom==2){
							this->Map2D[x-2][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y-1]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-2][y+1]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-1][y-1]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-1][y+1]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+1][y-1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+1][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+1][y+1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0){
							this->Map2D[x-2][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y-1]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-2][y+1]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-1][y-1]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-1][y+1]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+1][y-1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+1][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+1][y+1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[6].ReturnImageID();
						}
						break;
					case 4:
						this->Map2D[x][y-1] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y] = this->Pelne[randombiom].ReturnImageID();
						this->Map2D[x+1][y-1] = this->Pelne[randombiom].ReturnImageID();
						if(randombiom==2)
						{
							this->Map2D[x-1][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-1][y-1]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-1][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-1][y+1]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+1]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+1][y+1]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+2][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-1][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-1][y-1]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-1][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-1][y+1]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+1]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+1][y+1]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+2][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[6].ReturnImageID();
						}
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
						if(randombiom==2){
							this->Map2D[x-3][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-3][y-1]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-2][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x-2][y+1]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x-1][y+1]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+2][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+2]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0){
							this->Map2D[x-3][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-3][y-1]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-2][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x-2][y+1]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x-1][y+1]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+2][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+2]=this->WodaTrawa[6].ReturnImageID();
						}
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
						if(randombiom==2)
						{
							this->Map2D[x-3][y-1]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-3][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-2][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-2][y-1]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-2][y+1]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-2][y+2]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-1][y-3]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-1][y+3]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[3].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[8].ReturnImageID();
							this->Map2D[x+1][y+3]=this->TrawaPiach[6].ReturnImageID();
							this->Map2D[x+2][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->TrawaPiach[3].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[8].ReturnImageID();
							this->Map2D[x+2][y+2]=this->TrawaPiach[6].ReturnImageID();
							this->Map2D[x+3][y-1]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+3][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y+1]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-3][y-1]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-3][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-2][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-2][y-1]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-2][y+1]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-2][y+2]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-1][y-3]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-1][y+3]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[3].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[8].ReturnImageID();
							this->Map2D[x+1][y+3]=this->WodaTrawa[6].ReturnImageID();
							this->Map2D[x+2][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->WodaTrawa[3].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[8].ReturnImageID();
							this->Map2D[x+2][y+2]=this->WodaTrawa[6].ReturnImageID();
							this->Map2D[x+3][y-1]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+3][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y+1]=this->WodaTrawa[6].ReturnImageID();
						}
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
						if(randombiom==2)
						{
							this->Map2D[x-2][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-2][y-1]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y+1]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-1][y-3]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-1][y+1]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+2][y-3]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-2]=this->TrawaPiach[3].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[8].ReturnImageID();
							this->Map2D[x+2][y+2]=this->TrawaPiach[6].ReturnImageID();
							this->Map2D[x+3][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+3][y-1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y+1]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-2][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-2][y-1]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y+1]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-1][y-3]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-1][y+1]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+2][y-3]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-2]=this->WodaTrawa[3].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[8].ReturnImageID();
							this->Map2D[x+2][y+2]=this->WodaTrawa[6].ReturnImageID();
							this->Map2D[x+3][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+3][y-1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y+1]=this->WodaTrawa[6].ReturnImageID();
						}
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
						if(randombiom==2)
						{
							this->Map2D[x-3][y-1]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-3][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+2]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+3]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-2][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-2][y-1]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-2][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[8].ReturnImageID();
							this->Map2D[x-1][y+3]=this->TrawaPiach[6].ReturnImageID();
							this->Map2D[x][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+1]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x+1][y+3]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x+2][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->TrawaPiach[3].ReturnImageID();
							this->Map2D[x+2][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+3][y-1]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+3][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y+1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y+2]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y+3]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-3][y-1]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-3][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+2]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+3]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-2][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-2][y-1]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-2][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[8].ReturnImageID();
							this->Map2D[x-1][y+3]=this->WodaTrawa[6].ReturnImageID();
							this->Map2D[x][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+1]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x+1][y+3]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x+2][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->WodaTrawa[3].ReturnImageID();
							this->Map2D[x+2][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+3][y-1]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+3][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y+1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y+2]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y+3]=this->WodaTrawa[6].ReturnImageID();
						}
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
						if(randombiom==2)
						{
							this->Map2D[x-3][y-3]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-3][y-2]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y-1]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-2][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x-2][y+1]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-2][y+2]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-1][y-3]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[3].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x][y-1]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+2][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[8].ReturnImageID();
							this->Map2D[x+2][y+2]=this->TrawaPiach[6].ReturnImageID();
							this->Map2D[x+3][y-3]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+3][y-2]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y-1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y+1]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-3][y-3]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-3][y-2]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y-1]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+1]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-2][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x-2][y+1]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-2][y+2]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-1][y-3]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[3].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x][y-1]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+2][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[8].ReturnImageID();
							this->Map2D[x+2][y+2]=this->WodaTrawa[6].ReturnImageID();
							this->Map2D[x+3][y-3]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+3][y-2]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y-1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y+1]=this->WodaTrawa[6].ReturnImageID();
						}
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
						if(randombiom==2)
						{
							this->Map2D[x-3][y-3]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-3][y-2]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y-1]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-3][y+1]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-3][y+2]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-3][y+3]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-2][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x-2][y-1]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-2][y+1]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-2][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x-1][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x-1][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x-1][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+1][y-2]=this->TrawaPiach[3].ReturnImageID();
							this->Map2D[x+1][y+2]=this->TrawaPiach[8].ReturnImageID();
							this->Map2D[x+1][y+3]=this->TrawaPiach[6].ReturnImageID();
							this->Map2D[x+2][y-2]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+2][y+2]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-3][y-3]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-3][y-2]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y-1]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-3][y+1]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-3][y+2]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-3][y+3]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-2][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x-2][y-1]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-2][y+1]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-2][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x-1][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x-1][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x-1][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+1][y-2]=this->WodaTrawa[3].ReturnImageID();
							this->Map2D[x+1][y+2]=this->WodaTrawa[8].ReturnImageID();
							this->Map2D[x+1][y+3]=this->WodaTrawa[6].ReturnImageID();
							this->Map2D[x+2][y-2]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+2][y-1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+2][y+2]=this->WodaTrawa[6].ReturnImageID();
						}
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
						if(randombiom==2)
						{
							this->Map2D[x-2][y-2]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-2][y-1]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y+1]=this->TrawaPiach[1].ReturnImageID();
							this->Map2D[x-2][y+2]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x-1][y-3]=this->TrawaPiach[9].ReturnImageID();
							this->Map2D[x-1][y-2]=this->TrawaPiach[7].ReturnImageID();
							this->Map2D[x-1][y+2]=this->TrawaPiach[4].ReturnImageID();
							this->Map2D[x-1][y+3]=this->TrawaPiach[2].ReturnImageID();
							this->Map2D[x][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+1][y]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+1][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+2][y-3]=this->TrawaPiach[11].ReturnImageID();
							this->Map2D[x+2][y-1]=this->TrawaPiach[8].ReturnImageID();
							this->Map2D[x+2][y+1]=this->TrawaPiach[3].ReturnImageID();
							this->Map2D[x+2][y+3]=this->TrawaPiach[10].ReturnImageID();
							this->Map2D[x+3][y-3]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+3][y-2]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y-1]=this->TrawaPiach[6].ReturnImageID();
							this->Map2D[x+3][y+1]=this->TrawaPiach[5].ReturnImageID();
							this->Map2D[x+3][y+2]=this->TrawaPiach[0].ReturnImageID();
							this->Map2D[x+3][y+3]=this->TrawaPiach[6].ReturnImageID();
						}
						if(randombiom==0)
						{
							this->Map2D[x-2][y-2]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-2][y-1]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y+1]=this->WodaTrawa[1].ReturnImageID();
							this->Map2D[x-2][y+2]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x-1][y-3]=this->WodaTrawa[9].ReturnImageID();
							this->Map2D[x-1][y-2]=this->WodaTrawa[7].ReturnImageID();
							this->Map2D[x-1][y+2]=this->WodaTrawa[4].ReturnImageID();
							this->Map2D[x-1][y+3]=this->WodaTrawa[2].ReturnImageID();
							this->Map2D[x][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+1][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+1][y]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+1][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+2][y-3]=this->WodaTrawa[11].ReturnImageID();
							this->Map2D[x+2][y-1]=this->WodaTrawa[8].ReturnImageID();
							this->Map2D[x+2][y+1]=this->WodaTrawa[3].ReturnImageID();
							this->Map2D[x+2][y+3]=this->WodaTrawa[10].ReturnImageID();
							this->Map2D[x+3][y-3]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+3][y-2]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y-1]=this->WodaTrawa[6].ReturnImageID();
							this->Map2D[x+3][y+1]=this->WodaTrawa[5].ReturnImageID();
							this->Map2D[x+3][y+2]=this->WodaTrawa[0].ReturnImageID();
							this->Map2D[x+3][y+3]=this->WodaTrawa[6].ReturnImageID();
						}
						break;
				}
		}

		//losowanie obiektow
		for(int j=0;j<50;j++)
		{
			for(int h=0;h<50;h++)
			{
				int objectrandom = (std::rand() % 100) +0;
				if(this->Map2D[h][j] == this->Pelne[1].ReturnImageID())
				{
					if (objectrandom<=10) //drzewa na trawie
					{
						if(objectrandom%3==0)
						{
							this->Map2D_obj[h][j]=Drzewo[0].ReturnImageID();
						}
						if(objectrandom%3==1)
						{
							this->Map2D_obj[h][j]=Drzewo[1].ReturnImageID();
						}
						if(objectrandom%3==2)
						{
							this->Map2D_obj[h][j]=Drzewo[2].ReturnImageID();
						}
					}
					if (objectrandom<=5) //grzyby na trawie
					{
						if(objectrandom%3==0)
						{
							this->Map2D_obj[h][j]=Jedzenie[0].ReturnImageID();
						}
						if(objectrandom%3==1)
						{
							this->Map2D_obj[h][j]=Jedzenie[1].ReturnImageID();
						}
						if(objectrandom%3==2)
						{
							this->Map2D_obj[h][j]=Jedzenie[2].ReturnImageID();
						}
					}
					if (objectrandom==0) //kamienie na trawie
					{
						if(objectrandom%3==0)
						{
							this->Map2D_obj[h][j]=Kamien[0].ReturnImageID();
						}
						if(objectrandom%3==1)
						{
							this->Map2D_obj[h][j]=Kamien[1].ReturnImageID();
						}
						if(objectrandom%3==2)
						{
							this->Map2D_obj[h][j]=Kamien[2].ReturnImageID();
						}
					}
				}
				if(this->Map2D[h][j] == this->Pelne[2].ReturnImageID())
				{
					if (objectrandom<=10)
					{
						if(objectrandom%3==0)
						{
							this->Map2D_obj[h][j]=Kamien[0].ReturnImageID();
						}
						if(objectrandom%3==1)
						{
							this->Map2D_obj[h][j]=Kamien[1].ReturnImageID();
						}
						if(objectrandom%3==2)
						{
							this->Map2D_obj[h][j]=Kamien[2].ReturnImageID();
						}
					}
				}
			}
		}


		//OBIEKTY

		this->Error_Map = " ";
		this->Success = true;
	}
}

int Map::ReturnValueMap( int x, int y ){
	if( x<0 or x>=this->Width ){
		return this->Pelne[0].ReturnImageID();
	}
	else if( y<0 or y>=this->Height ){
		return this->Pelne[0].ReturnImageID();
	}
	else{
		return this->Map2D[y][x];
	}
}

int Map::ReturnValueMapObj( int x, int y ){
	if( x<0 or x>=this->Width ){
		return 0;
	}
	else if( y<0 or y>=this->Height ){
		return 0;
	}
	else{
		return this->Map2D_obj[y][x];
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

void Map::SetVarMap( std::vector <Img> &img, std::vector <Anim> &anim){
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
	this->WodaTrawa[1].SetLocalName( "GD_trawawoda" );
	this->WodaTrawa[0].SetLocalName( "GD_wodatrawa" );
	this->WodaTrawa[3].SetLocalName( "LD1_PG3_trawawoda" );
	this->WodaTrawa[2].SetLocalName( "LD1_PG3_wodatrawa" );
	this->WodaTrawa[5].SetLocalName( "LD3_PG1_trawawoda" );
	this->WodaTrawa[4].SetLocalName( "LD3_PG1_wodatrawa" );
	this->WodaTrawa[6].SetLocalName( "LG1_PD3_wodatrawa" );
	this->WodaTrawa[7].SetLocalName( "LG1_PD3_trawawoda" );
	this->WodaTrawa[9].SetLocalName( "LG3_PD1_trawawoda" );
	this->WodaTrawa[8].SetLocalName( "LG3_PD1_wodatrawa" );
	this->WodaTrawa[11].SetLocalName( "LP_trawawoda" );
	this->WodaTrawa[10].SetLocalName( "LP_wodatrawa" );

	this->Drzewo.resize( 4 );
	this->Drzewo[0].SetLocalName( "tree1" );
	this->Drzewo[1].SetLocalName( "tree2" );
	this->Drzewo[2].SetLocalName( "tree3" );
	this->Drzewo[3].SetLocalName( "pien" );

	this->Ognisko.resize( 3 );
	this->Ognisko[0].SetLocalName( "ognichoready" );
	this->Ognisko[1].SetLocalName( "ognichofire" );
	this->Ognisko[2].SetLocalName( "ognichospalone" );

	this->Kamien.resize( 3 );
	this->Kamien[0].SetLocalName( "stone1" );
	this->Kamien[1].SetLocalName( "stone2" );
	this->Kamien[2].SetLocalName( "stone3" );

	this->Jedzenie.resize( 3 );
	this->Jedzenie[0].SetLocalName( "grzyby1" );
	this->Jedzenie[1].SetLocalName( "grzyby2" );
	this->Jedzenie[2].SetLocalName( "grzyby3" );

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
		for( j=0; j<this->Jedzenie.size(); j++ ){
			if( not_found && this->Jedzenie[j].ReturnLocalName() == img[i].ReturnName() ){
				this->Jedzenie[j].SetImageID( i );
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
						this->Ognisko[j].SetImageID( (unsigned int)img.size()+i );
						not_found = false;
						break;
					}
				}
			}
			if( not_found ){
				for( j=0; j<this->Drzewo.size(); j++ ){
					if( not_found && this->Drzewo[j].ReturnLocalName() == anim[i].ReturnName() ){
						this->Drzewo[j].SetImageID( (unsigned int)img.size()+i );
						not_found = false;
						break;
					}
				}
			}
			not_found = true;
		}
		not_found = true;
		for( i=0; i<img.size(); i++ ){
			if( not_found ){
				if( this->Drzewo[3].ReturnLocalName() == img[i].ReturnName() ){
					this->Drzewo[3].SetImageID( i );
					not_found = false;
					break;
				}
			}
			else{
				break;
			}
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
	for( j=0; j<this->Jedzenie.size(); j++ ){
		if( this->Jedzenie[j].ReturnImageID() == -1 ){
			ile++;
			error_tmp+= this->Jedzenie[j].ReturnLocalName() + "; ";
		}
	}
	this->Error_Map = "Problem z inicjalizacją zmiennych dla generowania mapy!";
	this->Success = false;
	this->SuccessVarMap = false;
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
	else{
		this->Success = true;
		this->Error_Map.clear();
		this->SuccessVarMap = true;
	}
}

int Map::ReturnPlayerX(){
	return this->PlayerX;
}

int Map::ReturnPlayerY(){
	return this->PlayerY;
}

int Map::ReturnPlayer(){
	switch( this->PlayerDirection ){
		case 'u':
			return this->Player[0].ReturnImageID();
			break;
		case 'd':
			return this->Player[3].ReturnImageID();
			break;
		case 'l':
			return this->Player[1].ReturnImageID();
			break;
		case 'r':
			return this->Player[2].ReturnImageID();
			break;
		default:
			return this->Player[0].ReturnImageID();
	}
	return this->Player[0].ReturnImageID();
}

void Map::Operation( std::string &text ){
	//REMOVE SPACE CHAR
	std::string tmp = text;
	text.clear();
	for( unsigned int i=0; i<tmp.size(); i++ ){
		if( tmp[i] != ' ' ){
			text += tmp[i];
		}
	}
	//std::cout<<"POLECENIA: \'"<<text<<"\'\n";
	this->Other.clear();
	this->OtherBool = false;
	if( text.size() > 5 ){
		this->Other.clear();
		tmp.clear();
		for( unsigned int i=0; i<text.size(); i++ ){
			if( text[i] != '.' ){
				tmp += text[i];
			}
			else{
				this->Other.push_back( tmp );
				tmp.clear();
			}
		}
		/*
		for( std::vector <std::string>::iterator it = this->Other.begin(); it != this->Other.end(); it++ ){
			std::cout<<*it<<" ";
		}
		std::cout<<"\n";
		*/
		if( this->Other.size() > 0 ){
			this->TextOperation = this->Other[0];
			this->Other.erase( this->Other.begin() );
			this->OtherBool = true;
		}
	}
	else if( text[0] == '1' ){
		this->TextOperation = text;
	}
	else{
		this->TextOperation.clear();
	}
}

void Map::Update(){
	if( this->ToDeleteAnswer ){
		this->Answer.clear();
		this->ToDeleteAnswer = false;
		//this->Busy = false;
	}
	this->LastOperation = SDL_GetTicks();
	if( this->LastOperation >= this->NextOperation && ! this->TextOperation.empty() ){
		this->NextOperation = this->LastOperation;
		if( this->TextOperation[1] == 'g' ){
			//GO
			this->OperationGo();
		}
		else if( this->TextOperation[1] == 't' ){
			//TURN
			this->OperationTurn();
		}
		else if( this->TextOperation[1] == 'b' ){
			//BUILD FIRE
			if( this->TextOperation[2] == 'f' ){
				this->OperationBuildFire();
			}
			else{
				this->Answer = text_dont_know;
				this->ToDeleteAnswer = true;
				this->TextOperation.clear();
			}
		}
		else if( this->TextOperation == "1st" ){
			//STOP
			this->StopOperation();
			this->Answer = text_non;
			this->ToDeleteAnswer = true;
			this->TextOperation.clear();
		}
		else if( this->TextOperation == "1del" ){
			//DELETE
			this->OperationDelete();
		}
		else if( this->TextOperation == "1end" ){
			this->StopOperation();
			this->Answer = text_path_end;
		}
		//EAT
		else if( this->TextOperation == "1eat" ){
			this->Eat();
			this->ToDeleteAnswer = true;
			this->TextOperation.clear();
		}
		//FIND
		else if( this->TextOperation[1] == 'f' ){
			//TREE
			if( this->TextOperation[2] == 't' ){
				this->FindTree();
			}
			//STONE
			else if( this->TextOperation[2] == 's' ){
				this->FindStone();
			}
			//FIRE
			else if( this->TextOperation[2] == 'f' ){
				this->FindFire();
			}
			//FOOD
			else if( this->TextOperation[2] == 'm' ){
				this->FindFood();
			}
			else{
				this->Answer = text_dont_know;
				this->ToDeleteAnswer = true;
				this->TextOperation.clear();
			}
		}
		else if( this->TextOperation[1] == 'c' ){
			//CUT TREE
			if( this->TextOperation[2] == 't' ){
				this->CutTree();
			}
			//DESTROY STONE
			else if( this->TextOperation[2] == 's' ){
				this->DestroyStone();
			}
			//FOOD
			else if( this->TextOperation[2] == 'f' ){
				this->DestoryFood();
			}
			//CHEATS ON
			else if( this->TextOperation == "1cheatson" ){
				this->Cheats = true;
				this->Answer = text_cheats_on;
				this->ToDeleteAnswer = true;
				this->TextOperation.clear();
			}
			else{
				this->Answer = text_dont_know;
				this->ToDeleteAnswer = true;
				this->TextOperation.clear();
			}
		}
		else if( this->TextOperation[1] == 'o' ){
			//FIRE START
			if( this->TextOperation == "1osf" ){
				this->StartFire();
				this->ToDeleteAnswer = true;
				this->TextOperation.clear();
			}
			//FIRE STOP
			else if( this->TextOperation == "1opf" ){
				this->StopFire();
				this->Answer = text_done;
				this->TextOperation.clear();
			}
			else{
				this->Answer = text_dont_know;
				this->ToDeleteAnswer = true;
				this->TextOperation.clear();
			}
		}
		else if( this->Cheats ){
			//CHEATS
			if( this->TextOperation == "1allresources" ){
				this->Food = 9;
				this->Wood = 9;
				this->Stone = 9;
				this->Answer = text_cheats_on;
			}
			else{
				this->Answer = text_dont_know;
			}
			this->ToDeleteAnswer = true;
			this->TextOperation.clear();
		}
		else{
			this->Answer = text_dont_know;
			this->ToDeleteAnswer = true;
			this->TextOperation.clear();
		}

		if( this->TextOperation.empty() && this->Path.size() > 0 ){
				this->TextOperation = this->Path[0];
				this->Path.erase( this->Path.begin() );
				if( this->TextOperation == "1end" ){
					this->PathBoolEnd = true;
				}
		}

		if( this->PathBool ){
			this->Busy = true;
			if( this->Builds ){
				this->Answer = text_path_working;
			}
			else{
				this->Answer = text_path;
			}
			if( this->PathBoolEnd ){
				this->PathBoolEnd = false;
				this->Answer = text_path_end;
			}
		}
	}
	if( this->OtherBool ){
		this->Answer = text_path_working;
		if( this->Other.empty() ){
			//if( this->Other.empty() and this->Path.empty() and this->TextOperation.empty() ){
			this->OtherBool = false;
		}
		if(  this->PathBool == false and this->TextOperation.empty() ){
			if( this->Other.size() > 0 ){
				this->TextOperation = this->Other[0];
				this->Other.erase( this->Other.begin() );
			}
		}
	}
}

void Map::OperationGo(){
	if( this->TextOperation[2] == 'u' ){
		//UP
		this->Answer = text_go_up;
		this->NextOperation = SDL_GetTicks() + time_move;
		this->ToDeleteAnswer = true;
		this->Busy = true;
		switch( this->TextOperation[3] ){
			case '0':
				this->PlayerDirection = 'u';
				this->Answer = text_on_place;
				this->NextOperation -= time_move;
				this->TextOperation.clear();
				this->Busy = false;
				break;
			case '1':
				this->PlayerDirection = 'u';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY-1 ) ){
					this->TextOperation[3] = '0';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '2':
				this->PlayerDirection = 'u';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY-1 ) ){
					this->TextOperation[3] = '1';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '3':
				this->PlayerDirection = 'u';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY-1 ) ){
					this->TextOperation[3] = '2';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '4':
				this->PlayerDirection = 'u';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY-1 ) ){
					this->TextOperation[3] = '3';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '5':
				this->PlayerDirection = 'u';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY-1 ) ){
					this->TextOperation[3] = '4';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '6':
				this->PlayerDirection = 'u';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY-1 ) ){
					this->TextOperation[3] = '5';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			default:
				this->Answer = text_dont_know;
				this->NextOperation -= time_move;
				this->Busy = false;
				break;
		}
	}
	else if( this->TextOperation[2] == 'd' ){
		//DOWN
		this->Answer = text_go_down;
		this->NextOperation += time_move;
		this->ToDeleteAnswer = true;
		this->Busy = true;
		switch( this->TextOperation[3] ){
			case '0':
				this->PlayerDirection = 'd';
				this->Answer = text_on_place;
				this->NextOperation -= time_move;
				this->TextOperation.clear();
				this->Busy = false;
				break;
			case '1':
				this->PlayerDirection = 'd';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY+1 ) ){
					this->TextOperation[3] = '0';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '2':
				this->PlayerDirection = 'd';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY+1 ) ){
					this->TextOperation[3] = '1';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '3':
				this->PlayerDirection = 'd';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY+1 ) ){
					this->TextOperation[3] = '2';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '4':
				this->PlayerDirection = 'd';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY+1 ) ){
					this->TextOperation[3] = '3';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '5':
				this->PlayerDirection = 'd';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY+1 ) ){
					this->TextOperation[3] = '4';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '6':
				this->PlayerDirection = 'd';
				if( this->MovePlayerTo( this->PlayerX, this->PlayerY+1 ) ){
					this->TextOperation[3] = '5';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			default:
				this->Answer = text_dont_know;
				this->NextOperation -= time_move;
				this->Busy = false;
				break;
		}
	}
	else if( this->TextOperation[2] == 'l' ){
		//LEFT
		this->Answer = text_go_left;
		this->NextOperation += time_move;
		this->ToDeleteAnswer = true;
		this->Busy = true;
		switch( this->TextOperation[3] ){
			case '0':
				this->PlayerDirection = 'l';
				this->Answer = text_on_place;
				this->NextOperation -= time_move;
				this->TextOperation.clear();
				this->Busy = false;
				break;
			case '1':
				this->PlayerDirection = 'l';
				if( this->MovePlayerTo( this->PlayerX-1, this->PlayerY ) ){
					this->TextOperation[3] = '0';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '2':
				this->PlayerDirection = 'l';
				if( this->MovePlayerTo( this->PlayerX-1, this->PlayerY ) ){
					this->TextOperation[3] = '1';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '3':
				this->PlayerDirection = 'l';
				if( this->MovePlayerTo( this->PlayerX-1, this->PlayerY ) ){
					this->TextOperation[3] = '2';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '4':
				this->PlayerDirection = 'l';
				if( this->MovePlayerTo( this->PlayerX-1, this->PlayerY ) ){
					this->TextOperation[3] = '3';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '5':
				this->PlayerDirection = 'l';
				if( this->MovePlayerTo( this->PlayerX-1, this->PlayerY ) ){
					this->TextOperation[3] = '4';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '6':
				this->PlayerDirection = 'l';
				if( this->MovePlayerTo( this->PlayerX-1, this->PlayerY ) ){
					this->TextOperation[3] = '5';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			default:
				this->Answer = text_dont_know;
				this->NextOperation -= time_move;
				this->Busy = false;
				break;
		}
	}
	else if( this->TextOperation[2] == 'r' ){
		//RIGHT
		this->Answer = text_go_right;
		this->NextOperation += time_move;
		this->ToDeleteAnswer = true;
		this->Busy = true;
		switch( this->TextOperation[3] ){
			case '0':
				this->PlayerDirection = 'r';
				this->Answer = text_on_place;
				this->NextOperation -= time_move;
				this->TextOperation.clear();
				this->Busy = false;
				break;
			case '1':
				this->PlayerDirection = 'r';
				if( this->MovePlayerTo( this->PlayerX+1, this->PlayerY ) ){
					this->TextOperation[3] = '0';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '2':
				this->PlayerDirection = 'r';
				if( this->MovePlayerTo( this->PlayerX+1, this->PlayerY ) ){
					this->TextOperation[3] = '1';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '3':
				this->PlayerDirection = 'r';
				if( this->MovePlayerTo( this->PlayerX+1, this->PlayerY ) ){
					this->TextOperation[3] = '2';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '4':
				this->PlayerDirection = 'r';
				if( this->MovePlayerTo( this->PlayerX+1, this->PlayerY ) ){
					this->TextOperation[3] = '3';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '5':
				this->PlayerDirection = 'r';
				if( this->MovePlayerTo( this->PlayerX+1, this->PlayerY ) ){
					this->TextOperation[3] = '4';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			case '6':
				this->PlayerDirection = 'r';
				if( this->MovePlayerTo( this->PlayerX+1, this->PlayerY ) ){
					this->TextOperation[3] = '5';
				}
				else{
					this->Answer = text_cant_move;
					this->TextOperation.clear();
					this->Busy = false;
				}
				break;
			default:
				this->Answer = text_dont_know;
				this->NextOperation -= time_move;
				this->Busy = false;
				break;
		}
	}
	else{
		this->Answer = text_dont_know;
		this->ToDeleteAnswer = true;
		this->TextOperation.clear();
	}
}

void Map::OperationTurn(){
	this->NextOperation += time_turn;
	this->ToDeleteAnswer = true;
	switch( this->TextOperation[2] ){
		case 'u': //UP
			if( this->PlayerDirection == 'u' ){
				this->NextOperation -= time_turn;
				this->Answer = text_turn_ok;
			}
			else{
				this->PlayerDirection = 'u';
				this->Answer = text_turn_up;
			}
			break;
		case 'd': //DOWN
			if( this->PlayerDirection == 'd' ){
				this->NextOperation -= time_turn;
				this->Answer = text_turn_ok;
			}
			else{
				this->PlayerDirection = 'd';
				this->Answer = text_turn_down;
			}
			break;
		case 'l': //LEFT
			if( this->PlayerDirection == 'l' ){
				this->NextOperation -= time_turn;
				this->Answer = text_turn_ok;
			}
			else{
				this->PlayerDirection = 'l';
				this->Answer = text_turn_left;
			}
			break;
		case 'r': //RIGHT
			if( this->PlayerDirection == 'r' ){
				this->NextOperation -= time_turn;
				this->Answer = text_turn_ok;
			}
			else{
				this->PlayerDirection = 'r';
				this->Answer = text_turn_right;
			}
			break;
		default:
			this->NextOperation -= time_turn;
			this->Answer = text_dont_know;
			break;
	}
	this->TextOperation.clear();
}

void Map::OperationBuildFire(){
	if( this->LastOperation >= this->NextOperation ){
		if( this->Builds ){
			this->Builds = false;
			this->Busy = false;
			this->Answer = text_build_fire;
			this->ToDeleteAnswer = true;
			this->TextOperation.clear();
			//BUDOWA
			if( this->PlayerDirection == 'u' ){
				this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[0].ReturnImageID();
				this->Wood -= 4;
				this->Stone -= 2;
			}
			else if( this->PlayerDirection == 'd' ){
				this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[0].ReturnImageID();
				this->Wood -= 4;
				this->Stone -= 2;
			}
			else if( this->PlayerDirection == 'l' ){
				this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[0].ReturnImageID();
				this->Wood -= 4;
				this->Stone -= 2;
			}
			else if( this->PlayerDirection == 'r' ){
				this->Map2D_obj[this->PlayerY][this->PlayerX+1] = this->Ognisko[0].ReturnImageID();
				this->Wood -= 4;
				this->Stone -= 2;
			}
			else{
				this->Answer = text_dont_know;
			}
		}
		else{
			int tmp = -1;
			if( this->Wood >= 4 and this->Stone >= 2 ){
				if( this->PlayerDirection == 'u' ){
					tmp = this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 );
					if( tmp == 0 ){
						tmp = this->ReturnValueMap( this->PlayerX, this->PlayerY-1 );
						if( tmp == this->Pelne[1].ReturnImageID() or tmp == this->Pelne[2].ReturnImageID()
							or ( tmp >= this->TrawaPiach[0].ReturnImageID() and tmp <= this->TrawaPiach[11].ReturnImageID() ) ){
								this->Builds = true;
								this->Busy = true;
								this->Answer = text_builds;
								this->NextOperation = SDL_GetTicks() + time_build_fire;
						}
						else{
							this->Answer = text_build_wrong_place;
							this->ToDeleteAnswer = true;
							this->TextOperation.clear();
						}
					}
					else{
						this->Answer = text_build_is_item;
						this->ToDeleteAnswer = true;
						this->TextOperation.clear();
					}

				}
				else if( this->PlayerDirection == 'd' ){
					tmp = this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 );
					if( tmp == 0 ){
						tmp = this->ReturnValueMap( this->PlayerX, this->PlayerY+1 );
						if( tmp == this->Pelne[1].ReturnImageID() or tmp == this->Pelne[2].ReturnImageID()
							or ( tmp >= this->TrawaPiach[0].ReturnImageID() and tmp <= this->TrawaPiach[11].ReturnImageID() ) ){
								this->Builds = true;
								this->Busy = true;
								this->Answer = text_builds;
								this->NextOperation = SDL_GetTicks() + time_build_fire;
						}
						else{
							this->Answer = text_build_wrong_place;
							this->ToDeleteAnswer = true;
							this->TextOperation.clear();
						}
					}
					else{
						this->Answer = text_build_is_item;
						this->ToDeleteAnswer = true;
						this->TextOperation.clear();
					}
				}
				else if( this->PlayerDirection == 'l' ){
					tmp = this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY );
					if( tmp == 0 ){
						tmp = this->ReturnValueMap( this->PlayerX-1, this->PlayerY );
						if( tmp == this->Pelne[1].ReturnImageID() or tmp == this->Pelne[2].ReturnImageID()
							or ( tmp >= this->TrawaPiach[0].ReturnImageID() and tmp <= this->TrawaPiach[11].ReturnImageID() ) ){
								this->Builds = true;
								this->Busy = true;
								this->Answer = text_builds;
								this->NextOperation = SDL_GetTicks() + time_build_fire;
						}
						else{
							this->Answer = text_build_wrong_place;
							this->ToDeleteAnswer = true;
							this->TextOperation.clear();
						}
					}
					else{
						this->Answer = text_build_is_item;
						this->ToDeleteAnswer = true;
						this->TextOperation.clear();
					}
				}
				else if( this->PlayerDirection == 'r' ){
					tmp = this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY );
					if( tmp == 0 ){
						tmp = this->ReturnValueMap( this->PlayerX+1, this->PlayerY );
						if( tmp == this->Pelne[1].ReturnImageID() or tmp == this->Pelne[2].ReturnImageID()
							or ( tmp >= this->TrawaPiach[0].ReturnImageID() and tmp <= this->TrawaPiach[11].ReturnImageID() ) ){
								this->Builds = true;
								this->Busy = true;
								this->Answer = text_builds;
								this->NextOperation = SDL_GetTicks() + time_build_fire;
						}
						else{
							this->Answer = text_build_wrong_place;
							this->ToDeleteAnswer = true;
							this->TextOperation.clear();
						}
					}
					else{
						this->Answer = text_build_is_item;
						this->ToDeleteAnswer = true;
						this->TextOperation.clear();
					}
				}
				else{
					this->Answer = text_dont_know;
				}
			}
			else{
				this->Answer = text_build_no_items;
				this->ToDeleteAnswer = true;
				this->TextOperation.clear();
			}
		}
	}
}

void Map::TurnOnAnimation( bool value ){
	if( value ){
		this->Animation = true;
	}
	else{
		this->Animation = false;
	}
}

std::string Map::ReturnAnswer(){
	return this->Answer;
}

bool Map::MovePlayerTo( int x, int y ){
	if( x<0 or x>=this->Width ){
		return false;
	}
	else if( y<0 or y>=this->Height ){
		return false;
	}
	else if( Map2D[y][x] == this->Pelne[0].ReturnImageID() ){
		return false;
	}
	else if( Map2D_obj[y][x] == 0 ){
		this->PlayerX = x;
		this->PlayerY = y;
	}
	else{
		return false;
	}
	return true;
}

bool Map::ReturnBusy(){
	return this->Busy;
}

void Map::StopOperation(){
	this->TextOperation.clear();
	this->Answer = text_stop;
	this->ToDeleteAnswer = true;
	this->Builds = false;
	this->Busy = false;
	this->PathBool = false;
	this->Path.clear();
	this->LastOperation = SDL_GetTicks();
	this->NextOperation = this->LastOperation;
}

void Map::StopOperationAll(){
	this->StopOperation();
	this->Other.clear();
	this->OtherBool = false;
}

unsigned int Map::ReturnFood(){
	if( this->Food == 0 ){
		return 0;
	}
	else if( this->Food >= 1 and this->Food <= 3 ){
		//1-3
		return 1;
	}
	else if( this->Food >= 4 and this->Food <= 6 ){
		//4-6
		return 2;
	}
	else if( this->Food >= 7 and this->Food <= 9 ){
		//7-9
		return 3;
	}
	else{
		if( this->Food > 9){
			this->Food = 9;
			return 3;
		}
		else if( this->Food < 0 ){
			this->Food = 0;
		}
		return 0;
	}
	return 0;
}

unsigned int Map::ReturnWood(){
	if( this->Wood == 0 ){
		return 0;
	}
	else if( this->Wood >= 1 and this->Wood <= 3 ){
		//1-3
		return 1;
	}
	else if( this->Wood >= 4 and this->Wood <= 6 ){
		//4-6
		return 2;
	}
	else if( this->Wood >= 7 and this->Wood <= 9 ){
		//7-9
		return 3;
	}
	else{
		if( this->Wood > 9 ){
			this->Wood = 9;
			return 3;
		}
		else if (this->Wood < 0 ){
			this->Wood = 0;
		}
		return 0;
	}
	return 0;
}

unsigned int Map::ReturnStone(){
	if( this->Stone == 0 ){
		return 0;
	}
	else if( this->Stone >= 1 and this->Stone <= 3 ){
		//1-3
		return 1;
	}
	else if( this->Stone >= 4 and this->Stone <= 6 ){
		//4-6
		return 2;
	}
	else if( this->Stone >= 7 and this->Stone <= 9 ){
		//7-9
		return 3;
	}
	else{
		if( this->Stone > 9 ){
			this->Stone = 9;
			return 3;
		}
		else if( this->Stone < 0 ){
			this->Stone = 0;
		}
		return 0;
	}
	return 0;
}

void Map::OperationDelete(){
	if( this->LastOperation >= this->NextOperation ){
		if( this->Builds ){
			this->Builds = false;
			this->Busy = false;
			this->Answer = text_delete_end;
			this->ToDeleteAnswer = true;
			this->TextOperation.clear();
			if( this->PlayerDirection == 'u' ){
				this->DeleteObject( this->PlayerX, this->PlayerY-1 );
			}
			else if( this->PlayerDirection == 'd' ){
				this->DeleteObject( this->PlayerX, this->PlayerY+1 );
			}
			else if( this->PlayerDirection == 'l' ){
				this->DeleteObject( this->PlayerX-1, this->PlayerY );
			}
			else if( this->PlayerDirection == 'r' ){
				this->DeleteObject( this->PlayerX+1, this->PlayerY );
			}
			else{
				this->Answer = text_dont_know;
			}
		}
		else{
			int tmp = -1;
			if( this->PlayerDirection == 'u' ){
				tmp = this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 );
				if( tmp != 0 ){
					this->Builds = true;
					this->Busy = true;
					this->Answer = text_delete;
					this->NextOperation = SDL_GetTicks() + time_delete;
				}
				else{
					this->Answer = text_delete_not;
					this->ToDeleteAnswer = true;
					this->TextOperation.clear();
				}

			}
			else if( this->PlayerDirection == 'd' ){
				tmp = this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 );
				if( tmp != 0 ){
					this->Builds = true;
					this->Busy = true;
					this->Answer = text_delete;
					this->NextOperation = SDL_GetTicks() + time_delete;
				}
				else{
					this->Answer = text_delete_not;
					this->ToDeleteAnswer = true;
					this->TextOperation.clear();
				}

			}
			else if( this->PlayerDirection == 'l' ){
				tmp = this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY );
				if( tmp != 0 ){
					this->Builds = true;
					this->Busy = true;
					this->Answer = text_delete;
					this->NextOperation = SDL_GetTicks() + time_delete;
				}
				else{
					this->Answer = text_delete_not;
					this->ToDeleteAnswer = true;
					this->TextOperation.clear();
				}

			}
			else if( this->PlayerDirection == 'r' ){
				tmp = this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY );
				if( tmp != 0 ){
					this->Builds = true;
					this->Busy = true;
					this->Answer = text_delete;
					this->NextOperation = SDL_GetTicks() + time_delete;
				}
				else{
					this->Answer = text_delete_not;
					this->ToDeleteAnswer = true;
					this->TextOperation.clear();
				}

			}
			else {
				this->Answer = text_dont_know;
				this->ToDeleteAnswer = true;
				this->TextOperation.clear();
			}
		}

	}
}

void Map::DeleteObject( int x, int y ){
	int _tmp = this->Map2D_obj[y][x];
	if( _tmp == this->Drzewo[0].ReturnImageID() or _tmp == this->Drzewo[1].ReturnImageID() or _tmp == this->Drzewo[2].ReturnImageID() ){
		this->Map2D_obj[y][x] = this->Drzewo[3].ReturnImageID();
		this->Wood += 3;
	}
	else if( _tmp == this->Drzewo[3].ReturnImageID() ){
		this->Map2D_obj[y][x] = 0;
		this->Wood++;
	}
	else if( _tmp == this->Kamien[0].ReturnImageID() or _tmp == this->Kamien[1].ReturnImageID() or _tmp == this->Kamien[2].ReturnImageID() ){
		this->Map2D_obj[y][x] = 0;
		this->Stone += 3;
	}
	else if( _tmp == this->Ognisko[0].ReturnImageID() or _tmp == this->Ognisko[1].ReturnImageID() or _tmp == this->Ognisko[2].ReturnImageID() ){
		this->Wood++;
		this->Stone++;
		this->Map2D_obj[y][x] = 0;
	}
	else if( _tmp == this->Jedzenie[0].ReturnImageID() or _tmp == this->Jedzenie[1].ReturnImageID() or _tmp == this->Jedzenie[2].ReturnImageID() ){
		this->Food += 3;
		this->Map2D_obj[y][x] = 0;
	}
	else{
		this->Map2D_obj[y][x] = 0;
	}
}

void Map::CutTree(){
	this->FindObject( this->Drzewo );
	if( ! this->Path.empty() ){
		this->Path.push_back( "1del" );
		this->Path.push_back( "1end" );
	}
}

void Map::DestroyStone(){
	this->FindObject( this->Kamien );
	if( ! this->Path.empty() ){
		this->Path.push_back( "1del" );
		this->Path.push_back( "1end" );
	}
}

void Map::FindFire(){
	this->FindObject( this->Ognisko );
	if( ! this->Path.empty() ){
		this->Path.push_back( "1end" );
	}
}

void Map::FindTree(){
	this->FindObject( this->Drzewo );
	if( ! this->Path.empty() ){
		this->Path.push_back( "1end" );
	}
}

void Map::FindStone(){
	this->FindObject( this->Kamien );
	if( ! this->Path.empty() ){
		this->Path.push_back( "1end" );
	}
}

void Map::FindObject( std::vector <Podloze> &target ){
	std::vector < std::vector <char> > _map;
	_map.resize( this->MaxRange );
	for( unsigned int i=0; i<this->MaxRange; i++ ){
		_map[i].resize( this->MaxRange );
		for( unsigned int j=0; j<this->MaxRange; j++ ){
			_map[i][j] = '0';
		}
	}
	unsigned int _halfsize ;
	int _tmp, _tmp_Player;
	double _double;
	_halfsize = this->MaxRange/2;
	int _int_halfsize = (int)_halfsize;
	int  _int1, _int2;
	_map[_halfsize][_halfsize] = 's';
	bool _exist = false;
	std::vector <Object> _tree;
	_tree.clear();
	for( unsigned int i=0; i<this->MaxRange; i++ ){
		for( unsigned int j=0; j<this->MaxRange; j++ ){
			_tmp = this->ReturnValueMapObj( this->PlayerX-_halfsize+j, this->PlayerY-_halfsize+i );
			_tmp_Player = this->ReturnValueMap( this->PlayerX-_halfsize+j, this->PlayerY-_halfsize+i );
			if( _map[i][j] == '0' ){
				for( unsigned int k=0; k<target.size(); k++ ){
					if(  _tmp == target[k].ReturnImageID() ){
						//_tree.push_back( Object( this->PlayerX-_halfsize+j, this->PlayerY-_halfsize+i, this->PlayerX+this->PlayerY ) );
						_int1 = _int_halfsize - j;
						_int1 *= _int1;
						_int2 = _int_halfsize - i;
						_int2 *= _int2;
						_double = sqrt( _int1 + _int2 );
						_tree.push_back( Object( this->PlayerX-_halfsize+j, this->PlayerY-_halfsize+i, _double ) );
						break;
					}
				}
				if( _tmp != 0 ){
					_map[i][j] = 'x';
				}
				else if( _tmp_Player == this->Pelne[0].ReturnImageID() ){
					_map[i][j] = 'x';
				}
			}
		}
	}

	if( _tree.size() > 0 ){
		std::vector <Object> _end;
		_end.push_back( _tree[0] );
		int _tmpX, _tmpY;
		for( unsigned int i=1; i<_tree.size(); i++ ){
			if( _tree[i].ReturnTMP() < _end[0].ReturnTMP() ){
				_tmpX = _halfsize+_tree[i].ReturnX()-this->PlayerX;
				_tmpY = _halfsize+_tree[i].ReturnY()-this->PlayerY;
				if( _map[_tmpY+1][_tmpX] != 'x' or _map[_tmpY-1][_tmpX] != 'x' or _map[_tmpY][_tmpX+1] != 'x' or _map[_tmpY][_tmpX-1] != 'x' ){
					_end[0] = _tree[i];
					_exist = true;
				}
			}
		}
		if( _exist ){
			_map[_halfsize+_end[0].ReturnY()-this->PlayerY][_halfsize+_end[0].ReturnX()-this->PlayerX] = 'f';
		}
		else{
			_tmpX = _halfsize+_end[0].ReturnX()-this->PlayerX;
			_tmpY = _halfsize+_end[0].ReturnY()-this->PlayerY;
			if( _map[_tmpY+1][_tmpX] != 'x' or _map[_tmpY-1][_tmpX] != 'x' or _map[_tmpY][_tmpX+1] != 'x' or _map[_tmpY][_tmpX-1] != 'x' ){
				_map[_halfsize+_end[0].ReturnY()-this->PlayerY][_halfsize+_end[0].ReturnX()-this->PlayerX] = 'f';
				_exist = true;
			}
		}
	}

	if( _exist ){
		this->FindPath( _map );
		if( this->Path.size() == 0  ){
			this->Answer = text_path_error;
			this->ToDeleteAnswer = true;
			this->TextOperation.clear();
		}
		this->PathBool = true;
	}
	else{
		this->Answer = text_path_error;
		this->ToDeleteAnswer = true;
		this->TextOperation.clear();
	}
}

void Map::FindPath( std::vector < std::vector <char> > &In ){
	unsigned int _time = SDL_GetTicks() + 15000;
	this->TextOperation.clear();
	this->Path.clear();
	int _halfsize = this->MaxRange/2;
	int _MaxRange = this->MaxRange;
	int _curentX = _halfsize, _curentY = _halfsize;
	Object _start( _curentY, _curentX );
	unsigned int _value = 1, _number_start = 0, _number_end = 4, _number_counter = 0;
	std::vector <Object> _list;
	_list.push_back( Object( _curentX+1, _curentY ) );
	_list.push_back( Object( _curentX-1, _curentY ) );
	_list.push_back( Object( _curentX, _curentY+1 ) );
	_list.push_back( Object( _curentX, _curentY-1 ) );

	while( ! _list.empty() ){
		_number_start++;
		_curentY = _list[0].ReturnY();
		_curentX = _list[0].ReturnX();
		if( In[_curentY][_curentX] == '0' ){
			In[_curentY][_curentX] = _value;
			_curentY++;
			if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
				if( In[_curentY][_curentX] == '0' ){
					_list.push_back( Object( _curentX, _curentY ) );
					_number_counter++;
				}
				_curentY--;
			}

			_curentY--;
			if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
				if( In[_curentY][_curentX] == '0' ){
					_list.push_back( Object( _curentX, _curentY ) );
					_number_counter++;
				}
				_curentY++;
			}

			_curentX++;
			if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
				if( In[_curentY][_curentX] == '0' ){
					_list.push_back( Object( _curentX, _curentY ) );
					_number_counter++;
				}
				_curentX--;
			}

			_curentX--;
			if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
				if( In[_curentY][_curentX] == '0' ){
					_list.push_back( Object( _curentX, _curentY ) );
					_number_counter++;
				}
				_curentX++;
			}
		}

		if( _list.size() > 0 ){
			_list.erase( _list.begin() );
		}

		if( _number_start == _number_end ){
			_number_start = 0;
			_number_end = _number_counter;
			_number_counter = 0;
			_value++;
		}
	}

	Object _Finish;
	bool _exist_Finish = false;
	for( unsigned int i=0; i<this->MaxRange; i++ ){
		for( unsigned int j=0; j<this->MaxRange; j++ ){
			if( In[i][j] == '0' ){
				In[i][j] = 'x';
			}
			else if( In[i][j] == 'f' ){
				_Finish.SetX(j);
				_Finish.SetY(i);
				_exist_Finish = true;
			}
		}
	}

	if( _exist_Finish ){
		if( In[_Finish.ReturnY()+1][_Finish.ReturnX()] == 'x' and In[_Finish.ReturnY()-1][_Finish.ReturnX()] == 'x' and In[_Finish.ReturnY()][_Finish.ReturnX()+1] == 'x' and In[_Finish.ReturnY()][_Finish.ReturnX()-1] == 'x' ){
			_exist_Finish = false;
		}
	}

	if( _exist_Finish ){
		_list.clear();
		_curentX = _Finish.ReturnX();
		_curentY = _Finish.ReturnY();
		//_Finish.SetTMP( 10000 );
		_Finish.SetTMP( (int) 'f' );
		while( In[_curentY][_curentX] != 's' ){
			_curentY++;
			if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
				if( (int)In[_curentY][_curentX] < _Finish.ReturnTMP() ){
					_Finish.SetX( _curentX );
					_Finish.SetY( _curentY );
					_Finish.SetTMP( (int)In[_curentY][_curentX] );
				}
				else if( In[_curentY][_curentX] == 's' ){
					break;
				}
			}
			_curentY--;
			_curentY--;
			if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
				if( (int)In[_curentY][_curentX] < _Finish.ReturnTMP() ){
					_Finish.SetX( _curentX );
					_Finish.SetY( _curentY );
					_Finish.SetTMP( (int)In[_curentY][_curentX] );
				}
				else if( In[_curentY][_curentX] == 's' ){
					break;
				}
			}
			_curentY++;
			_curentX++;
			if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
				if( (int)In[_curentY][_curentX] < _Finish.ReturnTMP() ){
					_Finish.SetX( _curentX );
					_Finish.SetY( _curentY );
					_Finish.SetTMP( (int)In[_curentY][_curentX] );
				}
				else if( In[_curentY][_curentX] == 's' ){
					break;
				}
			}
			_curentX--;
			_curentX--;
			if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
				if( (int)In[_curentY][_curentX] < _Finish.ReturnTMP() ){
					_Finish.SetX( _curentX );
					_Finish.SetY( _curentY );
					_Finish.SetTMP( (int)In[_curentY][_curentX] );
				}
				else if( In[_curentY][_curentX] == 's' ){
					break;
				}
			}
			_curentX++;
			_curentX = _Finish.ReturnX();
			_curentY = _Finish.ReturnY();
			_list.push_back( Object( _curentX, _curentY ) );
			In[_curentY][_curentX] = 'o';

			if( SDL_GetTicks() > _time ){
				this->Path.clear();
				return;
			}
		}

		//PATH
		_curentX = _halfsize;
		_curentY = _halfsize;
		int _tmp;
		for( std::vector <Object>::reverse_iterator it=_list.rbegin(); it!=_list.rend(); ++it ){
			if( it->ReturnX() == _curentX ){
				_tmp = it->ReturnY() - _curentY;
				if( _tmp > 0 ){
					if( this->PlayerDirection != 'd' ){
						this->Path.push_back("1td");
					}
					this->Path.push_back("1gd1");
				}
				else{
					if( this->PlayerDirection != 'u' ){
						this->Path.push_back("1tu");
					}
					this->Path.push_back("1gu1");
				}
			}
			else if( it->ReturnY() == _curentY ){
				_tmp = it->ReturnX() - _curentX;
				if( _tmp > 0 ){
					if( this->PlayerDirection != 'r' ){
						this->Path.push_back("1tr");
					}
					this->Path.push_back("1gr1");
				}
				else{
					if( this->PlayerDirection != 'l' ){
						this->Path.push_back("1tl");
					}
					this->Path.push_back("1gl1");
				}
			}
			_curentX = it->ReturnX();
			_curentY = it->ReturnY();
			if( SDL_GetTicks() > _time ){
				this->Path.clear();
				return;
			}
		}

		//TURN
		_curentY++;
		if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
			if( In[_curentY][_curentX] == 'f' ){
				this->Path.push_back( "1td" );
			}
			_curentY--;
		}

		_curentY--;
		if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
			if( In[_curentY][_curentX] == 'f' ){
				this->Path.push_back( "1tu" );
			}
			_curentY++;
		}

		_curentX++;
		if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
			if( In[_curentY][_curentX] == 'f' ){
				this->Path.push_back( "1tr" );
			}
			_curentX--;
		}

		_curentX--;
		if( _curentX >= 0 and _curentX < _MaxRange and _curentY >= 0 and _curentY < _MaxRange ){
			if( In[_curentY][_curentX] == 'f' ){
				this->Path.push_back( "1tl" );
			}
			_curentX++;
		}
	}

	//LOG
	/*
	LogGame::Write( "\n" );
	for( std::vector<std::string>::iterator it=this->Path.begin(); it!=this->Path.end(); ++it ){
		LogGame::Write( *it );
		LogGame::Write( " " );
	}
	LogGame::Write( "\n" );
	for( unsigned int i=0; i<this->MaxRange; i++ ){
		for( unsigned int j=0; j<this->MaxRange; j++ ){
			if( In[i][j] != '0' and In[i][j] != 'x' and In[i][j] != 'f' and In[i][j] != 's' and  In[i][j] != 'o' ){
				LogGame::Write( (int)In[i][j] );
				LogGame::Write( "\t" );
			}
			else{
				LogGame::Write( In[i][j] );
				LogGame::Write( "\t" );
			}
		}
		LogGame::Write( "\n" );
	}
	*/
}

unsigned int Map::ReturnHungry(){
	if( this->Hungry == 0 ){
		return 0;
	}
	else if( this->Hungry >= 1 and this->Hungry <= 3 ){
		//1-3
		return 0;
	}
	else if( this->Hungry >= 4 and this->Hungry <= 6 ){
		//4-6
		return 1;
	}
	else if( this->Hungry >= 7 and this->Hungry <= 9 ){
		//7-9
		return 2;
	}
	else{
		if( this->Hungry > 9 or this->Hungry < 0 ){
			this->Hungry = 9;
		}
		return 2;
	}
	return 0;
}

void Map::StartFire(){
	if( this->PlayerDirection == 'r' ){
		if( this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][PlayerX+1] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'r';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'l';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'd';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj(this->PlayerX, this->PlayerY+1 ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'u';
			this->Answer = text_done;
		}
		else{
			this->Answer = text_dont_know;
		}
	}
	else if( this->PlayerDirection == 'l' ){
		if( this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'l';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][PlayerX+1] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'r';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'd';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj(this->PlayerX, this->PlayerY+1 ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'u';
			this->Answer = text_done;
		}
		else{
			this->Answer = text_dont_know;
		}
	}
	else if( this->PlayerDirection == 'u' ){
		if( this->ReturnValueMapObj(this->PlayerX, this->PlayerY+1 ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'u';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'd';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'l';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][PlayerX+1] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'r';
			this->Answer = text_done;
		}
		else{
			this->Answer = text_dont_know;
		}
	}
	else if( this->PlayerDirection == 'd' ){
		if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'd';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj(this->PlayerX, this->PlayerY+1 ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'u';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'l';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[0].ReturnImageID() or this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[2].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][PlayerX+1] = this->Ognisko[1].ReturnImageID();
			this->PlayerDirection = 'r';
			this->Answer = text_done;
		}
		else{
			this->Answer = text_dont_know;
		}
	}
	else{
		this->Answer = text_dont_know;
	}

}

void Map::StopFire(){
	if( this->PlayerDirection == 'r' ){
		if( this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX+1] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'r';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'l';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'u';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'd';
			this->Answer = text_done;
		}
		else{
			this->Answer = text_dont_know;
		}
	}
	else if( this->PlayerDirection == 'l' ){
		if( this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'l';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX+1] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'r';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'u';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'd';
			this->Answer = text_done;
		}
		else{
			this->Answer = text_dont_know;
		}
	}
	else if( this->PlayerDirection == 'u' ){
		if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'u';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'd';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX+1] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'r';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'l';
			this->Answer = text_done;
		}
		else{
			this->Answer = text_dont_know;
		}
	}
	else if( this->PlayerDirection == 'd' ){
		if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY-1 ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY-1][this->PlayerX] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'd';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX, this->PlayerY+1 ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY+1][this->PlayerX] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'u';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX+1, this->PlayerY ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX+1] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'r';
			this->Answer = text_done;
		}
		else if( this->ReturnValueMapObj( this->PlayerX-1, this->PlayerY ) == this->Ognisko[1].ReturnImageID() ){
			this->Map2D_obj[this->PlayerY][this->PlayerX-1] = this->Ognisko[2].ReturnImageID();
			this->PlayerDirection = 'l';
			this->Answer = text_done;
		}
		else{
			this->Answer = text_dont_know;
		}
	}
	else{
		this->Answer = text_dont_know;
	}
}

void Map::DestoryFood(){
	this->FindObject( this->Jedzenie );
	if( ! this->Path.empty() ){
		this->Path.push_back( "1del" );
		this->Path.push_back( "1end" );
	}
}

void Map::FindFood(){
	this->FindObject( this->Jedzenie );
	if( ! this->Path.empty() ){
		this->Path.push_back( "1end" );
	}
}

void Map::Eat(){
	if( this->Food > 0 ){
		if( this->Hungry == 9 ){
			this->Answer = text_hungry_full;
		}
		else if( ( 9 - this->Hungry ) <= this->Food ){
			this->Food = 9 - this->Hungry;
			this->Hungry = 9;
			this->Answer = text_hungry_eat;
		}
		else{
			this->Hungry += this->Food;
			this->Food = 0;
			this->Answer = text_hungry_eat;
		}
	}
	else{
		this->Answer = text_hungry_not;
	}
}

void Map::MinusHungry(){
	if( this->Hungry > 0 ){
		this->Hungry--;
	}
}
