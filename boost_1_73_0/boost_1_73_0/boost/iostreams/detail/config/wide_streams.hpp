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
JnjiAH/c8hBxggRlagKtFoJZO+2OyyxD8FZLqlasMkWXCbO8iy2DvYE3PFaaFGTpefkUPuSS5Ry64Dc+MdkIoPGRj0j8xTSJXqHnd1MSn0o08SpHB3WZMywnJAa8IHERWxJ9dUvijMcNaHY8z5QjkNj1lBT85wJhDn6d7pvdeoQmpBPjuQq6jxD6w2T+abb8VRE2FxFoYf3YB2AKLaQd+7V3Cbwz8O6XpBZA/Wf8ujKv64etgxu8O8BkyG3mrTg7yI438zwXxWu8OTLcqg6/LbYvZ9+b9ptG31v2r02+N0FeG3xbaqF1mjI54dh/XqPjWqmeCYn80ZVlk46HMyvj/sng8uy8/7653O56hu1W2WtUPIbfYpXTkfevr4/vE4HNfXxzs9uE3/z2bnWz67GiCAedZw1F1XxM2sOlVoyxtZwa2wilGYaYGP7SkGv51/uto+hmLbaLj1ZrAEv1I1gdRmE7XD6crfQSz8xTRRB+65UWT94x7FINsHdSLYOtgGzyPnWEvOYdf5f3Gfb0MbykcH68ng+jv3YkqqF8UjVfBCHW+b3VbI1y5Gmd0h34Byc5vouASxywOPXd64vhieWxYBmMlc6Zrfi4Uwi1oXxyrUHbbUK79jQyhrK2tkcqS4iY2rp+vqWr6tlK0j7u
*/