/**
*Anari Graphics System, version 0.1
*StaticLayer Class
*This is the most basic Layer type, representing a static image on the canvas.
*Last Updated: 30 April 2016
*
*Copyright (C) MousePaw Games
*Licensing:
*/

#ifndef STATICLAYER_H
#define STATICLAYER_H

#include "LayerInstance.hpp"
#include <string>

using std::string;

/*NOTE: Will use actual Matrix variables in the future,
but for now we'll typdef the int type.*/
typedef int Matrix;

class StaticLayer : public Layer
{
    public:

        /**Constructor
        *\param an optional parameter that represents the StaticLayer's image
        *\param an optional parameter that represents the x dimension of the
        *   Layer image in pixels.
        *\param an optional parameter that represents the y dimension of the
        *   layer image in pixels.
        *\param an optional parameter that represents the x coordinate of the
        *   origin point.
        *\param an optional parameter that represents the y coordinate of the
        *   origin point.*/
        //NOTE: We are currently storing the image as a string for testing
        StaticLayer(string image="", int xDim=250, int yDim=250, int xOrigin=960,
                    int yOrigin=540);

        ///Destructor
        virtual ~StaticLayer();

        /**Method to render the image to the screen
        *\param a transformation matrix that will translate, scale, and rotate
        *   the image on the screen.*/
        virtual void render(Matrix transformationMatrix);

        ///Method that returns the image
        string getImage();

        ///Method that sets the Layers' image
        void setImage(string newImage);

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

        ///Overidden Observable methods
        void addObserver(Observer* newObs);
        void removeObserver(Observer* newObs);
        void update();
        int getNumOfObservers();


        //editMode functions
        void editMode();





    protected:
    private:
        ///Base image that the Layer renders to the screen
        string image;

        ///boolean that determines whether or not the Layer is visible
        bool visibility;

        ///Array containing the dimensions of the image in pixels
        int dim [2];

        ///Array containing coordinates of Layer image origin.
        int originCoords[2];

        ///Vector that will contain the LayerInstances
        std::list<Observer*> observers;

        /**editMode functions that are specific to the StaticLayer type.
        *I chose to make these methods private, because we want the StaticLayer
        *class to handle these behind the scenes in the editMode function.*/
        void editMode_help();
        void editMode_getImage();
        void editMode_setImage();
        void editMode_setDim();
        void editMode_getDim();
        void editMode_setOrigin();
        void editMode_getOrigin();
        bool editMode_isVisible();
        void editMode_setVisibility();
};

#endif // STATICLAYER_H
