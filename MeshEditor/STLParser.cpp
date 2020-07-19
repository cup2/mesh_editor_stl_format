#include "STLparser.h"

bool operator & (const STLParser::TypeLine& first, const STLParser::TypeLineUnder& second) {
	return static_cast<bool>(static_cast<int>(first) & static_cast<int>(second));
};

STLParser::TypeLineUnder operator | (const STLParser::TypeLine& first, const STLParser::TypeLine& second) {
	return static_cast<STLParser::TypeLineUnder>(first) | static_cast<STLParser::TypeLineUnder>(second);
};

std::ostream & operator<<(std::ostream& fout, Vec vec) {
	fout << " " << std::to_string(vec.x) << " " + std::to_string(vec.y) << " " << std::to_string(vec.z);
	return fout;
};

void STLParser::write(const TriangleSoup& triangleSoup, const std::string& filename) {
	std::ofstream stlout;
	stlout.open(filename, std::ios::trunc);
	int counterVertices = 0;
	if (stlout.is_open()) {
		stlout << solidText_ + " " << std::endl;
		for (const auto& it : triangleSoup) {
			if (counterVertices % 3==0) {
				if (counterVertices != 0) {
					stlout << endLoopText_ << std::endl << endFacetText_<<std::endl;
				}
				stlout << startFacetText_ + " " + normalText_ + " " << it.normal << std::endl;
				stlout << startLoopText_ << std::endl;
			}	
			stlout << startVertexText_ << it.pos<<std::endl;
			counterVertices++;
		}
		stlout << endLoopText_ << std::endl << endFacetText_ << std::endl;
		stlout << endSolidText_;
	}
};

TriangleSoup STLParser::read(const std::string& filename) {
	std::ifstream stlin(filename.c_str());
	TriangleSoup buffTriangles;
	STLParser::TypeLine currentLine;
	auto needLine = static_cast<TypeLineUnder>(TypeLine::Solid);
	std::string buffString;
	int counterVertices = 0;

	try {
		while (std::getline(stlin, buffString)) {
			if (buffString.length() == 0) {
				continue;
			}
			currentLine = determineString(buffString);
			if (!(currentLine & needLine)) {
				throw invalidFileExeption();
			} 
			switch (currentLine) {
				case TypeLine::Solid:
					needLine = TypeLine::EndSolid | TypeLine::Facet;
					break;
				case TypeLine::Facet:
					needLine = static_cast<TypeLineUnder>(TypeLine::Loopbegin);
					break;
				case TypeLine::Loopbegin:
					needLine = static_cast<TypeLineUnder>(TypeLine::Vertex);
					break;
				case TypeLine::Vertex:
					if (counterVertices == 2) {
						needLine = static_cast<TypeLineUnder>(TypeLine::Loopend);
						buffTriangles.push_back({ parseVertex(buffString), {} });
						counterVertices = 0;
					}
					else if (counterVertices < 2) {
						needLine = static_cast<TypeLineUnder>(TypeLine::Vertex);
						counterVertices++;
						buffTriangles.push_back({ parseVertex(buffString), {} });
					}
					break;
				case TypeLine::EndFacet:
					needLine = TypeLine::EndSolid | TypeLine::Facet;
					break;
				case TypeLine::Loopend:
					needLine = static_cast<TypeLineUnder>(TypeLine::EndFacet);
					break;
				case TypeLine::EndSolid:
					needLine = static_cast<TypeLineUnder>(TypeLine::Solid);
					break;
				default:
					throw invalidFileExeption();
			}
		}
	}
	catch (invalidFileExeption& e) {
		return {};
	}
	return buffTriangles;
};

Vec  STLParser::parseVertex(const std::string& stringVertex) {
	double vertex[3];
	std::stringstream parsstl;
	parsstl << stringVertex;
	parsstl.ignore(startVertexText_.size(),' ');
	double cord;
	for (int i = 0; i < 3; i++) {
		if (parsstl.good()) {
			double cord;
			parsstl >> cord;
			vertex[i]=cord;
		}
		else {
			throw invalidFileExeption();
		}
	}
	return { vertex[0], vertex[1], vertex[2] };
}

STLParser::TypeLine STLParser::determineString(const std::string& stlString) {
	std::stringstream parsstl;
	std::string checkWord;
	parsstl << stlString;
	parsstl >> checkWord;
	auto it = TypeForStlString.find(checkWord);
	if (it != TypeForStlString.end()) {
		return it->second;
	}
	it = TypeForStlString.find(stlString);

	if (it != TypeForStlString.end()) { 
		return it->second;
	};
	throw invalidFileExeption();
}