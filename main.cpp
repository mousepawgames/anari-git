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


#include "StaticLayer.hpp"
#include "IOL.hpp"
#include "Frame.hpp"
#include "Timeline.hpp"


using std::cout;
using std::endl;
using std::cin;
using std::make_shared;

void displayMenu();
void menu_addIOL(Timeline* master);

int main()
{
    //Creating Layers to be used in timeline.
    //StaticLayer StaticLayer0 = StaticLayer("J", 1, 810, -720, 10);

    /*Create a new Timeline. The default constructor initializes the
    Timeline dimensions to be 1920x1080 and the partition dimensions
    to 480x270.*/
    Timeline master = Timeline();

    master.editMode();

    
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

//Allows the user to add a new Layer to the timeline and edit its contents.
void menu_addIOL(Timeline* master)
{
    //Prompt for the insertion index of the Layer
    string indexString = "";
    /*Right now we're allowing the user to hit enter and have the insertion
    *index default to the end of the Timeline's vector of Layers.*/
    cout << "Enter the index where you would like to insert the new layer. If"
    << " you would like to add the Layer at the end, just hit enter." << endl;
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
    if(index >= 0 && index <= (int)master->getNumberOfLayers())
    {
        //Create a new Layer and add it to the Timeline
        master->addLayer(make_shared<IOL>(), index);
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

