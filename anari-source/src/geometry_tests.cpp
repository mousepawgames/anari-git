#include "anari/geometry_tests.hpp"

void TestSuite_Resolution::load_tests()
{
    register_test("A-tB0101", new Test_ResolutionConstructor());
    register_test("A-tB0102", new Test_ResolutionCopy());
}

void TestSuite_Curve::load_tests()
{
    register_test("A-tB0301", new Test_CurveConstructor());
    register_test("A-tB0302", new Test_CurveAddSegment());
    register_test("A-tB0303", new Test_SubscriptOperator());
}