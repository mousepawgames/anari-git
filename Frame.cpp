/**
*Anari Graphics System, version 0.1
*Frame Class
*This is the definition of the methods for Frame.hpp
*Last Updated: 19 February 2016
*
*Copyright (C) MousePaw Games
*Licensing:
*/

#include "Frame.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

//Constructor
Frame::Frame(int newXDim, int newYDim, int newXPartDim, int newYPartDim,
             string newDesc)
{
    this->desc = newDesc;
    this->xDim = newXDim;
    this->yDim = newYDim;
    this->xPartDim = newXPartDim;
    this->yPartDim = newYPartDim;

    //Determine the number of partitions in the grid
    int xParts = xDim/xPartDim;
    int yParts = yDim/yPartDim;

    //Initialize the grid structure
    initializeGrid(xParts, yParts);
}

//Destructor
Frame::~Frame()
{
    while((int)layerInstances.size() != 0)
    {
        delete(layerInstances.at(0));
        layerInstances.erase(layerInstances.begin());
    }
}


void Frame::initializeGrid(int xParts, int yParts)
{
    //Creates a new vector for each x partition and adds it to the grid
    for(int i = 0; i < xParts; i++)
    {
        std::vector<std::vector<int>> xTemp;
        grid.push_back(xTemp);

        /*Creates a new vector for each y partition and adds it to
        the new x vector*/
        for(int j = 0; j < yParts; j++)
        {
            std::vector<int> yTemp;
            grid.at(i).push_back(yTemp);
        }
    }
}

//Sets and gets
void Frame::setDesc(string newDesc)
{
    desc = newDesc;
}

string Frame::getDesc()
{
    return desc;
}

void Frame::setXDim(int newXDim)
{
    this->xDim = newXDim;
}

void Frame::setYDim(int newYDim)
{
    this->yDim = newYDim;
}

//Consider having pointer to timeline value
void Frame::setXPartDim(int newDim)
{
    this->xPartDim = newDim;
}

void Frame::setYPartDim(int newDim)
{

    this->yPartDim = newDim;
}

int Frame::getXDim()
{
    return this->xDim;
}

int Frame::getYDim()
{
    return this->yDim;
}

int Frame::getXPartDim()
{
    return this->xPartDim;
}

int Frame::getYPartDim()
{
    return this->yPartDim;
}

int Frame::getNumXParts()
{
    return (int)this->grid.size();
}
int Frame::getNumYParts()
{
    return (int)this->grid.at(0).size();
}

//Here we have to handle adding the new Layer to the grid
//Because we were not given center coordinates, we will have the object
//centered at the origin (0,0)
/*AddLayer method that takes in a Layer* and uses it to create a new
*LayerInstance that will be added to the Frame. It adds the LayerInstance
*to the Frame's LayerInstance vector, and inserts the LayerInstance's
*z preference into the Frame's grid structure.*/
void Frame::addLayer(Layer* newLayer, int index, Matrix newMatrix)
{
    int listSize = (int)this->layerInstances.size();
    //Check for valid insertion index
    if(index >= 0 && index <= listSize)
    {
        //Get Layer* to give us new LayerInstance*
        LayerInstance* temp = newLayer->newLayerInstance(newMatrix);
        //Initialize new LayerInstance attributes
        temp->setZPreference(index);
        temp->addObserver(this);
        //Insert LayerInstance into Frame's LayerInstance vector
        if(index != listSize)
        {
            this->layerInstances.insert(this->layerInstances.begin() + index,
                temp);
        }
        /*This logic is different than that in the function above, will
        *reevaluate when I get the chance.*/
        else
        {
            this->layerInstances.insert(this->layerInstances.end(), temp);
        }
        //Reset LayerInstance zPrefs
        resetZPrefs();
        /*Check whether or not the new LayerInstance's dimensions fall in
        *the canvas.*/
        if(newLayer->getXDimension() > 0 && newLayer->getYDimension() > 0)
        {
            //Set the min and max partitions where the LayerInstance falls in
            setMaxPart(this->layerInstances.at(index));
            setMinPart(this->layerInstances.at(index));
            //Add the LayerInstance to the Frame's grid structure
            addLayerToGrid(this->layerInstances.at(index));
        }
    }
}

/*Inserts a new LayerInstance at the back of the Frame's LayerInstance*
*vector*/
void Frame::addLayerLast(Layer* newLayer)
{
    //Get the Layer* to give us a new LayerInstance*
    LayerInstance* temp = newLayer->newLayerInstance();
    int zPref = (int)this->layerInstances.size();
    //Set the new LayerInstance*'s attributes
    temp->setZPreference(zPref);
    temp->addObserver(this);
    /*Add the new LayerInstance* to the back of the Frame's
    LayerInstance vector */
    this->layerInstances.push_back(temp);
    //Test whether or not the LayerInstance falls in the canvas dimensions
    if(newLayer->getXDimension() > 0 && newLayer->getYDimension() > 0)
    {
        //Set the LayerInstance's min and max partitions
        setMaxPart(layerInstances.at(zPref));
        setMinPart(layerInstances.at(zPref));
        //Add the LayerInstance to the Frame's grid
        addLayerToGrid(layerInstances.at(zPref));
    }
}

//Like the above method, only adding the LayerInstance at the beginning
void Frame::addLayerFirst(Layer* newLayer)
{
    //Get the Layer* to give us a new LayerInstance*
    LayerInstance* temp = newLayer->newLayerInstance();
    //Add the Frame as a subscriber
    temp->addObserver(this);
    //Insert the LayerInstance* in the Frame's LayerInstance vector
    this->layerInstances.insert(this->layerInstances.begin(), temp);
    //Reset the LayerInstance sPrefs
    resetZPrefs();
    //Test if the LayerInstance falls in the Canvas dimensions
    if(newLayer->getXDimension() > 0 && newLayer->getYDimension() > 0)
    {
        //Set the LayerInstance's min and max partitions
        setMaxPart(layerInstances.at(0));
        setMinPart(layerInstances.at(0));
        //Add the LayerInstance* to the grid
        addLayerToGrid(layerInstances.at(0));
    }
}

//Method used to insert a LayerInstance in the Frames 3D grid
void Frame::addLayerToGrid(LayerInstance* newLayer)
{
    //Test the validity of the partition coordinates
    if(validPartitions(*newLayer))
    {
        /*The next two for loops iterate through all of the partitions that the
        *LayerInstance appears in and inserts the LayerInstance's zPreference.*/
        for(int i = newLayer->getXMinPart(); i <= newLayer->getXMaxPart(); i++)
        {
            for(int j = newLayer->getYMinPart(); j <= newLayer->getYMaxPart();
             j++)
            {
                //Insert the LayerInstance's zPref into the current partition
                insertIntoVector(newLayer->getZPreference(),
                                 &(grid.at(i).at(j)));
            }
        }
    }
}

//Method used to remove a layer from the Frame's 3D grid
void Frame::removeLayerFromGrid(LayerInstance* deleteMe)
{
    /*The next two for loops iterate through all of the partitions that the
    *LayerInstance appears in and deletes it from each partition.*/
    for(int i = deleteMe->getXMinPart(); i <= deleteMe->getXMaxPart(); i++)
    {
        for(int j = deleteMe->getYMinPart(); j <= deleteMe->getYMaxPart(); j++)
        {
            //Delete the LayerInstance from the partition
            deleteFromVector(deleteMe->getZPreference(), &(grid.at(i).at(j)));
        }
    }
}

/*This function accepts a vector<int> and a new int to insert into the
*vector. This function is used to insert the new ZPreference into a grid
*partition.*/
void Frame::insertIntoVector(int newLayer,
    std::vector<int>* thisVector)
{
    //Check for empty vector
    if((int)thisVector->size() != 0)
    {
        //Loop through and account for layer insertion
        /*Because of the design change where we need to use ints representing
        *the zPreferences rather than LayerInstance*s, we need to update the
        *zPreferences that come after the new layer. I will need to reevaluate
        *my design here.*/
        for(int i = 0; i < (int)thisVector->size(); i++)
        {
            //Test for LayerInstances that come after the new layer
          if(thisVector->at(i) >= newLayer)
          {
              //Increment values occurring after new Layer
              thisVector->at(i)++;
          }
        }
        //Iterate through the vector and insert in order
        for(int i = 0; i < (int)thisVector->size(); i++)
        {
            /*Because we're inserting into an ordered list, if we come across
            *a larger value, we know this is where we need to stop.*/
          if(thisVector->at(i) > newLayer)
          {
              thisVector->insert(thisVector->begin() + i, newLayer);
              return;
          }
        }
        //The layer had a greater z preference than all of the others
        thisVector->push_back(newLayer);
    }
    //Else, the vector was empty
    else
    {
        thisVector->push_back(newLayer);
    }
}

/*This method takes in a vector<int> and an int representing a new Layer's
*z Preference. The goal is to remove that int from the given vector. It's
*how the grid handles deletion for each partition.*/
void Frame::deleteFromVector(int deleteMe,
     std::vector<int>* thisVector)
{
    //Test for empty vector
    if((int)thisVector->size() != 0)
    {
        //Loop through the vector to find the int value
        for(int i = 0; i < (int)thisVector->size(); i++)
        {
            //If found, delete the value
            if(thisVector->at(i) == deleteMe)
            {
                thisVector->erase(thisVector->begin() + i);
            }
        }
        /*The purpose of this loop is to account for the Layer's deletion
        *from the vector. Any LayerInstance that was above the old Layer
        *is decremented to account for the deletion.*/
        //NOTE: Need to make sure the value was actually deleted from the array.
        for(int i = 0; i < (int)thisVector->size(); i++)
        {
          if(thisVector->at(i) > deleteMe)
          {
              thisVector->at(i)--;
          }
        }
    }
}

//Simple method that returns the LayerInstance at the given index
LayerInstance* Frame::getLayerInstanceAt(int index)
{
    int listSize = (int)this->layerInstances.size();
    //Make sure the index is valid
    if(index >=0 && (index < listSize || index == 0))
    {
        //Return the LayerInstance at the given index
        return this->layerInstances.at(index);
    }
    //Handle exceptions
    else
    {
        return nullptr;
    }
}


//This move method allows the user to move LayerInstance objects in the Frame.
//This move swaps the zPreferences between Layers
void Frame::reorderLayer(int fromIndex, int toIndex)
{

    int listSize = (int)this->layerInstances.size();
    //Check that both indexes are valid
    if((fromIndex >= 0 && fromIndex < listSize) &&
       (toIndex >= 0 && toIndex < listSize))
    {
        /*The way this method reorders the LayerInstances is it erases the
        *element at the "fromIndex" position in the Frame's LayerInstance
        *vector, then it reinserts that value into the vector at the specified
        *"toIndex".*/
        LayerInstance* tempInstance = layerInstances.at(fromIndex);
        layerInstances.erase(layerInstances.begin() + fromIndex);
        layerInstances.insert(layerInstances.begin() + toIndex, tempInstance);
        resetZPrefs();
        /*NOTE: the following code was the old version of the reorderLayer
        method. I'm keeping it here for the moment.*/
        /*//Determine how many swaps it will take to move the Layer
        int numberOfSwaps = toIndex - fromIndex;
        //Determine in which direction we need to swap the Layers
        if(numberOfSwaps < 0)
        {
            //If numberOfSwaps is negative, we swap Layer backwards
            for(int i = fromIndex; i > toIndex; i--)
            {
                swapLayerInstance(i, i-1);
            }
        }
        //Else, we're moving the Layer forward
        else
        {
            for(int i = fromIndex; i < toIndex; i++)
            {
                swapLayerInstance(i, i+1);
            }
        }*/
    }
    //Handle invalid indexes
    else
    {
        cout << "Error: Indexes out of bounds!" << endl;
    }
}


//This method removes a LayerInstance from the Frame
void Frame::removeLayer(int deleteIndex)
{
    /*Here I cast the layerInstances.size() variable to a signed int,
    *so there would be no issues comparing the two values.*/
    int listSize = (int)layerInstances.size();
    if(deleteIndex < listSize && deleteIndex >= 0)
    {
        //Remove the LayerInstance from the grid
        removeLayerFromGrid(*(layerInstances.begin() + deleteIndex));
        std::cout << "1" << std::endl;
        //Remove the LayerInstance from the Frame's vector of LayerInstances
        delete(*(layerInstances.begin() + deleteIndex));
        std::cout << "2" << std::endl;
        layerInstances.erase(layerInstances.begin() + deleteIndex);
        std::cout << "3" << std::endl;
        //Reset the zPreferences
        resetZPrefs();
    }
    //Handle the invalid index
    else
    {
        cout << "Error: invalid index." << endl;
    }
}

//This method empties out the Frame's LayerInstance vector and grid.
void Frame::clearFrame()
{
    //Clear layerInstances vector
    while((int)layerInstances.size() != 0)
    {
        delete(layerInstances.at(0));
        layerInstances.erase(layerInstances.begin());
    }
    //Loop through grid and empty each partition
    for(int i = 0; i < (int)grid.size(); i++)
    {
        for(int j = 0; j < (int)grid.at(0).size(); j++)
        {
            grid.at(i).at(j).clear();
        }
    }
}

//Helper method that swaps LayerInstances in the Frame
void Frame::swapLayerInstance(int fromIndex, int toIndex)
{
    //Check for valid indexes
   if(fromIndex >= 0 && fromIndex < (int)layerInstances.size()
      && toIndex >= 0 && toIndex < (int) layerInstances.size())
   {
       //Swap the LayerInstances in the Frame
       LayerInstance* temp = layerInstances.at(fromIndex);
       layerInstances.at(fromIndex) = layerInstances.at(toIndex);
       layerInstances.at(toIndex) = temp;
       //Reset the LayerInstances' zPreferences
       resetZPrefs();
   }
   //Handle invalid indexes
   else
   {
       //Index out of bounds
       if((int)layerInstances.size() == 0)
       {
           cout << "Error: Can't swap indexes on an empty frame!" << endl;
       }
       else
       {
           cout << "Error: Index out of bounds!" << endl;
       }

   }
}

//Method that loops through the LayerInstances and updates the zPreferences
void Frame::resetZPrefs()
{
    //Loop through the LayerInstances and set the zPreferences
    for(int i = 0; i < (int)this->layerInstances.size(); i++)
    {
        this->layerInstances.at(i)->setZPreference(i);
    }
    //Go through grid and account for changes
    for(int i = 0; i < (int)grid.size(); i++)
    {
        for(int j = 0; j < (int)grid.at(i).size(); j++)
        {
            sortInts(&grid.at(i).at(j));
        }
    }
}

//Method that renders the contents of the Frame
void Frame::render()
{
    if(layerInstances.size() > 0)
    {
        vector<LayerInstance*>::iterator curr;
        //Loop through the Frame's layerInstances and render each one
        for(curr = this->layerInstances.begin(); curr != layerInstances.end();
         ++curr)
        {
            (*curr)->render();
        }
    }
}

/*Method that calculates which partition the LayerInstance's top left corner
*falls in*/
int Frame::calcTopLeftXPart(LayerInstance instance)
{
    /*In order to calculate the x coordinate of the top left corner of the
    *Layer, take the x coordinate of the Layer's center and subtract half
    *of the Layer's x dimension.*/
    int topLeftXCoord = instance.getOriginX() -
    (instance.getLayer()->getXDimension() / 2);
    //Test whether or not the coordinates fall out of the scene
    if(topLeftXCoord < -(getXDim()/2))
    {
        //If the x coordinate falls outside of the canvas, set to min value
        topLeftXCoord = -(getXDim()/2);
    }
    else if(topLeftXCoord > getXDim()/2)
    {
        //Set to max if off canvas' right side
        topLeftXCoord = getXDim()/2;
    }
    //Now that we know the coordinates of the top left corner,
    //we need to figure out which partition that falls under.
    //Calculate X Partition
    //Set the tempX variable to the lowest x value possible
    int tempX = -(getXDim()/2);
    int minXPart = 0;
    /*Then loop through the different partition ranges in order to find
    *the x partition that the x coordinate falls in.*/
    while(topLeftXCoord > tempX + getXPartDim())
    {
        minXPart++;
        tempX += getXPartDim();
    }
    //Return our result
    return minXPart;
}

//See above
int Frame::calcTopLeftYPart(LayerInstance instance)
{
    int topLeftYCoord = instance.getOriginY() -
    (instance.getLayer()->getYDimension() / 2);
    if(topLeftYCoord  < -(getYDim()/2))
    {
        topLeftYCoord = -(getYDim()/2);
    }
    else if (topLeftYCoord > (getYDim()/2))
    {
        topLeftYCoord = getYDim()/2;
    }
    int tempY = -(getYDim()/2);
    int minYPart = 0;
    while(topLeftYCoord > tempY + getYPartDim())
    {
        minYPart++;
        tempY += getYPartDim();
    }
    return minYPart;
}

//See above
int Frame::calcBottomRightXPart(LayerInstance instance)
{
    /*This function is similar to the one above, except it calculates
    the partition of the bottom right corner of the LayerInstance.*/
    //Calculate the coordinates of the bottom right coordinate of the Layer
    int bottomRightXCoord = instance.getOriginX() +
    (instance.getLayer()->getXDimension() / 2);
    if(bottomRightXCoord < -(getXDim()/2))
    {
        bottomRightXCoord = -(getXDim()/2);
    }
    else if(bottomRightXCoord > getXDim()/2)
    {
        bottomRightXCoord = getXDim()/2;
    }
    //Calculate X Partition
    //Set the tempX variable to the lowest x value possible
    int tempX = -(getXDim()/2);
    int maxXPart = 0;
    while(bottomRightXCoord > tempX + getXPartDim())
    {
        maxXPart++;
        tempX += getXPartDim();
    }
    return maxXPart;
}

//See above
int Frame::calcBottomRightYPart(LayerInstance instance)
{
    int bottomRightYCoord = instance.getOriginY() +
    (instance.getLayer()->getYDimension() / 2);
    if(bottomRightYCoord  < -(getYDim()/2))
    {
        bottomRightYCoord = -(getYDim()/2);
    }
    else if (bottomRightYCoord > (getYDim()/2))
    {
        bottomRightYCoord = getYDim()/2;
    }
    int tempY = -(getYDim()/2);
    int maxYPart = 0;
    while(bottomRightYCoord > tempY + getYPartDim())
    {
        maxYPart++;
        tempY += getYPartDim();
    }
    return maxYPart;
}

/*This method calculates the partitions that the top left corner of the
*layer falls in and sets the minPart values accordingly.*/
void Frame::setMinPart(LayerInstance *instance)
{
    //Set the value for this particular LayerInstance
    instance->setXMinPart(calcTopLeftXPart(*instance));
    instance->setYMinPart(calcTopLeftYPart(*instance));
}

/*This method calculates the partitions that the bottom right corner of
*the layer falls in and sets the maxPart values accordingly.*/
void Frame::setMaxPart(LayerInstance *instance)
{
    //Set the value for this particular LayerInstance
    instance->setXMaxPart(calcBottomRightXPart(*instance));
    instance->setYMaxPart(calcBottomRightYPart(*instance));
}

/*This method determines whether or not the LayerInstance's coordinates
*fall within the limits of the canvas. With the way the calcPart methods
*work, this method is just another safety net.*/
bool Frame::validPartitions(LayerInstance newLayer)
{
    if(newLayer.getXMaxPart() >= 0 && newLayer.getXMaxPart() <
       (int)this->grid.size() && newLayer.getYMaxPart() >= 0 &&
       newLayer.getYMaxPart() < (int)this->grid.at(0).size() &&
       newLayer.getXMinPart() >= 0 && newLayer.getXMinPart() <
       (int)this->grid.size() && newLayer.getYMinPart() >= 0 &&
       newLayer.getYMinPart() < (int)this->grid.at(0).size())
    {
        return true;
    }
    return false;
}

/*This is the method where we check to see whether or not the LayerInstance
*has jumped spatial partitions. Will need to evaluate to determine whether
*or not it is performing correctly*/
void Frame::update(int zPref)
{
    LayerInstance* updateMe = layerInstances.at(zPref);
    //Calculate the partitions
    int minX = calcTopLeftXPart(*updateMe);
    int minY = calcTopLeftYPart(*updateMe);
    int maxX = calcBottomRightXPart(*updateMe);
    int maxY = calcBottomRightYPart(*updateMe);
    //Test to see if the new partitions are equal to the current ones
    if(minX != updateMe->getXMinPart() || minY != updateMe->getYMinPart() ||
       maxX != updateMe->getXMaxPart() || maxY != updateMe->getYMaxPart())
    {
        /*if it did jump partitions, remove from grid, update partitions,
        *then add to new partitions*/
        removeLayerFromGrid(layerInstances.at(zPref));
        setMinPart(layerInstances.at(zPref));
        setMaxPart(layerInstances.at(zPref));
        addLayerToGrid(layerInstances.at(zPref));
    }
}

/*This method accepts a vector<int>* as input and sorts the elements
*in the vector. It's a helper method to sort grid partitions.*/
void Frame::sortInts(std::vector<int>* thisVector)
{
    //The following logic implements the insertion sort algorithm
    if((int)thisVector->size() > 1)
    {
        for(int index = 1; index < (int)thisVector->size(); index++)
        {
            int key = thisVector->at(index);
            int position = index;
            while(position > 0 && key < thisVector->at(position-1))
            {
                thisVector->at(position) = thisVector->at(position - 1);
                position --;
            }
            thisVector->at(position) = key;
        }
    }
}

//Test method that renders the contents of the grid
void Frame::test_printGridContents()
{
    //Loop through the x and y dimensions of the grid
    for(int i = 0; i < (int)grid.at(0).size(); i++)
    {
        for(int j = 0; j < (int)grid.size(); j++)
        {
            //Print out the grid coordinates
            cout << "Sector (" << j << "," << i << ")" << endl;
            for(int k = 0; k < (int)grid.at(j).at(i).size(); k++)
            {
                //Render each LayerInstance in that partition.
                layerInstances.at(k)->render();
                std::cout << std::endl;
            }
        }
    }
}
