/**
*Anari Graphics System, version 0.1
*Layer Class
*This class is an interface, so far it only contains a stub for a render method.
*Each layer "flavor" should implement this interface.
*The main idea was to be able to utilize polymorphism.
*Ex: (Layer* layer = new IndependentObjectLayer();)
*Last Updated: 17 February 2016
*
*Copyright (C) MousePaw Games
*Licensing:
*/

#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <exception>
#include <list>

#include "Observable.hpp"

//Use a forward declaration so we can reference LayerInstance pointers
class LayerInstance;

using std::string;

/*NOTE: In the future we will use real Matrix variables, but for now
we'll just typedef an int.*/
typedef int Matrix;

class Layer : public Observable
{
    public:

        ///Constructor
        Layer();

        ///Desctructor
        virtual ~Layer();

        /** The render method that all Layer types will implement.
        *\param the transformation matrix that will be applied to the Layer's
        *   image and affect how it's displayed on the screen. The
        *   transformation matrix can translate, scale, and rotate the image
        *NOTE: For now, I just want the render method to display to the screen,
        *so I'll just have it return void.*/
        virtual void render(Matrix transformationMatrix) = 0;

        //Methods to be implemented by derived classes.
        /**Method that tells whether or not the Layer is currently visible.
        *\return a boolean that is "true" if the Layer is visible, and
        *   "false" if the Layer is not visible.*/
        virtual bool isVisible() = 0;

        /**Method that sets the visibility of the Layer
        *\param a bool value that sets whether the Layer is visible or not.*/
        virtual void setVisible(bool newVisibility) = 0;

        /**Method that returns a pointer to a new LayerInstance created from
        the layer*/

        /**Method that returns a pointer to a new LayerInstance that references
        *the current Layer.
        *\param an optional transformation matrix that will be applied to the
        *   new LayerInstance*.
        *\return a new LayerInstance* that references the current Layer*/
        virtual LayerInstance* newLayerInstance(Matrix mtx=-1) = 0;

        ///Methods to get and set the Layer's dimensions on the canvas
        virtual int getXDimension() = 0;
        virtual int getYDimension() = 0;
        virtual void setDimensions(int x, int y) = 0;

        /**Methods that will allow the user to set and retrieve the origin
        *coordinates*/
        ///Get methods for origin coordinates
        virtual int getOriginX() = 0;
        virtual int getOriginY() = 0;

        ///Set methods for origin coordinates.
        virtual void setOriginX(int newX) = 0;
        virtual void setOriginY(int newY) = 0;

        /**The editMode layer allows derived classes to interface with users
        depending on their unique features. */
        virtual void editMode() = 0;

        ///Overidden observable methods
        virtual void addObserver(Observer* newObs) = 0;
        virtual void removeObserver(Observer* newObs) = 0;
        virtual void update() = 0;
        virtual int getNumOfObservers() = 0;
    protected:
    private:
};

#endif // LAYER_H
