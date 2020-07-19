#ifndef APPLICATION_H
#define APPLICATION_H 
#include "Command.h" 
#include "Parser.h" 

class Application
{
public:
	void registerCommand(std::unique_ptr<Command> command);
	int execute(int argc, char *argv[]);
private:
	std::map<std::string, std::unique_ptr<Command>> commands_;
};

#endif // APPLICATION_H