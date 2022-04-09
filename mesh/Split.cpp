#include "Split.h"

const std::string& Split::getName()const {
	return this->name_;
};

int Split::execute(const std::map<std::string, std::string>& args) {
	Vec direction;
	Vec origin;	
	std::string inputFile;
	std::string outputFile1;
	std::string outputFile2;
	try {
		getArgument(args, directionKeyName_, direction);
		getArgument(args, originKeyName_, origin);
		getArgument(args, inputFileKeyName_, inputFile);
		getArgument(args, output1FileKeyName_, outputFile1);
		getArgument(args, output2FileKeyName_, outputFile2);
	}
	catch (std::out_of_range& e) {
		return 3;
	}
	catch (std::logic_error& e) {
		return 2;
	}
	STLParser stlReader;
	TriangleSoup splitFigures;
	splitFigures = stlReader.read(inputFile);
	setNormal(splitFigures);
	return buildSplit(splitFigures, origin, direction, outputFile1, outputFile2);
};

int Split::buildSplit(const TriangleSoup& figure, const Vec& origin, const Vec& direction, const std::string& outputfile1, const std::string& outputfile2){
	std::vector<double> canonPlane = findCanonPlane(origin, direction);
	TriangleSoup splitFigures[2];
	TriangleSoup triangle;
	bool isOnOneSide=true;
	int countVertex = 0;
	int side=0;
	for (const auto& it : figure) {		
		int numberFigure = checkIsDotHigher(canonPlane, it.pos);
		splitFigures[numberFigure].push_back(it);
		triangle.push_back(it);
		isOnOneSide = (countVertex==0 || side == numberFigure ) ? isOnOneSide : false;
		side = checkIsDotHigher(canonPlane, it.pos);
		countVertex++;		
		if (countVertex==3 && !isOnOneSide) {
			int counterDot = 0;
			Vec intersectionPoint1;
			Vec intersectionPoint2;
			if (findIntersection(triangle[0].pos, triangle[1].pos, canonPlane, intersectionPoint1)) {
				if (!findIntersection(triangle[1].pos, triangle[2].pos, canonPlane, intersectionPoint2)) {
					findIntersection(triangle[2].pos, triangle[0].pos, canonPlane, intersectionPoint2);
				}
			}
			else {
				findIntersection(triangle[2].pos, triangle[0].pos, canonPlane, intersectionPoint1);
				findIntersection(triangle[1].pos, triangle[2].pos, canonPlane, intersectionPoint2);
			}		
			numberFigure = ((splitFigures[0].size() + 2) % 3 == 0) ? 1 : 0;
			Vertex point = splitFigures[numberFigure].back();
			splitFigures[0].push_back({ intersectionPoint1,{} });
			splitFigures[0].push_back({ intersectionPoint2,{} });
			splitFigures[1].push_back({ intersectionPoint1,{} });
			splitFigures[1].push_back({ intersectionPoint2,{} });
			splitFigures[numberFigure].push_back({ intersectionPoint1,{} });
			splitFigures[numberFigure].push_back(point);
		}
		if (countVertex == 3) {
			triangle.clear();
			isOnOneSide = true;
			countVertex = 0;
		}
	}
	if (splitFigures[0].size() == 0 || splitFigures[1].size() == 0) {
		return 4;
	}
	setNormal(splitFigures[0]);
	setNormal(splitFigures[1]);
	STLParser stlWriter;
	stlWriter.write(splitFigures[0], outputfile1);
	stlWriter.write(splitFigures[1], outputfile2);
	return 0;
}

int Split::checkIsDotHigher(const std::vector<double>& planeCanon, const Vec& dot) {
	return planeCanon[0] * dot.x + planeCanon[1] * dot.y + planeCanon[2] * dot.z + planeCanon[3] > 0.0;
}

std::vector<double>  Split::findCanonPlane(const Vec& origin,const Vec& direction) {
	std::vector<double> plane;
	plane.push_back(direction.x);
	plane.push_back(direction.y);
	plane.push_back(direction.z);
	plane.push_back(-(plane[0] * origin.x + plane[1] + origin.y + plane[2] * origin.z));
	return plane;
}

int Split::findIntersection(const Vec& start,const Vec& end, const std::vector<double>& planeCanon, Vec& intersectionPoint) {
	double m = end.x - start.x;
	double n = end.y - start.y;
	double p = end.z - start.z;
	if (planeCanon[0] * m + planeCanon[1] * n + planeCanon[2] * p + planeCanon[3] != 0) {
		double t = (-planeCanon[0] * start.x - planeCanon[1] * start.y - planeCanon[2] * start.z - planeCanon[3]) / (planeCanon[0] * m + planeCanon[1] * n + planeCanon[2] * p);
		if (checkIsBetween(start, end, { start.x + m * t, start.y + n * t,start.z + p * t })) {
			intersectionPoint = { start.x + m * t, start.y + n * t,start.z + p * t };
			return 1;
		}
	}
	return 0;
}

bool Split::checkIsBetween(const Vec &first, const Vec &second, const Vec &checkDot) {
	if (!(first.x <= checkDot.x && checkDot.x <= second.x || second.x <= checkDot.x && checkDot.x <= first.x)) {
		return false;
	}
	if (!(first.y <= checkDot.y && checkDot.y <= second.y || second.y <= checkDot.y && checkDot.y <= first.y)) {
		return false;
	}
	if (!(first.z <= checkDot.z && checkDot.z <= second.z || second.z <= checkDot.z && checkDot.z <= first.z)) {
		return false;
	}
	return true;
}