// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from http://www.boost.org/more/separate_compilation.html, by
// John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <cstddef>

#if defined(_MSC_VER)
# pragma once
#endif       

//------------------Templated stream support----------------------------------//

// From boost/dynamic_bitset.hpp; thanks to Matthias Troyer for cray patch.
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# if defined(__STL_CONFIG_H) && \
    !defined (__STL_USE_NEW_IOSTREAMS) && !defined(__crayx1) \
    /**/
#  define BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES

//------------------Wide stream support---------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
# if defined(BOOST_IOSTREAMS_NO_STREAM_TEMPLATES) || \
     defined (BOOST_NO_STD_WSTREAMBUF) && \
     ( !defined(__MSL_CPP__) || defined(_MSL_NO_WCHART_CPP_SUPPORT) ) \
     /**/
#  define BOOST_IOSTREAMS_NO_WIDE_STREAMS
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS   

//------------------Locale support--------------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
# if defined(BOOST_NO_STD_LOCALE) && \
     ( !defined(__MSL_CPP__) || defined(_MSL_NO_WCHART_CPP_SUPPORT) ) \
     /**/
#  define BOOST_IOSTREAMS_NO_LOCALE
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_LOCALE

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED

/* wide_streams.hpp
Y5VsvbkS6vgrx49uf8Kgv37ez++hmDGIgY0rOYNTUgIwfg3QO8hF0zhwty8hm3ycx5CAvXJSXwKLGr/3E7DBA+C3C+0UR7O3f7xlETb4zrHQ61uFQlQyY1ZtBBrVhJ22whoE7TBLBkhAVSBoh/QS3geqzr4QwQAp68Ixv/ZmUVQx3R9u6lpGP9fyk+mgrFwl/fmYtqvhIi/E4gmkwo0qIEfC3scBljPC7ccA3IK5ESqT2xeM468+tn9r73PJ1oBq6GYKD5Eqwq8lZQEptliNctPu/guG9QjLIuKMjr0pb59mbUjuSZkzmn9KIONCabuoAyzXtHJeOliFD+TVoKC2128WQdEXwXirOYkeanuhYctKvUGOs2vJhbiY606VP4vwT0TPFvfY7RcNqt0OGt5FDGq48aMjp11K/di73dLtHy/SyqiWEOgHS/57QKTMX6GCrZDS8M6sd6zDfScleq9a/XKE3ny/vKL8pngsameZzL5yU2ymieN8b4qcXSSt/9y+LXDgwFfk1Sz2QmJ88z+RAJRwpuYoYibccruZHxpc+cBw2QeSC0/89feymQ==
*/