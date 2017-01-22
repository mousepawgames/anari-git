/** Frame [Anari Graphics System]
* Version: 0.1
*
*This file defines the Frame class, which contains multiple
*LayerInstance objects. When a Frame is rendered, it displays
*each LayerInstance object to the screen in the order they are stored.
*The LayerInstances together make an entire image, with a LayerInstance
*for the background, a LayerInstance for the middleground, and a character
*in the foreground. LayerInstance images can appear differently on different
*Frames. When Frames are rendered one after the other, it gives the illusion
*of movement, animation.
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

#ifndef FRAME_H
#define FRAME_H

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <Eigen/Dense>
#include "anari/layerinstance.hpp"


using std::string;
using std::vector;

//Matrix transformation
typedef Eigen::MatrixXf Matrix;

/**The Frame class stores LayerInstance objects, and a list of them is
*rendered by the Timeline object, in order to display the animation.*/
class Frame: public Observer
{
    public:

        ///Frame Constructor with an optional string parameter
        Frame(int newXDim, int newYDim, int newXPartDim, int newYPartDim,
              string newDesc="");

        ///Destructor
        virtual ~Frame();

        ///Sets and gets
        void setDesc(string);
        string getDesc();
        int getNumLayerInstances();

        int getXDim();
        int getYDim();
        int getXPartDim();
        int getYPartDim();

        /**Get methods that return the grid dimensions, measured in partitions.
        *For example, a getNumXParts() value of 3 means that the grid is 3
        *partitions wide.**/
        int getNumXParts();
        int getNumYParts();

        /**This method initializes the three-dimensional vector that makes up
        *the grid.
        *\param an int that represents the number of partitions wide the grid
            will be.
        *\param an int that represents the number of partitions tall the grid
            will be.
        */
        void initializeGrid(unsigned int xParts, unsigned int yParts);

        /**addLayer method that accepts a Matrix as an optional parameter.
        *\param a pointer to the Layer we will be adding to the Frame.
        *    (we won't add the Layer itself, we will have it create a new
        *    LayerInstance that will reference its Layer of origin, and
        *    add that LayerInstance to the Frame.)
        *\param an int that represents the insertion index for the new
        *   LayerInstance. It determines where in the LayerInstance vector
        *   we will insert the new LayerInstance
        *\param an optional parameter that sets the transformation matrix
        *   for the new LayerInstance.
        */
        void addLayer(shared_ptr<Layer> newLayer, int index, Matrix newMatrix = Matrix::Identity(1,1));

        /**Add a layer to the end of the Frame's LayerInstance vector. It will
        *essentially add a new LayerInstance to the background.
        *\param a pointer to the new Layer to be added. We will have it create
        *   a new LayerInstance and add that LayerInstance at the back.
        *NOTE: This method functions properly, but I have no use for it at
        *present.*/
        void addLayerLast(shared_ptr<Layer> newLayer);

        /**Add a layer to the front of the Frame's LayerInstance vector.
        *The new LayerInstance will be added to the foreground of the scene.
        *\param a pointer to the new Layer to be added. It will create a new
        *    LayerInstance which we will then insert at the front of the
        *    LayerInstance vector.
        *NOTE: This method functions properly, but I have no use for it at
        *present.*/
        void addLayerFirst(shared_ptr<Layer> newLayer);


        /**This function returns the Frame's LayerInstance at the given
        *index.
        *\param the index of the desired LayerInstance pointer in the Frame's
        *   LayerInstance pointer vector.
        *\return the LayerInstance pointer found at the given index*/
        LayerInstance* getLayerInstanceAt(unsigned int index);

        /**Reorder LayerInstances in the Frame's LayerInstance pointer vector
        *based on index.
        *\param the index of the LayerInstance pointer that will be moved
        *\param the index that the selected LayerInstance pointer will be
        *moved to*/
        void reorderLayer(unsigned int fromIndex, unsigned int toIndex);

        /**Method used to update the grid after changes are made to the
        *Layer's dimensions.
        *\param The index of the LayerInstance pointer in the LayerInstance
        *   pointer vector that will be moved.
        *\param the new x-coordinate on the screen where the LayerInstance
        *   pointer's origin is now located.
        *\param the new y-coordinate on the screen where the LayerInstance
        *   pointer's origin is now located.*/
        void moveLayerOnCanvas(int index, int newX, int newY);

        /**removeLayer method removes a layerInstance from the Frame's
        *layerInstances object by index.
        *\param the index of the LayerInstance pointer in the LayerInstance
        *   pointer vector to be deleted.*/
        void removeLayer(unsigned int deleteIndex);

        /**removeLayer method that takes in a Layer pointer as input. The
        *purpose of this method is to allow users to delete all LayerInstances
        *that point so a particular Layer in the Timeline.
        *\param the Layer pointer that is being removed. All LayerInstances in
        *   the Frame that point to this Layer pointer will be removed.*/
        void removeLayer(Layer* deleteLayer);

        ///clearFrame empties out the Frame's layerInstance* vector.
        void clearFrame();

        /**The render method calls the render method on all of the
        *LayerInstances in the Frame. It will display the
        *LayerInstance images from the background to the foreground.*/
        void render();

        /**Update method inherited from Observer class. Used to update grid
        *based on Layer property changes.
        *\param the zPreference of the LayerInstance pointer in the Frame
        *   that will be updated*/
        void update(int zPref);

        /**Method that determines whether or not there is a LayerInstance
        *for the specified Layer in the Frame.
        *\param the Layer we want to test the Frame for.
        *\return a boolean that indicates whether or not the Frame already
        *   contains a LayerInstance for the given Layer.*/
        bool containsLayer(Layer* testLayer);

        /**Test method, not to be used in actual implementation.
        *It prints the contents of each grid partition to the screen.*/
        void test_printGridContents();

        /**This method allows the user to interact with and edit the Frame at
        *runtime.*/
        void editMode();

    private:
        ///String variable that describes the Frame
        string desc;

        ///Vector that contains all of the LayerInstances in the Frame
        std::vector<LayerInstance*> layerInstances;

        /*The grid was originally meant to contain pointers to LayerInstance
        objects, however after implementing this design I realized that the
        LayerInstance objects were only stored in the Frame's LayerInstance
        vector. In order to have the LayerInstances in the grid update
        appropriately, they needed to point to the actual LayerInstances
        contained in the vector. Unfortunately, pointers to objects in
        vectors are invalidated after simple operations like "insert". I came
        up with a working solution where instead of storing a pointer to the
        LayerInstance, the grid stores that LayerInstance's z Preference. For
        all insertions, swaps, and deletions, I've configured it so that the
        grid updates appropriately. At the moment I'm looking into possibly
        allocating memory for new LayerInstances, so this could change in the
        future. For the moment the 3D grid functions as we need it to.*/
        ///3D Vector structure to represent spatial partitioning
        std::vector< std::vector< std::vector<unsigned int> > > grid;

        ///Int representing x dimension of canvas in pixels
        int xDim;

        ///Int representing y dimension of canvas in pixels
        int yDim;

        ///Int representing x dimension of partitions in pixels
        int xPartDim;

        ///Int representing y dimension of partitions in pixels
        int yPartDim;



        //Private helper methods


        void setXDim(int newXDim);
        void setYDim(int newYDim);
        void setXPartDim(int newDim);
        void setYPartDim(int newDim);

        /**Method that inserts a LayerInstance into the appropriate grid
        *partition
        *\param The LayerInstance pointer that will be added to the grid.*/
        void addLayerToGrid(LayerInstance* newLayer);

        /**Method that removes a particular LayerInstance from the grid
        *\param The LayerInstance pointer that will be removed from the grid*/
        void removeLayerFromGrid(LayerInstance* deleteMe);

        /**Method that determines whether the LayerInstance's dimensions
        *fall in the given canvas dimensions.
        *\param The LayerInstance in question
        *\return a boolean that is true if the LayerInstance falls within
        *   the canvas's boundaries.*/
        bool validPartitions(LayerInstance newLayer);

        /**Methods used to calculate where a Layer falls on the grid.
        *\param The coordinate we are trying to determine which partition
        *   it falls in
        *\return an int that represents the X or Y coordinate of the grid
        *   that was calculated.*/
        int calcBottomLeftXPart(int bottomLeftXCoord);
        int calcBottomLeftYPart(int bottomLeftYCoord);
        int calcTopRightXPart(int topRightXCoord);
        int calcTopRightYPart(int topRightYCoord);

        /**Helper method I defined to swap LayerInstance pointers in the
        *Frame's vector of LayerInstance pointers.
        *\param an int that represents the index of the first LayerInstance
        *   pointer we want to swap
        *\param an int that represents the index of the second LayerInstance
        *   pointer we are going to swap*/
        void swapLayerInstance(unsigned int fromIndex, unsigned int toIndex);

        /**Helper method made to ensure ZPrefs are set properly when a new
        *LayerInstance is added to the Frame. It loops through the vector of
        *LayerInstance pointers and sets each LayerInstance pointer's z
        *preference to its corresponding index in the vector. It will also
        *go through the Grid and update the Z Preference values appropriately.
        *\param an unsigned int that represents the index where the new
        *   LayerInstance was added.*/
        void updateZPrefs_Add(unsigned int newLayerIndex);

        /**Helper method made to ensure ZPrefs are set properly when a
        *LayerInstance is removed from the Frame. It loops through the vector
        *of LayerInstance pointers and sets each LayerInstance pointer's z
        *preference to its corresponding index in the vector. It will also
        *go through the Grid and update the Z Preference values appropriately.
        *\param an unsigned int that represents the index where the
        *   LayerInstance was deleted from.*/
        void updateZPrefs_Delete(unsigned int deletedIndex);

        /**Helper method made to ensure ZPrefs are set properly when a
        *LayerInstance is reordered in the Frame. It loops through the vector
        *of LayerInstance pointers and sets each LayerInstance pointer's z
        *preference to its corresponding index in the vector. It will also
        *go through the Grid and update the Z Preference values appropriately.
        *\param an unsigned int that represents the index of the LayerInstance
        *   that was moved.
        *\param an unsigned int that represents the index of where the
        *   LayerInstance was moved to.*/
        void updateZPrefs_Reorder(unsigned int fromIndex,
                                  unsigned int toIndex);

        /**Helper method that sorts a vector of ints. Currently it sorts the
        *vector using the insertion sort algorithm.
        *\param a pointer to a vector of ints that will be sorted*/
        void sortInts(std::vector<unsigned int>* thisVector);

        /**Method that inserts an int into a vector. This is a helper method
        *for the "addLayerToGrid" method.
        *\param an int that represents the z preference of the Layer that we
        *   will add to the grid.
        *\param the vector of ints that we will insert the z preference into*/
        void insertIntoVector(unsigned int newLayer,
                              std::vector<unsigned int>* thisVector);

        /**Method that removes an int from a vector. This is a helper method
        *for the "removeLayerFromGrid" method.
        *\param the z preference of the Layer that will be removed from the
        *   vector
        *\param the vector of ints that we will remove the z preference from*/
        void deleteFromVector(unsigned int deleteMe,
                              std::vector<unsigned int>* thisVector);

        /**Method that determines whether or not a LayerInstance's image
        *falls within the canvas boundaries. If it determines that the
        *LayerInstance does fall within the canvas limits, then it will set
        *the LayerInstance's min and max partitions accordingly. Otherwise,
        *the min and max partition values will be set to -1.
        *\param the LayerInstance whose dimensions will be tested*/
        void setLayerPartitions(LayerInstance* testLayer);

        //Private helper editMode methods
        void editMode_displayMenu();
        void editMode_setLayerInstanceMatrix();
        void editMode_moveLayerInstance();
};

#endif // FRAME_H
