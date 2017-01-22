/**How does the IOL work?
*The IOL is a Layer type that contains its own Layers and Frames in a Timeline
*object. It's essentially a self-contained animation that can be added as part
*of a master Timeline. What makes an IOL special is that it can animate
*independently of the master Timeline. The master Timeline can be paused on one
*Frame, but the IOL can continue to animate, and even repeat the same animation
*indefinitely.
*We use a couple of extra variables in the IOL to control the animation.
*The "currentFrame" variable is an int that stores the index of the current
*Frame in the animation/Timeline. Whenever the IOL renders a Frame, if the
*IOL is running, the current Frame will be incremented. We keep track of
*whether the animation is running with the "running" bool. There is also a
*"repeating" bool that toggles whether or not the animation repeats. If it
*repeats, the currentFrame value will be reset to zero when the end of the
*animation is reached, and will be incremented as usual. If it's not set
*to repeat, then the last frame of the IOL will continue to be displayed.
*
*NOTE: Right now I envision that when an IOL is running on a master Timeline
*that isn't currently running, (i.e. the master Timeline is paused on a Frame)
*the master's current Frame will be re-rendered over and over again so that
*the IOL can progress. If the master Timeline didn't re-render its contents,
*then the IOL's contents would be rendered over all Layers in the master
*Timeline, regardless of its position. This behavior may change in the future.
*
*NOTE: Right now you can't add a new IOL to a Timeline within the Timeline's
*editMode method. I tried to implement this previously, but found that things
*got a little hairy with circular references. (Timeline tries to create IOL
*which in turn needs to create a Timeline which needs to know about IOL, etc.)
*To get around this I pulled the "addIOL" functionality out of the Timeline
*class itself and moved it to the Main.cpp class, which creates and manages
*the master Timeline. This makes it so that only the master Timeline can
*contain IOLs. (e.g. IOLs won't be able to contain other IOLs within their
*Timelines.) This works for now, but if we want to be able to add IOLs to IOLs
*in the future, we will have to face this complication. I know that this
*complication will also apply to the future SOL Layer type, and any others that
*contain a Timeline.*/

#include "anari/iol.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::list;

IOL::IOL(): timeline(Timeline()), visibility(true),
currentFrame((unsigned int)0), running(false), repeats(false)
{
    //ctor
    dim[0] = 0;
    dim[1] = 0;
    originCoords[0] = 0;
    originCoords[1] = 0;
}

IOL::~IOL()
{
    //dtor
}

//This method renders the current animation Frame to the screen
void IOL::render(Matrix transformationMatrix, int frameIndex)
{
    (void)frameIndex;
    //Determine whether or not there are any Frames in the Timeline to render
    if(timeline.getNumberOfFrames() > 0 && visibility)
    {
        //Display the current frame
        timeline.displayFrame(currentFrame);
        /*Display the general transformation matrix that will be applied to
        *the whole IOL.*/
        cout << "(" << transformationMatrix << ")";
        /*If the animation is running and there are still more Frames in the
        *animation, increment the current Frame*/
        if(running && currentFrame < timeline.getNumberOfFrames() - 1)
        {
            ++currentFrame;
        }
        /*If the animation is running but we're at the end of the animation
        *and we allow the animation to repeat, set the currentFrame to zero.*/
        else if(running && currentFrame == timeline.getNumberOfFrames() - 1
                && repeats)
        {
            currentFrame = 0;
        }
    }
}

//Sets and gets for currentFrame variable
unsigned int IOL::getCurrentFrame()
{
    return currentFrame;
}

void IOL::setCurrentFrame(unsigned int newFrame)
{
    if(newFrame < timeline.getNumberOfFrames())
    {
        currentFrame = newFrame;
    }
}

void IOL::nextFrame()
{
    //Test to make sure we haven't hit the end of the timeline
    if(currentFrame < timeline.getNumberOfFrames() - 1)
    {
        ++currentFrame;
    }
    /*If the currentFrame is at the end of the timeline, check to see if
    the IOL animation repeats.*/
    else if(repeats)
    {
        //If the animation repeats, return the currentFrame to the beginning.
        currentFrame = 0;
    }
    //If none of the above conditions were met, do nothing.
}

//Sets and gets for isRunning variable
bool IOL::isRunning()
{
    return running;
}

void IOL::setRunning(bool newRunning)
{
    running = newRunning;
}


//Sets and gets for animationRepeats variable
bool IOL::animationRepeats()
{
    return repeats;
}

void IOL::setRepeat(bool newRepeat)
{
    repeats = newRepeat;
}

///Overidden methods from Layer class. Set and get visibility variable.
bool IOL::isVisible()
{
    return visibility;
}

void IOL::setVisible(bool newVisibility)
{
    visibility = newVisibility;
}

//Overidden method from Layer class that creates a new LayerInstance pointer
/*Right now with the way we're rendering the IOL and storing data, there's
*no need to use anything other than a standard LayerInstance object for
*the IOL. This may change in the future.*/
LayerInstance* IOL::newLayerInstance(Matrix mtx)
{
    LayerInstance* newInstance = new LayerInstance(this, mtx);
    observers.push_back(newInstance);
    return newInstance;
}

///Overridden methods from Layer class, get and set Layer dimensions
int IOL::getXDimension()
{
    return dim[0];
}

int IOL::getYDimension()
{
    return dim[1];
}

void IOL::setDimensions(int x, int y)
{
    (void)x;
    (void)y;
    /*At this point I don't want to allow the user to change the dimensions
    *of the IOL manually, as that should be handled according to the Layers
    *in the Timeline. We still have to override it though.*/
}

/**Overridden methods from the Layer class, get and set the Layer
*origin coordinates.*/
///Get methods for origin coordinates
int IOL::getOriginX()
{
    return originCoords[0];
}

int IOL::getOriginY()
{
    return originCoords[1];
}

///Set methods for origin coordinates.
void IOL::setOriginCoord(int newX, int newY)
{
    (void)newX;
    (void)newY;
    /*NOTE: I'd like to take this method out of the class entirely, but
    *because it's a virtual method inherited from the Layer class, I can't
    *not implement it. For the moment, I'll just have this method call the
    *updateDimensionData function, so that the origin coords are set properly,
    *they just aren't set to the input parameters.*/
    updateDimensionData();
}

void IOL::updateDimensionData()
{
    //Set the default values
    int currentXMin = 0;
    int currentXMax = 0;
    int currentYMin = 0;
    int currentYMax = 0;
    //Test to see if there are any Layers in the animation
    if(timeline.getNumberOfLayers() > 0)
    {
        /*Set the current min/max dimensions to those of the first
        Layer in the animation*/
        int currentXMin = timeline.getLayerAt(0)->getOriginX() -
            (timeline.getLayerAt(0)->getXDimension()/2);
        int currentXMax = timeline.getLayerAt(0)->getOriginX() +
            (timeline.getLayerAt(0)->getXDimension()/2);
        int currentYMin = timeline.getLayerAt(0)->getOriginY() -
            (timeline.getLayerAt(0)->getYDimension()/2);
        int currentYMax = timeline.getLayerAt(0)->getOriginY() +
            (timeline.getLayerAt(0)->getYDimension()/2);
        /*Loop through the rest of the Layers in the animation. If the Layer
        *has a greater/smaller value than the current max/min, the current
        *X/Y Min/Max value is updated.*/
        for(unsigned int i = 1; i < timeline.getNumberOfLayers(); ++i)
        {
            int tempXMin = timeline.getLayerAt(i)->getOriginX() -
            (timeline.getLayerAt(i)->getXDimension()/2);
            if(tempXMin < currentXMin)
            {
                currentXMin = tempXMin;
            }
            int tempXMax = timeline.getLayerAt(i)->getOriginX() +
            (timeline.getLayerAt(i)->getXDimension()/2);
            {
                if(tempXMax > currentXMax)
                {
                    currentXMax = tempXMax;
                }
            }
            int tempYMin = timeline.getLayerAt(i)->getOriginY() -
            (timeline.getLayerAt(i)->getYDimension()/2);
            if(tempYMin < currentYMin)
            {
                currentYMin = tempYMin;
            }
            int tempYMax = timeline.getLayerAt(i)->getOriginY() +
            (timeline.getLayerAt(i)->getYDimension()/2);
            if(tempYMax > currentYMax)
            {
                currentYMax = tempYMax;
            }
        }
    }
    /*Now we have the min and max dimensions of all of the layers,
    *we can sum them up. This calculation works, even if there weren't any
    *Layers in the animation, and the values are set to zero.*/
    dim[0] = currentXMax - currentXMin;
    dim[1] = currentYMax - currentYMin;
    originCoords[0] = currentXMin + (dim[0]/2);
    originCoords[1] = currentYMin + (dim[1]/2);
    update();
}

/**The editMode layer allows derived classes to interface with users
depending on their unique features. */
//void IOL::editMode()
//{
//    string choice = "";
//    while(choice != "exit")
//    {
//        editMode_displayMenu();
//        getline(cin, choice);
//        if(choice == "setvisibility")
//        {
//            editMode_setVisibility();
//        }
//        else if(choice == "getvisibility")
//        {
//            editMode_isVisible();
//        }
//        else if(choice == "setrepeats")
//        {
//            editMode_setRepeats();
//        }
//        else if(choice == "getrepeats")
//        {
//            editMode_getRepeats();
//        }
//        else if(choice == "getrunning")
//        {
//            editMode_getRunning();
//        }
//        else if(choice == "setrunning")
//        {
//            editMode_setRunning();
//        }
//        else if(choice == "getcurrentframe")
//        {
//            editMode_getCurrentFrame();
//        }
//        else if(choice == "setcurrentframe")
//        {
//            editMode_setCurrentFrame();
//        }
//        else if(choice == "edittimeline")
//        {
//            timeline.editMode();
//            //Once they're done editing the timeline, make sure we
//            //update the dimensions of the IOL.
//            updateDimensionData();
//        }
//        else if(choice != "exit")
//        {
//            cout << "Error: Please select a valid command from the menu." << endl;
//        }
//    }
//}

///Overidden observable methods
void IOL::addObserver(Observer* newObs)
{
    bool alreadySubscribed = false;
    for(list<Observer*>::iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        if((*it) == newObs)
        {
            alreadySubscribed = true;
        }
    }
    if(!alreadySubscribed)
    {
        observers.push_back(newObs);
    }
}

void IOL::removeObserver(Observer* newObs)
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

void IOL::update()
{
    for(list<Observer*>::iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        (*it)->update();
    }
}

unsigned int IOL::getNumOfObservers()
{
    return observers.size();
}


//The following are implementations of helper methods for edit mode

void IOL::editMode_getRepeats()
{
    if(repeats)
    {
        cout << "The Layer is set to repeat." << endl;
    }
    else
    {
        cout << "The Layer isn't set to repeat." << endl;
    }
}

void IOL::editMode_setRepeats()
{
    //SetRepeats
    string newRepeats;
    //Prompt for input
    cout << "Set whether or not the animation repeats (true/false):";
    getline(cin, newRepeats);
    if(newRepeats == "true")
    {
        repeats = true;
    }
    else if(newRepeats == "false")
    {
        repeats = false;
    }
    //Handle invalid option
    else
    {
        cout << "Error: Input must be either \"true\" or \"false\""
        << endl;
    }
}

void IOL::editMode_getRunning()
{
    if(running)
    {
        cout << "The Layer is currently running." << endl;
    }
    else
    {
        cout << "The Layer isn't currently running." << endl;
    }
}

void IOL::editMode_setRunning()
{
    string newRunning;
    //Prompt for input
    cout << "Set whether or not the layer is running (true/false):";
    getline(cin, newRunning);
    if(newRunning == "true")
    {
        running = true;
    }
    else if(newRunning == "false")
    {
        running = false;
    }
    //Handle invalid option
    else
    {
        cout << "Error: Input must be either \"true\" or \"false\""
        << endl;
    }
}

void IOL::editMode_getCurrentFrame()
{
    cout << "The current frame is " << currentFrame << "." << endl;
}

void IOL::editMode_setCurrentFrame()
{
    //Prompt the user to enter in the new current frame index
    string frameString = "";
    cout << "Enter the index of the new current frame: ";
    getline(cin, frameString);
    try
    {
        int frameIndex = stoi(frameString);
        if(frameIndex >= 0 && frameIndex < (int)timeline.getNumberOfFrames())
        {
            currentFrame = frameIndex;
        }
        else
        {
            cout << "Error: Requested index out of bounds." << endl;
        }
    }
    catch(...)
    {
        cout << "Error: Input must be a valid integer." << endl;
    }
}

void IOL::editMode_isVisible()
{
    if(visibility)
    {
        cout << "The Layer is currently visible." << endl;
    }
    else
    {
        cout << "The Layer is currently not visible." << endl;
    }
}

void IOL::editMode_setVisibility()
{
    string newVisibility;
    //Prompt for input
    cout << "Set the visibility of the layer (true/false):";
    getline(cin, newVisibility);
    /*Test the user input. If they answered true or false, set the visibility
    *value accordingly. Otherwise, display an error.*/
    if(newVisibility == "true")
    {
        visibility = true;
    }
    else if(newVisibility == "false")
    {
        visibility = false;
    }
    //Handle invalid option
    else
    {
        cout << "Error: Input must be either \"true\" or \"false\""
        << endl;
    }
}

void IOL::editMode_displayMenu()
{
    //This menu displays all of the available commands for the IOL editMode.
    cout << "\nIOL Edit Mode Menu\n----------------------------" << endl;
    cout << "setvisibility - set the visibility of the Layer" << endl;
    cout << "getvisibility - get the visibility of the Layer" << endl;
    cout << "getrepeats - get whether or not the IOL repeats" << endl;
    cout << "setrepeats - set whether or not the IOL repeats" << endl;
    cout << "getrunning - get whether or not the IOL is running" << endl;
    cout << "setrunning - set whether or not the IOL is running" << endl;
    cout << "getcurrentframe - get the current frame in the IOL animation"
    << endl;
    cout << "setcurrentframe - set the current frame in the IOL animation"
    << endl;
    cout << "edittimeline - edit the IOL's animation" << endl;
    cout << "exit - exits out of the IOL edit menu" << endl;
    cout << "Choice: ";
}
