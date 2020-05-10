#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "pawlib/flex_array.hpp"

struct Segment
{
    double x1, y1;
    double cx1, cy1;
    double x2, y2;
    double cx2, cy2;
};

class Curve
{
    private:
        FlexArray<Segment> m_Array;
        Segment m_Seg;
        bool segmentClosed;

    public:
        Curve()
            : m_Seg{0, 0, 0, 0, 0, 0, 0, 0},
              segmentClosed(false)
          {}

        explicit Curve(const Segment& seg)
            : m_Seg(seg),
              segmentClosed(true)
        {
            addSegment(m_Seg);
        }

        /// Copy Constructor
        Curve(const Curve& rhs)
            : m_Array(rhs.m_Array),
            m_Seg(rhs.m_Seg),
            segmentClosed(false)
        {}

        /// Move Constructor
        Curve(Curve&& rhs)
            : m_Array(std::move(rhs.m_Array)),
              m_Seg(std::move(rhs.m_Seg)),
              segmentClosed(std::move(rhs.segmentClosed))
        {}

        Curve& operator=(const Curve& rhs)
        {
            /// Self-assignment detection
            if (&rhs == this)
            {
                return *this;
            }
            /// Check for failure
            m_Array.clear();

            this->m_Array = rhs.m_Array;
            this->m_Seg = rhs.m_Seg;
            this->segmentClosed = rhs.segmentClosed;
            return *this;
        }

        /// Subscript overload to get a particular segments
        Segment& operator[] (size_t index)
        {
            return m_Array.at(index);
        }
        /** Get array size
         * \return size
         */
        size_t size()
        {
            return m_Array.length();
        }

        void addSegment(Segment& seg)
        {
            m_Array.push(seg);
        }
        // Setter for start points of the curve
        void start(double x, double y, double cx, double cy)
        {
            m_Seg.x1 = x;
            m_Seg.y1 = y;
            m_Seg.cx1 = cx;
            m_Seg.cy1 = cy;
            segmentClosed = false;
        }
        // Setter for the end points of the curve
        void add(double x, double y, double cx, double cy)
        {
            if (segmentClosed)
            {
                start(x, y, cx, cy);
            }
            else
            {
                m_Seg.x2 = x;
                m_Seg.y2 = y;
                m_Seg.cx2 = cx;
                m_Seg.cy2 = cy;
                segmentClosed = true;
                addSegment(this->m_Seg);
            }
        }
};

class Resolution
{
    public:
        int width, height;

        /// Default constructor
        Resolution()
        : width(600), height(800) {}

        /** Constructor that validates input
         * \param width
         * \param height
         */
        explicit Resolution(const int width, const int height)
        {
            this->width = width > 0 ? width : 600;
            this->height = height > 0 ? height : 800;
        }
        /// Copy constructor
        Resolution(const Resolution& rhs)
        {
            this->width = rhs.width;
            this->height = rhs.height;
        }
        /// Copy assingment operator
        Resolution& operator=(const Resolution& rhs)
        {
            this->width = rhs.width;
            this->height = rhs.height;
            return *this;
        }
};

#endif