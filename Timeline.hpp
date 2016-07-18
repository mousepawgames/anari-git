/** Timeline [Anari Graphics System]
* Version: 0.1
*
* This is a more complicated Layer type, representing an independent Timeline/
* animation in the master Timeline.
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

#ifndef TIMELINE_HPP_INCLUDED
#define TIMELINE_HPP_INCLUDED

#include <vector>
#include <memory>
#include "Frame.hpp"


using std::vector;
using std::string;

//NOTE: Using an int in place of Matrix object for the moment
typedef int Matrix;


class Timeline
{
private:

    ///Dimensions of the canvas partitions in pixels
    int xPartDim;
    int yPartDim;

    ///Dimensions of the canvas in pixels
    int xDim;
    int yDim;

    ///The container that stores all of the Frames in the animation
    std::vector<Frame*> frames;

    ///The container that stores references to all of the layers
    std::vector<shared_ptr<Layer>> layers;

    /**Helper method I defined to handle frame swapping
    *\param index of the first frame in the timeline's frame vector to
    *   be swapped
    *\param index of the second frame in the timeline that will be swapped
    *   with the first
    *NOTE: Currently unused*/
    //void swapFrame(unsigned int fromIndex, unsigned int toIndex);

    /**Helper method I defined to handle layer swapping. It swaps Layer
    *pointers in the Timeline's vector of Layer pointers. After the two Layer
    *pointers are swapped, the method will then go through all of the Frames
    *in the Timeline and swap the corresponding LayerInstances for each one.
    *\param the index of the first Layer to be swapped
    *\param the index of the second Layer to be swapped
    *NOTE: Currently unused*/
    //void swapLayer(unsigned int fromIndex, unsigned int toIndex);

    /**Creates a new frame based on the Timeline settings. This method
    *initializes a new Frame pointer with the appropriate grid and partition
    *dimensions.*/
    Frame* getNewFrame();

    /*NOTE: May want to consider an "Active Layer/Frame" mechanic
    Also timeline scrubber, but I'm not sure how that fits in yet.*/

public:
    /**Default Constructor that accepts optional starting length parameter. If
    * a non-zero value is provided, the Timeline will be created with the
    *specified number of Frames.
    *\param an optional int parameter that specifies how many frames will be
    *created for the new Timeline. Default value is zero.*/
    explicit Timeline(unsigned int startingLength=0);

    ///Destructor
    virtual ~Timeline();

    ///Get function to access number of Frames/length of animation.
    unsigned int getNumberOfFrames();

    ///Get function that returns the number of Layers in animation.
    unsigned int getNumberOfLayers();

    ///Sets and Gets functions for x/y partition dimensions
    void setXPartDim(int newDim);
    void setYPartDim(int newDim);
    int getXPartDim();
    int getYPartDim();

    ///Sets and gets for canvas dimensions
    void setXDim(int newDim);
    void setYDim(int newDim);
    int getXDim();
    int getYDim();

    //Basic functions to edit vector "frames"

    /**Inserts a new Frame into the Timeline at the given index
    *\param an int that specifies the index in the Timeline's vector of
    *   Frames that the new Frame will be inserted. It will default to
    *   zero. (The beginning of the vector)*/
    void addFrame(unsigned int index=0);

    /**A method that inserts a new Layer, taking a transformation matrix
    *as an optional parameter.
    *\param a pointer to the Layer we want to add to the Timeline
    *\param the index in the Timeline's Layer pointer vector where the new
    *   Layer will be inserted.
    *\param an optional parameter that specifies the transformation matrix
    *   value of the new LayerInstances that will be created for each Frame.*/
    void addLayer(shared_ptr<Layer> newLayer, unsigned int index,
                  Matrix newMatrix=-1);

    ///A method that inserts an SOL into the timeline, with starting indexes
    //void insertSOL(SOL* newSOL, int layerIndex, int frameIndex);

    /**Returns the Layer pointer at the given index
    *\param the index in the Timeline's vector of Layer pointers where the
    *   requested Layer is located.*/
    shared_ptr<Layer> getLayerAt(unsigned int index);

    /**Retrieves the Frame pointer at the given index
    *\param the index in the Timeline's vector of Frame pointers where the
    *   requested Frame is located.*/
    Frame* getFrameAt(unsigned int index);

    /**This method displays a Frame in the animation at the given index.
    *It's safer than having an outside class retrieve the Frame.
    *\param the index in the Timeline of the requested Frame to render.*/
    void displayFrame(unsigned int index);

    /**Deletes a Layer from the Timeline at the given index. It will delete the
    *Layer in the Timeline's vector of Layer pointers, then it will loop
    *through the Timeline's Frames and delete the corresponding LayerInstance
    *from each.
    *\param The index in the Timeline's vector of Layer pointers that contains
    *   the Layer to be deleted.*/
    void deleteLayer(unsigned int deleteIndex);

    /**Deletes a Frame from the animation at the given index
    *\param the index in the Timeline's vector of Frame pointers that contains
    *   the Frame pointer to be deleted.*/
    void deleteFrame(unsigned int deleteIndex);

    /**This method allows the user to access and edit a Frame in the Timeline.
    *\param the index of the Frame contained within the Timeline.*/
    void editFrame(unsigned int frameIndex);

    /**Moves a Frame from one index location to another in the Timeline's
    *vector of Frame pointers.
    *\param the index in the Timeline's Frame pointer vector that contains the
    *   Frame to be moved.
    *\param the destination index in the Timeline's Frame pointer vector
    *   where we want to move the Frame.*/
    void reorderFrame(unsigned int indexFrom, unsigned int indexTo);

    /**Renders the animation on the screen. It will loop through all of the
    *Frames in the Timeline and render each one in order.*/
    void play();

    /**Renders the animation on the screen backwards. It will loop through all
    *of the Timeline's Frames backwards, and render them one after the other.*/
    /*NOTE: This method currently functions as intended, however it's not
    *particularly useful at this stage, and we may find a better way to
    *achieve this functionality in the future.*/
    void playBackwards();

    void displayInfo();

    //This method initializes the Timeline's editMode menu.
    void editMode();

    void editMode_displayMenu();
    void editMode_editLayer();
    void editMode_addLayer();
    void editMode_addFrame();
    void editMode_deleteLayer();
    void editMode_deleteFrame();
    void editMode_displayGrid();
    void editMode_editFrame();
    void editMode_deleteLayerInstance();
    void editMode_insertLayerInstance();
    int editMode_chooseLayerType();

};

#endif // TIMELINE_HPP_INCLUDED
