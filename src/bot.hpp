#ifndef BOT_HPP_
#define BOT_HPP_
#include <std_utils/std_util.h>
#include <fstream>
#include <iostream>
#include "aiml/aiml.h"
#include "log_game.hpp"
//using namespace std;
using std_util::strip;
using namespace aiml;

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
private:
	bool Init;
	cInterpreter *interpreter;
	std::string Answer;
};



#endif
