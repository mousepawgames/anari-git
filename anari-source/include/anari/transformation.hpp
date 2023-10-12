/** Transformation [Anari]
 * Version: 0.1
 *
 * Class that represents linear transformations with 3x3 matrices
 *
 * Author(s): Manuel Mateo, Graham Mix
 */

/* LICENSE
 * Copyright (C) 2020 MousePaw Media.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRANSFORMATION_REFACTOR_H
#define TRANSFORMATION_REFACTOR_H

#include "Eigen/Core"

using namespace Eigen;

// Use a Dynamic matrix to account for all sizes of matrices and vectors
typedef Matrix<double, Dynamic, Dynamic> DynamicMatrix;

class Transformation
{
public:
	DynamicMatrix dynamic_matrix;
	size_t num_cols;
	size_t num_rows;

	/** Makes a new Transformation object of the specifieid size.
	 * \param rows: The number of rows for the matrix
	 * \param cols: The number of columns for the matrix
	 */
	Transformation()
	: dynamic_matrix(3, 3), num_cols(3), num_rows(3)
	{
		for (size_t i = 0; i < 3; ++i) {
			for (size_t j = 0; j < 3; ++j) {
				dynamic_matrix(i, j) = 0;
			}
		}
	}

	explicit Transformation(size_t rows, size_t cols)
	: dynamic_matrix(rows, cols), num_cols(cols), num_rows(rows)
	{
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				dynamic_matrix(i, j) = 0;
			}
		}
	}

	/** Makes a copy of a DynamicMatrix.
	 * \param incoming: The constructed matrix takes the rows, columns, and
	 * values of the incoming dynamic matrix
	 */
	explicit Transformation(const DynamicMatrix& incoming)
	: dynamic_matrix(incoming), num_cols(incoming.cols()),
	num_rows(incoming.rows())

	{
	}

	/** Makes a copy of a Transformation object.
	 * \param cpy: Takes in a Transformation object, takes the rows, columns,
	 * and values of the object
	 */
	explicit Transformation(const Transformation& cpy)
	: dynamic_matrix(cpy.dynamic_matrix), num_cols(cpy.num_cols),
	num_rows(cpy.num_rows)

	{
	}

	/** Multiplies the dynamic matrix of this, other_matrix.
	 * \param other_matrix: the matrix to combine with this one.
	 */
	void do_transformation(const DynamicMatrix& other_matrix)
	{
		// Order matters with dynamic matrices
		// First matrix's column number must equal second matrix's row number
		if (dynamic_matrix.cols() == other_matrix.rows()) {
			this->dynamic_matrix *= other_matrix;
		}
	}

	/** Multiplies the dynamic matrix of this, other_transformation.
	 * \param other_transformation: the object to transform this' matrix with.
	 */
	void do_transformation(const Transformation& other_transformation)
	{
		// Order matters with dynamic matrices
		// First matrix's column number must equal second matrix's row number
		if (dynamic_matrix.cols() == other_transformation.num_rows) {
			this->dynamic_matrix *= other_transformation.dynamic_matrix;
		}
	}

	/** This function does such and such a thing.
	 * \param rhs: The Transformation object to copy from.
	 * \return a Transformation object.
	 */
	Transformation& operator=(const Transformation& rhs)
	{
		this->dynamic_matrix = rhs.dynamic_matrix;
		this->num_rows = rhs.num_rows;
		this->num_cols = rhs.num_cols;
		return *this;
	}

	/** Access a matrix at a row, column.
	 * \param row: The row to access.
	 * \param col: The column to access.
	 * \return the value at the specified row and column.
	 */
	float operator()(const size_t row, const size_t col)
	{
		assert(row <= num_rows);
		assert(col <= num_cols);
		return this->dynamic_matrix(row, col);
	}
};

#endif