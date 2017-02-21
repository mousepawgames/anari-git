#include "anari/frame.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;

//Constructor
Frame::Frame(int newXDim, int newYDim, int newXPartDim, int newYPartDim,
             string newDesc)
{
    desc = newDesc;
    xDim = newXDim;
    yDim = newYDim;
    xPartDim = newXPartDim;
    yPartDim = newYPartDim;

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


void Frame::initializeGrid(unsigned int xParts, unsigned int yParts)
{
    //Creates a new vector for each x partition and adds it to the grid
    for(unsigned int i = 0; i < xParts; ++i)
    {
        std::vector<std::vector<unsigned int> > xTemp;
        grid.push_back(xTemp);

        /*Creates a new vector for each y partition and adds it to
        the new x vector*/
        for(unsigned int j = 0; j < yParts; ++j)
        {
            std::vector<unsigned int> yTemp;
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

int Frame::getNumLayerInstances()
{
    return (int)layerInstances.size();
}

void Frame::setXDim(int newXDim)
{
    xDim = newXDim;
}

void Frame::setYDim(int newYDim)
{
    yDim = newYDim;
}

void Frame::setXPartDim(int newDim)
{
    xPartDim = newDim;
}

void Frame::setYPartDim(int newDim)
{

    yPartDim = newDim;
}

int Frame::getXDim()
{
    return xDim;
}

int Frame::getYDim()
{
    return yDim;
}

int Frame::getXPartDim()
{
    return xPartDim;
}

int Frame::getYPartDim()
{
    return yPartDim;
}

int Frame::getNumXParts()
{
    return (int)grid.size();
}
int Frame::getNumYParts()
{
    return (int)grid.at(0).size();
}

//Here we have to handle adding the new Layer to the grid
//Because we were not given center coordinates, we will have the object
//located at the origin (0,0)
/*AddLayer method that takes in a Layer pointer and uses it to create a new
*LayerInstance that will be added to the Frame. It adds the LayerInstance
*to the Frame's LayerInstance vector, and inserts the LayerInstance's
*z preference into the Frame's grid structure.*/
void Frame::addLayer(shared_ptr<Layer> newLayer, int index, Matrix newMatrix)
{
    int listSize = (int)layerInstances.size();
    //Check for valid insertion index
    if(index >= 0 && index <= listSize)
    {
        //Get Layer pointer to give us new LayerInstance pointer
        LayerInstance* temp = newLayer->newLayerInstance(newMatrix);
        //Initialize new LayerInstance attributes
        temp->setZPreference(index);
        temp->addObserver(this);
        //Insert LayerInstance into Frame's LayerInstance vector
        if(index != listSize)
        {
            layerInstances.insert(layerInstances.begin() + index,
                temp);
        }
        /*This logic is different than that in the function above, will
        *reevaluate when I get the chance.*/
        else
        {
            layerInstances.insert(layerInstances.end(), temp);
        }
        //Update the LayerInstance zPrefs in preparation for grid insertion
        updateZPrefs_Add(index);
        /*Check whether or not the new LayerInstance's dimensions fall in
        *the canvas.*/
        if(newLayer->getXDimension() > 0 && newLayer->getYDimension() > 0)
        {
            //Set the min and max partitions where the LayerInstance falls in
            setLayerPartitions(layerInstances.at(index));
            //Add the LayerInstance to the Frame's grid structure
            addLayerToGrid(layerInstances.at(index));
        }
    }
}

/*Inserts a new LayerInstance at the back of the Frame's LayerInstance
*pointer vector*/
void Frame::addLayerLast(shared_ptr<Layer> newLayer)
{
    //Get the Layer pointer to give us a new LayerInstance pointer
    LayerInstance* temp = newLayer->newLayerInstance();
    int zPref = (int)layerInstances.size();
    //Set the new LayerInstance pointer's attributes
    temp->setZPreference(zPref);
    temp->addObserver(this);
    /*Add the new LayerInstance pointer to the back of the Frame's
    LayerInstance vector */
    layerInstances.push_back(temp);

    updateZPrefs_Add(zPref);
    //Test whether or not the LayerInstance falls in the canvas dimensions
    if(newLayer->getXDimension() > 0 && newLayer->getYDimension() > 0)
    {
        //Set the LayerInstance's min and max partitions
        setLayerPartitions(layerInstances.at(zPref));
        //Add the LayerInstance to the Frame's grid
        addLayerToGrid(layerInstances.at(zPref));
    }
}

//Like the above method, only adding the LayerInstance at the beginning
void Frame::addLayerFirst(shared_ptr<Layer> newLayer)
{
    //Get the Layer pointer to give us a new LayerInstance pointer
    LayerInstance* temp = newLayer->newLayerInstance();
    //Add the Frame as a subscriber
    temp->addObserver(this);
    //Insert the LayerInstance pointer in the Frame's LayerInstance vector
    layerInstances.insert(layerInstances.begin(), temp);
    //Update the LayerInstance zPrefs
    updateZPrefs_Add(0);
    //Test if the LayerInstance falls in the Canvas dimensions
    if(newLayer->getXDimension() > 0 && newLayer->getYDimension() > 0)
    {
        //Set the LayerInstance's min and max partitions
        setLayerPartitions(layerInstances.at(0));
        //Add the LayerInstance pointer to the grid
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
        for(int i = newLayer->getXMinPart(); i <= newLayer->getXMaxPart(); ++i)
        {
            /*NOTE: Because the partition origin begins at the bottom left
            *corner, the y value increases as it moves up.*/
            for(int j = newLayer->getYMinPart(); j <= newLayer->getYMaxPart();
             ++j)
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
    if(validPartitions(*deleteMe))
    {
        for(int i = deleteMe->getXMinPart(); i <= deleteMe->getXMaxPart(); ++i)
        {
            for(int j = deleteMe->getYMinPart(); j <= deleteMe->getYMaxPart(); ++j)
            {
                //Delete the LayerInstance from the partition
                deleteFromVector(deleteMe->getZPreference(), &(grid.at(i).at(j)));
            }
        }
    }
}

/*This function accepts a vector of ints and a new int to insert into the
*vector. This function is used to insert the new ZPreference into a grid
*partition.*/
void Frame::insertIntoVector(unsigned int newLayer,
    std::vector<unsigned int>* thisVector)
{
    //Check for empty vector
    if((int)thisVector->size() != 0)
    {
        //Iterate through the vector and insert in order
        for(unsigned int i = 0; i < thisVector->size(); ++i)
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

/*This method takes in a vector of ints and an int representing a new Layer's
*z Preference. The goal is to remove that int from the given vector. It's
*how the grid handles deletion for each partition.*/
void Frame::deleteFromVector(unsigned int deleteMe,
     std::vector<unsigned int>* thisVector)
{
    //Test for empty vector
    if((int)thisVector->size() != 0)
    {
        //Loop through the vector to find the int value
        for(unsigned int i = 0; i < thisVector->size(); ++i)
        {
            //If found, delete the value
            if(thisVector->at(i) == deleteMe)
            {
                thisVector->erase(thisVector->begin() + i);
                break;
            }
        }
    }
}

//Simple method that returns the LayerInstance at the given index
LayerInstance* Frame::getLayerInstanceAt(unsigned int index)
{
    unsigned int listSize = layerInstances.size();
    //Make sure the index is valid
    if(index < listSize)
    {
        //Return the LayerInstance at the given index
        return layerInstances.at(index);
    }
    //Handle exceptions
    else
    {
        return nullptr;
    }
}


//This move method allows the user to move LayerInstance objects in the Frame.
//This move swaps the zPreferences between Layers
void Frame::reorderLayer(unsigned int fromIndex, unsigned int toIndex)
{

    unsigned int listSize = layerInstances.size();
    //Check that both indexes are valid
    if(fromIndex < listSize && toIndex < listSize)
    {
        /*The way this method reorders the LayerInstances is it erases the
        *element at the "fromIndex" position in the Frame's LayerInstance
        *vector, then it reinserts that value into the vector at the specified
        *"toIndex".*/
        LayerInstance* tempInstance = layerInstances.at(fromIndex);
        layerInstances.erase(layerInstances.begin() + fromIndex);
        layerInstances.insert(layerInstances.begin() + toIndex, tempInstance);
        updateZPrefs_Reorder(fromIndex, toIndex);
    }
    //Handle invalid indexes
    else
    {
        cout << "Error: Indexes out of bounds!" << endl;
    }
}


//This method removes a LayerInstance from the Frame
void Frame::removeLayer(unsigned int deleteIndex)
{
    unsigned int listSize = layerInstances.size();
    if(deleteIndex < listSize)
    {
        //Remove the LayerInstance from the grid
        removeLayerFromGrid(layerInstances.at(deleteIndex));
        //Remove the LayerInstance from the Frame's vector of LayerInstances
        delete(layerInstances.at(deleteIndex));
        layerInstances.erase(layerInstances.begin() + deleteIndex);
        //Update the zPreferences
        updateZPrefs_Delete(deleteIndex);
    }
    //Handle the invalid index
    else
    {
        cout << "Error: invalid index." << endl;
    }
}

void Frame::removeLayer(Layer* deleteLayer)
{
    for(unsigned int i = 0; i < layerInstances.size(); ++i)
    {
        if(layerInstances.at(i)->getLayer() == deleteLayer)
        {
            removeLayerFromGrid(layerInstances.at(i));
            delete(layerInstances.at(i));
            layerInstances.erase(layerInstances.begin() + i);
            updateZPrefs_Delete(i);
            break;
        }
    }
}

//This method empties out the Frame's LayerInstance vector and grid.
void Frame::clearFrame()
{
    //Clear layerInstances vector
    while(layerInstances.size() != 0)
    {
        delete(layerInstances.at(0));
        layerInstances.erase(layerInstances.begin());
    }
    //Loop through grid and empty each partition
    for(unsigned int i = 0; i < grid.size(); ++i)
    {
        for(unsigned int j = 0; j < grid.at(0).size(); ++j)
        {
            grid.at(i).at(j).clear();
        }
    }
}

//Helper method that swaps LayerInstances in the Frame
void Frame::swapLayerInstance(unsigned int fromIndex, unsigned int toIndex)
{
    //Check for valid indexes
   if(fromIndex < layerInstances.size() && toIndex < layerInstances.size())
   {
       //Swap the LayerInstances in the Frame
       LayerInstance* temp = layerInstances.at(fromIndex);
       layerInstances.at(fromIndex) = layerInstances.at(toIndex);
       layerInstances.at(toIndex) = temp;
       //Update the LayerInstances' zPreferences
       updateZPrefs_Reorder(fromIndex, toIndex);
   }
   //Handle invalid indexes
   else
   {
       //Index out of bounds
       if(layerInstances.size() == 0)
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
/*void Frame::updateZPrefs()
{
    //Loop through the LayerInstances and set the zPreferences
    for(int i = 0; i < (int)layerInstances.size(); i++)
    {
        layerInstances.at(i)->setZPreference(i);
    }
    //Go through grid and account for changes
    for(int i = 0; i < (int)grid.size(); i++)
    {
        for(int j = 0; j < (int)grid.at(i).size(); j++)
        {
            sortInts(&grid.at(i).at(j));
        }
    }
}*/

//This method updates the z prefs BEFORE the new layerInstance is added to
//the grid.
void Frame::updateZPrefs_Add(unsigned int newLayerIndex)
{
    //Loop through the LayerInstances and set the zPreferences
    for(unsigned int i = 0; i < layerInstances.size(); ++i)
    {
        layerInstances.at(i)->setZPreference(i);
    }
    //Go through grid and account for changes
    for(unsigned int i = 0; i < grid.size(); ++i)
    {
        for(unsigned int j = 0; j < grid.at(i).size(); ++j)
        {
            //Loop through each partition and increment any index that
            //appears after the insertion index.
            for(unsigned int k = 0; k < grid.at(i).at(j).size(); ++k)
            {
                if(grid.at(i).at(j).at(k) >= newLayerIndex)
                {
                    ++grid.at(i).at(j).at(k);
                }
            }
        }
    }
    //Now the grid should be ready to insert the new LayerInstance
}

//This method will update the z preferences of all of the LayerInstances
//AFTER the layerInstance has been removed from the Frame.
void Frame::updateZPrefs_Delete(unsigned int deletedIndex)
{
    //Loop through the LayerInstances and set the zPreferences
    for(unsigned int i = 0; i < layerInstances.size(); ++i)
    {
        layerInstances.at(i)->setZPreference(i);
    }
    //Go through grid and account for changes
    for(unsigned int i = 0; i < grid.size(); ++i)
    {
        for(unsigned int j = 0; j < grid.at(i).size(); ++j)
        {
            //Loop through each partition and decrement any index that
            //appears after the insertion index.
            for(unsigned int k = 0; k < grid.at(i).at(j).size(); ++k)
            {
                if(grid.at(i).at(j).at(k) > deletedIndex)
                {
                    --grid.at(i).at(j).at(k);
                }
            }
        }
    }
}

void Frame::updateZPrefs_Reorder(unsigned int fromIndex, unsigned int toIndex)
{
    //Loop through the LayerInstances and set the zPreferences
    for(unsigned int i = 0; i < layerInstances.size(); ++i)
    {
        layerInstances.at(i)->setZPreference(i);
    }
    //Go through grid and account for changes
    for(unsigned int i = 0; i < grid.size(); ++i)
    {
        for(unsigned int j = 0; j < grid.at(i).size(); ++j)
        {
            /*Loop through the contents of each partition and account for
            *layer reordering. This kind of looks like a scary statement,
            *but the basic logic behind it is this: Update the index of the
            *layer we want to move to the desired destination index. Then,
            *if that Layer is moving forward, decrement all of the other
            *zPreferences that are between the origin and the destination.
            *If the Layer is moving backward, increment all of the Z
            *preferences between the origin and the destination.*/
            for(unsigned int k = 0; k < grid.at(i).at(j).size(); ++k)
            {
                //Update the zPreference of the layer we're moving
                if(grid.at(i).at(j).at(k) == fromIndex)
                {
                    grid.at(i).at(j).at(k) = toIndex;
                }
                //Test to see if we're moving the LayerInstance forward
                else if(toIndex > fromIndex)
                {
                    if(grid.at(i).at(j).at(k) > fromIndex &&
                       grid.at(i).at(j).at(k) <= toIndex)
                    {
                        --grid.at(i).at(j).at(k);
                    }
                }
                //Otherwise, we're moving the LayerInstance backward
                else
                {
                    if(grid.at(i).at(j).at(k) > toIndex &&
                       grid.at(i).at(j).at(k) <= fromIndex)
                    {
                        ++grid.at(i).at(j).at(k);
                    }
                }
            }
            //After updating the zPreferences, sort the partition
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
        for(curr = layerInstances.begin(); curr != layerInstances.end();
         ++curr)
        {
            (*curr)->render();
        }
    }
}

/*Method that calculates which partition the LayerInstance's top left corner
*falls in*/
int Frame::calcBottomLeftXPart(int bottomLeftXCoord)
{
    //Calculate X Partition
    //Set the tempX variable to the lowest x value possible
    int tempX = 0;
    int minXPart = 0;
    /*Then loop through the different partition ranges in order to find
    *the x partition that the x coordinate falls in.*/
    while(bottomLeftXCoord > tempX + getXPartDim())
    {
        ++minXPart;
        tempX += getXPartDim();
    }
    //Return our result
    return minXPart;
}

//See above
int Frame::calcBottomLeftYPart(int bottomLeftYCoord)
{
    int tempY = 0;
    int minYPart = 0;
    while(bottomLeftYCoord > tempY + getYPartDim())
    {
        ++minYPart;
        tempY += getYPartDim();
    }
    return minYPart;
}

//See above
int Frame::calcTopRightXPart(int topRightXCoord)
{
    /*This function is similar to the one above, except it calculates
    the partition of the bottom right corner of the LayerInstance.*/
    //Calculate X Partition
    //Set the tempX variable to the lowest x value possible
    int tempX = 0;
    int maxXPart = 0;
    while(topRightXCoord > tempX + getXPartDim())
    {
        ++maxXPart;
        tempX += getXPartDim();
    }
    return maxXPart;
}

//See above
int Frame::calcTopRightYPart(int topRightYCoord)
{
    int tempY = 0;
    int maxYPart = 0;
    while(topRightYCoord > tempY + getYPartDim())
    {
        ++maxYPart;
        tempY += getYPartDim();
    }
    return maxYPart;
}



/*This method determines whether or not the LayerInstance's coordinates
*fall within the limits of the canvas. With the way the calcPart methods
*work, this method is just another safety net.*/
bool Frame::validPartitions(LayerInstance newLayer)
{
    if(newLayer.getXMaxPart() >= 0 && newLayer.getXMaxPart() <
       (int)grid.size() && newLayer.getYMaxPart() >= 0 &&
       newLayer.getYMaxPart() < (int)grid.at(0).size() &&
       newLayer.getXMinPart() >= 0 && newLayer.getXMinPart() <
       (int)grid.size() && newLayer.getYMinPart() >= 0 &&
       newLayer.getYMinPart() < (int)grid.at(0).size())
    {
        return true;
    }
    return false;
}

/*This method determines whether or not the given LayerInstance falls within
*the Canvas boundaries. */
void Frame::setLayerPartitions(LayerInstance* testLayer)
{
    //Calculate the min and max coordinate values on the canvas
    int canvasMinX = 0;
    int canvasMinY = 0;
    int canvasMaxX = xDim;
    int canvasMaxY = yDim;
    //Calculate the min and max coordinate values for the LayerInstance
    int layerMinX = testLayer->getOriginX() -
        (testLayer->getLayer()->getXDimension() / 2);
    int layerMinY = testLayer->getOriginY() -
        (testLayer->getLayer()->getYDimension() / 2);
    int layerMaxX = testLayer->getOriginX() +
        (testLayer->getLayer()->getXDimension() / 2);
    int layerMaxY = testLayer->getOriginY() +
        (testLayer->getLayer()->getYDimension() / 2);

    /*This logic statement will weed out any LayerInstances that do not fall
    *within the canvas limits.*/
    if((canvasMinX > layerMaxX) || (canvasMinY > layerMaxY) ||
       (canvasMaxX < layerMinX) || (canvasMaxY < layerMinY))
    {
        testLayer->setXMaxPart(-1);
        testLayer->setYMaxPart(-1);
        testLayer->setXMinPart(-1);
        testLayer->setYMinPart(-1);
    }
    /*Now that we've determined that the Layer and the canvas do intersect,
    *calculate the resulting rectangle and set the LayerInstance's partitions
    *accordingly.*/
    else
    {
        testLayer->setXMinPart(calcBottomLeftXPart(std::max(canvasMinX, layerMinX)));
        testLayer->setYMinPart(calcBottomLeftYPart(std::max(canvasMinY, layerMinY)));
        testLayer->setXMaxPart(calcTopRightXPart(std::min(canvasMaxX, layerMaxX)));
        testLayer->setYMaxPart(calcTopRightYPart(std::min(canvasMaxY, layerMaxY)));
    }
}

/*This is the method where we check to see whether or not the LayerInstance
*has jumped spatial partitions. Will need to evaluate to determine whether
*or not it is performing correctly*/
void Frame::update(int zPref)
{
    LayerInstance* updateMe = layerInstances.at(zPref);
    //Calculate the partitions
    int minX = calcBottomLeftXPart(updateMe->getOriginX() -
                                   (updateMe->getLayer()->getXDimension()/2));
    int minY = calcBottomLeftYPart(updateMe->getOriginY() -
                                   (updateMe->getLayer()->getYDimension()/2));
    int maxX = calcTopRightXPart(updateMe->getOriginX() +
                                 (updateMe->getLayer()->getXDimension()/2));
    int maxY = calcTopRightYPart(updateMe->getOriginY() +
                                 (updateMe->getLayer()->getYDimension()/2));
    //Test to see if the new partitions are equal to the current ones
    if(minX != updateMe->getXMinPart() || minY != updateMe->getYMinPart() ||
       maxX != updateMe->getXMaxPart() || maxY != updateMe->getYMaxPart())
    {
        /*if it did jump partitions, remove from grid, update partitions,
        *then add to new partitions*/
        removeLayerFromGrid(layerInstances.at(zPref));
        setLayerPartitions(layerInstances.at(zPref));
        addLayerToGrid(layerInstances.at(zPref));
    }
}

/*This method accepts a pointer to a vector of ints as input and sorts the
*elements in the vector. It's a helper method to sort grid partitions.*/
void Frame::sortInts(std::vector<unsigned int>* thisVector)
{
    //The following logic implements the insertion sort algorithm
    if((int)thisVector->size() > 1)
    {
        for(unsigned int index = 1; index < thisVector->size(); ++index)
        {
            unsigned int key = thisVector->at(index);
            unsigned int position = index;
            while(position > 0 && key < thisVector->at(position-1))
            {
                thisVector->at(position) = thisVector->at(position - 1);
                position --;
            }
            thisVector->at(position) = key;
        }
    }
}

bool Frame::containsLayer(Layer* testLayer)
{
    for(unsigned int i = 0; i < layerInstances.size(); ++i)
    {
        if(layerInstances.at(i)->getLayer() == testLayer)
        {
            return true;
        }
    }
    return false;
}

/*
* Return the frame's grid to display in testing
*/
std::vector< std::vector< std::vector<unsigned int> > > Frame::getGrid() {
    return grid;
}
