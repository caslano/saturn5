// ----------------------------------------------------------------------------
// workarounds_stlport.hpp : workaround STLport issues
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_MACROS_STLPORT_HPP
#define BOOST_MACROS_STLPORT_HPP

// *** This should go to "boost/config/stdlib/stlport.hpp".

// If the streams are not native and there are problems with using templates
// accross namespaces, we define some macros to enable a workaround for this.

// STLport 4.5
#if !defined(_STLP_OWN_IOSTREAMS) && defined(_STLP_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif

// STLport 4.0
#if !defined(__SGI_STL_OWN_IOSTREAMS) && defined(__STL_USE_OWN_NAMESPACE) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif


// ----------------------------------------------------------------------------

#endif // BOOST_MACROS_STLPORT_HPP

/* workarounds_stlport.hpp
HmdqPb55GfY4R+0xsbUeJXWOJ7Pb0mNv0aNN67Ef9Vim9rjstlZ6jFR7fLpNPS6/lPf4UbDa47eXUtDqeIfnWUzUWXdHNEXgJTcCbP6aOiXwKG6PF6MIatMoksUortRGcb1uFHBGyXf6GcWnO1sZxYvdxCimDmnLKD5J4KP4LEgdxecJCP0lKvRTMluB/q0XiR4j29RjqugxQ+txAPW4VO1xg6OVHu0XiB5fGtyWHjf25D3uNqk9bukJQV6e5YeJQ9oJRwJeG67iBwgS9AU9tQAwr/Q0BODP0R8mVWq8l44NxGIspctf2KZ4kBLvecMA7pFz1QBy3bmcPy/mzwv4M5o/I/kziD9P3kzPo/zZwJ8H+HPXzci9zEjXzmz1PhmuaD2vG8zE8MyuZ//q2LldBzP++BI/Oach8AURHIwnHTXgfQgBckEi3eYWTeIBV2ZdosYEweM35xKAWFjybkNm6A7irOYhnkXM+VOMsOmMu9Yd1DHwBRT5gID4z004x8M3CT4+Xhc75+PXNB6eIkpgXvtxCdk4ekyrUH2xsBWJpJKM5GYH8lNdujPU6r2DvEHM5RHAgVvsvatdEZkha4ABbyzd6Oro8KClYMOHaHEJ323tht+19gUQs4Yi9Yu5rX/R3Vw+KCLPXbyQYyOOO4KNu6xhqtpG0rl7BSrSEKx+sezCc34B276hNkh8MfSCc36BsZzfUL945qJzfgHS
*/