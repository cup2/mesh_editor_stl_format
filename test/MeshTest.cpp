#include "Application.h"
#include "Cube.h"
#include "Sphere.h"
#include "Split.h"
#include "stlparsemock.h"
#include <cstring>
#include <gtest/gtest.h>
/*struct Vec {
  double x, y, z;
};

struct Vertex {
  Vec pos;
  Vec normal;
};

using TriangleSoup = std::vector<Vertex>;*/

;
class MockCube : public Cube {
public:
  MockSTLParser for_test;
};

namespace test {
using namespace testing::internal;
using namespace testing;

void run(int argc, char *argv[]) {

  Application app;
  app.registerCommand(std::make_unique<Cube>());
  app.registerCommand(std::make_unique<Sphere>());
  app.registerCommand(std::make_unique<Split>());
  app.execute(argc, argv);
}
TEST(testCube, invalida) {
  std::map<std::string, std::string> args = {
      {"Laa", "2"}, {"filepathaa", "testsss"}, {"originss", "4.5 3.4 2.1"}};
  Cube test;
  NiceMock<MockSTLParser> nice_STLParse;

  auto res = test.execute(args, nice_STLParse);

  EXPECT_EQ(3, res);
}

TEST(testCube, cube_1x1) {
  std::map<std::string, std::string> args = {
      {"L", "2"}, {"filepath", "testsss"}, {"origin", "4.5 3.4 2.1"}};
  Cube test;
  MockSTLParser nice_STLParse;

  EXPECT_CALL(nice_STLParse, read(_)).Times(0);
  // here can check result
  EXPECT_CALL(nice_STLParse, write(_, _)).Times(AtLeast(1)).WillOnce(Return());
  auto res = test.execute(args, nice_STLParse);
  EXPECT_EQ(0, res);
}
} // namespace test
