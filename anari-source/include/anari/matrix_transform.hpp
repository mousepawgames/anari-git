/** Matrix Transform [Anari]
 * Version: 0.1
 *
 * Class to handle static layer matrix transformations
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

#ifndef ANARI_MATRIXTRANSFORM_HPP
#define ANARI_MATRIXTRANSFORM_HPP

#include "Eigen/Core"
#include "static_layer.hpp"
#include "transformation.hpp"
#include "geometry.hpp"

using namespace Eigen;

class MatrixTransform{

    private:
    StaticLayer static_layer;

    public:
    /// Default Constructor
    explicit MatrixTransform()
    : static_layer()
    {}

    explicit MatrixTransform(const StaticLayer& input_layer)
    : static_layer(input_layer)
    {}

    /// Copy Constructor
    explicit MatrixTransform (const MatrixTransform& matrix_transform)
    : static_layer(matrix_transform.static_layer)
    {}

    ///Copy Assignment
    MatrixTransform& operator=(const MatrixTransform& rhs){
        this->static_layer = rhs.static_layer;
        return *this;
    }


    /// Transform the static layer's Curve variable with the
    /// Transformation class (perhaps maybe the LayerInstance instead)

};

#endif