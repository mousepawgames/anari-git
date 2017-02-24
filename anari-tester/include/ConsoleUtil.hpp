/** ConsoleUtil [Anari Tester]
  * Version: 0.1
  *
  * Author(s): Andrew Peacock
  */

/* LICENSE
 * Copyright (C) 2017 MousePaw Media.
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

#ifndef CONSOLEUTIL_H
#define CONSOLEUTIL_H

#include <iostream>
#include <sstream>
#include <limits>

// Portable method to clear console screen
inline void consoleClear()
{
    // Magic
    std::cout << "\033[2J\033[1;1H";
}

// Wait for "enter" input
inline void consolePause()
{
    std::cout << "..." << std::flush;
    std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n' );
}

#endif
