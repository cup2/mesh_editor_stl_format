#include "Sphere.h"

const std::string& Sphere::getName()const {
	return name_;
};

int Sphere::execute(const std::map<std::string, std::string>& args) {	
	double radius;
	Vec origin;
	std::string filepath;
	try {
		getArgument(args, fileKeyName_, filepath);
		getArgument(args, radiusKeyName_, radius);
		getArgument(args, originKeyName_, origin);
	}
	catch (std::out_of_range& e) {
		return 3;
	}
	catch (std::logic_error& e) {
		return 2;
	}
	TriangleSoup sphere = buildSphere(radius, origin);
	setNormal(sphere);
	STLParser stlWriter;
	stlWriter.write(sphere, filepath);
	return 0;
}

Vec Sphere::findVertexSphere(const double& lo, const double& la, const double& radius, const Vec& origin) {
	Vec vertex;
	vertex.x = origin.x + radius * sin(la)*cos(lo);
	vertex.y = origin.y + radius * sin(la)*sin(lo);
	vertex.z = origin.z + radius * cos(la);
	return vertex;
}

TriangleSoup Sphere::buildSphere(const double& radius,const Vec& origin) {
	const double PI = 3.1415926;
	const double endLo = 2 * PI;
	const double endLa = PI;
	const double resolution = 200;
	const double stepLo = endLo / (resolution);
	const double stepLa = endLa / (resolution);
	TriangleSoup sphere;
	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
			double currentLa = j * stepLa;
			double currentLo = i * stepLo;
			double nextLo = ((i + 1) == resolution) ? endLo : (i + 1) * stepLo;
			double nextLa = ((j + 1) == resolution) ? endLa : (j + 1) * stepLa;
			Vec vec1 = findVertexSphere(currentLa, currentLo, radius, origin);
			Vec vec2 = findVertexSphere(nextLa, currentLo, radius, origin);
			Vec vec3 = findVertexSphere(currentLa, nextLo, radius, origin);
			Vec vec4 = findVertexSphere(nextLa, nextLo, radius, origin);
			if (i < resolution / 2) {
				if (i != 0) {
					sphere.push_back({ vec1,{} });
					sphere.push_back({ vec3,{} });
					sphere.push_back({ vec2,{} });
				}
				if (i + 1 != resolution / 2) {
					sphere.push_back({ vec4,{} });
					sphere.push_back({ vec2,{} });
					sphere.push_back({ vec3,{} });
				}
			}
			else {
				if (i != resolution / 2) {
					sphere.push_back({ vec2,{} });
					sphere.push_back({ vec3,{} });
					sphere.push_back({ vec1,{} });
				}
				if (i + 1 != resolution) {
					sphere.push_back({ vec3,{} });
					sphere.push_back({ vec2,{} });
					sphere.push_back({ vec4,{} });
				}
			}
		}
	}
	return sphere;
}