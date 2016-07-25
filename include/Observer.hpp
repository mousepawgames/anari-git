/** Observer [Anari Graphics System]
* Version: 0.1
*
*This is an abstract class that fulfills the role of the "Observer" in the
*Observer design pattern. A class that inherits the Observer class must
*implement the "update" method. An Observer can subscribe to multiple objects
*that implement the Observable interface. When the Observable class wants to
*update its subscribers, it will call each subscriber's "update" method.
*This class is inherited by the Frame class.
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
        virtual void update(int zPref=0) = 0;
    protected:
    private:
};

#endif // OBSERVER_HPP
