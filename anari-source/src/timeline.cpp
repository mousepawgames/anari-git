#include "anari/timeline.hpp"
#include "anari/staticlayer.hpp"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::make_shared;


//Constructor that creates a timeline with the given number of Frames
Timeline::Timeline(unsigned int startingLength)
{
    //Make sure the number of Frames is greater than zero
    if(startingLength > 0)
    {
        for(unsigned int i = 0; i < startingLength; ++i)
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
    while(frames.size() != 0)
    {
        delete(frames.at(0));
        frames.erase(frames.begin());
    }
}

//Set and get methods
unsigned int Timeline::getNumberOfFrames()
{
    return frames.size();
}

unsigned int Timeline::getNumberOfLayers()
{
    return layers.size();
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
void Timeline::addFrame(unsigned int index)
{
    unsigned int listSize = frames.size();
    //Check for valid index value
    if(index <= listSize)
    {
        //Create new Frame
        Frame* newFrame = getNewFrame();
        /*Loop through Timeline's Layer and add a new LayerInstance to the
        *new Frame for each.*/
        for(unsigned int i = 0; i < getNumberOfLayers(); ++i)
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
void Timeline::addLayer(shared_ptr<Layer> newLayer, unsigned int index,
                        Matrix newMatrix)
{
    //Check for valid index
    if(index <= getNumberOfLayers())
    {
        //Insert new Layer in the Timeline's Layers vector
        layers.insert(layers.begin() + index, newLayer);
        //Loop through all of the Frames and add the new Layer to each
        for(unsigned int i = 0; i < getNumberOfFrames(); ++i)
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
shared_ptr<Layer> Timeline::getLayerAt(unsigned int index)
{
    //Check for valid index
    if(index < getNumberOfLayers())
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
Frame* Timeline::getFrameAt(unsigned int index)
{
    //Check for valid index
    if(index < getNumberOfFrames())
    {
        return frames.at(index);
    }
    //Handle invalid index
    else
    {
        return nullptr;
    }
}

//Method that displays the Frame at the given index
void Timeline::displayFrame(unsigned int index)
{
    if(index < frames.size())
    {
        frames.at(index)->render();
    }
}

//Method that removes a Layer from the Timeline at the given index
void Timeline::deleteLayer(unsigned int deleteIndex)
{
    //Check for valid index
    if(deleteIndex < getNumberOfLayers())
    {
        /*Remove the given LayerInstance from all of the Frames
        in the animation*/
        for(unsigned int i = 0; i < getNumberOfFrames(); ++i)
        {
            frames.at(i)->removeLayer(&(*layers.at(deleteIndex)));
        }
        //Remove the layer from the vector of Layer pointers
        layers.erase(layers.begin() + deleteIndex);
    }
}

//Method that deletes a Frame from the Timeline at the given index
void Timeline::deleteFrame(unsigned int deleteIndex)
{
    //Check for valid index
    if(deleteIndex < getNumberOfFrames())
    {
        //Remove frame from the vector
        delete(*(frames.begin() + deleteIndex));
        frames.erase(frames.begin() + deleteIndex);
    }
}

/*Method that moves a Frame from the index in the first argument to the
index in the second.*/
void Timeline::reorderFrame(unsigned int indexFrom, unsigned int indexTo)
{
    //Check to make sure that both indexes are valid
    if(indexFrom < getNumberOfFrames() && indexTo < getNumberOfFrames() &&
       indexFrom != indexTo)
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


