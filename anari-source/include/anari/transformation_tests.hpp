#ifndef ANARI_TRANSFORMATION_TESTS_HPP
#define ANARI_TRANSFORMATION_TESTS_HPP

#include "pawlib/goldilocks.hpp"
#include "anari/transformation.hpp"
#include "Eigen/Core"

class TransformationEmptyConstructorTester : public Test
{
public:
    testdoc_t get_title()
    {
        return "Transformation Empty Constructor";
    }

    testdoc_t get_docs()
    {
        return "Create a new Transformation object and test the constructor.";
    }

    bool run()
    {
        Transformation transform = Transformation();
        for ( int i = 0; i < DIMENSION; ++i)
        {
            for ( int j = 0; j < DIMENSION; ++j)
            {
                PL_ASSERT_EQUAL(transform.the_matrix(i, j), 0);
            }
        }
        return true;
    }
};

class TransformationConstructorTester: public Test
{
public:
    testdoc_t get_title()
    {
        return "Transformation Matrix3d Constructor";
    }

    testdoc_t get_docs()
    {
        return "Create a new Transformation object with a Matrix3d and test the constructor.";
    }

    bool run()
    {
        Matrix3d test_matrix; // Create a new test matrix

        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                test_matrix(i, j) = i + j; // Random calculation
            }

        }
        Transformation transform = Transformation(test_matrix);
        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                PL_ASSERT_EQUAL(transform.the_matrix(i,j), test_matrix(i, j));
            }

        }
        return true;
    }

};

class LinearTransformationTester: public Test
{
public:
    testdoc_t get_title()
    {
        return "Linear Transformation Tester";
    }

    testdoc_t get_docs()
    {
        return "Create a new Transformation object with a Matrix3d and test do_transformation.";
    }

    bool run()
    {
        Matrix3d test_matrix; // Create a new test matrix
        Matrix3d input_matrix;
        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                test_matrix(i, j) = 1;
                input_matrix(i, j) = 1;
            }

        }
        Transformation transform = Transformation(input_matrix);
        transform.do_transformation(test_matrix);
        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                PL_ASSERT_EQUAL(transform.the_matrix(i,j), 2);
            }

        }
        return true;
};

class TestSuite_Transformation : public TestSuite
{
public:
    testdoc_t get_title()
    {
        return "Transformation Tests";
    }

    void load_tests();
};
#endif
