#include "anari/timeline.hpp"
#include "anari/staticlayer.hpp"
//#include "ConsoleUtil.hpp"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::make_shared;

/*
const int PLAY = 1;
const int TIMELINE_INFO = 2;
const int ADD_LAYER = 3;
const int EDIT_LAYER = 4;
const int ADD_FRAME = 5;
const int EDIT_FRAME = 6;
const int DELETE_LAYER = 7;
const int DELETE_FRAME = 8;
const int FRAME_GRID_INFO = 9;
const int INSERT_INSTANCE = 10;
const int DELETE_INSTANCE = 11;
const int EXIT_MENU = 0;
*/

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

//void Timeline::editMode_displayMenu()
//{
//    cout << "Main Timeline" << endl;
//    cout << "=====================" << endl;
//    cout << std::left << std::setw(5) << "1." << "Play from start" << endl;
//    cout << std::left << std::setw(5) << "2." << "Display timeline info" << endl;
//    cout << std::left << std::setw(5) << "3." << "Create new static layer" << endl;
//    cout << std::left << std::setw(5) << "4." << "Edit a layer" << endl;
//    cout << std::left << std::setw(5) << "5." << "Add empty frame to timeline" << endl;
//    cout << std::left << std::setw(5) << "6." << "Edit frame" << endl;
//    cout << std::left << std::setw(5) << "7." << "Delete layer" << endl;
//    cout << std::left << std::setw(5) << "8." << "Delete frame" << endl;
//    cout << std::left << std::setw(5) << "9." << "Display frame grid partion" << endl;
//    cout << std::left << std::setw(5) << "10." << "Insert layer instance into frame" << endl;
//    cout << std::left << std::setw(5) << "11." << "Delete layer instance from frame" << endl;
//    cout << std::left << std::setw(5) << "0." << "Exit" << endl;
//
//}

//void Timeline::editMode()
//{
//    int choice = -1;
//    do
//    {
//        // Display the list of avail1able commands
//        editMode_displayMenu();
//
//        // Get the input from the user
//        string strInput = "";
//
//        getline(std::cin, strInput);
//        try
//        {
//            choice = stoi(strInput);
//        }
//        catch (...)
//        {
//            cout << "Invalid input. Try again." << endl;
//            consolePause();
//            consoleClear();
//            continue;
//        }
//
//        switch (choice)
//        {
//            case PLAY:
//            {
//                consoleClear();
//                play();
//                break;
//            }
//            case TIMELINE_INFO:
//            {
//                consoleClear();
//                displayInfo();
//                break;
//            }
//            case ADD_LAYER:
//            {
//                consoleClear();
//                editMode_addLayer();
//                break;
//            }
//            case EDIT_LAYER:
//            {
//                consoleClear();
//                editMode_editLayer();
//                break;
//            }
//            case ADD_FRAME:
//            {
//                consoleClear();
//                editMode_addFrame();
//                break;
//            }
//            case EDIT_FRAME:
//            {
//                consoleClear();
//                editMode_editFrame();
//                break;
//            }
//            case DELETE_LAYER:
//            {
//                consoleClear();
//                editMode_deleteLayer();
//                break;
//            }
//            case DELETE_FRAME:
//            {
//                consoleClear();
//                editMode_deleteFrame();
//                break;
//            }
//            case FRAME_GRID_INFO:
//            {
//                consoleClear();
//                editMode_displayGrid();
//                break;
//            }
//            case INSERT_INSTANCE:
//            {
//                consoleClear();
//                editMode_insertLayerInstance();
//                break;
//            }
//            case DELETE_INSTANCE:
//            {
//                consoleClear();
//                editMode_deleteLayerInstance();
//                break;
//            }
//            case EXIT_MENU:
//            {
//                cout << "Goodbye!" << endl;
//                break;
//            }
//            default:
//            {
//                cout << "Invalid selection. Try again." << endl;
//                consolePause();
//                consoleClear();
//
//                break;
//            }
//
//        }

        /*// Test the user input against all of the available commands
        if(choice == EDIT_LAYER)
        {
            editMode_editLayer();
        }
        else if(choice == ADD_LAYER)
        {
            editMode_addLayer();
        }
        else if(choice == ADD_FRAME)
        {
            editMode_addFrame();
        }
        else if(choice == DELETE_LAYER)
        {
            editMode_deleteLayer();
        }
        else if(choice == DELETE_FRAME)
        {
            editMode_deleteFrame();
        }
        else if(choice == PLAY)
        {
            play();
        }
        else if(choice == TIMELINE_INFO)
        {
            displayInfo();
        }
        else if(choice == FRAME_GRID_INFO)
        {
            editMode_displayGrid();
        }
        else if(choice == DELETE_INSTANCE)
        {
            editMode_deleteLayerInstance();
        }
        else if(choice == INSERT_INSTANCE)
        {
            editMode_insertLayerInstance();
        }
        else if(choice == EDIT_FRAME)
        {
            editMode_editFrame();
        }
        else if(choice == EXIT_MENU)
        {
            cout << "Goodbye! =)" << endl;
        }
        else
        {
            cout << "Error: Unrecognized command." << endl;
        }*/

//    } while (!(choice == EXIT_MENU));
//
//}

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

//This method allows the user to edit a Frame in the Timeline
void Timeline::editFrame(unsigned int frameIndex)
{
    if(frameIndex >= frames.size())
    {
        cout << "Error: The requested index was out of bounds." << endl;
        //consolePause();
    }
    else
    {
        frames.at(frameIndex)->editMode();
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

//Render the Timeline
void Timeline::play()
{
    if(getNumberOfFrames() > 0)
    {
        cout << "Animation Start: \n---------------------------------" << endl;
        //Loop through the Frames in the animation, rendering each one in order
        for(unsigned int i = 0; i < getNumberOfFrames(); ++i)
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
    //consolePause();
    //consoleClear();
}

//Method that plays the Timeline backwards
void Timeline::playBackwards()
{
    if(getNumberOfFrames() > 0)
    {
        cout << "Animation Backwards Start: \n---------------"
        <<"------------------" << endl;
        //Iterate through the Frames in the Timeline backwards
        for(unsigned int i = getNumberOfFrames(); i-- > 0 ;)
        {
            //Render each Frame
            frames.at(i)->render();
            cout << endl;
        }
        cout << "-----------------------------------\nAnimation End" << endl;
    }
}

//void Timeline::displayInfo()
//{
//    cout << "Timeline Info\n==============" << endl;
//    cout << "Number of Frames: " << getNumberOfFrames() << endl;
//    cout << "Number of Layers: " << getNumberOfLayers() << endl;
//    cout << "X Dimension: " << getXDim() << endl;
//    cout << "Y Dimension: " << getYDim() << endl;
//    cout << "X Partition Dimension: " << getXPartDim() << endl;
//    cout << "Y Partition Dimension: " << getYPartDim() << endl;
//    consolePause();
//    consoleClear();
//}

//Helper Methods
//Method that swaps two frames in the Timeline's Frames vector
//Currently unused
/*void Timeline::swapFrame(unsigned int fromIndex, unsigned int toIndex)
{
    //Check for valid indexes
    if(fromIndex < frames.size() && toIndex < frames.size())
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
       if(frames.size() == 0)
       {
           cout << "Error: There aren't any frames to swap!" << endl;
       }
       else
       {
           cout << "Error: Index out of bounds!" << endl;
       }

   }
}*/

//Method that swaps Layers in the Timeline
//Currently unused
/*void Timeline::swapLayer(unsigned int fromIndex, unsigned int toIndex)
{
    //Check for valid indexes
       if(fromIndex < layers.size() && toIndex < layers.size())
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
       if(layers.size() == 0)
       {
           cout << "Error: Can't swap indexes on an empty frame!" << endl;
       }
       else
       {
           cout << "Error: Index out of bounds!" << endl;
       }

   }
}*/

//void Timeline::editMode_editLayer()
//{
//    //Prompt for the index of the Layer to edit
//    string layerChoice = "";
//    cout << "Enter the index of the layer you would like to edit: ";
//    getline(cin, layerChoice);
//    //Attempt to parse the input to an int
//    try
//    {
//        int layerIndex = stoi(layerChoice);
//        //Test to see that the input index is within the bounds of the vector
//        if(layerIndex >= 0 && layerIndex < (int)getNumberOfLayers())
//        {
//            consoleClear();
//            //Call the requested Layer's editMode function.
//            layers.at(layerIndex)->editMode();
//        }
//        //Handle out-of-bounds index
//        else
//        {
//            cout << "Error: Input was not a valid Layer index." << endl;
//            consolePause();
//        }
//    }
//    //Handle invalid input
//    catch(...)
//    {
//        cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//    }
//    consoleClear();
//}
//
//void Timeline::editMode_addLayer()
//{
//    //Prompt for the insertion index of the Layer
//    string indexString = "";
//    /*Right now we're allowing the user to hit enter and have the insertion
//    *index default to the end of the Timeline's vector of Layers.*/
//    cout << "Enter the index where you would like to insert the new layer."
//    << "\n(Press enter to insert at end)" << endl;
//    getline(cin, indexString);
//    int index = -1;
//    /*If the user just hit enter, set the insertion index to the end
//    of the Timeline's vector of Layers*/
//    if(indexString == "")
//    {
//        index = getNumberOfLayers();
//    }
//    else
//    {
//        //Attempt to parse the user input into an integer
//        try
//        {
//            index = stoi(indexString);
//        }
//        /*If the input was invalid, display an error message and
//        *exit out of the method.*/
//        catch(...)
//        {
//            cout << "Error: Input must be a valid integer." << endl;
//            consolePause();
//            consoleClear();
//            return;
//        }
//    }
//    //Test to see if the index is within the bounds of the vector
//    if(index >= 0 && index <= (int)getNumberOfLayers())
//    {
//        /*If the insertion index is legitimate, prompt for a new image
//        *for the Layer.*/
//        string newImage = "";
//        cout << "Enter a new image (text string) for the Layer: ";
//        getline(cin, newImage);
//        //Create a new Layer and add it to the Timeline
//        addLayer(make_shared<StaticLayer>(newImage), index);
//        /*Once we've created the new Layer, call that Layer's editMode,
//        *so the user can continue customizing it.*/
//        //getLayerAt(index)->editMode();
//    }
//    //Handle out-of-bounds index
//    else
//    {
//        cout << "Error: The requested index was out of range." << endl;
//        consolePause();
//    }
//    consoleClear();
//}
//
//void Timeline::editMode_addFrame()
//{
//    //Prompt the user for an index where they would like to insert a new Frame
//    string indexChoice = "";
//    //For user's reference, provide them with the current number of Frames.
//    cout << "The current number of Frames in the timeline is " <<
//    getNumberOfFrames() << "." << endl;
//
//    /*Right now we'll allow users to just hit "enter" which will add a new
//    *Frame to the end of the Timeline's Frame vector by default.*/
//    cout << "Enter the index that you would like to insert a new Frame into.\n"
//    << "(Press \"enter\" to add the Frame at the end of the Timeline)\n";
//
//    //Get the input from the user
//    getline(cin, indexChoice);
//    //Test for the default case
//    if(indexChoice == "")
//    {
//        //Add the Frame at the end
//        addFrame(getNumberOfFrames());
//    }
//    else
//    {
//        //Attempt to parse the user input to an integer
//        try
//        {
//            int frameIndex = stoi(indexChoice);
//            //Test the index to make sure it's in the vector's bounds
//            if(frameIndex >= 0 && frameIndex <= (int)getNumberOfFrames())
//            {
//                //Insert the new Frame
//                addFrame(frameIndex);
//            }
//            //If the index was out of bounds, display an error message.
//            else
//            {
//                cout << "Error: An invalid index was entered." << endl;
//                consolePause();
//            }
//        }
//        //Handle invalid input
//        catch(...)
//        {
//            cout << "Error: Input must be a valid integer." << endl;
//            consolePause();
//        }
//    }
//    consoleClear();
//}
//
//void Timeline::editMode_deleteLayer()
//{
//    //Prompt the user for the index of the Layer they would like to delete
//    string layerChoice = "";
//    cout << "Enter the index of the Layer you would like to delete: ";
//    getline(cin, layerChoice);
//    //Attempt to parse the input to an integer
//    try
//    {
//        int index = stoi(layerChoice);
//        //Test to make sure that the index is within the vector's bounds
//        if(index >= 0 && index < (int)getNumberOfLayers())
//        {
//            //Delete the Layer from the Timeline
//            deleteLayer(index);
//        }
//        //If the index was out-of-bounds, display an error
//        else
//        {
//            cout << "Error: Specified index was out of range for the timeline."
//            << endl;
//            consolePause();
//        }
//    }
//    //Handle invalid input
//    catch(...)
//    {
//        cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//    }
//    consoleClear();
//}
//
//void Timeline::editMode_deleteFrame()
//{
//    //Prompt for the index of the Frame they would like to delete
//    string indexString = "";
//    cout << "Enter the index of the Frame you would like to delete: ";
//    getline(cin, indexString);
//    //Attempt to parse the input to an integer
//    try
//    {
//        int index = stoi(indexString);
//        //Check to see if the index is within the vector's bounds
//        if(index >= 0 && index < (int)getNumberOfFrames())
//        {
//            //Delete the Frame from the Timeline
//            deleteFrame(index);
//        }
//        //If the index was out-of-bounds, display an error.
//        else
//        {
//            cout << "Error: Specified index was out of range for the timeline."
//            << endl;
//            consolePause();
//        }
//    }
//    //Handle invalid input
//    catch(...)
//    {
//        cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//    }
//    consoleClear();
//}
//
//void Timeline::editMode_displayGrid()
//{
//    string frameString = "";
//    cout << "Enter the index of the Frame whose grid you would like to be"
//    << " displayed." << endl;
//    getline(cin, frameString);
//    try
//    {
//        int frameIndex = stoi(frameString);
//        if(frameIndex >= 0 && frameIndex < (int)getNumberOfFrames())
//        {
//            frames.at(frameIndex)->test_printGridContents();
//        }
//        else
//        {
//            cout << "Error: The requested Frame is out of range." << endl;
//            consolePause();
//        }
//    }
//    catch(...)
//    {
//        cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//    }
//    consoleClear();
//}
//
//void Timeline::editMode_editFrame()
//{
//    string choice = "";
//    cout << "Enter the index of the Frame you want to edit: ";
//    getline(cin, choice);
//    try
//    {
//        int frameIndex = stoi(choice);
//        if(frameIndex < 0 || frameIndex >= (int)getNumberOfFrames())
//        {
//            cout << "Error: Index out of bounds." << endl;
//            consolePause();
//        }
//        else
//        {
//            consoleClear();
//            frames.at(frameIndex)->editMode();
//        }
//    }
//    catch(...)
//    {
//        cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//    }
//    consoleClear();
//}
//
//void Timeline::editMode_deleteLayerInstance()
//{
//    string choice = "";
//    cout << "Enter the index of the Frame you would like to delete the "
//    << "LayerInstance from: ";
//    getline(cin, choice);
//    int frameIndex = -1;
//    int layerInstanceIndex = -1;
//    try
//    {
//       frameIndex = stoi(choice);
//    }
//    catch(...)
//    {
//        cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//        consoleClear();
//        return;
//    }
//    if (frameIndex < 0 || frameIndex >= (int)getNumberOfFrames())
//    {
//        cout << "Error: Index out of bounds." << endl;
//        consolePause();
//        consoleClear();
//        return;
//    }
//    cout << "\nThere are currently " << frames.at(frameIndex)->getNumLayerInstances()
//    << " LayerInstances in the Frame." << endl;
//    cout << "Enter the index of the LayerInstance you would like to delete "
//    << "from the Frame: ";
//    getline(cin, choice);
//    try
//    {
//        layerInstanceIndex = stoi(choice);
//    }
//    catch(...)
//    {
//        cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//        consoleClear();
//        return;
//    }
//    if(layerInstanceIndex < 0 || layerInstanceIndex >=
//       frames.at(frameIndex)->getNumLayerInstances())
//    {
//        cout << "Error: Index out of bounds." << endl;
//        consolePause();
//        consoleClear();
//        return;
//    }
//    frames.at(frameIndex)->removeLayer(layerInstanceIndex);
//    consoleClear();
//}
//
///*The purpose of this method is to insert a LayerInstance that points to an
//*existing Layer in the Timeline into a specified Frame. For example, a user
//*might have deleted a LayerInstance from this Frame, and want to reinsert it.
//*Right now I'm running into the problem where we don't know WHERE in the Frame
//*to reinsert the LayerInstance. The order of the LayerInstances in the Frame
//*can be entirely independent of the order of the Layers in the Timeline. For
//*now I'll prompt the user for an index in the Frame's vector of LayerInstances
//*that we can insert the new LayerInstance into. I'm not sure how we'll want
//*to do this in the future. (I know it's a super huge ugly method at the moment)
//*/
//
//void Timeline::editMode_insertLayerInstance()
//{
//    string choice = "";
//    //Prompt for Frame index
//    cout << "There are currently " << getNumberOfFrames() <<
//    " Frames available in the Timeline." << endl;
//    cout << "Enter the index of the Frame you would like to insert the "
//    << "LayerInstance into: ";
//    getline(cin, choice);
//    int frameIndex = -1;
//    int layerInstanceIndex = -1;
//    int layerIndex = -1;
//    try
//    {
//       frameIndex = stoi(choice);
//    }
//    catch(...)
//    {
//       cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//        consoleClear();
//       return;
//    }
//    if(frameIndex < 0 || frameIndex >= (int)getNumberOfFrames())
//    {
//       cout << "Error: Index out of bounds." <<  endl;
//        consolePause();
//        consoleClear();
//       return;
//    }
//    //Prompt for Timeline Layer index
//    cout << "\nThere are currently " << getNumberOfLayers() <<
//    " Layers available in the Timeline." << endl;
//    cout << "Enter the index of the Layer (in the Timeline) you would like"
//    << "to insert into the Frame: ";
//    getline(cin, choice);
//    try
//    {
//       layerIndex = stoi(choice);
//    }
//    catch(...)
//    {
//       cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//    }
//    if(layerIndex < 0 || layerIndex >= (int)getNumberOfLayers())
//    {
//       cout << "Error: Index out of bounds." << endl;
//        consolePause();
//        consoleClear();
//       return;
//    }
//    //Prompt for LayerInstance index in Frame
//    cout << "\nThere are currently " <<
//    frames.at(frameIndex)->getNumLayerInstances() <<
//    " LayerInstances in the specified Frame." << endl;
//    cout << "Enter the index you would like to insert the LayerInstance " <<
//    "into: ";
//    getline(cin, choice);
//    try
//    {
//       layerInstanceIndex = stoi(choice);
//    }
//    catch(...)
//    {
//       cout << "Error: Input must be a valid integer." << endl;
//        consolePause();
//    }
//    if(layerInstanceIndex < 0 || layerInstanceIndex >
//      frames.at(frameIndex)->getNumLayerInstances())
//    {
//       cout << "Error: Index out of bounds." << endl;
//        consolePause();
//        consoleClear();
//       return;
//    }
//    Layer* testLayer = layers.at(layerIndex).get();
//    if(!frames.at(frameIndex)->containsLayer(testLayer))
//    {
//        frames.at(frameIndex)->addLayer(
//                            layers.at(layerIndex), layerInstanceIndex);
//    }
//    else
//    {
//        cout << "A LayerInstance for that Layer is already contained in the "
//        << "specified Frame." << endl;
//        consolePause();
//    }
//    consoleClear();
//}
//
///*This method allows the user to select the type of Layer they want to insert
//*into the Timeline.
//*Until we have more LayerTypes to add in the Timeline's editMode, we won't be
//*using this method.*/
//int Timeline::editMode_chooseLayerType()
//{
//    string choice = "";
//    int layerType = -1;
//    while(layerType == -1)
//    {
//        cout << "Choose the type of Layer to add to the Timeline." << endl;
//        cout << "1. StaticLayer" << endl;
//        cout << "Choice: ";
//        getline(cin, choice);
//        try
//        {
//            layerType = stoi(choice);
//        }
//        catch(...)
//        {
//            layerType = -1;
//        }
//        if(layerType > 0 && layerType < 2)
//        {
//            return layerType;
//        }
//        else
//        {
//            cout << "Error: Invalid option.";
//            layerType = -1;
//        }
//    }
//    //The method shouldn't get to this point, but return dummy value anyway.
//    return -1;
//}
//
