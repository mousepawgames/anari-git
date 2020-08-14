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
        for ( int i = 0; i < DIMENSION; ++i)
        {
            for ( int j = 0; j < DIMENSION; ++j)
            {
                PL_ASSERT_EQUAL(transform.theMatrix(i, j), 0);
            }
        }
        return true;
    }

    // bool post()

    // bool postmortem()
};

class TransformationConstructorTester: public Test
{
testdoc_t get_title()
    {
        return "Transformation Matrix3D Constructor";
    }

    testdoc_t get_docs()
    {
        return "Create a new Transformation object with a Matrix3D and test the constructor.";
    }

    // bool pre()

    // bool prefail()

    // bool janitor()

    bool run()
    {
        Matrix3D testMatrix; // Create a new test matrix

        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; i < DIMENSION; j++)
            {
                testMatrix(i, j) = i + j; // Random calculation
            }

        }
        Transformation transform = Transformation(testMatrix);
        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; i < DIMENSION; j++)
            {
                PL_ASSERT_EQUAL(transform.theMatrix(i,j), testMatrix(i, j));
            }

        }
        return true;
    }

    // bool post()

    // bool postmortem()

};

class TestSuite_Transformation : TestSuite
{
    testdoc_t get_title()
    {
        return "Transformation Tests";
    }

    void load_tests();
};
#endif
