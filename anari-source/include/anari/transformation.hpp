/** Transformation [Anari]
 * Version: 0.1
 *
 * Class that represents linear transformations with 3x3 matrices
 *
 * Author(s): Graham Mix
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

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Eigen/Core"

// Use 3 Dimensional matrices
using namespace Eigen;
typedef Matrix3d TransformMatrix;

const int DIMENSION = 3;

class Transformation
{

    public:

        TransformMatrix the_matrix;

        /// Default Constructor
        explicit Transformation()
        : the_matrix()
        {
            for (int i = 0; i < DIMENSION; ++i)
            {
                for (int j = 0; j < DIMENSION; ++j)
                {
                    this->the_matrix(i, j) = 0;
                }
            }
        }

        /** Constructor
         * \param other_matrix: Matrix we are initializing with
         */
        explicit Transformation(const Matrix3d& other_matrix)
        : the_matrix(other_matrix)
        {
            this->the_matrix = other_matrix;
        }

        /// Copy Constructor
        explicit Transformation(const Transformation& transformation)
        : the_matrix(transformation.the_matrix)
        {}

        /// Copy Assignment
        Transformation& operator=(const Transformation& rhs)
        {
           this->the_matrix = rhs.the_matrix;
           return *this;
        }

        double& operator()(const int row, const int col)
        {
            assert(row >= 0 && row <= 3);
            assert(col >= 0 && col <= 3);
            return this->the_matrix(row, col);
        }

        /** Perform a linear transformation with another 3x3 matrix
         * \param transform_matrix: The matrix to perform a linear transformation with
         * \return the result of the linear transformation
         */
        Matrix3d transform_matrix(const Matrix3d& transform_matrix)
        {
            the_matrix = the_matrix + transform_matrix;
            return the_matrix;
        }

};

#endif