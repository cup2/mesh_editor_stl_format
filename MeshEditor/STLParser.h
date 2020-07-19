#ifndef STLPARSER_H
#define STLPARSER_H
#include <vector> 
#include <string> 
#include <fstream>
#include <sstream>
#include <exception>
#include <map> 

struct Vec { double x, y, z; };

struct Vertex
{
	Vec pos;
	Vec normal;
};

using TriangleSoup = std::vector<Vertex>;

class STLParser
{
public:
	TriangleSoup read(const std::string& filename);
	void write(const TriangleSoup& triangleSoup, const std::string& filename);
private:
	const std::string solidText_ = "solid";
	const std::string endSolidText_ = "endsolid";
	const std::string startFacetText_ = "facet";
	const std::string endFacetText_ = "endfacet";
	const std::string startLoopText_ = "outer loop";
	const std::string endLoopText_ = "endloop";
	const std::string normalText_ = "normal";
	const std::string startVertexText_ = "vertex";

	enum class TypeLine: unsigned int { 
		Solid = 1,
		Loopbegin = 2, 
		Facet = 4,
		Vertex = 8,
		Loopend = 16, 
		EndFacet = 32, 
		EndSolid = 64, 
	};
	typedef std::underlying_type<TypeLine>::type TypeLineUnder;

	const std::map<std::string, TypeLine> TypeForStlString = {
		{startFacetText_, TypeLine::Facet},
		{solidText_,TypeLine::Solid},
		{startVertexText_,TypeLine::Vertex},
		{endLoopText_,TypeLine::Loopend},
		{endFacetText_,TypeLine::EndFacet},
		{startLoopText_,TypeLine::Loopbegin},
		{endSolidText_,TypeLine::EndSolid},
	};

	Vec parseVertex(const std::string& stringVertex);
	TypeLine determineString(const std::string& stringstl);	
	friend TypeLineUnder operator | (const TypeLine& first, const TypeLine& second);
	friend bool operator & (const TypeLine& first, const TypeLineUnder& second);
	class invalidFileExeption : public std::exception {};
};

#endif // STLPARSER_H