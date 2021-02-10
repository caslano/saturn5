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
/6lR6jnezeoDRVHAmWNLgm2KHpUx7SjO+4lY4TJQwJBV6hp1ocfF6YANRhpZNxiEYuZLtDySuvFh5wS/k/O6KTjpfgNKmqb8mvK/zdTiOvJ3aPNLchWpQxeEsgfhkxDh9XzC4+H1+FzCH1BLAwQKAAAACAAtZ0pSNSRNhuwAAABWAQAAJQAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3NzbHYzLmRVVAUAAbZIJGA1kE1rhEAMhu/5FTm2B4Uq/WBuZWHpwULZ2fZuNejAOLGTjHb/fce1e8kXz/smxI4c1WANDYfBoIhfaji3gxj8oiiOg8BHZOWOfZ5Z28Br31Nv4D0p/ebiqqlQvSwPeyxvuYIT/SQXKSvPjQVLVLRe2OCoOm/clit4Iz8b/BTa/PP+Q6s0cLyYzQeKooAjx44EuxQ9KmPaUVz2E7HGdaSAIavUterCgKvTEVuMNLFeYRCKmS/R8kTqppudE/xOzutVwUn3G1DSPOfXlP9tplbXk79Al1+Sq0g9uiCUPQjvhAhPxwM+Pz693JfwB1BLAwQKAAAACAAtZ0pSd45ac7YAAAAcAQAAJgAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3N0ZGVyci5kVVQFAAG2
*/