// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp> // BOOST_STRINGIZE.

#if defined(BOOST_ZLIB_BINARY)
# if defined(BOOST_MSVC) || \
     defined(__BORLANDC__) || \
     (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) || \
     (defined(__ICL) && defined(_MSC_EXTENSIONS)) \
     /**/

// Specify the name of the .lib file.
#  pragma comment(lib, BOOST_STRINGIZE(BOOST_ZLIB_BINARY))
# endif
#else 
# if !defined(BOOST_IOSTREAMS_SOURCE) && \
     !defined(BOOST_ALL_NO_LIB) && \
     !defined(BOOST_IOSTREAMS_NO_LIB) \
     /**/

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it.
#  define BOOST_LIB_NAME boost_zlib

// If we're importing code from a dll, then tell auto_link.hpp about it.
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif

// And include the header that does the work.
#  include <boost/config/auto_link.hpp>
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED

/* zlib.hpp
a0iL4fKUmswO8y1z5NGVMNCcKZW/5jPwOYh+Ny7oS7HZnvDjjxPH/k95lxYQMDuUcjPfmsZdxJ3ffYrwJLB7AFJmFdtzxbHSY7J8bNTu+n2ssupIRrfU8fNPavHD16vtqYcXVGncg0tDAGH9i9t87k8Wvnb4qFQZ4TRZmznn914E19kC+t9NZNeX2gXcPsqYRWrbF+q9hpO19fL/RUrMs0L/WWx60Cp4rIW0mYNnAZB17kXYlE2d//hUbRVheB07IhxfuCOpOn4qmTBmIMol04WSb9pk9sUg3LJJIS4HY9IYxHmoega6I9VmWj6MlMvJ1KR+Dy0fDGgQQOfXkbi6K+2z7fNxdKmh7BgXFINnonWSn0zJxaAxzIBxJWswl263NB7x+8Lxi0KUKYJ0+lKvHdAzakKZINsgzn5J/Myf7ez807aV83xe9upcGZ1CG/h+6cZQ/YNjN8UcLdF6Yq9hcc0TYTOhdj5RjO7YMzewkYUGk4vCAyX+Lo8/7tOu74QOQ89MwKPEcb/fhfQ9Yw0ONmhT2VjbiJgHXv5IsYF5DZT4K+6nR+2gydZCNyol86gLUE6i9VAAUH3BTrzq97Js2RKU8zr/2vz8a374Y+f3/ujaX8bvOvB7HQstJPyVJDUcVLHmfEYt5CXBKjip/d66HTi2eKX2OSnfHVVFSv2DdSVSp2SEpp0gYVAPCdGF72imOi2i7N4fi57l7YuE
*/