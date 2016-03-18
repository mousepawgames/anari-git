/**
*Anari Graphics System, version 0.1
*Observer Class
*This is an abstract class that fulfills the role of the "Observer" in the
*Observer design pattern. A class that inherits the Observer class must
*implement the "update" method. An Observer can subscribe to multiple objects
*that implement the Observable interface. When the Observable class wants to
*update its subscribers, it will call each subscriber's "update" method.
*This class is inherited by the Frame class.
*Last Updated: 17 February 2016
*
*Copyright (C) MousePaw Games
*Licensing:
*/

#ifndef OBSERVER_HPP
#define OBSERVER_HPP


class Observer
{
    public:
        //Constructor
        Observer();
        //Destructor
        virtual ~Observer();

        /*Method that is called by the Observable object in order to update
         *the Observer. It was originally designed around the Frame object.
         \param the zPreference of the LayerInstance in the Frame that will
            need to be updated.*/
        virtual void update(int zPref) = 0;
    protected:
    private:
};

#endif // OBSERVER_HPP
