#include "Cube.h"
#include <iostream>

const std::string &Cube::getName() const { return name_; };

int Cube::execute(const std::map<std::string, std::string> &args,
                  STLParser &y) {
  std::string filepath;
  double length = 0.0;
  Vec origin;
  try {
    getArgument(args, fileKeyName_, filepath);
    getArgument(args, lengthKeyName_, length);
    getArgument(args, originKeyName_, origin);
  } catch (std::out_of_range &e) {
    return 3;
  } catch (std::logic_error &e) {
    return 2;
  }
  TriangleSoup cube;
  cube = buildCube(length, origin);
  y.read("ssss");
  setNormal(cube);
  std::cout << "debug info1";
  y.write(cube, filepath);
  return 0;
};

int Cube::execute(const std::map<std::string, std::string> &args) {
  std::string filepath;
  double length = 0.0;
  Vec origin;
  try {
    getArgument(args, fileKeyName_, filepath);
    getArgument(args, lengthKeyName_, length);
    getArgument(args, originKeyName_, origin);
  } catch (std::out_of_range &e) {
    return 3;
  } catch (std::logic_error &e) {
    return 2;
  }
  TriangleSoup cube;
  cube = buildCube(length, origin);
  STLParser y;
  y.read("ssss");
  setNormal(cube);
  std::cout << "debug info1";
  y.write(cube, filepath);
  return 0;
};
TriangleSoup Cube::buildCube(const double &length, const Vec &origin) {
  TriangleSoup vertices;
  Vec vertex;
  for (int i = 0; i < 8; i++) {
    vertex.x = ((i & 4) >> 2) * length + origin.x;
    vertex.y = ((i & 2) >> 1) * length + origin.y;
    vertex.z = (i & 1) * length + origin.z;
    vertices.push_back({vertex, {}});
  }
  const int verticesTriangles[36] = {
      0, 1, 2, 1, 3, 2, 4, 6, 5, 5, 6, 7, 5, 1, 0, 0, 4, 5,
      6, 2, 7, 2, 3, 7, 2, 4, 0, 4, 2, 6, 3, 1, 5, 3, 5, 7,
  };
  TriangleSoup cube;
  for (auto it : verticesTriangles) {
    cube.push_back(vertices[it]);
  }
  return cube;
};
