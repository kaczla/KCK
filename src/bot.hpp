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

typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;

class cTestAppCallbacks : public cInterpreterCallbacks {
  public:
	void onAimlLoad(const std::string& filename);
};


class Bot{
public:
	Bot();
	~Bot();
	bool InitBot();
	std::string ReturnAnswer( std::string text );
	std::string ReturnAnswer( u16string text );
private:
	bool Init;
	cInterpreter *interpreter;
	std::string Answer;
};



#endif
