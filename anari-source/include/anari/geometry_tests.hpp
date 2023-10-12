#ifndef ANARI_GEOMETRY_TESTS_HPP
#define ANARI_GEOMETRY_TESTS_HPP

#include "goldilocks/test.hpp"
#include "goldilocks/assertions.hpp"
#include "goldilocks/suite.hpp"
#include "goldilocks/types.hpp"
#include "anari/geometry.hpp"
#include "Eigen/Core"

class Test_ResolutionConstructor : public Test
{
    testdoc_t get_title()
    {
        return "Resolution Constructor";
    }

    testdoc_t get_docs()
    {
        return "Create a new Resolution object from integers.";
    }

    // bool pre()

    // bool prefail()

    // bool janitor()

    bool run()
    {
        Resolution res = Resolution(640, 480);
        PL_ASSERT_EQUAL(res.width, 640);
        PL_ASSERT_EQUAL(res.height, 480);
        return true;
    }

    // bool post()

    // bool postmortem()
};

class Test_ResolutionCopy : public Test
{
    testdoc_t get_title()
    {
        return "Resolution Copy Assignment and Constructor";
    }
    testdoc_t get_docs()
    {
        return "Copy another Resolution object";
    }

    bool run()
    {
        Resolution res(640, 480);
        /// Copy constructor check
        Resolution copy = res;
        PL_ASSERT_EQUAL(copy.width, res.width);
        PL_ASSERT_EQUAL(copy.height, res.height);

        /// Copy assignment check
        Resolution def;
        copy = def;
        PL_ASSERT_EQUAL(copy.width, 600);
        PL_ASSERT_EQUAL(copy.height, 800);
        return true;
    }
};

class Test_CurveConstructor : public Test
{
    testdoc_t get_title()
    {
        return "Curve Constructor Tests";
    }
    testdoc_t get_docs()
    {
        return "Test Constructing Objects";
    }

    bool run()
    {
        Curve curv = Curve();
        /// Limit lifetime to make sure it's not a shallow copy
        {
            Segment* mySeg = new Segment;
            Eigen::Vector4d startVector = Eigen::Vector4d(100, 100, 30, 200);
            Eigen::Vector4d endVector = Eigen::Vector4d(113, 110, 200, 500);
            *mySeg = { startVector, endVector };
            curv.addSegment(*mySeg);
            delete mySeg;
        }
        Curve curv_copy(curv);
        PL_ASSERT_EQUAL(curv[0].start_point(0,0), curv_copy[0].start_point(0,0));
        PL_ASSERT_EQUAL(curv[0].start_point(1,0), curv_copy[0].start_point(1,0));
        PL_ASSERT_EQUAL(curv[0].start_point(2,0), curv_copy[0].start_point(2,0));
        PL_ASSERT_EQUAL(curv[0].start_point(3,0), curv_copy[0].start_point(3,0));
        PL_ASSERT_EQUAL(curv[0].end_point(0,0), curv_copy[0].end_point(0,0));
        PL_ASSERT_EQUAL(curv[0].end_point(1,0), curv_copy[0].end_point(1,0));
        PL_ASSERT_EQUAL(curv[0].end_point(2,0), curv_copy[0].end_point(2,0));
        PL_ASSERT_EQUAL(curv[0].end_point(3,0), curv_copy[0].end_point(3,0));
        return true;
    }
};

class Test_SubscriptOperator : public Test
{
    testdoc_t get_title()
    {
        return "Curve Subscript Operator Tests";
    }
    testdoc_t get_docs()
    {
        return "Tests the subscript operator for Curves";
    }
    bool run()
    {
        Curve test = Curve();
        Eigen::Vector4d startVector = Eigen::Vector4d(100, 100, 30, 200);
        Eigen::Vector4d endVector = Eigen::Vector4d(113, 110, 200, 500);
        Segment mySeg = { startVector, endVector };
        test.addSegment(mySeg);
        PL_ASSERT_EQUAL(test[0].start_point(0,0), startVector(0,0));
        PL_ASSERT_EQUAL(test[0].start_point(1,0), startVector(1,0));
        PL_ASSERT_EQUAL(test[0].start_point(2,0), startVector(2,0));
        PL_ASSERT_EQUAL(test[0].start_point(3,0), startVector(3,0));
        PL_ASSERT_EQUAL(test[0].end_point(0,0), endVector(0,0));
        PL_ASSERT_EQUAL(test[0].end_point(1,0), endVector(1,0));
        PL_ASSERT_EQUAL(test[0].end_point(2,0), endVector(2,0));
        PL_ASSERT_EQUAL(test[0].end_point(3,0), endVector(3,0));
        return true;
    }

};

class Test_CurveAddSegment : public Test
{
    testdoc_t get_title()
    {
        return "Curve Segment Adding Tests";
    }
    testdoc_t get_docs()
    {
        return "Test adding segments using start/add";
    }

    bool run()
    {
        Curve curv = Curve();
        curv.start(32, 122, 200, 300);
        curv.add(64, 244, 400, 400);
        PL_ASSERT_EQUAL(curv[0].start_point(0,0), 32);
        PL_ASSERT_EQUAL(curv[0].start_point(1,0), 122);
        PL_ASSERT_EQUAL(curv[0].start_point(2,0), 200);
        PL_ASSERT_EQUAL(curv[0].start_point(3,0), 300);
        PL_ASSERT_EQUAL(curv[0].end_point(0,0), 64);
        PL_ASSERT_EQUAL(curv[0].end_point(1,0), 244);
        PL_ASSERT_EQUAL(curv[0].end_point(2,0), 400);
        PL_ASSERT_EQUAL(curv[0].end_point(3,0), 400);
        return true;
    }
};

class TestSuite_Curve : public TestSuite
{
    testdoc_t get_title()
    {
        return "Curve Tests";
    }

    void load_tests();
};

class TestSuite_Resolution : public TestSuite
{
    testdoc_t get_title()
    {
        return "Resolution Tests";
    }
    void load_tests();
};

#endif