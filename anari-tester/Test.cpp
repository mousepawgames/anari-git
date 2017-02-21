//
//  Test.cpp
//  anari
//
//  Created by Andrew Peacock on 1/21/17.
//  Copyright © 2017 MousePaw. All rights reserved.
//

#include "Test.hpp"

void Test::editMode_displayMenu()
{
    ioc << "Main Timeline" << io_end;
    ioc << "=====================" << io_end;
    ioc << "1." << "Play from start" << io_end;
    ioc << "2." << "Display timeline info" << io_end;
    ioc << "3." << "Create new static layer" << io_end;
    ioc << "4." << "Edit a layer" << io_end;
    ioc << "5." << "Add empty frame to timeline" << io_end;
    ioc << "6." << "Edit frame" << io_end;
    ioc << "7." << "Delete layer" << io_end;
    ioc << "8." << "Delete frame" << io_end;
    ioc << "9." << "Display frame grid partion" << io_end;
    ioc << "10." << "Insert layer instance into frame" << io_end;
    ioc << "11." << "Delete layer instance from frame" << io_end;
    ioc << "0." << "Exit" << io_end;

}

void Test::editMode()
{
    timeline = Timeline();
    cpgf::GCallbackList<int (const string &)> cbList;
    int choice = -1;
    do
    {
        // Display the list of avail1able commands
        editMode_displayMenu();

        // Get the input from the user
        string strInput = "";

        getline(std::cin, strInput);
        try
        {
            choice = stoi(strInput);
        }
        catch (...)
        {
            ioc << "Invalid input. Try again." << io_end;
            consolePause();
            consoleClear();
            continue;
        }

        switch (choice)
        {
            case PLAY:
            {
                consoleClear();
                play();
                break;
            }
            case TIMELINE_INFO:
            {
                consoleClear();
                displayInfo();
                break;
            }
            case ADD_LAYER:
            {
                consoleClear();
                editMode_addLayer();
                break;
            }
            case EDIT_LAYER:
            {
                consoleClear();
                editMode_editLayer();
                break;
            }
            case ADD_FRAME:
            {
                consoleClear();
                editMode_addFrame();
                break;
            }
            case EDIT_FRAME:
            {
                consoleClear();
                editMode_editFrame();
                break;
            }
            case DELETE_LAYER:
            {
                consoleClear();
                editMode_deleteLayer();
                break;
            }
            case DELETE_FRAME:
            {
                consoleClear();
                editMode_deleteFrame();
                break;
            }
            case FRAME_GRID_INFO:
            {
                consoleClear();
                editMode_displayGrid();
                break;
            }
            case INSERT_INSTANCE:
            {
                consoleClear();
                editMode_insertLayerInstance();
                break;
            }
            case DELETE_INSTANCE:
            {
                consoleClear();
                editMode_deleteLayerInstance();
                break;
            }
            case EXIT_MENU:
            {
                ioc << "Goodbye!" << io_end;
                break;
            }
            default:
            {
                ioc << "Invalid selection. Try again." << io_end;
                consolePause();
                consoleClear();

                break;
            }

        }

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
         ioc << "Goodbye! =)" << io_end;
         }
         else
         {
         ioc << "Error: Unrecognized command." << io_end;
         }*/

    } while (!(choice == EXIT_MENU));

}

void Test::displayInfo()
{
    ioc << "Timeline Info\n==============" << io_end;
    ioc << "Number of Frames: " << timeline.getNumberOfFrames() << io_end;
    ioc << "Number of Layers: " << timeline.getNumberOfLayers() << io_end;
    ioc << "X Dimension: " << timeline.getXDim() << io_end;
    ioc << "Y Dimension: " << timeline.getYDim() << io_end;
    ioc << "X Partition Dimension: " << timeline.getXPartDim() << io_end;
    ioc << "Y Partition Dimension: " << timeline.getYPartDim() << io_end;
    consolePause();
    consoleClear();
}

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
 ioc << "Error: There aren't any frames to swap!" << io_end;
 }
 else
 {
 ioc << "Error: Index out of bounds!" << io_end;
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
 ioc << "Error: Can't swap indexes on an empty frame!" << io_end;
 }
 else
 {
 ioc << "Error: Index out of bounds!" << io_end;
 }

 }
 }*/

void Test::editMode_editLayer()
{
    // Check if there are frames to edit
    if ((int)timeline.getNumberOfLayers() <= 0)
    {
        ioc << "No layers to edit" << io_end;
        consolePause();
        consoleClear();
        return;
    }
    //Display frames currently in Timeline
    ioc << "Layers in Main Timeline" << io_end;
    ioc << "---------------------------" << io_end;
    for (int i = 0; i < (int)timeline.getNumberOfLayers(); i++)
    {
        //TODO: Layers should probably have names to identify them easier
        ioc << i << ". " << "Static Layer " << i + 1 << io_end;
    }
    //Prompt for the index of the Layer to edit
    string layerChoice = "";
    ioc << io_end << "Enter the index of the layer you would like to edit: " << io_send;
    getline(cin, layerChoice);
    //Attempt to parse the input to an int
    try
    {
        int layerIndex = stoi(layerChoice);
        //Test to see that the input index is within the bounds of the vector
        if(layerIndex >= 0 && layerIndex < (int)timeline.getNumberOfLayers())
        {
            consoleClear();
            //Call the requested Layer's editMode function.
            shared_ptr<StaticLayer> layer = dynamic_pointer_cast<StaticLayer>(timeline.getLayerAt(layerIndex));
            staticEditMode(layer);
        }
        //Handle out-of-bounds index
        else
        {
            ioc << "Error: Input was not a valid Layer index." << io_end;
            consolePause();
        }
    }
    //Handle invalid input
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
    }
    consoleClear();
}

void Test::editMode_addLayer()
{
    //Prompt for the insertion index of the Layer
    string indexString = "";
    /*Right now we're allowing the user to hit enter and have the insertion
     *index default to the end of the Timeline's vector of Layers.*/
    ioc << "Enter the index where you would like to insert the new layer."
    << "\n(Press enter to insert at end)" << io_end;
    getline(cin, indexString);
    int index = -1;
    /*If the user just hit enter, set the insertion index to the end
     of the Timeline's vector of Layers*/
    if(indexString == "")
    {
        index = timeline.getNumberOfLayers();
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
            ioc << "Error: Input must be a valid integer." << io_end;
            consolePause();
            consoleClear();
            return;
        }
    }
    //Test to see if the index is within the bounds of the vector
    if(index >= 0 && index <= (int)timeline.getNumberOfLayers())
    {
        /*If the insertion index is legitimate, prompt for a new image
         *for the Layer.*/
        //TODO: Create UI to make new matrix
        Matrix newMatrix = Matrix::Identity(5,5);
        //ioc << "Enter a new image (text string) for the Layer: " << io_send;
        //getline(cin, newImage);
        //Create a new Layer and add it to the Timeline
        timeline.addLayer(make_shared<StaticLayer>(newMatrix), index);
        /*Once we've created the new Layer, call that Layer's editMode,
         *so the user can continue customizing it.*/
        //getLayerAt(index)->editMode();
    }
    //Handle out-of-bounds index
    else
    {
        ioc << "Error: The requested index was out of range." << io_end;
        consolePause();
    }
    consoleClear();
}

void Test::editMode_addFrame()
{
    //Prompt the user for an index where they would like to insert a new Frame
    string indexChoice = "";

    //Display frames in timeline
    ioc << "Frames in Timeline" << io_end;
    ioc << "-----------------------" << io_end;
    if ((int)timeline.getNumberOfFrames() > 0)
    {
        for (int i = 0; i < (int)timeline.getNumberOfFrames(); i++)
        {
            ioc << i << ". " << "Frame " << i + 1 << io_end;
        }
    }
    else
    {
        ioc << "No frames to display" << io_end;
    }

    /*Right now we'll allow users to just hit "enter" which will add a new
     *Frame to the end of the Timeline's Frame vector by default.*/
    ioc << io_end << "Enter the index that you would like to insert a new Frame into.\n"
    << "(Press \"enter\" to add the Frame at the end of the Timeline)" << io_end;

    //Get the input from the user
    getline(cin, indexChoice);
    //Test for the default case
    if(indexChoice == "")
    {
        //Add the Frame at the end
        timeline.addFrame(timeline.getNumberOfFrames());
    }
    else
    {
        //Attempt to parse the user input to an integer
        try
        {
            int frameIndex = stoi(indexChoice);
            //Test the index to make sure it's in the vector's bounds
            if(frameIndex >= 0 && frameIndex <= (int)timeline.getNumberOfFrames())
            {
                //Insert the new Frame
                timeline.addFrame(frameIndex);
            }
            //If the index was out of bounds, display an error message.
            else
            {
                ioc << "Error: An invalid index was entered." << io_end;
                consolePause();
            }
        }
        //Handle invalid input
        catch(...)
        {
            ioc << "Error: Input must be a valid integer." << io_end;
            consolePause();
        }
    }
    consoleClear();
}

void Test::editMode_deleteLayer()
{
    //Prompt the user for the index of the Layer they would like to delete
    string layerChoice = "";
    ioc << "Enter the index of the Layer you would like to delete: " << io_send;
    getline(cin, layerChoice);
    //Attempt to parse the input to an integer
    try
    {
        int index = stoi(layerChoice);
        //Test to make sure that the index is within the vector's bounds
        if(index >= 0 && index < (int)timeline.getNumberOfLayers())
        {
            //Delete the Layer from the Timeline
            timeline.deleteLayer(index);
        }
        //If the index was out-of-bounds, display an error
        else
        {
            ioc << "Error: Specified index was out of range for the timeline."
            << io_end;
            consolePause();
        }
    }
    //Handle invalid input
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
    }
    consoleClear();
}

void Test::editMode_deleteFrame()
{
    //Prompt for the index of the Frame they would like to delete
    string indexString = "";
    ioc << "Enter the index of the Frame you would like to delete: " << io_send;
    getline(cin, indexString);
    //Attempt to parse the input to an integer
    try
    {
        int index = stoi(indexString);
        //Check to see if the index is within the vector's bounds
        if(index >= 0 && index < (int)timeline.getNumberOfFrames())
        {
            //Delete the Frame from the Timeline
            timeline.deleteFrame(index);
        }
        //If the index was out-of-bounds, display an error.
        else
        {
            ioc << "Error: Specified index was out of range for the timeline."
            << io_end;
            consolePause();
        }
    }
    //Handle invalid input
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
    }
    consoleClear();
}

void Test::editMode_displayGrid()
{
    string frameString = "";
    ioc << "Enter the index of the Frame whose grid you would like to be"
    << " displayed." << io_end;
    getline(cin, frameString);
    try
    {
        int frameIndex = stoi(frameString);
        if(frameIndex >= 0 && frameIndex < (int)timeline.getNumberOfFrames())
        {
            frameTest_printGridContents(*(timeline.getFrameAt(frameIndex)));
        }
        else
        {
            ioc << "Error: The requested Frame is out of range." << io_end;
            consolePause();
        }
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
    }
    consoleClear();
}

void Test::editMode_editFrame()
{
    // Check if there are frames to edit
    if ((int)timeline.getNumberOfFrames() <= 0)
    {
        ioc << "No frames to edit" << io_end;
        consolePause();
        consoleClear();
        return;
    }
    // Display frames in timeline
    ioc << "Frames in Timeline" << io_end;
    ioc << "-----------------------" << io_end;
    for (int i = 0; i < (int)timeline.getNumberOfFrames(); i++)
    {
        ioc << i << ". " << "Frame " << i + 1 << io_end;
    }

    string choice = "";
    ioc << "Enter the index of the Frame you want to edit: " << io_send;
    getline(cin, choice);
    try
    {
        int frameIndex = stoi(choice);
        if(frameIndex < 0 || frameIndex >= (int)timeline.getNumberOfFrames())
        {
            ioc << "Error: Index out of bounds." << io_end;
            consolePause();
        }
        else
        {
            consoleClear();
            // timeline.getFrameAt(frameIndex)->editMode();
            frameEditMode(*timeline.getFrameAt(frameIndex));
        }
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
    }
    consoleClear();
}

void Test::editMode_deleteLayerInstance()
{
    string choice = "";
    ioc << "Enter the index of the Frame you would like to delete the "
    << "LayerInstance from: " << io_send;
    getline(cin, choice);
    int frameIndex = -1;
    int layerInstanceIndex = -1;
    try
    {
        frameIndex = stoi(choice);
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
        consoleClear();
        return;
    }
    if (frameIndex < 0 || frameIndex >= (int)timeline.getNumberOfFrames())
    {
        ioc << "Error: Index out of bounds." << io_end;
        consolePause();
        consoleClear();
        return;
    }
    ioc << "\nThere are currently " << timeline.getFrameAt(frameIndex)->getNumLayerInstances()
    << " LayerInstances in the Frame." << io_end;
    ioc << "Enter the index of the LayerInstance you would like to delete "
    << "from the Frame: " << io_send;
    getline(cin, choice);
    try
    {
        layerInstanceIndex = stoi(choice);
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
        consoleClear();
        return;
    }
    if(layerInstanceIndex < 0 || layerInstanceIndex >=
       timeline.getFrameAt(frameIndex)->getNumLayerInstances())
    {
        ioc << "Error: Index out of bounds." << io_end;
        consolePause();
        consoleClear();
        return;
    }
    timeline.getFrameAt(frameIndex)->removeLayer(layerInstanceIndex);
    consoleClear();
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

void Test::editMode_insertLayerInstance()
{
    string choice = "";
    //Prompt for Frame index
    ioc << "There are currently " << timeline.getNumberOfFrames() <<
    " Frames available in the Timeline." << io_end;
    ioc << "Enter the index of the Frame you would like to insert the "
    << "LayerInstance into: " << io_send;
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
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
        consoleClear();
        return;
    }
    if(frameIndex < 0 || frameIndex >= (int)timeline.getNumberOfFrames())
    {
        ioc << "Error: Index out of bounds." <<  io_end;
        consolePause();
        consoleClear();
        return;
    }
    //Prompt for Timeline Layer index
    ioc << "\nThere are currently " << timeline.getNumberOfLayers() <<
    " Layers available in the Timeline." << io_end;
    ioc << "Enter the index of the Layer (in the Timeline) you would like"
    << "to insert into the Frame: " << io_send;
    getline(cin, choice);
    try
    {
        layerIndex = stoi(choice);
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
    }
    if(layerIndex < 0 || layerIndex >= (int)timeline.getNumberOfLayers())
    {
        ioc << "Error: Index out of bounds." << io_end;
        consolePause();
        consoleClear();
        return;
    }
    //Prompt for LayerInstance index in Frame
    ioc << "\nThere are currently " <<
    timeline.getFrameAt(frameIndex)->getNumLayerInstances() <<
    " LayerInstances in the specified Frame." << io_end;
    ioc << "Enter the index you would like to insert the LayerInstance " <<
    "into: " << io_send;
    getline(cin, choice);
    try
    {
        layerInstanceIndex = stoi(choice);
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
    }
    if(layerInstanceIndex < 0 || layerInstanceIndex >
       timeline.getFrameAt(frameIndex)->getNumLayerInstances())
    {
        ioc << "Error: Index out of bounds." << io_end;
        consolePause();
        consoleClear();
        return;
    }
    Layer* testLayer = timeline.getLayerAt(layerIndex).get();
    if(!timeline.getFrameAt(frameIndex)->containsLayer(testLayer))
    {
        timeline.getFrameAt(frameIndex)->addLayer(
                                        timeline.getLayerAt(layerIndex), layerInstanceIndex);
    }
    else
    {
        ioc << "A LayerInstance for that Layer is already contained in the "
        << "specified Frame." << io_end;
        consolePause();
    }
    consoleClear();
}

/*This method allows the user to select the type of Layer they want to insert
 *into the Timeline.
 *Until we have more LayerTypes to add in the Timeline's editMode, we won't be
 *using this method.*/
int Test::editMode_chooseLayerType()
{
    string choice = "";
    int layerType = -1;
    while(layerType == -1)
    {
        ioc << "Choose the type of Layer to add to the Timeline." << io_end;
        ioc << "1. StaticLayer" << io_end;
        ioc << "Choice: " << io_send;
        getline(cin, choice);
        try
        {
            layerType = stoi(choice);
        }
        catch(...)
        {
            layerType = -1;
        }
        if(layerType > 0 && layerType < 2)
        {
            return layerType;
        }
        else
        {
            ioc << "Error: Invalid option.";
            layerType = -1;
        }
    }
    //The method shouldn't get to this point, but return dummy value anyway.
    return -1;
}

void Test::frameEditMode(Frame &frame)
{
    string choiceString = "";
    int choice = -1;
    while(choice != 5)
    {
        frameEditMode_displayMenu();
        getline(cin, choiceString);
        try
        {
            choice = stoi(choiceString);
        }
        catch(...)
        {
            choice = -1;
        }
        //Display all of the LayerInstances
        if(choice == 1)
        {
            consoleClear();
            for(int i = 0; i < frame.getNumLayerInstances(); ++i)
            {
                ioc << i << ". ";
                frame.getLayerInstanceAt(i)->render();
            }
            consolePause();
        }
        //Move a LayerInstance in the Frame
        else if(choice == 2)
        {
            consoleClear();
            frameEditMode_moveLayerInstance(frame);
        }
        //Set a LayerInstance Matrix
        else if (choice == 3)
        {
            consoleClear();
            frameEditMode_setLayerInstanceMatrix(frame);
        }
        //Display the grid
        else if (choice == 4)
        {
            consoleClear();
            frameTest_printGridContents(frame);
        }
        //Exit
        else if(choice == 5)
        {
            //Do nothing
        }
        else
        {
            ioc << "Error: Choice must be a valid option from the menu."
            << io_end;
            consolePause();
        }
        consoleClear();
    }
}


//Test method that renders the contents of the grid
void Test::frameTest_printGridContents(Frame &frame)
{
    //Loop through the x and y dimensions of the grid
    for(unsigned int i = 0; i < frame.getGrid().at(0).size(); ++i)
    {
        for(unsigned int j = 0; j < frame.getGrid().size(); ++j)
        {
            //Print out the grid coordinates
            ioc << "Sector (" << j << "," << i << ")" << io_end;
            for(unsigned int k = 0; k < frame.getGrid().at(j).at(i).size(); ++k)
            {
                //Render each LayerInstance in that partition.
                frame.getLayerInstanceAt(frame.getGrid().at(j).at(i).at(k))->render();
                ioc << io_end;
            }
        }
    }
    consolePause();
}

void Test::frameEditMode_displayMenu()
{
    ioc << "Frame Edit Mode\n------------------------\n";
    ioc << "1. Display the LayerInstances in the Frame" << io_end;
    ioc << "2. Move a LayerInstance" << io_end;
    ioc << "3. Edit a LayerInstance Transformation Matrix" << io_end;
    ioc << "4. Display the Frame grid" << io_end;
    ioc << "5. Exit Edit Mode" << io_end;
}

void Test::frameEditMode_setLayerInstanceMatrix(Frame &frame)
{
    string choice = "";
    ioc << "Enter the index of the LayerInstance you would like to edit: " << io_send;
    getline(cin, choice);
    try
    {
        int layerInstanceIndex = stoi(choice);
        if(layerInstanceIndex < 0 || layerInstanceIndex >=
           (int)frame.getNumLayerInstances())
        {
            ioc << "Error: Index out of bounds." << io_end;
            consolePause();
        }
        else
        {
            ioc << "Enter the new matrix for the LayerInstance: " << io_send;
            getline(cin, choice);
            try
            {
                ///TODO: Write UI for entering new matrix
                //Matrix newMatrix = stoi(choice);
                //frame.getLayerInstanceAt(layerInstanceIndex)->setMatrix(newMatrix);
            }
            catch(...)
            {
                ioc << "Error: Input must be a valid integer." << io_end;
                consolePause();
            }
        }
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid index." << io_end;
        consolePause();
    }
    consoleClear();
}

void Test::frameEditMode_moveLayerInstance(Frame &frame)
{
    string choice = "";
    ioc << "Enter the index of the LayerInstance you would like to move: " << io_send;
    getline(cin, choice);
    try
    {
        int indexA = stoi(choice);
        if(indexA < 0 || indexA >= (int)frame.getNumLayerInstances())
        {
            ioc << "Error: Index out of bounds." << io_end;
            consolePause();
        }
        else
        {
            ioc << "Enter the index that you would like to move the "
            << "LayerInstance to: " << io_send;
            getline(cin, choice);
            try
            {
                int indexB = stoi(choice);
                if(indexB < 0 || indexB >= (int)frame.getNumLayerInstances())
                {
                    ioc << "Error: Index out of bounds." << io_end;
                    consolePause();
                }
                else
                {
                    frame.reorderLayer(indexA, indexB);
                }
            }
            catch(...)
            {
                ioc << "Error: Input must be a valid integer." << io_end;
                consolePause();
            }
        }
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
        consolePause();
    }
    consoleClear();
}

/*Ambitious function that will allow the user to interface with the
 *StaticLayer object. It functions like a command-line application, prompting the
 *user for commands.*/
void Test::staticEditMode(shared_ptr<StaticLayer> s)
{
    string input = "";
    int option = -1;
    while(option != 9)
    {
        //TODO: Display layer name here once implemented
        ioc << "Static Layer Edit Mode" << io_end;
        ioc << "-------------------------" << io_end;
        //Prompt for input
        staticEditMode_help();
        ioc << "Choose an option from the menu: " << io_send;
        //Retrieve input
        getline(cin, input);
        consoleClear();
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
            staticEditMode_getImage(s);
        }
        else if(option == 2)
        {
            staticEditMode_setImage(s);
        }
        else if(option == 3)
        {
            staticEditMode_getDim(s);
        }
        else if(option == 4)
        {
            staticEditMode_setDim(s);
        }
        else if(option == 5)
        {
            staticEditMode_getOrigin(s);
        }
        else if(option == 6)
        {
            staticEditMode_setOrigin(s);
        }
        else if(option == 7)
        {
            /*if(staticEditMode_isVisible(s))
            {
                ioc << "true" << io_end;
            }
            else
            {
                ioc << "false" << io_end;
            }*/
            ioc << staticEditMode_isVisible(s) << io_end;
            consolePause();
        }
        else if(option == 8)
        {
            staticEditMode_setVisibility(s);
        }
        /*If the input wasn't any of the available commands, and it's not
         *the exit value, inform the user that the input was invalid.*/
        else if(option != 9)
        {
            ioc << "Error: Unrecognized command." << io_end;
            consolePause();
        }
        consoleClear();
    }
}

/*The following are all editMode functions. Each essentially represents its
 *own editMode command. */

/*This method displays all of the available commands used to interact
 *with the StaticLayer.*/
void Test::staticEditMode_help()
{
    ioc << "Available Commands\n-------------------------" << io_end;
    ioc << "1. Get Image: Display Layer image on screen." << io_end;
    ioc << "2. Set Image: Command to change the layer image." <<
    " Prompts for a string." << io_end;
    ioc << "3. Get Dimensions: Command to display current image dimensions."
    << io_end;
    ioc << "4. Set Dimensions: Command to change the image dimensions."
    << " Prompts for X and Y dimensions, must be positive whole numbers."
    << io_end;
    ioc << "5. Get Origin Coordinates: Command to display the current "
    << "origin coordinates of the Layer." << io_end;
    ioc << "6. Set Origin Coordinates: Command to set the origin coordinates"
    << " of the Layer." << io_end;
    ioc << "7. Is Visible: Displays whether or not the layer is currently "
    << "visible. " << io_end;
    ioc << "8. Set Visibility: Command to set the visibility of the Layer. "
    << "Input must either be \"true\" or \"false\"" << io_end;
    ioc << "9. Exit: Exits out of editMode.\n" << io_end;
}

//This method displays the Layer's image to the user
void Test::staticEditMode_getImage(shared_ptr<StaticLayer> s)
{
    (void)s;
    //TODO: Make function to display matrix to console
    //ioc << "Layer Image: " << s->getImage() << io_end;
    ioc << "Layer Image: " << "PRINT_MATRIX_CONTENTS" << io_end;
    consolePause();
}

//this method allows the user to set the Layer's image
void Test::staticEditMode_setImage(shared_ptr<StaticLayer> s)
{
    string image;
    //Prompt for input
    ioc << "Enter new Layer Image: " << io_send;
    getline(cin, image);
    ///TODO: Create UI to add new Matrix
    s->isVisible();
    //s->setImage(image);
}

//This method allows the user to set the Layer's base dimensions
void Test::staticEditMode_setDim(shared_ptr<StaticLayer> s)
{
    //Print out the old values for user reference
    ioc << "Old X Dimension: " << s->getXDimension() << io_end;
    ioc << "Old Y Dimension: " << s->getYDimension() << io_end;
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
        ioc << "Enter new X Dimension: " << io_send;
        getline(cin, input);
        //Try to parse the input as an int
        try
        {
            newXDim = stoi(input);
            validInput = true;
        }
        //Display an error message
        catch(...)
        {
            ioc << "Error: Input must be an integer." << io_end;
        }
    }
    //Perform the same method as above to get a new y dimension
    validInput = false;
    while(!validInput)
    {
        ioc << "Enter new Y Dimension: " << io_send;
        getline(cin, input);
        try
        {
            newYDim = stoi(input);
            validInput = true;
        }
        catch(...)
        {
            ioc << "Error: Input must be an integer." << io_end;
        }
    }
    //Test to make sure that the numbers are non-negative
    if(newXDim >= 0 && newYDim >= 0)
    {
        //If they are, update the Layer's dimensions
        s->setDimensions(newXDim, newYDim);
    }
    //Otherwise, let the user know the input was invalid
    else
    {
        ioc << "Error: Dimensions cannot be less than zero." << io_end;
        consolePause();
    }
}

//This method displays the Layer dimensions to the user
void Test::staticEditMode_getDim(shared_ptr<StaticLayer> s)
{
    ioc << "X Dimension: " << s->getXDimension() << io_end;
    ioc << "Y Dimension: " << s->getYDimension() << io_end;
    consolePause();
}

void Test::staticEditMode_setOrigin(shared_ptr<StaticLayer> s)
{
    //Print out the old values for user reference
    ioc << "Old X Coordinate: " << s->getOriginX() << io_end;
    ioc << "Old Y Coordinate: " << s->getOriginY() << io_end;
    //String that will handle console input
    string input;
    //Int that holds the new x coordinate
    int newXCoord = 0;
    //Int that holds the new y coordinate
    int newYCoord = 0;
    //Bool that determines whether or not the input is valid
    bool validInput = false;
    //This while loop will execute until the user enters valid input
    while(!validInput)
    {
        //Prompt for new x origin coordinate
        ioc << "Enter new X Coordinate: " << io_send;
        getline(cin, input);
        //Try to parse the input as an int
        try
        {
            newXCoord = stoi(input);
            validInput = true;
        }
        //Display an error message
        catch(...)
        {
            ioc << "Error: Input must be an integer." << io_end;
        }
    }
    //Perform the same method as above to get a new y dimension
    validInput = false;
    while(!validInput)
    {
        ioc << "Enter new Y Coordinate: " << io_send;
        getline(cin, input);
        try
        {
            newYCoord = stoi(input);
            validInput = true;
        }
        catch(...)
        {
            ioc << "Error: Input must be an integer." << io_end;
        }
    }
    //If they are, update the Layer's dimensions
    s->setOriginCoord(newXCoord, newYCoord);
}

void Test::staticEditMode_getOrigin(shared_ptr<StaticLayer> s)
{
    ioc << "X Origin Coord: " << s->getOriginX() << io_end;
    ioc << "Y Origin Coord: " << s->getOriginY() << io_end;
    consolePause();
}

//This method tells the user whether or not the Layer is visible
bool Test::staticEditMode_isVisible(shared_ptr<StaticLayer> s)
{
    //True if visible, false if invisible.
    return s->isVisible();
}

//This method allows the user to set whether or not the Layer is visible
void Test::staticEditMode_setVisibility(shared_ptr<StaticLayer> s)
{
    string newVisibility;
    //Prompt for input
    ioc << "Set the visibility of the layer (true/false): " << io_send;
    getline(cin, newVisibility);
    if(newVisibility == "true")
    {
        s->setVisible(true);
    }
    else if(newVisibility == "false")
    {
        s->setVisible(false);
    }
    //Handle invalid option
    else
    {
        ioc << "Error: Input must be either \"true\" or \"false\""
        << io_end;
        consolePause();
    }
}

/**The editMode layer allows derived classes to interface with users
 depending on their unique features. */
void Test::iolEditMode(shared_ptr<IOL> iol)
{
    (void)iol;
    /*string choice = "";
     while(choice != "exit")
     {
     editMode_displayMenu();
     getline(cin, choice);
     if(choice == "setvisibility")
     {
     editMode_setVisibility();
     }
     else if(choice == "getvisibility")
     {
     editMode_isVisible();
     }
     else if(choice == "setrepeats")
     {
     editMode_setRepeats();
     }
     else if(choice == "getrepeats")
     {
     editMode_getRepeats();
     }
     else if(choice == "getrunning")
     {
     editMode_getRunning();
     }
     else if(choice == "setrunning")
     {
     editMode_setRunning();
     }
     else if(choice == "getcurrentframe")
     {
     editMode_getCurrentFrame();
     }
     else if(choice == "setcurrentframe")
     {
     editMode_setCurrentFrame();
     }
     else if(choice == "edittimeline")
     {
     timeline.editMode();
     //Once they're done editing the timeline, make sure we
     //update the dimensions of the IOL.
     updateDimensionData();
     }
     else if(choice != "exit")
     {
     ioc << "Error: Please select a valid command from the menu." << io_end;
     }
     }*/
}

//The following are implementations of helper methods for edit mode

void Test::iolEditMode_getRepeats(shared_ptr<IOL> iol)
{
    if(iol->animationRepeats())
    {
        ioc << "The Layer is set to repeat." << io_end;
    }
    else
    {
        ioc << "The Layer isn't set to repeat." << io_end;
    }
}

void Test::iolEditMode_setRepeats(shared_ptr<IOL> iol)
{
    //SetRepeats
    string newRepeats;
    //Prompt for input
    ioc << "Set whether or not the animation repeats (true/false): " << io_send;
    getline(cin, newRepeats);
    if(newRepeats == "true")
    {
        iol->setRepeat(true);
    }
    else if(newRepeats == "false")
    {
        iol->setRepeat(false);
    }
    //Handle invalid option
    else
    {
        ioc << "Error: Input must be either \"true\" or \"false\""
        << io_end;
    }
}

void Test::iolEditMode_getRunning(shared_ptr<IOL> iol)
{
    if(iol->isRunning())
    {
        ioc << "The Layer is currently running." << io_end;
    }
    else
    {
        ioc << "The Layer isn't currently running." << io_end;
    }
}

void Test::iolEditMode_setRunning(shared_ptr<IOL> iol)
{
    string newRunning;
    //Prompt for input
    ioc << "Set whether or not the layer is running (true/false): " << io_send;
    getline(cin, newRunning);
    if(newRunning == "true")
    {
        iol->setRunning(true);
    }
    else if(newRunning == "false")
    {
        iol->setRunning(false);
    }
    //Handle invalid option
    else
    {
        ioc << "Error: Input must be either \"true\" or \"false\""
        << io_end;
    }
}

void Test::iolEditMode_getCurrentFrame(shared_ptr<IOL> iol)
{
    ioc << "The current frame is " << iol->getCurrentFrame() << "." << io_end;
}

void Test::iolEditMode_setCurrentFrame(shared_ptr<IOL> iol)
{
    //Prompt the user to enter in the new current frame index
    string frameString = "";
    ioc << "Enter the index of the new current frame: " << io_send;
    getline(cin, frameString);
    try
    {
        int frameIndex = stoi(frameString);
        if(frameIndex >= 0 && frameIndex < (int)timeline.getNumberOfFrames())
        {
            iol->setCurrentFrame(frameIndex);
        }
        else
        {
            ioc << "Error: Requested index out of bounds." << io_end;
        }
    }
    catch(...)
    {
        ioc << "Error: Input must be a valid integer." << io_end;
    }
}

void Test::iolEditMode_isVisible(shared_ptr<IOL> iol)
{
    if(iol->isVisible())
    {
        ioc << "The Layer is currently visible." << io_end;
    }
    else
    {
        ioc << "The Layer is currently not visible." << io_end;
    }
}

void Test::iolEditMode_setVisibility(shared_ptr<IOL> iol)
{
    string newVisibility;
    //Prompt for input
    ioc << "Set the visibility of the layer (true/false): " << io_send;
    getline(cin, newVisibility);
    /*Test the user input. If they answered true or false, set the visibility
     *value accordingly. Otherwise, display an error.*/
    if(newVisibility == "true")
    {
        iol->setVisible(true);
    }
    else if(newVisibility == "false")
    {
        iol->setVisible(false);
    }
    //Handle invalid option
    else
    {
        ioc << "Error: Input must be either \"true\" or \"false\""
        << io_end;
    }
}

void Test::iolEditMode_displayMenu()
{
    //This menu displays all of the available commands for the IOL editMode.
    ioc << "\nIOL Edit Mode Menu\n----------------------------" << io_end;
    ioc << "setvisibility - set the visibility of the Layer" << io_end;
    ioc << "getvisibility - get the visibility of the Layer" << io_end;
    ioc << "getrepeats - get whether or not the IOL repeats" << io_end;
    ioc << "setrepeats - set whether or not the IOL repeats" << io_end;
    ioc << "getrunning - get whether or not the IOL is running" << io_end;
    ioc << "setrunning - set whether or not the IOL is running" << io_end;
    ioc << "getcurrentframe - get the current frame in the IOL animation"
    << io_end;
    ioc << "setcurrentframe - set the current frame in the IOL animation"
    << io_end;
    ioc << "edittimeline - edit the IOL's animation" << io_end;
    ioc << "exit - exits out of the IOL edit menu" << io_end;
    ioc << "Choice: ";
}

//Render the Timeline
void Test::play()
{
    if(timeline.getNumberOfFrames() > 0)
    {
        ioc << "Animation Start: \n---------------------------------" << io_end;
        //Loop through the Frames in the animation, rendering each one in order
        for(unsigned int i = 0; i < timeline.getNumberOfFrames(); ++i)
        {
            timeline.getFrameAt(i)->render();
            ioc << io_end;
        }
        ioc << "-----------------------------------\nAnimation End" << io_end;
    }
    //Handle empty timeline
    else
    {
        ioc << "No frames to render" << io_end;
    }
    consolePause();
    consoleClear();
}

//Method that plays the Timeline backwards
void Test::playBackwards()
{
    if(timeline.getNumberOfFrames() > 0)
    {
        ioc << "Animation Backwards Start: \n---------------"
        <<"------------------" << io_end;
        //Iterate through the Frames in the Timeline backwards
        for(unsigned int i = timeline.getNumberOfFrames(); i-- > 0 ;)
        {
            //Render each Frame
            timeline.getFrameAt(i)->render();
            ioc << io_end;
        }
        ioc << "-----------------------------------\nAnimation End" << io_end;
    }
}


