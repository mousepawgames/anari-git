#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Eigen/Core"
using namespace Eigen;

const int DIMENSION = 3;

class Transformation
{

    public:

        Matrix3d the_matrix;

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
        explicit Transformation(const Transformation& cpy)
        : the_matrix(cpy.the_matrix)
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
        Matrix3d do_transformation(const Matrix3d& transform_matrix)
        {
            the_matrix = the_matrix + transform_matrix;
            return the_matrix;
        }
};

#endif