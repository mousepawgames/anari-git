#include "anari/basic_test.hpp"

void TestSuite_Basic::load_tests()
{
    register_test("A-tB0001", new TestBasic_Inheritance);
    register_test("A-tB0002", new TestBasic_NonInheritance);
}