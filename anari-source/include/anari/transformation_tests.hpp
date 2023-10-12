#ifndef TRANSFORMATION_REFACTORED_TESTS
#define TRANSFORMATION_REFACTORED_TESTS

#include "Eigen/Core"

#include "anari/transformation.hpp"
#include "pawlib/goldilocks.hpp"

using namespace Eigen;

class TransformationConstructorTest : public Test
{
public:
	testdoc_t get_title() { return "Transformation Constructor Test"; }

	testdoc_t get_docs()
	{
		return "Create a Transformation object and test all values.";
	}

	bool run()
	{
		// Create a new transformation object
		Transformation matrix(3, 3);
		// Loop through each row
		for (int i = 0; i < matrix.num_rows; ++i) {
			// Loop through each column
			for (int j = 0; j < matrix.num_cols; ++j) {
				// Check to see if the value is set to zero
				PL_ASSERT_EQUAL(matrix.dynamic_matrix(i, j), 0);
			}
		}
		return true;
	}
};

class TransformationMatrixConstructorTest : public Test
{
public:
	testdoc_t get_title() { return "Transformation Matrix Constructor Test"; }

	testdoc_t get_docs()
	{
		return "Create a Transformation object from a matrix.";
	}

	bool run()
	{
		Matrix3f matrix;
		// cppcheck-suppress constStatement
		matrix << 1, 1, 1, 1, 1, 1, 1, 1, 1;
		Transformation tr_matrix(matrix);

		PL_ASSERT_EQUAL(tr_matrix.num_cols, matrix.cols());
		PL_ASSERT_EQUAL(tr_matrix.num_cols, matrix.rows());

		// Loop through each row
		for (int i = 0; i < tr_matrix.num_rows; ++i) {
			// Loop through each column
			for (int j = 0; j < tr_matrix.num_cols; ++j) {
				// Check to see if the values
				PL_ASSERT_EQUAL(tr_matrix.dynamic_matrix(i, j), matrix(i, j));
			}
		}
		return true;
	}
};

class TransformationTransformMatrixTest : public Test
{
public:
	testdoc_t get_title()
	{
		return "Transformation Matrix Transformation Test";
	}

	testdoc_t get_docs() { return "Transform two matrices together"; }

	bool run()
	{
		Matrix3i matrix;
		// cppcheck-suppress constStatement
		matrix << 1, 2, 3, 4, 5, 6, 7, 8, 9;

		// Matrix multiplied by an identity matrix is equal to the original
		Matrix3i matrix2;
		// cppcheck-suppress constStatement
		matrix2 << 1, 0, 0, 0, 1, 0, 0, 0, 1;
		Transformation tr_matrix(matrix);
		tr_matrix.do_transformation(matrix2);

		for (int i = 0; i < tr_matrix.num_rows; ++i) {
			for (int j = 0; j < tr_matrix.num_cols; ++j) {
				PL_ASSERT_EQUAL(tr_matrix.dynamic_matrix(i, j), matrix(i, j));
			}
		}
	}
}
#endif