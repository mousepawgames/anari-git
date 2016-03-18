/**
*Anari Graphics System, version 0.1
*StaticLayer Class
*This class defines all of the methods declared in the StaticLayer.hpp class.
*A StaticLayer is very simple, one layer with no moving parts.
*Last Updated: 24 February 2016
*
*Copyright (C) MousePaw Games
*Licensing:
*/


#include "StaticLayer.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::stoi;
using std::getline;
using std::list;
typedef int Matrix;

//Constructor
StaticLayer::StaticLayer(string newImage)
{
    this->image = newImage;
    this->visibility = true;
    this->dim[0] = 250;
    this->dim[1] = 250;
    this->originCoords[0] = 0;
    this->originCoords[1] = 0;
}

//Default destructor
StaticLayer::~StaticLayer()
{

}

/*Method that displays the StaticLayer to the screen. It is given a
*transformation matrix as input to help render.*/
void StaticLayer::render(Matrix transformMtx)
{
    cout << image << "(" << transformMtx << ")";
}

//Sets and gets
string StaticLayer::getImage()
{
    return this->image;
}

void StaticLayer::setImage(string newImage)
{
    this->image = newImage;
}

bool StaticLayer::isVisible()
{
    return this->visibility;
}

void StaticLayer::setVisible(bool newVisibility)
{
    this->visibility = newVisibility;
}

int StaticLayer::getXDimension()
{
    return this->dim[0];
}
int StaticLayer::getYDimension()
{
    return this->dim[1];
}

//Method that sets both the x and y dimensions of the Layer
void StaticLayer::setDimensions(int x, int y)
{
    if(x >= 0 && y >= 0)
    {
        this->dim[0] = x;
        this->dim[1] = y;
        //Method that updates all of the Layer's subscribers(LayerInstances)
        update();
    }
}

//Overridden methods from Layer class to set/get origin coordinates
int StaticLayer::getOriginX()
{
    return this->originCoords[0];
}
int StaticLayer::getOriginY()
{
    return this->originCoords[1];
}

void StaticLayer::setOriginX(int newX)
{
    this->originCoords[0] = newX;
}
void StaticLayer::setOriginY(int newY)
{
    this->originCoords[1] = newY;
}


//This method creates a new LayerInstance with an optional matrix param.
LayerInstance* StaticLayer::newLayerInstance(Matrix mtx)
{
    LayerInstance* newInstance = new LayerInstance(this, mtx);
    this->observers.push_back(newInstance);
    return newInstance;
}

//Overidden Methods from Layer inherited from Observable
//This method adds a new Observer to the Observer* list
void StaticLayer::addObserver(Observer* newObs)
{
    /*Create a bool variable to track whether or not the Observer is already
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
        this->observers.push_back(newObs);
    }
}

//Method that removes an Observer from the list of Observer*s
void StaticLayer::removeObserver(Observer* newObs)
{
    //Iterate through the list looking for the given Observer*
    for(list<Observer*>::iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        //If we find it, remove it from the list
        if((*it) == newObs)
        {
            observers.erase(it);
            //Test output, will remove once we confirm it works
            cout << "Successful deletion from Layer's observers." << endl;
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
        (*it)->update(0);
    }
}

/*Method that returns the number of Observers, or LayerInstances connected
*to this particular Layer.*/
int StaticLayer::getNumOfObservers()
{
    return (int)this->observers.size();
}

/*Ambitious function that will allow the user to interface with the
*StaticLayer object. It functions like a command-line application, prompting the
*user for commands.*/
void StaticLayer::editMode()
{
    string input = "";
    int option = -1;
    while(option != 7)
    {
        cout << "\nStatic Layer Edit Mode \n-------------------------\n"
        << endl;
        //Prompt for input
        editMode_help();
        cout << "Choose an option from the menu:";
        //Retrieve input
        getline(cin, input);
        //Try to parse the input as an int
        try
        {
            option = stoi(input);
        }
        //Display an error message
        catch(...)
        {
            option = -1;
        }
        //Compare the input to all of the available commands
        if(option == 1)
        {
            editMode_getImage();
        }
        else if(option == 2)
        {
            editMode_setImage();
        }
        else if(option == 3)
        {
            editMode_getDim();
        }
        else if(option == 4)
        {
            editMode_setDim();
        }
        else if(option == 5)
        {
            editMode_isVisible();
        }
        else if(option == 6)
        {
            editMode_setVisibility();
        }
        /*If the input wasn't any of the available commands, and it's not
        *the exit value, inform the user that the input was invalid.*/
        else if(option != 7)
        {
            cout << "Error: Unrecognized command." << endl;
        }
    }
}

/*The following are all editMode functions. Each essentially represents its
*own editMode command. */

/*This method displays all of the available commands used to interact
*with the StaticLayer.*/
void StaticLayer::editMode_help()
{
    cout << "Available Commands\n-------------------------" << endl;
    cout << "1. Get Image: Display Layer image on screen." << endl;
    cout << "2. Set Image: Command to change the layer image." <<
    " Prompts for a string." << endl;
    cout << "3. Get Dimensions: Command to display current image dimensions."
    << endl;
    cout << "4. Set Dimensions: Command to change the image dimensions."
    << " Prompts for X and Y dimensions, must be positive whole numbers."
    << endl;
    cout << "5. Is Visible: Displays whether or not the layer is currently "
    << "visible. " << endl;
    cout << "6. Set Visibility: Command to set the visibility of the Layer. "
    << "Input must either be \"true\" or \"false\"" << endl;
    cout << "7. Exit: Exits out of editMode.\n" << endl;
}

//This method displays the Layer's image to the user
void StaticLayer::editMode_getImage()
{
    cout << "Layer Image: " << getImage() << endl;
}

//this method allows the user to set the Layer's image
void StaticLayer::editMode_setImage()
{
    //Prompt for input
    cout << "Enter new Layer Image:";
    getline(cin, this->image);
}

//This method allows the user to set the Layer's base dimensions
void StaticLayer::editMode_setDim()
{
    //Print out the old values for user reference
    cout << "Old X Dimension: " << this->dim[0] << endl;
    cout << "Old Y Dimension: " << this->dim[1] << endl;
    //String that will handle console input
    string input;
    //Int that holds the new x dimension
    int newXDim = 0;
    //Int that holds the new y dimension
    int newYDim = 0;
    //Bool that determines whether or not the input is valid
    bool validInput = false;
    //This while loop will execute until the user enters valid input
    while(!validInput)
    {
        //Prompt for new x dimension
        cout << "Enter new X Dimension: ";
        getline(cin, input);
        //Try to parse the input as an int
        try
        {
            /*The stoi method attempts to parse a string to an int.
            *it's new in c++11. It does convert any input that starts
            *with a number into an integer, ignoring any anything
            *past the first non-numeric character. e.g. "45rk73b"
            *becomes 45.*/
            newXDim = stoi(input);
            validInput = true;
        }
        //Display an error message
        catch(...)
        {
            cout << "Error: Input must be an integer." << endl;
        }
    }
    //Perform the same method as above to get a new y dimension
    validInput = false;
    while(!validInput)
    {
        cout << "Enter new Y Dimension: ";
        getline(cin, input);
        try
        {
            newYDim = stoi(input);
            validInput = true;
        }
        catch(...)
        {
            cout << "Error: Input must be an integer." << endl;
        }
    }
    //Test to make sure that the numbers are non-negative
    if(newXDim >= 0 && newYDim >= 0)
    {
        //If they are, update the Layer's dimensions
        this->setDimensions(newXDim, newYDim);
    }
    //Otherwise, let the user know the input was invalid
    else
    {
        cout << "Error: Dimensions cannot be less than zero." << endl;
    }
}

//This method displays the Layer dimensions to the user
void StaticLayer::editMode_getDim()
{
    cout << "X Dimension: " << this->dim[0] << endl;
    cout << "Y Dimension: " << this->dim[1] << endl;
}

//This method tells the user whether or not the Layer is visible
bool StaticLayer::editMode_isVisible()
{
    //True if visible, false if invisible.
    return visibility;
}

//This method allows the user to set whether or not the Layer is visible
void StaticLayer::editMode_setVisibility()
{
    string newVisibility;
    //Prompt for input
    cout << "Set the visibility of the layer (true/false):";
    getline(cin, newVisibility);
    if(newVisibility == "true")
    {
        this->visibility = true;
    }
    else if(newVisibility == "false")
    {
        this->visibility = false;
    }
    //Handle invalid option
    else
    {
        cout << "Error: Input must be either \"true\" or \"false\""
        << endl;
    }
}
