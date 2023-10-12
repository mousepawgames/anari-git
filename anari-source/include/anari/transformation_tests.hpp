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
            // Create a new array with all values set to zero
            Transformation transform = Transformation();
            // Loop through each row
            for ( int i = 0; i < DIMENSION; ++i)
            {
                // Loop through each column
                for ( int j = 0; j < DIMENSION; ++j)
                {
                    // Check to see if the value is set to zero
                    PL_ASSERT_EQUAL(transform.the_matrix(i, j), 0);
                }
            }
            return true;
        }
};

class LinearTransformationTester : public Test
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
            // Create a new test matrix to test a linear transformation
            Matrix3d test_matrix;
            // Create a new input matrix for a new Transformation object
            Matrix3d input_matrix;
            for (int i = 0; i < DIMENSION; i++)
            {
                for (int j = 0; j < DIMENSION; j++)
                {
                    // Set all values to the value one
                    test_matrix(i, j) = 1;
                    input_matrix(i, j) = 1;
                }

            }
            Transformation transform = Transformation(input_matrix);
            transform.transform_matrix(test_matrix);
            for (int i = 0; i < DIMENSION; i++)
            {
                for (int j = 0; j < DIMENSION; j++)
                {
                    // Assuming the do_transformation method performed correctly, all values should be two
                    PL_ASSERT_EQUAL(transform.the_matrix(i,j), 2);
                }

            }
            return true;
        }
};

class TransformationConstructorTester : public Test
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
            // Create a new test matrix
            Matrix3d test_matrix;

            for (int i = 0; i < DIMENSION; i++)
            {
                for (int j = 0; j < DIMENSION; j++)
                {
                    // Random calculation of row# + col#
                    test_matrix(i, j) = i + j;
                }

            }
            Transformation transform = Transformation(test_matrix);
            for (int i = 0; i < DIMENSION; i++)
            {
                for (int j = 0; j < DIMENSION; j++)
                {
                    // Test to see if value inside index is calculated correctly from calculation above
                    PL_ASSERT_EQUAL(transform.the_matrix(i,j), test_matrix(i, j));
                }

            }
            return true;
        }
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
