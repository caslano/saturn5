// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//  
 

#ifndef BOOST_ASSIGN_ASSIGNMENT_EXCEPTION_HPP
#define BOOST_ASSIGN_ASSIGNMENT_EXCEPTION_HPP

#include <boost/config.hpp>
#include <exception>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

namespace boost
{    
    namespace assign
    {
        class assignment_exception : public std::exception
        {
        public:
            assignment_exception( const char* _what ) 
            : what_( _what )
            { }

            virtual const char* what() const BOOST_NOEXCEPT_OR_NOTHROW
            {
                return what_;
            }

        private:
                const char* what_;
        };
    }
}

#endif

/* assignment_exception.hpp
ZXNPZLrsOduBEb8oKPaHHqFLnnK++iEwO9H6s53l7DCsZSHujO/869A1nrMTmAkuepx3sJyPgBEfUYrlvuUL8Uc67Dm7gIkqa30DtHDZc3YDM8kw18Nh+5uP4Tl7gNmM1ufdLCcfGLEHFvsNl8BXB/Gcjw37epjPcvYCEylzpuVVesr+8BNg7hj6+LWX5XwKjHVeE3H0YSOesw8YfB/gU5YDR1IncfdPuEd9X/YmzzkAzEg0PvtZzmckJ6rrlBI=
*/