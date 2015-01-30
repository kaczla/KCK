#include "bot.hpp"

void cTestAppCallbacks::onAimlLoad(const std::string& filename) {
	LogGame::Write( "[LOG] " );
	LogGame::Write( "AIML - Załadowano: " );
	LogGame::Write( filename );
	LogGame::NewLine();
}

Bot::Bot(){
	this->Init = false;
	this->interpreter = NULL;
	this->Answer.clear();
}

Bot::~Bot(){
	delete this->interpreter;
}

bool Bot::InitBot(){
	this->interpreter = cInterpreter::newInterpreter();
	cTestAppCallbacks myCallbacks;
	this->interpreter->registerCallbacks( &myCallbacks );
	LogGame::Write( "[LOG] " );
	LogGame::Write( "AIML - Inicjalizowanie\n" );
	if ( ! this->interpreter->initialize( "libaiml.xml" ) ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( "AIML - Brak plików potrzebych do inicjalizacji!\n" );
		return false;
	}
	else{
		LogGame::Write( "[LOG] " );
		LogGame::Write( "AIML - Inicjalizacja przebiegła pomyślnie\n" );
		this->Init = true;
	}
	/*
	this->Init = this->InitSynonym();
	*/
	return true;
}

std::string Bot::ReturnAnswer( std::string text ){
	if( text.size() > 0 ){
		if( ! this->interpreter->respond( text, "localhost", this->Answer ) ){
			LogGame::Write( "[ERR] " );
			LogGame::Write( "AIML - Błąd: interpreter->respond( text, \"localhost\", this->Answer )\n" );
		}
	}
	return this->Answer;
}

std::string Bot::ReturnAnswer( u16string text ){
	for( unsigned int i=0; i<text.size(); i++ ){
		switch( text[i] ){
		case 0x104:
			text[i] = 'A';
			break;
		case 0x15A:
			text[i] = 'S';
			break;
		case 0x106:
			text[i] = 'C';
			break;
		case 0x118:
			text[i] = 'E';
			break;
		case 0xD3:
			text[i] = 'O';
			break;
		case 0x141:
			text[i] = 'L';
			break;
		case 0x143:
			text[i] = 'N';
			break;
		case 0x17B:
			text[i] = 'Z';
			break;
		case 0x179:
			text[i] = 'Z';
			break;
		case 0x105:
			text[i] = 'a';
			break;
		case 0x15B:
			text[i] = 's';
			break;
		case 0x107:
			text[i] = 'c';
			break;
		case 0x119:
			text[i] = 'e';
			break;
		case 0xF3:
			text[i] = 'o';
			break;
		case 0x142:
			text[i] = 'l';
			break;
		case 0x144:
			text[i] = 'n';
			break;
		case 0x17C:
			text[i] = 'z';
			break;
		case 0x17A:
			text[i] = 'z';
			break;
		default:
			break;
		}
	}
	std::string tmp_text ( text.begin(), text.end() );
	return this->ReturnAnswer( tmp_text );
}

/*
//SYNONIMS
bool Bot::InitSynonym(){
	xmlDoc *file = NULL;
	file = xmlParseFile( "synonim.xml" );
	if( file == NULL ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( "AIML - Problem z plikiem synonim.xml\n" );
		return false;
	}
	else{
		xmlNode *Root = NULL;
		Root = xmlDocGetRootElement( file );
		if( Root == NULL ){
			LogGame::Write( "[ERR] " );
			LogGame::Write( "AIML - Brak korzenia dla pliku synonim.xml\n" );
			return false;
		}
		unsigned int check = 0;
		std::string value1, value2;
		const xmlChar *var1 = (unsigned char*)"nazwa", *var2 = (unsigned char*)"synonim";
		for( xmlNode *Node = Root->children; Node; Node = Node->next ){
			if( Node->type == XML_ELEMENT_NODE ){
				check = 0;
				for( xmlNode *NodeChildren = Node->children; NodeChildren; NodeChildren = NodeChildren->next ){
					if( NodeChildren->type == XML_ELEMENT_NODE ){
						if( xmlStrEqual(NodeChildren->name,  var1 ) == 1 ){
							value1 = (char*) NodeChildren->children->content;
							check++;
						}
						else if( xmlStrEqual( NodeChildren->name, var2 ) == 1 ){
							value2 = (char*)NodeChildren->children->content;
							check++;
						}
					}
				}
				if( check == 2 ){
					this->Synonym[value1] = value2;
				}
			}
		}
		LogGame::Write( "[LOG] " );
		LogGame::Write( "AIML - Wczytano synonimy z pliku synonim.xml\n[LOG] AIML - Ilość wczytanych synonimów: " );
		LogGame::Write( this->Synonym.size() );
		LogGame::NewLine();
		xmlFreeDoc( file );
	}
	xmlCleanupParser();
	return true;
}

void Bot::LogSynonym(){
	for( std::map< std::string, std::string >::iterator it = this->Synonym.begin(); it != this->Synonym.end(); it++ ){
		//std::cout<<it->first<<" = "<<it->second<<"\n";
		LogGame::Write( it->first );
		LogGame::Write( " = " );
		LogGame::Write( it->second );
		LogGame::NewLine();
	}
}

FILE SYNONIM.XML
<root>
	<wyraz>
		<nazwa>drzewko</nazwa>
		<synonim>drzewo</synonim>
	</wyraz>
	<wyraz>
		<nazwa>tree</nazwa>
		<synonim>drzewo</synonim>
	</wyraz>
	<wyraz>
		<nazwa>drzew</nazwa>
		<synonim>drzewo</synonim>
	</wyraz>
</root>

*/


