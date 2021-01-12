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
ZQQ9kJekcj9o1RMEbos+Ig5yuMQZj6CvMoRKpIfx+U3FSGUCVxlebap9ehb2qWM0w14IaY0CAt4qv8UNeq9SP9gsc5/HhKrAAri5ul3xikgr/Q+lYKq+JNRA+1unosg3JPN2F05zx3acb+udbabK9t5Ytp4qf7bkeuRl5upWuf5Zcl38lvC90xAMSrm4oBsq2mmeTdbJrW+5Ug8XPbnkiJlzYZU/60Fser2brnYAXeSwLSi6
*/