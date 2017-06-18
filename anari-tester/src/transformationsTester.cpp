///*
//*Anari Graphics System, version 0.1
//*main Class
//*Description: This is the main method that tests the functionality of the
//*Timeline class as well as Frame, Layer, LayerInstance, and StaticLayer.
//*Last Updated: 30 April 2016
//*
//*Copyright (C) MousePawMedia
//*Licenses:
//*/
//
//
//#include <iostream>
//#include "StaticLayer.hpp"
//#include "IOL.hpp"
//#include "Frame.hpp"
//#include "Timeline.hpp"
//#include <Eigen/Dense>
//#include <cmath>
//
//
//
//using std::cout;
//using std::endl;
//using std::cin;
//
//
//int main()
//{
//
//    //MatrixXf defines a matrix with variable size of type float.
//    //In this case: 3 values and 3 dimensions.
//    //The 3rd dimension is used to generate the matrices but 2d points are used.
//    //3rd dimension is just set to 0's
//    Eigen::MatrixXf M(4,3);
//
//
//    //Initializing 3 points.
//    //Bottom is set to 1's to define the points to be used with affine space functions
//
//
//    M <<    10, 20, 15,
//            10, 10, 15,
//            0,  0,  0,
//            1,  1,  1;
//
//
//
//
//    cout << "Number of points: 3" << endl;
//    cout << "Point matrix M: \n" << endl;
//    cout << M << "\n" << endl;
//
//
//    //Getting the centroid of the triangle.
//    float cx = (M(0, 0) + M(0, 1) + M(0, 2))/3;
//    float cy = (M(1, 0) + M(1, 1) + M(1, 2))/3;
//    cout << "Centroid of points: " << cx << "," << cy << "\n" << endl;
//
//
//    //Creating a rotation about the Z axis by 90 degrees counter clockwise.
//    Eigen::Affine3f rx = Eigen::Affine3f(Eigen::AngleAxisf(0, Eigen::Vector3f(1, 0, 0)));
//    Eigen::Affine3f ry = Eigen::Affine3f(Eigen::AngleAxisf(0, Eigen::Vector3f(0, 1, 0)));
//    Eigen::Affine3f rz = Eigen::Affine3f(Eigen::AngleAxisf(M_PI/2.0, Eigen::Vector3f(0, 0, 1)));
//    Eigen::Affine3f rotation = rx * ry * rz;
//
//    //Creating a translation to move the triangle to origin.
//    Eigen::Affine3f translation(Eigen::Translation3f(Eigen::Vector3f(-cx, -cy, 0)));
//
//    //Creating a translation to move the triangle back to its original spot after rotation.
//    Eigen::Affine3f translationB(Eigen::Translation3f(Eigen::Vector3f(cx, cy, 0)));
//
//    //Merging all transformations together.
//    Eigen::MatrixXf transformation = (translationB * rotation * translation).matrix() ;
//
//
//    //Applying the transformation.
//    cout << transformation * M  << endl;
//
//
//
//
//    return 0;
//}
//
//
//
//
//
//
