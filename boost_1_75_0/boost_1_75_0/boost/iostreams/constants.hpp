// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains constants used by library.

#ifndef BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED
#define BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#ifndef BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE 4096
#endif

#ifndef BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE 128
#endif

#ifndef BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE 4
#endif

#include <boost/iostreams/detail/ios.hpp>  // streamsize.

namespace boost { namespace iostreams {

const std::streamsize default_device_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE; 
const std::streamsize default_filter_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE;
const std::streamsize default_pback_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED

/* constants.hpp
JmnAbzyRLheD6PzXR/NrHPk2th1mvK3hRrZkq3/xEJPWGIO0e8nFy9j5h6z+ZJ8w6CKfWnIPqupBMSmunsD3RQp3+MusTKFM/j3kvkfoFogEZ4JIg1AB82il+mAZrNiR0ro9q513N7NzGTWZX6pHuHd00WUC8kG0Zu1ci7Rzw5Fwb5906Hc075DVAr2M/CO41HhQwTcyKAdb/imm3iOyMIcbczuSJsaiWeIgFKEky7MfIwarLtsGJPIIbDBMbMyxKK67cKAgQTRKa/0rJ9dWTqvp1LbiXwVt95J+PRz3LqBsJ2N3OSePaG3ci8tqLs2hb2xYx5gttCYcHVa1OyLoJ7z8gMq3H/zlARmINJf6XaQLyiFRTX1r2YZ8RrvBjAkd6okcCprbmNFZH9Dzun7R2pe4IN+kviC5yPFi2qhXuHYO6pchkvBZHOdJWFw6bfxdG8kp0i7wuuGsEsv9dH9NXAuC3b4EwJhfM6ZbGZs70b0YZTDnphcOBcWzC/0VSjgXOnEODW/mxLNHL8HDzqkyctkT0nKD1s1k9xaz9Dnd6pdyR5mXB4d7l3KH5heEBWP2INnDrBug+qWz1uV9bhzsp8KU/M2cL8ESbK9n7tfDyR7nbrNcNicocvr+EqVgLM154dtrT9PjXMFYoYjLwlqIfW87CYk/nF2E0vMFsJRSb2VGw58+e2zOEgSTb42GpaKMuEvH2n9m5jSja6z5
*/