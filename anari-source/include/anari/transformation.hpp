#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Eigen/Core"
using namespace Eigen;

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXD;

class Transformation
{

    public:

        MatrixXD theMatrix;

        Transformation()
        {
            theMatrix << 0, 0,
                         0, 0;
        }

        Transformation(MatrixXD otherMatrix)
        {
            this->theMatrix = otherMatrix;
        }

        Transformation& operator=(const Transformation* rhs)
        {
           this->theMatrix = rhs->theMatrix;
           return *this;
        }

        MatrixXD doTransformation(MatrixXD transformMatrix)
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