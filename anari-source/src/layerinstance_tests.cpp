#include "anari/layerinstance_tests.hpp"

void TestSuite_LayerInstance::load_tests()
{
    register_test("A-tB0501", new TestDefaultConstructor());
    register_test("A-tB0502", new TestConstructor());
    register_test("A-tB0503", new TestCopyConstructor());
}