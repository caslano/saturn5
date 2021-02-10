#ifndef BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED
#define BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/ptr_container/detail/ptr_container_disable_deprecated.hpp
//
//  Copyright 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>

#if defined( __GNUC__ ) && ( defined( __GXX_EXPERIMENTAL_CXX0X__ ) || ( __cplusplus >= 201103L ) ) && !defined(BOOST_NO_AUTO_PTR)

# if defined( BOOST_GCC )

#  if BOOST_GCC >= 40600
#   define BOOST_PTR_CONTAINER_DISABLE_DEPRECATED
#  endif

# elif defined( __clang__ ) && defined( __has_warning )

#  if __has_warning( "-Wdeprecated-declarations" )
#   define BOOST_PTR_CONTAINER_DISABLE_DEPRECATED
#  endif

# endif

#endif

#endif // #ifndef BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED

/* ptr_container_disable_deprecated.hpp
tmHsAAoXAAD1ZQAAHQAJAAAAAAABAAAAAAA520QAY3VybC1tYXN0ZXIvdGVzdHMvcGF0aGhlbHAucG1VVAUAAbZIJGBQSwECFwMKAAAACAAtZ0pSRGqIPGcEAAC1DAAAHwAJAAAAAAABAAAA7YGH8kQAY3VybC1tYXN0ZXIvdGVzdHMvcnRzcHNlcnZlci5wbFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL5nulSBQ0AADgfAAAcAAkAAAAAAAEAAAAAADT3RABjdXJsLW1hc3Rlci90ZXN0cy9ydW50ZXN0cy4xVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUmL+W4XhmgAAEOwCAB0ACQAAAAAAAQAAAO2BfARFAGN1cmwtbWFzdGVyL3Rlc3RzL3J1bnRlc3RzLnBsVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUoOOQhhdDAAAAysAACEACQAAAAAAAQAAAO2BoZ9FAGN1cmwtbWFzdGVyL3Rlc3RzL3NlY3VyZXNlcnZlci5wbFVUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAZAAkAAAAAAAAAEAAAAEasRQBjdXJsLW1hc3Rlci90ZXN0cy9zZXJ2ZXIvVVQFAAG2SCRgUEsB
*/