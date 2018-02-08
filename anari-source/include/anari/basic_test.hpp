/** Basic Sanity Tests (Anari)
  * Version: 0.1
  *
  * Once other tests have been added to Anari, this file can
  * be removed.
  *
  * Author(s): Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2018 MousePaw Media.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

#ifndef ANARI_BASIC_TESTS_HPP
#define ANARI_BASIC_TESTS_HPP

#include <type_traits>

#include "pawlib/goldilocks.hpp"

#include "anari/layer.hpp"
#include "anari/staticlayer.hpp"

class TestBasic_Inheritance : public pawlib::Test
{
    public:
        TestBasic_Inheritance()
        {}

        testdoc_t get_title()
        {
            return "StaticLayer is Layer";
        }

        testdoc_t get_docs()
        {
            return "Tests to make sure StaticLayer is a derived class of Layer.";
        }

        bool run()
        {
            if(std::is_base_of<Layer, StaticLayer>::value)
            {
                return true;
            }
            return false;
        }

        ~TestBasic_Inheritance()
        {}
};

class TestBasic_NonInheritance : public pawlib::Test
{
    public:
        TestBasic_NonInheritance()
        {}

        testdoc_t get_title()
        {
            return "LayerInstance Is Not Layer";
        }

        testdoc_t get_docs()
        {
            return "Tests to make sure LayerInstance is not a derived class of Layer.";
        }

        bool run()
        {
            if(std::is_base_of<Layer, LayerInstance>::value)
            {
                return false;
            }
            return true;
        }

        ~TestBasic_NonInheritance()
        {}
};

class TestSuite_Basic : public pawlib::TestSuite
{
    public:
        TestSuite_Basic()
        {}

        void load_tests();

        testdoc_t get_title()
        {
            return "Anari: Basic Sanity Tests";
        }

        ~TestSuite_Basic()
        {}
};

#endif //ANARI_BASIC_TESTS_HPP