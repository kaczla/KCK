#ifndef BOT_HPP_
#define BOT_HPP_
//#include <fstream>
#include <iostream>
#include <std_utils/std_util.h>
#include "aiml/aiml.h"
#include "log_game.hpp"
#include "include_SDL_ttf.hpp"
using std_util::strip;
using namespace aiml;

// Uint16 text
typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;

/**
 * Wyświetlenie wczytywanych plików
 */
class cTestAppCallbacks : public cInterpreterCallbacks {
  public:
	/**
	 *Wczytuje plik o podanej nazwie
	 * @param filename - nazwa wczytywanego pliku
	 */
	void onAimlLoad(const std::string& filename);
};

/**

Plik bot.hpp:

Umożliwia uruchomienie AIML.

Za inicjalizacje AIML odpowiada metoda:

InitBot() - zwraca false w razie błędu

Wprowadzanie pytań do AIML umożliwiają metody, które zwracają string jako odpowiedź:

ReturnAnswer( std::string text ) - pytanie jako string

ReturnAnswer( u16string text ) - pytanie jako u16string ( UTF16 )

 */
class Bot{
public:
	Bot();
	~Bot();
	/**
	 * Inicjalizowanie AIML
	 * @return - kod błędu
	 */
	bool InitBot();
	/**
	 * Przetwarza zadane pytanie jako argument do postaci odpowiedzi
	 * @param text - tekst pytania
	 * @return odpowiedź na pytanie
	 */
	std::string ReturnAnswer( std::string text );
	/**
	 * Przetwarza zadane pytanie jako argument do postaci odpowiedzi
	 * @param text - tekst pytania (utf16)
	 * @return odpowiedź na pytanie
	 */
	std::string ReturnAnswer( u16string text );
private:
	bool Init;
	cInterpreter *interpreter;
	std::string Answer;
};



#endif
