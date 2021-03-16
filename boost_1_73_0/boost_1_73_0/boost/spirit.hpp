/*=============================================================================
  Copyright (c) 2001-2008 Joel de Guzman
  Copyright (c) 2001-2008 Hartmut Kaiser
  http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_DEPRECATED_INCLUDE_SPIRIT
#define BOOST_SPIRIT_DEPRECATED_INCLUDE_SPIRIT

#include <boost/version.hpp>

#if BOOST_VERSION >= 103800
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__)
#  pragma message ("Warning: This header is deprecated. Please use: boost/spirit/include/classic.hpp")
#elif defined(__GNUC__) || defined(__HP_aCC) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#  warning "This header is deprecated. Please use: boost/spirit/include/classic.hpp"
#endif
#endif

#if !defined(BOOST_SPIRIT_USE_OLD_NAMESPACE)
#define BOOST_SPIRIT_USE_OLD_NAMESPACE
#endif
#include <boost/spirit/include/classic.hpp>

#endif

/* spirit.hpp
bo4arpTBm7L1BjnEah6NAD0aL+xKF/WHvSY39AoQrLL7dPbs5q+yN+hEzY7bL5+oFm/kqLmfTN/8gjnUJoPML/0qE8HI088Rw9RicB5kM0fF07fKfFSvBky+Yt3vV9aoXm0xqUO2s3AlTw61s5CF6+TjI3INkFM/xk2k10267SDZl+7oL6dF9EGeLuu5P9sxPs2O2FtNNu9swvcOwOpsm3UHugdov3Y2T14Y5NhAdrtBdvmg9rsDNEpf5biDodg=
*/