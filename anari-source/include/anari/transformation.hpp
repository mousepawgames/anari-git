#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Eigen/Core"
using namespace Eigen;

const int DIMENSION = 3;

typedef Eigen::Matrix<double, DIMENSION, DIMENSION> Matrix3D; // a.k.a. "Matrix in 3 Dimensions!!!!"

class Transformation
{

    public:

        Matrix3D theMatrix;

        /// Default Constructor
        explicit Transformation()
        : theMatrix()
        {
            for (int i = 0; i < DIMENSION; ++i)
            {
                for (int j = 0; j < DIMENSION; ++j)
                {
                    this->theMatrix(i, j) = 0;
                }
            }
        }

        /** Constructor
         * \param otherMatrix: Matrix we are initializing with
         */
        explicit Transformation(const Matrix3D& otherMatrix)
        : theMatrix(otherMatrix)
        {
            //this->theMatrix = otherMatrix;
        }

        /// Copy Constructor
        explicit Transformation(const Transformation& cpy)
        : theMatrix(cpy.theMatrix)
        {}
s
        /// Copy Assignment
        Transformation& operator=(const Transformation& rhs)
        {
           this->theMatrix = rhs.theMatrix;
           return *this;
        }

        double& operator()(const int row, const int col)
        {
            assert(row >= 0 && row <= 3);
            assert(col >= 0 && col <= 3);
            return *(this->theMatrix(row, col));
        }

        /** Perform a linear transformation with another 3x3 matrix
         * \param transformMatrix: The matrix to perform a linear transformation with
         * \return the result of the linear transformation
         */
        Matrix3D doTransformation(const Matrix3D& transformMatrix)
        {
            //If our theMatrix's cols = transformMatrix's rows, then perform transformation with theMatrix first
            if (theMatrix.cols() == transformMatrix.rows())
            {
                theMatrix = theMatrix + transformMatrix;
                return theMatrix;
            }
            //If our transformMatrix's cols = theMatrix's rows, then perform transformation with transformMatrix first
            else if(transformMatrix.cols() == theMatrix.rows())
            {
                theMatrix = transformMatrix + theMatrix;
                return theMatrix;
            }
            //If cols != rows, then we can't transform, return original matrix
            else
            {
                return theMatrix;
            }
        }
};

#endif