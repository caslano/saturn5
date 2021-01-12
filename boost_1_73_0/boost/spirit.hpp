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
RiA9cHI09NJP1viHT2kuuYXoNZ9q/9QUfIXIk2wNE7FZ6geHZoXTa8zb0ISq0nAdIDqEfJkdvcidZQp3W5lFPKwHkLmzzM5XSp1lkPiFywZLZ7JHsdNFd/Nk86wOOvxY3QHYhfoywlMyYTAqbp58uBoRoyBRjz1jLtKpFNz0FxyKdUIbD1vj/raFWqT4gO2eH1EoQCDqn9Rj1PbkD/obmn9OYvO7Ept/cmLzX1Z8wDdXJalF
*/