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
18C0It0xLrfYi9ynUn0cS1RUxVQaKc2gxJ8pFTEesTqV52nXHZTja4AnrHk0q75wUuFs2jP9lHHTKG7HmeOYO5gMNlA8Kp2UTks/IXZ/ka7BMY+U50HhnlNqGwPt2Chizy+fYSrxVRF3tfn6PAvnovKfgO2nilusgfEtYh9vAhkrFAibpW3SLmmfdED6Xjom/Qjui4FuXqH8qTewx7KIfY3LmHJ8Rb4K2LkWMpnhBb4n/ydfBvnrBifaTKKIY7/iJEBoKbyrWl5RuAK4ULXWrsKs9aaQInZ/i0JNbbLWETne3ehl9DX6Q3MPMUYbVLjjOHGkND2Z3sWsZEvzX4pHxIZyC2UYsH2b4Wz62H69iO3TvuTjgNcWhxWx1/32cj9xP3NLkW2b7bmTZ7w1ZxIHpFsAVXBauAd0rSpqUHSHRC+pt5QjpUHTSJppV4Hu17z0PP2m7mkUNRKNCXCozmYzeOciVDqOfZopxVaxZ/baIHLusaW4KvZ8tjVjt407yT/nSwrlhDChk12x+63gIlYUFekE/FkZuJN4cNcOeS942UKaq9AV7kp7pZPSVemh9AbuDFAGKXOQrb5qOJh0HHz1KbVA9dCKauW0QKjAVtp3WjG9mr5U/05n4Y0+hcav5pj3SitCJThZawo6lPVTUpIW6CbQ0+PovfQvwP/JzDrGlW0AJp8DJ/Eb685V4KJw1bO5ZXBoJ7njfKjQG7p3
*/