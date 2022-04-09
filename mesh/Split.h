#ifndef SPLIT_H
#define SPLIT_H
#include "Command.h" 

class Split : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:
	const std::string name_ = "Split";
	const std::string directionKeyName_ = "direction";
	const std::string inputFileKeyName_ = "input";
	const std::string output1FileKeyName_ = "output1";
	const std::string output2FileKeyName_ = "output2";
	const std::string originKeyName_ = "origin";
	int buildSplit(const TriangleSoup& figure, const Vec& origin, const Vec& direction, const std::string& outputfile1, const std::string& outputfile2);
	int findIntersection(const Vec& start,const Vec& end, const std::vector<double>& planeCanon, Vec& intersectionPoint);
	bool checkIsBetween(const Vec& first, const Vec& second, const Vec& checkDot);
	std::vector<double> findCanonPlane(const Vec& origin,const Vec& direction);
	int checkIsDotHigher(const std::vector<double>& planeCanon, const Vec& dot);
	int checkClock(const Vec& a, const Vec& b, const Vec& c);
};

#endif //SPLIT_H