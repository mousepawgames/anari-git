/** Independent Object Layer [Anari Graphics System]
* Version: 0.1
*
*This is a more complicated Layer type, representing an independent Timeline/
*animation in the master Timeline.
*
* Last Updated: 14 May 2016
* Author: Audrey Henry
*/

/* LICENSE
* Copyright (C) 2016 MousePaw Games.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IOL_HPP
#define IOL_HPP

#include "Layer.hpp"
#include "Timeline.hpp"
#include <string>

typedef int Matrix;

class IOL : public Layer
{
    public:
        IOL();

        //Destructor
        virtual ~IOL();

        //Sets and gets for currentFrame variable
        unsigned int getCurrentFrame();
        void setCurrentFrame(unsigned int newFrame);

        /**This method increments the currentFrame depending on the IOL's
        *state (running/repeating/etc.). This way the user doesn't need
        *to know the currentFrame in order to move ahead one Frame.*/
        void nextFrame();

        //Sets and gets for isRunning variable
        bool isRunning();
        void setRunning(bool newRunning);

        //Sets and gets for animationRepeats variable
        bool animationRepeats();
        void setRepeat(bool newRepeat);

        /**Method to render the image to the screen
        *\param a transformation matrix that will translate, scale, and rotate
        *   the image on the screen.
        *\param an optional integer parameter that is used for some layer
        *   types. Because the IOL is independent of the master Timeline,
        *   it doesn't need to be told what Frame to render.*/
        virtual void render(Matrix transformationMatrix, int frameIndex=0);

        ///Overidden methods from Layer class. Set and get visibility variable.
        bool isVisible();
        void setVisible(bool newVisibility);

        /**Overidden method from Layer class that creates a new LayerInstance pointer
        *\param the transformation matrix that will be applied to the new
        *   LayerInstance.*/
        LayerInstance* newLayerInstance(Matrix mtx=-1);

        ///Overridden methods from Layer class, get and set Layer dimensions
        int getXDimension();
        int getYDimension();
        void setDimensions(int x, int y);

        /**Overridden methods from the Layer class, get and set the Layer
        *origin coordinates.*/
        ///Get methods for origin coordinates
        int getOriginX();
        int getOriginY();

        ///Set methods for origin coordinates.
        void setOriginCoord(int newX, int newY);

        /**The editMode layer allows derived classes to interface with users
        depending on their unique features. */
        void editMode();

        ///Overidden observable methods
        void addObserver(Observer* newObs);
        void removeObserver(Observer* newObs);
        void update();
        unsigned int getNumOfObservers();


    protected:
    private:

        ///This is the IOL's personal Timeline that it manages
        Timeline timeline;

        ///boolean that determines whether or not the Layer is visible
        bool visibility;

        /**Array containing the dimensions of the image in pixels. Because
        *the IOL is made up of multiple Layers, the overall dimensions will
        *be calculated using all of the Layers. This will be subject to
        *change.*/
        int dim [2];

        /**Array containing coordinates of the IOL's origin. The origin will
        *be determined as the average origin of all of the Layers in the
        *IOL's Timeline.*/
        int originCoords[2];

        ///Vector that will contain the LayerInstances
        std::list<Observer*> observers;

        /**This integer value stores the index of the current frame in the
        *animation. When the IOL is signaled to render, it will display the
        *Frame at this index.*/
        unsigned int currentFrame;
        /**This boolean value determines whether or not the IOL animation
        *is currently running. If the animation is running, the currentFrame
        *value will be incremented each time the IOL is told to render.
        *If it's not running, the IOL will not update the currentFrame index,
        *and will keep displaying that Frame.*/
        bool running;
        /**This boolean determines whether or not the IOL animation repeats.
        *If it repeats, then when the currentFrame reaches the end of the
        *Timeline, it will go back to the first Frame of the animation and
        *continue.*/
        bool repeats;

        /**This is a private helper method that is called whenever the Layer
        *coordinates/dimensions could have been updated. It currently only
        *determines the IOL dimensions based off of the dimensions and origin
        *coordinates of the Layers contained in the Timeline. It does not yet
        *make calculations based on the current frame in the IOL, and the
        *transformation matrices that may have been applied to the
        *LayerInstances there. This function should be called any time a Layer
        *is added to or removed from the IOL.*/
        void updateDimensionData();

        //Helper methods for edit mode
        void editMode_getRepeats();
        void editMode_setRepeats();
        void editMode_getRunning();
        void editMode_setRunning();
        void editMode_getCurrentFrame();
        void editMode_setCurrentFrame();
        void editMode_isVisible();
        void editMode_setVisibility();
        void editMode_displayMenu();
};

#endif // IOL_HPP
