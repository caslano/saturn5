// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENVIRONMENT_ITERATOR_VP_2004_05_14
#define BOOST_ENVIRONMENT_ITERATOR_VP_2004_05_14

#include "eof_iterator.hpp"

#include <utility>
#include <string>
#include <cassert>

namespace boost {

    class environment_iterator 
        : public eof_iterator<environment_iterator, 
                              std::pair<std::string, std::string> >
    {
    public:
        environment_iterator(char** environment)
        : m_environment(environment)
        {
            get();
        }
        
        environment_iterator()
        {
            found_eof();
        }
        
        void get()
        {
            if (*m_environment == 0)
                found_eof();
            else {
                std::string s(*m_environment);
                std::string::size_type n = s.find('=');
                assert(n != s.npos);
                value().first = s.substr(0, n);
                value().second = s.substr(n+1);
                
                ++m_environment;
            }
        }
        
    private:
        char** m_environment;
    };
}
#endif

/* environment_iterator.hpp
xf8FdyzIwwLJBJENxzoWFgt9Mdu8KNE2b1PtRVNDz6olvZn2dvsN8NuTcaKY+4R3fR1aFMCOeN6UjGfF1sfx0kVw37mW85gTUprg16Xi5Xksss0HxeFuvPlrUwk8AvsdKfLzXDyOQ7HARsO5JSXjEiOaeq4FWr1agbUw25u9KxXFK8xlC2XZZ2j9cU8K4+XqrUm+dm4x+dkQFtZFX1A/u1eVyQds7XYf5bF1ns5Tr2nsjOHWKgXh5hXKbO2Fb9A=
*/