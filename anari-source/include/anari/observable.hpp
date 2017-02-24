/** Observable [Anari]
  * Version: 0.1
  *
  * This is the header file for the abstract class Observable. It provides an
  * interface for objects to implement the Observer pattern. LayerInstance and
  * Layer both inherit from this class. A class that inherits the Observable
  * class will have a list of subscribers (objects that inherit the Observer
  * interface). When the Observable object wants to update its subscribers,
  * it can loop through all of its stored Observers and call their "update"
  * method.
  *
  * Author(s): Audrey Henry
  */

/* LICENSE
 * Copyright (C) 2016 MousePaw Media.
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


#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include "anari/observer.hpp"


class Observable
{
    public:
        //Constructor
        Observable();
        //Destructor
        virtual ~Observable();

        //Virtual methods that will be implemented by derived classes:
        /*Virtual method that will add an Observers to a list or container
        *of Observers. The Observer will be a new subscriber to this object.
        *\param a pointer to the Observer that will be added as a subscriber*/
        virtual void addObserver(Observer* newObs) = 0;

        /*Virtual method that will remove an observer/subscriber from
        *the container.
        \param a pointer to the Observer that will be removed from the list
            of subscribers*/
        virtual void removeObserver(Observer* newObs) = 0;

        /*Derived classes will use this method to loop through all of their
        *Observers/subscribers and call their update method.*/
        virtual void update() = 0;

        /*Virtual method that will return the number of subscribers to a given
        *Observable object. */
        virtual unsigned int getNumOfObservers() = 0;
    protected:
    private:
};

#endif // OBSERVABLE_HPP
