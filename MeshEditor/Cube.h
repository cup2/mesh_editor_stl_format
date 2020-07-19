#ifndef CUBE_H
#define CUBE_H
#include "Command.h" 

class Cube : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:
	const std::string name_ = "Cube";
	const std::string lengthKeyName_="L";
	const std::string fileKeyName_ = "filepath";
	const std::string originKeyName_ = "origin";
	TriangleSoup buildCube(const double& length, const Vec& origin);
};

#endif // CUBE_H
