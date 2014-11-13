#include "map.hpp"

Map::Map(){
	this->Width = 50;
	this->Height = 50;
	this->Success = false;
	//this->SetVector();
}

Map::Map(int height, int width){
	this->Width = width;
	this->Height = height;
	this->Success = false;
	this->SetVector();
}

bool Map::ReturnSuccess(){
	return this->Success;
}

void Map::SetValue(int height, int width){
	this->Width = width;
	this->Height = height;
	this->SetVector();
	//RAND
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

	//Obj
	this->Success = true;
}

int Map::ReturnValueMap(int x, int y){
	//std::cout<<"map x="<<x<<" y="<<y<<" :"<<this->Map2D[x][y]<<"\n";
	if( x<0 or x>=this->Width ){
		return 0;
	}
	else if( y<0 or y>=this->Height ){
		return 0;
	}
	else{
		return this->Map2D[x][y];
	}
}

int Map::ReturnValueMapObj(int x, int y){
	return this->Map2D_obj[x][y];
}

void Map::SaveToFile(){
	/*for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			std::cout<<this->Map2D[i][j]<<" ";
		}
		std::cout<<"\n";
	}*/
	for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			std::cout<<this->Map2D_obj[i][j]<<" ";
		}
		std::cout<<"\n";
	}
}

void Map::SetVector(){
	this->Map2D.resize(this->Height);
	//this->map.clear();
	for( int i=0; i<this->Height; i++){
		this->Map2D[i].resize(this->Width);
		//this->map[i].clear();
	}
	this->Map2D_obj.resize(this->Height);
	for( int i=0; i<this->Height; i++){
		this->Map2D_obj[i].resize(this->Width);
	}
	for( int i=0; i<this->Height; i++ ){
		for( int j=0; j<this->Width; j++ ){
			this->Map2D_obj[i][j] = rand()%2+6;
		}
	}
}

Map::~Map(){
}




