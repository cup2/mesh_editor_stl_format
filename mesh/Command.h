#ifndef COMMAND_H
#define COMMAND_H
#include "STLParser.h"
#include <cmath>
#include <exception>
#include <map>
#include <sstream>
#include <string>
#include <vector>
class Command {
public:
  virtual ~Command() {}
  virtual const std::string &getName() const = 0;
  virtual int execute(const std::map<std::string, std::string> &args) = 0;
  virtual int execute(const std::map<std::string, std::string> &args,
                      STLParser &y){};

protected:
  void setNormal(TriangleSoup &triangleSoup);
  Vec convertToVec(const std::string &dot);
  Vec getNormal(const Vec &dot1, const Vec &dot2, const Vec &dot3);
  Vec getVector(const Vec &start, const Vec &end);
  void getArgument(const std::map<std::string, std::string> &args,
                   const std::string &keyName, Vec &value);
  void getArgument(const std::map<std::string, std::string> &args,
                   const std::string &keyName, double &value);
  void getArgument(const std::map<std::string, std::string> &args,
                   const std::string &keyName, std::string &value);
};

#endif // COMMAND_H
