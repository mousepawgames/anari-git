//
//  ConsoleUtilities.h
//  anari
//
//  Created by Andrew Peacock on 12/10/16.
//  Copyright © 2016 MousePaw. All rights reserved.
//

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