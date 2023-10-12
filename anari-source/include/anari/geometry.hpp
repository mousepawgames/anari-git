/** Geometry Refactor [Anari] Subject to change
 * Version: 0.1
 *
 * Class related to geometry
 *
 * Author(s): Graham Mix, Anna Dunster
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

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "nimbly/flexarray.hpp"
#include "Eigen/Core"

struct Coordinate
{
    // cppcheck-suppress unusedStructMember
    float x;
    // cppcheck-suppress unusedStructMember
    float y;
};

struct Segment
{
    //Compress these into a Vector? [x1, y1, cx1, cy1]
    Eigen::Vector4d start_point;
    //Possibly get rid of these?
    //double x1, y1;
    //double cx1, cy1;

    //Same here
    Eigen::Vector4d end_point;
    //Rid of these too?
    //double x2, y2;
    //double cx2, cy2;
};


class Curve
{
    private:
        //Rename m_Array to something else?
        FlexArray<Segment> m_Array;
        Segment m_Seg;
        bool segmentClosed;

    public:
        Curve()
            : segmentClosed(false)
          {
              m_Seg.start_point = Eigen::Vector4d(0, 0, 0, 0);
              m_Seg.end_point = Eigen::Vector4d(0, 0, 0, 0);
          }

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
            //m_Seg.x1 = x;
            //m_Seg.y1 = y;
            //m_Seg.cx1 = cx;
            //m_Seg.cy1 = cy;
            m_Seg.start_point = Eigen::Vector4d(x, y, cx, cy);
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
                //m_Seg.x2 = x;
                //m_Seg.y2 = y;
                //m_Seg.cx2 = cx;
                //m_Seg.cy2 = cy;
                m_Seg.end_point = Eigen::Vector4d(x, y, cx, cy);
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