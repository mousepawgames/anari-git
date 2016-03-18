/*
*Anari Graphics System, version 0.1
*main Class
*Description: This is the main method that tests the functionality of the
*Timeline class as well as Frame, Layer, LayerInstance, and StaticLayer.
*Last Updated: 18 February 2016
*
*Copyright (C) MousePawGames
*Licenses:
*/


#include <iostream>
#include "StaticLayer.hpp"
#include "Frame.hpp"
#include "Timeline.hpp"


using namespace std;

int main()
{
    string input;

    //Creating Layers to be used in timeline.
    StaticLayer StaticLayer0 = StaticLayer("0");
    StaticLayer StaticLayer1 = StaticLayer("1");
    StaticLayer StaticLayer2 = StaticLayer("2");
    StaticLayer StaticLayer3 = StaticLayer("3");
    StaticLayer StaticLayer4 = StaticLayer("4");

    /*Create a new Timeline. The default constructor initializes the
    Timeline dimensions to be 1920x1080 and the partition dimensions
    to 480x270.*/
    Timeline master = Timeline();
    master.addLayer(&StaticLayer0, 0);

    master.addLayer(&StaticLayer1, 1);
    master.addFrame();
    master.addFrame();
    master.addFrame();

    master.addLayer(&StaticLayer2, 2);
    master.reorderLayer(0, 2);
    master.addLayer(&StaticLayer3, 3);
    master.getFrameAt(1)->reorderLayer(0, 1);
    master.reorderLayer(3, 2);
    master.play();
    master.getFrameAt(1)->test_printGridContents();
    getline(cin, input);
    master.getLayerAt(0)->editMode();
    master.play();
    master.getFrameAt(0)->test_printGridContents();

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
