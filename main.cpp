/*
*Anari Graphics System, version 0.1
*main Class
*Description: This is the main method that tests the functionality of the
*Timeline class as well as Frame, Layer, LayerInstance, and StaticLayer.
*Last Updated: 30 April 2016
*
*Copyright (C) MousePawGames
*Licenses:
*/


#include <iostream>
#include "StaticLayer.hpp"
#include "Frame.hpp"
#include "Timeline.hpp"


using namespace std;

void menu_editLayer(Timeline* master);
void displayMenu();
void menu_addLayer(Timeline* master);
void menu_addFrame(Timeline* master);
void menu_deleteLayer(Timeline* master);
void menu_deleteFrame(Timeline* master);
void menu_displayGrid(Timeline* master);
void menu_editFrame(Timeline* master);
void menu_deleteLayerInstance(Timeline* master);
void menu_insertLayerInstance(Timeline* master);

int main()
{
    string input;

    //Creating Layers to be used in timeline.
    //StaticLayer StaticLayer0 = StaticLayer("J", 1, 810, -720, 10);

    /*Create a new Timeline. The default constructor initializes the
    Timeline dimensions to be 1920x1080 and the partition dimensions
    to 480x270.*/
    Timeline master = Timeline();



    string choice = "";
    /*The following while loop handles the main menu of the Timeline editing
    *program. It prompts the user for a command, and performs the specified
    *command, if the command exists. When the user wants to exit the program,
    *they type the command "exit", and the loop will exit.*/
    while(!(choice == "exit"))
    {
        //Display the list of available commands
        displayMenu();
        //Get the input from the user
        getline(cin, choice);
        //Test the user input against all of the available commands
        if(choice == "editlayer")
        {
            menu_editLayer(&master);
        }
        else if(choice == "addlayer")
        {
            menu_addLayer(&master);
        }
        else if(choice == "addframe")
        {
            menu_addFrame(&master);
        }
        else if(choice == "deletelayer")
        {
            menu_deleteLayer(&master);
        }
        else if(choice == "deleteframe")
        {
            menu_deleteFrame(&master);
        }
        else if(choice == "play")
        {
            master.play();
        }
        else if(choice == "displaytimelineinfo")
        {
            master.displayInfo();
        }
        else if(choice == "displayframegrid")
        {
            menu_displayGrid(&master);
        }
        else if(choice == "deletelayerinstance")
        {
            menu_deleteLayerInstance(&master);
        }
        else if(choice == "insertlayerinstance")
        {
            menu_insertLayerInstance(&master);
        }
        else if(choice == "editframe")
        {
            menu_editFrame(&master);
        }
        else if(choice == "exit")
        {
            cout << "Goodbye! =)" << endl;
        }
        /*If the user's input didn't fit any of the preceding commands,
        *then it was invalid.*/
        else
        {
            cout << "Error: Unrecognized command." << endl;
        }

    }

    /*Test Layers
    StaticLayer StaticLayerA = StaticLayer("A", 250, 250, -480, 0);
        This will appear in sector (0,1), (1,1), (0,2), (1,2)
    StaticLayer StaticLayerB = StaticLayer("B", 250, 250, -1080, 660);
        This will appear in sector (0,3)
    StaticLayer StaticLayerC = StaticLayer("C", 350, 120, -1000, -785);
        This Layer is offscreen, and will not appear in any partition.
    StaticLayer StaticLayerD = StaticLayer("D", 960, 150, 240, 545);
        This will appear in sectors (1,3), (2,3), and (3,3)
    StaticLayer StaticLayerE = StaticLayer("E", 300, 540, 1260, -270);
        This Layer is offscreen and will not appear in any partition
    StaticLayer StaticLayerF = StaticLayer("F", 1920, 1080, 0, 0);
        This Layer will appear in every partition from (0,0) to (3,3)
    StaticLayer StaticLayerG = StaticLayer("G", 300, 540, 480, -135);
        This Layer will appear in partitions (2,0), (3,0), (2,1), (3,1),
        (2,2), and (3,2).
    StaticLayer StaticLayerH = StaticLayer("H", 3840, 2160, 0, 0);
        This Layer will appear in all partitions.
    StaticLayer StaticLayerI = StaticLayer("I", 1, 1, -720, -405);
        This Layer will appear in partition (0,0)
    StaticLayer StaticLayerJ = StaticLayer("J", 1, 810, -720, 10);
        This Layer will appear in partitions (0,0), (0,1), (0,2), (0,3)

                master.addFrame();
        master.getFrameAt(0)->test_printGridContents();
        */

    /*master.play();
    master.getFrameAt(0)->test_printGridContents();
    cout << "Number of observers on Layer 0: " << master.getLayerAt(0)->getNumOfObservers() << endl;
    cout << "Number of observers on LayerInstance 0, 0: " << master.getFrameAt(0)->getLayerInstanceAt(0)->getNumOfObservers() << endl;
    cout << "Testin gupdate method0" << endl;
    getline(cin, input);

    master.getFrameAt(0)->getLayerInstanceAt(0)->update(5);*/
    /*master.play();
    //cout << "Entering edit mode" << endl;
    cout << "Testing delete Frame method" << endl;
    getline(cin, input);
    master.deleteFrame(1);
    master.play();
    master.getFrameAt(0)->test_printGridContents();
    Timeline master2 = Timeline();*/


    //Section that retrieves all pertinent information from a LayerInstance
    /*Frame* myFrame = master.getFrameAt(0);
    LayerInstance *myInstance = myFrame->getLayerInstanceAt(0);
    int xDim = myInstance->getLayer()->getXDimension();
    int yDim = myInstance->getLayer()->getYDimension();
    int originX = myInstance->getOriginX();
    int originY = myInstance->getOriginY();
    int minPartX = myInstance->getXMinPart();
    int minPartY = myInstance->getYMinPart();
    int maxPartX = myInstance->getXMaxPart();
    int maxPartY = myInstance->getYMaxPart();
    int zPref = myInstance->getZPreference();
    cout << "Min Partition: " << minPartX << ", " << minPartY << endl;
    cout << "Max Partition: " << maxPartX << ", " << maxPartY << endl;*/


    /*cout << "\nTest to determine where on the grid the Layer should be located." << endl;

    cout << "\nDimensions of the layer: " << xDim << "x" << yDim << "." << endl;
    cout << "Origin Coordinates: (" << originX << "," << originY << ")" << endl;
    cout << "Calculated Top Left Coordinate: (" << originX - (xDim/2) << "," << originY - (yDim/2) << ")" << endl;
    cout << "Calculated Bottom Right Coordinate: (" << originX + (xDim/2) << "," << originY + (yDim/2) << ")" << endl;
    cout << "Calculated Min Partitions: (" << minPartX << "," << minPartY << ")" << endl;
    cout << "Calculate MaxPartitions: (" << maxPartX << "," << maxPartY << ")" << endl;
    cout << "Zpref should be: 0 but is actually: " << zPref << endl;

    master.addLayer(&StaticLayer1, 1);
    master.play();
    master.getFrameAt(0)->test_printGridContents();*/

    /*Test to prove that the Frame was initialized with the correct dimensions
        cout << "Accessing Frame that was added to the Timeline, checking" <<
    " dimensions and number of partitions." << endl;
    Frame* temp = master.getFrameAt(0);
    if(temp != nullptr)
    {
        int xParts = temp->getNumXParts();
        int yParts = temp->getNumYParts();
        cout << "Frame 1 has " << xParts << " X partitions and " << yParts <<
         " Y parts." << endl;
         int xDim = temp->getXDim();
         int yDim = temp->getYDim();
         int xPartDim = temp->getXPartDim();
         int yPartDim = temp->getYPartDim();
         cout << "\n 1920 : " << xDim << "\n1080 : " << yDim << "\n480 : " << xPartDim << "\n270 : " << yPartDim << endl;
    }*/
    return 0;
}

//This method displays the available commands, and asks the user to choose one
void displayMenu()
{
    cout << "Main Menu" << endl;
    cout << "=====================" << endl;
    cout << "editlayer - Allows the user to edit a layer" << endl;
    cout << "addlayer - Allows the user to add a new Layer" << endl;
    cout << "addframe - Allows the user to add a new Frame" << endl;
    cout << "editframe - Allows the user to edit a Frame in the Timeline"
    << endl;
    cout << "deletelayer - Allows the user to delete a Layer from " <<
    "the timeline" << endl;
    cout << "deleteframe - Allows the user to delete a Frame from the "
    << "timeline" << endl;
    cout << "play - plays the current animation." << endl;
    cout << "displaytimelineinfo - Displays the info about the current"
    << " timeline" << endl;
    cout << "displayframegrid - Displays the grid partitions of a specified"
    << " frame" << endl;
    cout << "deletelayerinstance - Allows the user to delete a LayerInstance"
    << " object from a specified Frame in the Timeline." << endl;
    cout << "insertlayerinstance - Allows the user to insert a LayerInstance"
    << " into a specified Frame. It will not insert a LayerInstance for a "
    << "Layer that is already in the Frame." << endl;
    cout << "exit - Exit the main menu\n" << endl;

}

//Allows the user to add a new Layer to the timeline and edit its contents.
void menu_addLayer(Timeline* master)
{
    //Prompt for the insertion index of the Layer
    string indexString = "";
    /*Right now we're allowing the user to hit enter and have the insertion
    *index default to the end of the Timeline's vector of Layers.*/
    cout << "Enter the index where you would like to insert the new layer. If"
    << "you would like to add the Layer at the end, just hit enter." << endl;
    getline(cin, indexString);
    int index = -1;
    /*If the user just hit enter, set the insertion index to the end
    of the Timeline's vector of Layers*/
    if(indexString == "")
    {
        index = master->getNumberOfLayers();
    }
    else
    {
        //Attempt to parse the user input into an integer
        try
        {
            index = stoi(indexString);
        }
        /*If the input was invalid, display an error message and
        *exit out of the method.*/
        catch(...)
        {
            cout << "Error: Input must be a valid integer." << endl;
            return;
        }
    }
    //Test to see if the index is within the bounds of the vector
    if(index >= 0 && index <= master->getNumberOfLayers())
    {
        /*If the insertion index is legitimate, prompt for a new image
        *for the Layer.*/
        string newImage = "";
        cout << "Enter a new image for the Layer: ";
        getline(cin, newImage);
        //Create a new Layer and add it to the Timeline
        master->addLayer(make_shared<StaticLayer>(newImage), index);
        /*Once we've created the new Layer, call that Layer's editMode,
        *so the user can continue customizing it.*/
        master->getLayerAt(index)->editMode();
    }
    //Handle out-of-bounds index
    else
    {
        cout << "Error: The requested index was out of range." << endl;
    }
}

//Allows a user to edit a Layer in the timeline
void menu_editLayer(Timeline* master)
{
    //Prompt for the index of the Layer to edit
    string layerChoice = "";
    cout << "Enter the index of the layer you would like to edit: ";
    getline(cin, layerChoice);
    //Attempt to parse the input to an int
    try
    {
        int layerIndex = stoi(layerChoice);
        //Test to see that the input index is within the bounds of the vector
        if(layerIndex >= 0 && layerIndex < master->getNumberOfLayers())
        {
            //Call the requested Layer's editMode function.
            master->getLayerAt(layerIndex)->editMode();
        }
        //Handle out-of-bounds index
        else
        {
            cout << "Error: Input was not a valid Layer index." << endl;
        }
    }
    //Handle invalid input
    catch(...)
    {
        cout << "Error: Input must be a valid integer." << endl;
    }

}

//Allows a user to add a new frame to the given timeline.
void menu_addFrame(Timeline* master)
{
    //Prompt the user for an index where they would like to insert a new Frame
    string indexChoice = "";
    //For user's reference, provide them with the current number of Frames.
    cout << "The current number of Frames in the timeline is " <<
    master->getNumberOfFrames() << "." << endl;

    /*Right now we'll allow users to just hit "enter" which will add a new
    *Frame to the end of the Timeline's Frame vector by default.*/
    cout << "Enter the index that you would like to insert a new Frame into,"
    << " or just hit \"enter\" to add the Frame at the end of the Timeline."
    << endl;

    //Get the input from the user
    getline(cin, indexChoice);
    //Test for the default case
    if(indexChoice == "")
    {
        //Add the Frame at the end
        master->addFrame(master->getNumberOfFrames());
    }
    else
    {
        //Attempt to parse the user input to an integer
        try
        {
            int frameIndex = stoi(indexChoice);
            //Test the index to make sure it's in the vector's bounds
            if(frameIndex >= 0 && frameIndex <= master->getNumberOfFrames())
            {
                //Insert the new Frame
                master->addFrame(frameIndex);
            }
            //If the index was out of bounds, display an error message.
            else
            {
                cout << "Error: An invalid index was entered." << endl;
            }
        }
        //Handle invalid input
        catch(...)
        {
            cout << "Error: Input must be a valid integer." << endl;
        }
    }
}

//This method allows users to delete a Layer from the Timeline.
void menu_deleteLayer(Timeline* master)
{
    //Prompt the user for the index of the Layer they would like to delete
    string layerChoice = "";
    cout << "Enter the index of the Layer you would like to delete: ";
    getline(cin, layerChoice);
    //Attempt to parse the input to an integer
    try
    {
        int index = stoi(layerChoice);
        //Test to make sure that the index is within the vector's bounds
        if(index >= 0 && index < master->getNumberOfLayers())
        {
            //Delete the Layer from the Timeline
            master->deleteLayer(index);
        }
        //If the index was out-of-bounds, display an error
        else
        {
            cout << "Error: Specified index was out of range for the timeline."
            << endl;
        }
    }
    //Handle invalid input
    catch(...)
    {
        cout << "Error: Input must be a valid integer." << endl;
    }
}

//This method allows the user to select and delete a Frame from a Timeline
void menu_deleteFrame(Timeline* master)
{
    //Prompt for the index of the Frame they would like to delete
    string indexString = "";
    cout << "Enter the index of the Frame you would like to delete: ";
    getline(cin, indexString);
    //Attempt to parse the input to an integer
    try
    {
        int index = stoi(indexString);
        //Check to see if the index is within the vector's bounds
        if(index >= 0 && index < master->getNumberOfFrames())
        {
            //Delete the Frame from the Timeline
            master->deleteFrame(index);
        }
        //If the index was out-of-bounds, display an error.
        else
        {
            cout << "Error: Specified index was out of range for the timeline."
            << endl;
        }
    }
    //Handle invalid input
    catch(...)
    {
        cout << "Error: Input must be a valid integer." << endl;
    }
}


void menu_displayGrid(Timeline* master)
{
    string frameString = "";
    cout << "Enter the index of the Frame whose grid you would like to be"
    << " displayed." << endl;
    getline(cin, frameString);
    try
    {
        int frameIndex = stoi(frameString);
        if(frameIndex >= 0 && frameIndex < master->getNumberOfFrames())
        {
            master->getFrameAt(frameIndex)->test_printGridContents();
        }
        else
        {
            cout << "Error: The requested Frame is out of range." << endl;
        }
    }
    catch(...)
    {
        cout << "Error: Input must be a valid integer." << endl;
    }
}

//This method allows the user to delete a LayerInstance from a Frame
void menu_deleteLayerInstance(Timeline* master)
{
   string choice = "";
   cout << "Enter the index of the Frame you would like to delete the "
   << "LayerInstance from: ";
   getline(cin, choice);
   int frameIndex = -1;
   int layerInstanceIndex = -1;
   try
   {
       frameIndex = stoi(choice);
   }
   catch(...)
   {
       cout << "Error: Input must be a valid integer." << endl;
       return;
   }
   if(frameIndex < 0 || frameIndex >= master->getNumberOfFrames())
   {
       cout << "Error: Index out of bounds." << endl;
       return;
   }
   cout << "There are currently " << master->getFrameAt(frameIndex)
   ->getNumLayerInstances() << " LayerInstances in the Frame." << endl;
   cout << "Enter the index of the LayerInstance you would like to delete "
   << "from the Frame: ";
   getline(cin, choice);
   try
   {
       layerInstanceIndex = stoi(choice);
   }
   catch(...)
   {
       cout << "Error: Input must be a valid integer." << endl;
       return;
   }
   if(layerInstanceIndex < 0 || layerInstanceIndex >=
      master->getFrameAt(frameIndex)->getNumLayerInstances())
   {
       cout << "Error: Index out of bounds." << endl;
       return;
   }
   master->getFrameAt(frameIndex)->removeLayer(layerInstanceIndex);
}

/*The purpose of this method is to insert a LayerInstance that points to an
*existing Layer in the Timeline into a specified Frame. For example, a user
*might have deleted a LayerInstance from this Frame, and want to reinsert it.
*Right now I'm running into the problem where we don't know WHERE in the Frame
*to reinsert the LayerInstance. The order of the LayerInstances in the Frame
*can be entirely independent of the order of the Layers in the Timeline. For
*now I'll prompt the user for an index in the Frame's vector of LayerInstances
*that we can insert the new LayerInstance into. I'm not sure how we'll want
*to do this in the future. (I know it's a super huge ugly method at the moment)
*/
void menu_insertLayerInstance(Timeline* master)
{
    string choice = "";
    //Prompt for Frame index
    cout << "There are currently " << master->getNumberOfFrames() <<
    " Frames available in the Timeline." << endl;
    cout << "Enter the index of the Frame you would like to insert the "
    << "LayerInstance into: ";
    getline(cin, choice);
    int frameIndex = -1;
    int layerInstanceIndex = -1;
    int layerIndex = -1;
    try
    {
       frameIndex = stoi(choice);
    }
    catch(...)
    {
       cout << "Error: Input must be a valid integer." << endl;
       return;
    }
    if(frameIndex < 0 || frameIndex >= master->getNumberOfFrames())
    {
       cout << "Error: Index out of bounds." << endl;
       return;
    }
    //Prompt for Timeline Layer index
    cout << "There are currently " << master->getNumberOfLayers() <<
    " Layers available in the Timeline." << endl;
    cout << "Enter the index of the Layer (in the Timeline) you would like"
    << "to insert into the Frame: ";
    getline(cin, choice);
    try
    {
       layerIndex = stoi(choice);
    }
    catch(...)
    {
       cout << "Error: Input must be a valid integer." << endl;
    }
    if(layerIndex < 0 || layerIndex >= master->getNumberOfLayers())
    {
       cout << "Error: Index out of bounds." << endl;
       return;
    }
    //Prompt for LayerInstance index in Frame
    cout << "There are currently " <<
    master->getFrameAt(frameIndex)->getNumLayerInstances() <<
    " LayerInstances in the specified Frame." << endl;
    cout << "Enter the index you would like to insert the LayerInstance " <<
    "into: ";
    getline(cin, choice);
    try
    {
       layerInstanceIndex = stoi(choice);
    }
    catch(...)
    {
       cout << "Error: Input must be a valid integer." << endl;
    }
    if(layerInstanceIndex < 0 || layerInstanceIndex >
      master->getFrameAt(frameIndex)->getNumLayerInstances())
    {
       cout << "Error: Index out of bounds." << endl;
       return;
    }
    Layer* testLayer = master->getLayerAt(layerIndex).get();
    if(!master->getFrameAt(frameIndex)->containsLayer(testLayer))
    {
        master->getFrameAt(frameIndex)->addLayer(master->
                            getLayerAt(layerIndex), layerInstanceIndex);
    }
    else
    {
        cout << "A LayerInstance for that Layer is already contained in the "
        << "specified Frame." << endl;
    }

}

//This method allows the user to select a Frame in the Timeline to edit
void menu_editFrame(Timeline* master)
{
    string choice = "";
    cout << "Enter the index of the Frame you want to edit: ";
    getline(cin, choice);
    try
    {
        int frameIndex = stoi(choice);
        if(frameIndex < 0 || frameIndex >= master->getNumberOfFrames())
        {
            cout << "Error: Index out of bounds." << endl;
        }
        else
        {
            master->getFrameAt(frameIndex)->editMode();
        }
    }
    catch(...)
    {
        cout << "Error: Input must be a valid integer." << endl;
    }
}
