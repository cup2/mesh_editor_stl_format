#include "Command.h"

void Command::setNormal(TriangleSoup &triangleSoup) {
  Vec normal = {0, 0, 0};
  int nTriangle = triangleSoup.size() / 3;
  int counterTriangles = 0;
  int counterVertices = 0;
  if (nTriangle > 0) {
    for (auto it = triangleSoup.begin(); it < triangleSoup.end(); ++it) {
      if (counterTriangles < nTriangle && counterVertices % 3 == 0) {
        normal = getNormal(it->pos, (it + 1)->pos, (it + 2)->pos);
        nTriangle++;
      }
      counterVertices++;
      it->normal = normal;
    }
  }
}

Vec Command::getNormal(const Vec &dot1, const Vec &dot2, const Vec &dot3) {
  Vec vec1 = getVector(dot1, dot2);
  Vec vec2 = getVector(dot2, dot3);
  Vec normal;
  normal.x = (vec1.y * vec2.z - vec1.z * vec2.y);
  normal.y = (vec1.z * vec2.x - vec1.x * vec2.z);
  normal.z = (vec1.x * vec2.y - vec1.y * vec2.x);
  double lengthvec =
      2; // sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
  normal.x = normal.x / lengthvec;
  normal.y = normal.y / lengthvec;
  normal.z = normal.z / lengthvec;
  return normal;
}

Vec Command::getVector(const Vec &start, const Vec &end) {
  return {start.x - end.x, start.y - end.y, start.z - end.z};
}

void Command::getArgument(const std::map<std::string, std::string> &args,
                          const std::string &keyName, double &value) {
  auto it = args.find(keyName);
  if (it != args.end()) {
    std::stringstream strtodouble;
    strtodouble << it->second;
    if (strtodouble.good()) {
      strtodouble >> value;
    } else {
      throw new std::logic_error(keyName);
    }
  } else {
    throw std::out_of_range(keyName);
  }
  if (value <= 0) {
    throw std::logic_error(keyName);
  }
}

void Command::getArgument(const std::map<std::string, std::string> &args,
                          const std::string &keyName, Vec &value) {
  auto it = args.find(keyName);
  if (it != args.end()) {
    std::string strvec = it->second;
    value = convertToVec(strvec);
  } else {
    throw std::out_of_range(keyName);
  }
}

void Command::getArgument(const std::map<std::string, std::string> &args,
                          const std::string &keyName, std::string &value) {
  auto it = args.find(keyName);
  if (it != args.end()) {
    value = it->second;
  } else {
    throw std::out_of_range(keyName);
  }
}

Vec Command::convertToVec(const std::string &dot) {
  double vec[3];
  std::stringstream strtodouble;
  strtodouble << dot;
  double cord;
  for (int i = 0; i < 3; i++) {
    if (strtodouble.good()) {
      double cord;
      strtodouble >> cord;
      vec[i] = cord;
    } else {
      throw std::logic_error(dot);
    }
  }
  return {vec[0], vec[1], vec[2]};
}
