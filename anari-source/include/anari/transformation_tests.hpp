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
        Transformation transform = Transformation();    // Create a new array with all values set to zero
        for ( int i = 0; i < DIMENSION; ++i)            // Loop through each row
        {
            for ( int j = 0; j < DIMENSION; ++j)        // Loop through each column
            {
                PL_ASSERT_EQUAL(transform.the_matrix(i, j), 0); // Check to see if the value is set to zero
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
                test_matrix(i, j) = i + j; // Random calculation of row# + col#
            }

        }
        Transformation transform = Transformation(test_matrix);
        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                PL_ASSERT_EQUAL(transform.the_matrix(i,j), test_matrix(i, j));  // Test to see if value inside index is calculated correctly from calculation above
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
        Matrix3d test_matrix;   // Create a new test matrix to test a linear transformation
        Matrix3d input_matrix;  // Create a new input matrix for a new Transformation object
        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                test_matrix(i, j) = 1;  // Set all values to the value one
                input_matrix(i, j) = 1;
            }

        }
        Transformation transform = Transformation(input_matrix);
        transform.do_transformation(test_matrix);
        for (int i = 0; i < DIMENSION; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                PL_ASSERT_EQUAL(transform.the_matrix(i,j), 2);  // Assuming the do_transformation method performed correctly, all values should be two
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
