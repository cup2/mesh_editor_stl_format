#ifndef APPLICATION_H
#define APPLICATION_H
#include "Command.h"
#include "Parser.h"
#include <cmath>
#include <map>
#include <memory> // для std::unique_ptr
#include <string>
#include <vector>
class Application {
public:
  void registerCommand(std::unique_ptr<Command> command);
  int execute(int argc, char *argv[]);

private:
  std::map<std::string, std::unique_ptr<Command>> commands_;
};

#endif // APPLICATION_H
