/** Layer Instance [Anari Graphics System]
* Version: 0.1
*
*This class represents one instance of a Layer object that will be
*contained in a Frame object to be sequentially rendered. It contains
*a transformation matrix variable, that describes the manipulation of
*the original Layer object's image.
*The LayerInstance class inherits from both the Observable and Observer
*classes. This is because a LayerInstance wants to know when its parent
*Layer changes properties (like dimensions), and it also wants to update
*the Frame that it's stored in, so that the Frame can update its grid
*appropriately.
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

#ifndef LAYERINSTANCE_H
#define LAYERINSTANCE_H

#include <memory>
#include <Eigen/Dense>
#include "anari/layer.hpp"
#include "anari/observable.hpp"


//Matrix transformation
typedef Eigen::MatrixXf Matrix;
using std::shared_ptr;

class LayerInstance : public Observable, public Observer
{
    public:
        /**Constructor with optional Layer pointer and Matrix parameters
        *\param a Layer pointer that the new LayerInstance will point to.
        *\param Default matrix transformation that the new LayerInstance will implement,
        * as the identity matrix so no changes will be made to original matrix.*/
        LayerInstance(Layer* newLayer, Matrix newMatrix);

         ///Destructor
        virtual ~LayerInstance();

        //Sets and Gets
        ///Set Matrix
        void setMatrix(Matrix newMatrix);
        ///Set Layer
        void setLayer(Layer* newLayer);
        ///Get Matrix
        Matrix getMatrix();
        ///Get Layer
        Layer* getLayer();

        ///Set ZPreference
        void setZPreference(int newPref);

        ///Get ZPreference
        int getZPreference();

        //Sets and Gets for min/max partition coordinates
        ///Set X Max Partition
        void setXMaxPart(int newX);

        ///Set Y Max Partition
        void setYMaxPart(int newY);

        ///Set X Min Partition
        void setXMinPart(int newX);

        ///Set Y Min Partition
        void setYMinPart(int newY);

        ///Get X Max Partition
        int getXMaxPart();

        ///Get Y Max Partition
        int getYMaxPart();

        ///Get X Min Partition
        int getXMinPart();

        ///Set Y Min Partition
        int getYMinPart();

        ///Get the x coordinate of the LayerInstance's center point
        int getOriginX();
        ///Get the y coordinate of the LayerInstance's center point
        int getOriginY();


        /**The render method calls the render method of the Layer that the
        *LayerInstance points to, and passes the LayerInstance's transformation
        *matrix as a parameter.*/
        void render();

        //Overidden methods from Observer pattern
        void addObserver(Observer* newObs);
        void removeObserver(Observer* newObs);
        void update();
        unsigned int getNumOfObservers();

        //Overidden method from Observable interface
        void update(int zPref);

        /**Method used to copy the attributes from one LayerInstance to another
        *\param the LayerInstance whose contents will be copied into the
        *   current LayerInstance.*/
        //NOTE: Functions properly, but isn't used in the code
        void copyContentsFrom(LayerInstance that);

        /**Method that adds the current LayerInstance as a subscriber to its
         parent Layer*/
        /*NOTE: This method is no longer used in the code. When the Layer
        *creates a new LayerInstance, the LayerInstance is added as a
        *subscriber then and there, rendering this method obsolete.*/
        void subscribeToLayer();

    protected:
    private:
        ///Variable representing the "parent" Layer
        Layer* layer;

        ///The transformation matrix used for rendering
        Matrix matrix;

        ///This int represents the LayerInstance's "depth" in the Frame.
        int zPreference;

        /**These arrays represent the coordinates of the grid partitions
        *where the LayerInstance appears, the minPart coordinates represent
        *the location of the top left corner, and the maxPart coordinates
        *represent the bottom right corner.*/
        int maxPart[2];
        int minPart[2];

        /**The list of Observers (There will typically only be one Frame
        *that subscribes to a given LayerInstance)*/
        std::list<Observer*> observers;
};

#endif // LAYERINSTANCE_H
