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
+3Qjo/SwX5si0Ue35UHFkms0KwP+7LR106oEk+BxLC5Ny2g84PBdSyyUMDlq5NixM00jiQK/mRrQeDSv7U7ZkhFZWFzwxM+fpGqKfKoB+MsDUcMMWTth8+i+6fvWCjTr/dX7YcwkTEqgV2DO4XYQjI+Vk1J/8BroQ5t/JNvuh96uoZv1lYCIYUs2ZYGpNQD69+UC4+DkduAxWngEcHplmoHII75YCRWiWCRalx8ZfVjrMqiGP3JWJViTLqi3mIJqvai/fwCy23fEBnQfggT6djkTZp8X+Bg31nsYV9W4xoJ4JsUK+SxkA17h9v7sA/DGqrIXyEiFUH7b/5JVcrJum1gy49+MYbJqKPhIbj95VbBknRQ25+2CJlUN6y3YX9LixwQuzLkoSvHcYY/JpIfVVZ/1+8zmKsS4PtMQoubPe50NKW6fgBXwNY8pd3mxGGLlDW7CGifXsvScWUgaUG+fkwdgs8ahGFyLHmKN/nJqPIrmSxCqFvUJaDAdneq5N5eGYVLstEGrVdMyBR6tM3Pv/tmbN7V/BYjkA24VpTZVpmFOacYf0xDpeNer5Q==
*/