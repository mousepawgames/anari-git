#ifndef ANARI_TRANSFORMATION_TESTS_HPP
#define ANARI_TRANSFORMATION_TESTS_HPP

#include "pawlib/goldilocks.hpp"
#include "anari/transformation.hpp"
#include "Eigen/Core"

class TransformationEmptyConstructorTester : public Test
{
    testdoc_t get_title()
    {
        return "Transformation Empty Constructor";
    }

    testdoc_t get_docs()
    {
        return "Create a new Transformation object and test the constructor.";
    }

    // bool pre()

    // bool prefail()

    // bool janitor()

    bool run()
    {
        Transformation transform = Transformation();
        PL_ASSERT_EQUAL(transform.theMatrix(0,0), 0);
        PL_ASSERT_EQUAL(transform.theMatrix(0,1), 0);
        PL_ASSERT_EQUAL(transform.theMatrix(1,0), 0);
        PL_ASSERT_EQUAL(transform.theMatrix(1,1), 0);
        return true;
    }

    // bool post()

    // bool postmortem()
};

class TransformationConstructorTester: public Test
{


};

#endif