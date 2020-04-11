#include "anari/colors_test.hpp"

void TestSuite_Colors::load_tests()
{
    register_test("A-tB0200", new Test_CMYKtoRGBA);
    register_test("A-tB0201", new Test_RGBAtoCMYK);
    register_test("A-tB0202", new Test_HSLtoRGBA);
    register_test("A-tB0203", new Test_RGBAtoHSL);
    register_test("A-tB0204", new Test_RGBADoubletoRGBA);
    register_test("A-tB0205", new Test_RGBAtoRGBADouble);
    register_test("A-tB0206", new Test_HEXtoRGBA);
    register_test("A-tB0207", new Test_RGBAtoHEX);
    // Tests for constructors and Copy Constructors
    register_test("A-tB0208", new Test_RGBAConstructor);
    register_test("A-tB0209", new Test_CMYKConstructor);
    register_test("A-tB0210", new Test_HSLConstructor);
    register_test("A-tB0211", new Test_RGBADoubleConstructor);

}