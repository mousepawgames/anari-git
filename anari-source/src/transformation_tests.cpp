#include "anari/transformation_tests.hpp"

void TestSuite_Transformation::load_tests()
{
    register_test("A-tB0401", new TransformationEmptyConstructorTester());
    register_test("A-tB0402", new TransformationConstructorTester());
    register_test("A-tB0403", new LinearTransformationTester());
    register_test("A-tB0404", new InvalidTransformationTester());
}
