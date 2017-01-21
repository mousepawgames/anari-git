#include "StaticLayer.hpp"
#include "ConsoleUtil.hpp"
#include <Eigen/Dense>

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

/*Ambitious function that will allow the user to interface with the
*StaticLayer object. It functions like a command-line application, prompting the
*user for commands.*/
//void StaticLayer::editMode()
//{
//    string input = "";
//    int option = -1;
//    while(option != 9)
//    {
//        cout << "Static Layer Edit Mode \n-------------------------\n";
//        //Prompt for input
//        editMode_help();
//        cout << "Choose an option from the menu:";
//        //Retrieve input
//        getline(cin, input);
//        consoleClear();
//        //Try to parse the input as an int
//        try
//        {
//            option = stoi(input);
//        }
//        //Display an error message
//        catch(...)
//        {
//            option = -1;
//        }
//        //Compare the input to all of the available commands
//        if(option == 1)
//        {
//            editMode_getImage();
//        }
//        else if(option == 2)
//        {
//            editMode_setImage();
//        }
//        else if(option == 3)
//        {
//            editMode_getDim();
//        }
//        else if(option == 4)
//        {
//            editMode_setDim();
//        }
//        else if(option == 5)
//        {
//            editMode_getOrigin();
//        }
//        else if(option == 6)
//        {
//            editMode_setOrigin();
//        }
//        else if(option == 7)
//        {
//            if(editMode_isVisible())
//            {
//                cout << "true" << endl;
//            }
//            else
//            {
//                cout << "false" << endl;
//            }
//            consolePause();
//        }
//        else if(option == 8)
//        {
//            editMode_setVisibility();
//        }
//        /*If the input wasn't any of the available commands, and it's not
//        *the exit value, inform the user that the input was invalid.*/
//        else if(option != 9)
//        {
//            cout << "Error: Unrecognized command." << endl;
//            consolePause();
//        }
//        consoleClear();
//    }
//}

/*The following are all editMode functions. Each essentially represents its
*own editMode command. */

/*This method displays all of the available commands used to interact
//*with the StaticLayer.*/
//void StaticLayer::editMode_help()
//{
//    cout << "Available Commands\n-------------------------" << endl;
//    cout << "1. Get Image: Display Layer image on screen." << endl;
//    cout << "2. Set Image: Command to change the layer image." <<
//    " Prompts for a string." << endl;
//    cout << "3. Get Dimensions: Command to display current image dimensions."
//    << endl;
//    cout << "4. Set Dimensions: Command to change the image dimensions."
//    << " Prompts for X and Y dimensions, must be positive whole numbers."
//    << endl;
//    cout << "5. Get Origin Coordinates: Command to display the current "
//    << "origin coordinates of the Layer." << endl;
//    cout << "6. Set Origin Coordinates: Command to set the origin coordinates"
//    << " of the Layer." << endl;
//    cout << "7. Is Visible: Displays whether or not the layer is currently "
//    << "visible. " << endl;
//    cout << "8. Set Visibility: Command to set the visibility of the Layer. "
//    << "Input must either be \"true\" or \"false\"" << endl;
//    cout << "9. Exit: Exits out of editMode.\n" << endl;
//}

//This method displays the Layer's image to the user
//void StaticLayer::editMode_getImage()
//{
//    cout << "\nLayer Image: " << getImage() << endl;
//    consolePause();
//}

//this method allows the user to set the Layer's image
//void StaticLayer::editMode_setImage()
//{
//    //Prompt for input
//    cout << "Enter new Layer Image:";
//    getline(cin, image);
//}

//This method allows the user to set the Layer's base dimensions
//void StaticLayer::editMode_setDim()
//{
//    //Print out the old values for user reference
//    cout << "Old X Dimension: " << dim[0] << endl;
//    cout << "Old Y Dimension: " << dim[1] << endl;
//    //String that will handle console input
//    string input;
//    //Int that holds the new x dimension
//    int newXDim = 0;
//    //Int that holds the new y dimension
//    int newYDim = 0;
//    //Bool that determines whether or not the input is valid
//    bool validInput = false;
//    //This while loop will execute until the user enters valid input
//    while(!validInput)
//    {
//        //Prompt for new x dimension
//        cout << "Enter new X Dimension: ";
//        getline(cin, input);
//        //Try to parse the input as an int
//        try
//        {
//            newXDim = stoi(input);
//            validInput = true;
//        }
//        //Display an error message
//        catch(...)
//        {
//            cout << "Error: Input must be an integer." << endl;
//        }
//    }
//    //Perform the same method as above to get a new y dimension
//    validInput = false;
//    while(!validInput)
//    {
//        cout << "Enter new Y Dimension: ";
//        getline(cin, input);
//        try
//        {
//            newYDim = stoi(input);
//            validInput = true;
//        }
//        catch(...)
//        {
//            cout << "Error: Input must be an integer." << endl;
//        }
//    }
//    //Test to make sure that the numbers are non-negative
//    if(newXDim >= 0 && newYDim >= 0)
//    {
//        //If they are, update the Layer's dimensions
//        setDimensions(newXDim, newYDim);
//    }
//    //Otherwise, let the user know the input was invalid
//    else
//    {
//        cout << "Error: Dimensions cannot be less than zero." << endl;
//        consolePause();
//    }
//}

//This method displays the Layer dimensions to the user
//void StaticLayer::editMode_getDim()
//{
//    cout << "X Dimension: " << dim[0] << endl;
//    cout << "Y Dimension: " << dim[1] << endl;
//    consolePause();
//}

//void StaticLayer::editMode_setOrigin()
//{
//    //Print out the old values for user reference
//    cout << "Old X Coordinate: " << originCoords[0] << endl;
//    cout << "Old Y Coordinate: " << originCoords[1] << endl;
//    //String that will handle console input
//    string input;
//    //Int that holds the new x coordinate
//    int newXCoord = 0;
//    //Int that holds the new y coordinate
//    int newYCoord = 0;
//    //Bool that determines whether or not the input is valid
//    bool validInput = false;
//    //This while loop will execute until the user enters valid input
//    while(!validInput)
//    {
//        //Prompt for new x origin coordinate
//        cout << "Enter new X Coordinate: ";
//        getline(cin, input);
//        //Try to parse the input as an int
//        try
//        {
//            newXCoord = stoi(input);
//            validInput = true;
//        }
//        //Display an error message
//        catch(...)
//        {
//            cout << "Error: Input must be an integer." << endl;
//        }
//    }
//    //Perform the same method as above to get a new y dimension
//    validInput = false;
//    while(!validInput)
//    {
//        cout << "Enter new Y Coordinate: ";
//        getline(cin, input);
//        try
//        {
//            newYCoord = stoi(input);
//            validInput = true;
//        }
//        catch(...)
//        {
//            cout << "Error: Input must be an integer." << endl;
//        }
//    }
//    //If they are, update the Layer's dimensions
//    setOriginCoord(newXCoord, newYCoord);
//}
//
//void StaticLayer::editMode_getOrigin()
//{
//    cout << "X Origin Coord: " << originCoords[0] << endl;
//    cout << "Y Origin Coord: " << originCoords[1] << endl;
//    consolePause();
//}
//
////This method tells the user whether or not the Layer is visible
//bool StaticLayer::editMode_isVisible()
//{
//    //True if visible, false if invisible.
//    return visibility;
//}
//
////This method allows the user to set whether or not the Layer is visible
//void StaticLayer::editMode_setVisibility()
//{
//    string newVisibility;
//    //Prompt for input
//    cout << "Set the visibility of the layer (true/false):";
//    getline(cin, newVisibility);
//    if(newVisibility == "true")
//    {
//        visibility = true;
//    }
//    else if(newVisibility == "false")
//    {
//        visibility = false;
//    }
//    //Handle invalid option
//    else
//    {
//        cout << "Error: Input must be either \"true\" or \"false\""
//        << endl;
//        consolePause();
//    }
//}
