#include "anari/staticlayer.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::stoi;
using std::getline;
using std::list;
//Matrix transformation
typedef Eigen::MatrixXf Matrix;

//Constructor
StaticLayer::StaticLayer(Matrix newImage, int xDim, int yDim, int xOrigin,
                         int yOrigin): visibility(true)
{
    image = newImage;
    dim[0] = xDim;
    dim[1] = yDim;
    originCoords[0] = xOrigin;
    originCoords[1] = yOrigin;
}

//Default destructor
StaticLayer::~StaticLayer()
{

}

/*Method that displays the StaticLayer to the screen. It is given a
*transformation matrix as input to help render.*/
void StaticLayer::render(Matrix transformMtx, int frameIndex)
{
    (void)frameIndex;
    //cout << image << "(" << transformMtx << ")";
    image = transformMtx * image;
}

//Sets and gets
Matrix StaticLayer::getImage()
{
    return image;
}

void StaticLayer::setImage(Matrix newImage)
{
    image = newImage;
}

bool StaticLayer::isVisible()
{
    return visibility;
}

void StaticLayer::setVisible(bool newVisibility)
{
    visibility = newVisibility;
}

int StaticLayer::getXDimension()
{
    return dim[0];
}
int StaticLayer::getYDimension()
{
    return dim[1];
}

//Method that sets both the x and y dimensions of the Layer
void StaticLayer::setDimensions(int x, int y)
{
    if(x >= 0 && y >= 0)
    {
        dim[0] = x;
        dim[1] = y;
        //Method that updates all of the Layer's subscribers(LayerInstances)
        update();
    }
}

//Overridden methods from Layer class to set/get origin coordinates
int StaticLayer::getOriginX()
{
    return originCoords[0];
}
int StaticLayer::getOriginY()
{
    return originCoords[1];
}

void StaticLayer::setOriginCoord(int newX, int newY)
{
    originCoords[0] = newX;
    originCoords[1] = newY;
    update();
}


//This method creates a new LayerInstance with an optional matrix param.
LayerInstance* StaticLayer::newLayerInstance(Matrix mtx)
{
    LayerInstance* newInstance = new LayerInstance(this, mtx);
    observers.push_back(newInstance);
    return newInstance;
}

//Overidden Methods from Layer inherited from Observable
//This method adds a new Observer to the list of Observer pointers.
void StaticLayer::addObserver(Observer* newObs)
{
    /*Create a boolean variable to track whether or not the Observer is already
    in the list.*/
    bool alreadySubscribed = false;
    //Loop through and look for the given Observer
    for(list<Observer*>::iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        //If we find it, set the bool test variable to true
        if((*it) == newObs)
        {
            cout << "Item already found in StaticLayer's observers" << endl;
            alreadySubscribed = true;
        }
    }
    //If the Observer isn't already in the list, push it back
    if(!alreadySubscribed)
    {
        observers.push_back(newObs);
    }
}

//Method that removes an Observer from the list of Observer pointers
void StaticLayer::removeObserver(Observer* newObs)
{
    //Iterate through the list looking for the given Observer pointer
    for(list<Observer*>::iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        //If we find it, remove it from the list
        if((*it) == newObs)
        {
            observers.erase(it);
            return;
        }
    }
}

//Update method used to update the Layer's LayerInstances
void StaticLayer::update()
{
    //Iterate through the list of Observers
    for(list<Observer*>::const_iterator it = observers.begin(); it != observers.end(); ++it)
    {
        //Update each individual observer
        (*it)->update();
    }
}

/*Method that returns the number of Observers, or LayerInstances connected
*to this particular Layer.*/
unsigned int StaticLayer::getNumOfObservers()
{
    return observers.size();
}
