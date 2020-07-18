#include "Eigen/Core"

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXD;

class Transformation
{
    private: MatrixXD theMatrix;

    public: MatrixXD doTransformation(MatrixXD otherMatrix)
    {
        if (theMatrix.cols() == otherMatrix.rows())
        {
            theMatrix = theMatrix + otherMatrix;
            return theMatrix;
        }
        else if(otherMatrix.cols() == theMatrix.rows())
        {
            theMatrix = otherMatrix + theMatrix;
            return theMatrix;
        }
        else
        {
            return theMatrix;
        }
    }
};