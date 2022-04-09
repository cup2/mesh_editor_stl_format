#ifndef SPHERE_H
#define SPHERE_H
#include "Command.h"

class Sphere : public Command {
public:
  const std::string &getName() const override;
  int execute(const std::map<std::string, std::string> &args) override;

private:
  const std::string name_ = "Sphere";
  const std::string radiusKeyName_ = "R";
  const std::string fileKeyName_ = "filepath";
  const std::string originKeyName_ = "origin";
  Vec findVertexSphere(const double &lo, const double &la, const double &radius,
                       const Vec &origin);
  TriangleSoup buildSphere(const double &radius, const Vec &origin);
};

#endif // SPHERE_H
