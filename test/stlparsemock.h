#ifndef STLPARSEMOCK_H
#define STLPARSEMOCK_H
#include "STLParser.h"
#include "gmock/gmock.h"

class MockSTLParser : public STLParser {
public:
  MOCK_METHOD(TriangleSoup, read, (const std::string &filename),
              (override)); // TriangleSoup STLParser::read(const
                           // std::string &filename) {

  MOCK_METHOD(void, write,
              (const TriangleSoup &triangleSoup, const std::string &filename),
              (override));

  //  virtual void write(const TriangleSoup &triangleSoup,
  // const std::string &filename);
};

#endif // STLPARSEMOCK_H
