#include "Application.h"

void Application::registerCommand(std::unique_ptr<Command> command) {
	commands_[command->getName()]=std::move(command);
};

int Application::execute(int argc, char *argv[]) {
	if(argc==1){
		return 4;
	}
	std::map<std::string, std::string> parsed_text;
	parsed_text = Parser::parseArgv(argc, argv);
	auto it = commands_.find(parsed_text.at("Command"));
	if (it == commands_.end()) {
		return 4;
	}
	else {
		return !it->second ? 3 : it->second->execute(parsed_text);
	}
};