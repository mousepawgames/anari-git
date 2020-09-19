/** Layer Instance [Anari]
 * Version: 0.1
 *
 * Class to handle tranformations
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
#ifndef ANARI_LAYERINSTANCE_HPP
#define ANARI_LAYERINSTANCE_HPP

#include "Eigen/Core"
#include "anari/transformation.hpp"
using namespace Eigen;

class LayerInstance
{
public:
    Transformation transform;

    /// Default Constructor
    explicit LayerInstance()
    : transform(Transformation())
    {
}

    /** Constructor
    * \param other_transform: Transformation object we are initializing with
    */
    explicit LayerInstance(const Transformation& other_transform)
    : transform()
    {
        this->transform = other_transform;
    }

    /// Copy Constructor
    explicit LayerInstance(const LayerInstance& cpy)
    : transform(cpy.transform)
    {}

    LayerInstance& operator=(const LayerInstance& cmp)
    {
        this->transform = cmp.transform;
        return *this;
    }

    /** Method
    * \param new_matrix: New matrix object we are setting
    */
    void set_matrix(Matrix3d new_matrix)
    {
        this->transform.the_matrix = new_matrix;
    }

    void do_transformation(Matrix3d matrix)
    {
        this->transform.do_transformation(matrix);

        // Do something else with the transformed matrix in transform
    }
};

#endif