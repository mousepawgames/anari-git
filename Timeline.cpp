/**
*Anari Graphics System, version 0.1
*Timeline Class
*This file defines the Timeline class. It's basically a vector of Frames
*that's iterated through and rendered in order to display the animation.
*Last Updated: 16 April 2016
*
*Copyright (C) MousePaw Games
*Licensing:
*/

#include "Timeline.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;


//Constructor that creates a timeline with the given number of Frames
Timeline::Timeline(int startingLength)
{
    //Make sure the number of Frames is greater than zero
    if(startingLength > 0)
    {
        for(int i = 0; i < startingLength; i++)
        {
            frames.push_back(getNewFrame());
        }
    }
    //Set up default dimensions
    xDim = 1920;
    yDim = 1080;
    xPartDim = 480;
    yPartDim = 270;
}

//Destructor
Timeline::~Timeline()
{
    while((int)frames.size() != 0)
    {
        delete(frames.at(0));
        frames.erase(frames.begin());
    }
}

//Set and get methods
int Timeline::getNumberOfFrames()
{
    return (int)frames.size();
}

int Timeline::getNumberOfLayers()
{
    return (int)layers.size();
}

void Timeline::setXPartDim(int newDim)
{
    xPartDim = newDim;
}

void Timeline::setYPartDim(int newDim)
{
    yPartDim = newDim;
}

int Timeline::getXPartDim()
{
    return xPartDim;
}

int Timeline::getYPartDim()
{
    return yPartDim;
}


void Timeline::setXDim(int newDim)
{
    xDim = newDim;
}

void Timeline::setYDim(int newDim)
{
    yDim = newDim;
}

int Timeline::getXDim()
{
    return xDim;
}

int Timeline::getYDim()
{
    return yDim;
}

//Basic functions to edit vector "frames"

Frame* Timeline::getNewFrame()
{
    Frame* newFrame = new Frame(xDim, yDim, xPartDim, yPartDim);
    return newFrame;
}


//This method inserts a new Frame at the given index
void Timeline::addFrame(int index)
{
    int listSize = (int)frames.size();
    //Check for valid index value
    if(index >= 0 && index <= listSize)
    {
        //Create new Frame
        Frame* newFrame = getNewFrame();
        /*Loop through Timeline's Layer and add a new LayerInstance to the
        *new Frame for each.*/
        for(int i = 0; i < getNumberOfLayers(); i++)
        {
            newFrame->addLayerLast(layers.at(i));
        }
        //Test for edgecase, where we add it at the end
        if(index == listSize)
        {
            frames.push_back(newFrame);
        }
        //Otherwise, just insert it at the given index
        else
        {
            frames.insert(frames.begin() + index, newFrame);
        }
    }
}


//Method that adds a new Layer to the Timeline with an initial Matrix value
void Timeline::addLayer(shared_ptr<Layer> newLayer, int index, Matrix newMatrix)
{
    //Check for valid index
    if(index >= 0 && index <= getNumberOfLayers())
    {
        //Insert new Layer in the Timeline's Layers vector
        layers.insert(layers.begin() + index, newLayer);
        //Loop through all of the Frames and add the new Layer to each
        for(int i = 0; i < getNumberOfFrames(); i++)
        {
            frames.at(i)->addLayer(newLayer, index, newMatrix);
        }
    }
}

//Not implementing SOL at this time
/*void Timeline::insertSOL(SOL* newSOL, int layerIndex, int frameIndex)
{
    //Checking indexes for validity
    if(layerIndex >= 0 &&
       (layerIndex < this->numberOfLayers || layerIndex == 0) &&
       frameIndex >= 0 &&
       (frameIndex < this->numberOfFrames || frameIndex ==0 ))
    {
        //Insert insertion code here
    }
}*/

//Method that returns the Layer pointer at the given index
shared_ptr<Layer> Timeline::getLayerAt(int index)
{
    //Check for valid index
    if(index >= 0 && index < getNumberOfLayers())
    {
        return layers.at(index);
    }
    //Handle invalid index
    else
    {
        return nullptr;
    }
}

//Method that returns the Frame pointer at the given index
Frame* Timeline::getFrameAt(int index)
{
    //Check for valid index
    if(index >= 0 && index < getNumberOfFrames())
    {
        return frames.at(index);
    }
    //Handle invalid index
    else
    {
        return nullptr;
    }
}

//Method that removes a Layer from the Timeline at the given index
void Timeline::deleteLayer(int deleteIndex)
{
    //Check for valid index
    if(deleteIndex >= 0 && deleteIndex < getNumberOfLayers())
    {
        /*Remove the given LayerInstance from all of the Frames
        in the animation*/
        for(int i = 0; i < getNumberOfFrames(); i++)
        {
            frames.at(i)->removeLayer(&(*layers.at(deleteIndex)));
        }
        //Remove the layer from the vector of Layer pointers
        layers.erase(layers.begin() + deleteIndex);
    }
}

//Method that deletes a Frame from the Timeline at the given index
void Timeline::deleteFrame(int deleteIndex)
{
    //Check for valid index
    if(deleteIndex >= 0 && deleteIndex < getNumberOfFrames())
    {
        //Remove frame from the vector
        delete(*(frames.begin() + deleteIndex));
        frames.erase(frames.begin() + deleteIndex);
    }
}

//This method allows the user to edit a Frame in the Timeline
void Timeline::editFrame(int frameIndex)
{
    if(frameIndex < 0 || frameIndex >= (int)frames.size())
    {
        cout << "Error: The requested index was out of bounds." << endl;
    }
    else
    {
        frames.at(frameIndex)->editMode();
    }
}

/*Method that moves a Frame from the index in the first argument to the
index in the second.*/
void Timeline::reorderFrame(int indexFrom, int indexTo)
{
    //Check to make sure that both indexes are valid
    if(indexFrom >= 0 && indexFrom < getNumberOfFrames() && indexTo >= 0 &&
        indexTo < getNumberOfFrames() && indexFrom != indexTo)
    {
        Frame* tempFrame = frames.at(indexFrom);
        frames.erase(frames.begin() + indexFrom);
        frames.insert(frames.begin() + indexTo, tempFrame);
    }
    //Handle invalid indexes
    else if (indexTo != indexFrom)
    {
        cout << "Error: Invalid Index" << endl;
    }
}

//Render the Timeline
void Timeline::play()
{
    if(getNumberOfFrames() > 0)
    {
        cout << "Animation Start: \n---------------------------------" << endl;
        //Loop through the Frames in the animation, rendering each one in order
        for(int i = 0; i < getNumberOfFrames(); i++)
        {
            frames.at(i)->render();
            cout << endl;
        }
        cout << "-----------------------------------\nAnimation End" << endl;
    }
    //Handle empty timeline
    else
    {
        cout << "No frames to render" << endl;
    }
}

//Method that plays the Timeline backwards
void Timeline::playBackwards()
{
    if(getNumberOfFrames() > 0)
    {
        cout << "Animation Backwards Start: \n---------------"
        <<"------------------" << endl;
        //Iterate through the Frames in the Timeline backwards
        for(int i = (getNumberOfFrames() - 1); i >=0; i--)
        {
            //Render each Frame
            frames.at(i)->render();
            cout << endl;
        }
        cout << "-----------------------------------\nAnimation End" << endl;
    }
}

void Timeline::displayInfo()
{
    cout << "Timeline Info\n==============\n" << endl;
    cout << "Number of Frames: " << getNumberOfFrames() << endl;
    cout << "Number of Layers: " << getNumberOfLayers() << endl;
    cout << "X Dimension: " << getXDim() << endl;
    cout << "Y Dimension: " << getYDim() << endl;
    cout << "X Partition Dimension: " << getXPartDim() << endl;
    cout << "Y Partition Dimension: " << getYPartDim() << endl;
}

//Helper Methods
//Method that swaps two frames in the Timeline's Frames vector
void Timeline::swapFrame(int fromIndex, int toIndex)
{
    //Check for valid indexes
    if(fromIndex >= 0 && fromIndex < (int)frames.size()
      && toIndex >= 0 && toIndex < (int) frames.size())
   {
       //Swap the frames
       Frame* temp = frames.at(toIndex);
       frames.at(toIndex) = frames.at(fromIndex);
       frames.at(fromIndex) = temp;
   }
   //Handle exceptions
   else
   {
       //Index out of bounds
       if((int)frames.size() == 0)
       {
           cout << "Error: There aren't any frames to swap!" << endl;
       }
       else
       {
           cout << "Error: Index out of bounds!" << endl;
       }

   }
}

//Method that swaps Layers in the Timeline
void Timeline::swapLayer(int fromIndex, int toIndex)
{
    //Check for valid indexes
       if(fromIndex >= 0 && fromIndex < (int)layers.size()
      && toIndex >= 0 && toIndex < (int)layers.size())
   {
       //Swap the Layers
       shared_ptr<Layer> temp = layers.at(toIndex);
       layers.at(toIndex) = layers.at(fromIndex);
       layers.at(fromIndex) = temp;
   }
   //Handle invalid input
   else
   {
       //Index out of bounds
       if((int)layers.size() == 0)
       {
           cout << "Error: Can't swap indexes on an empty frame!" << endl;
       }
       else
       {
           cout << "Error: Index out of bounds!" << endl;
       }

   }
}




