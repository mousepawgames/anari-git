/** Layer [Anari Graphics System]
* Version: 0.1
*
*This class is an interface, so far it only contains a stub for a render method.
*Each layer "flavor" should implement this interface.
*The main idea was to be able to utilize polymorphism.
*Ex: (Layer* layer = new IndependentObjectLayer();)
*
* Last Updated: 14 May 2016
* Author: Audrey Henry
*/

/* LICENSE
* Copyright (C) 2016 MousePaw Games.
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

#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <exception>
#include <list>
#include <Eigen/Dense>

#include "anari/observable.hpp"

//Use a forward declaration so we can reference LayerInstance pointers
class LayerInstance;

using std::string;

//Matrix transformation
typedef Eigen::MatrixXf Matrix;

class Layer : public Observable
{
    public:

        ///Constructor
        Layer();

        ///Desctructor
        virtual ~Layer();

        /** The render method that all Layer types will implement.
        *\param the transformation matrix that will be applied to the Layer's
        *   image and affect how it's displayed on the screen. The
        *   transformation matrix can translate, scale, and rotate the image
        *\param an optional int parameter that will be used for more complicated
        *   layer types like SOL. Other layer types will ignore this value.
        *NOTE: For now, I just want the render method to display to the screen,
        *so I'll just have it return void.*/
        virtual void render(Matrix transformationMatrix, int frameNumber=0) = 0;

        //Methods to be implemented by derived classes.
        /**Method that tells whether or not the Layer is currently visible.
        *\return a boolean that is "true" if the Layer is visible, and
        *   "false" if the Layer is not visible.*/
        virtual bool isVisible() = 0;

        /**Method that sets the visibility of the Layer
        *\param a boolean value that sets whether the Layer is visible or not.*/
        virtual void setVisible(bool newVisibility) = 0;

        /**Method that returns a pointer to a new LayerInstance that references
        *the current Layer.
        *\param an optional transformation matrix that will be applied to the
        *   new LayerInstance pointer.
        *\return a new LayerInstance pointer that references the current Layer*/
        virtual LayerInstance* newLayerInstance(Matrix newMatrix = Matrix::Identity(1,1)) = 0;

        ///Methods to get and set the Layer's dimensions on the canvas
        virtual int getXDimension() = 0;
        virtual int getYDimension() = 0;
        virtual void setDimensions(int x, int y) = 0;

        /**Methods that will allow the user to set and retrieve the origin
        *coordinates*/
        ///Get methods for origin coordinates
        virtual int getOriginX() = 0;
        virtual int getOriginY() = 0;

        ///Set methods for origin coordinates.
        virtual void setOriginCoord(int newX, int newY) = 0;

        /**The editMode layer allows derived classes to interface with users
        depending on their unique features. */
        //virtual void editMode() = 0;

        ///Overidden observable methods
        virtual void addObserver(Observer* newObs) = 0;
        virtual void removeObserver(Observer* newObs) = 0;
        virtual void update() = 0;
        virtual unsigned int getNumOfObservers() = 0;
    protected:
    private:
};

#endif // LAYER_H
