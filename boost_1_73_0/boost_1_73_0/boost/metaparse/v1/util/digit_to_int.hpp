#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/digit_to_int_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class D = boost::mpl::na>
        struct digit_to_int : digit_to_int_c<D::type::value> {};

        template <>
        struct digit_to_int<boost::mpl::na>
        {
          typedef digit_to_int type;
          
          template <class D = boost::mpl::na>
          struct apply : digit_to_int<D> {};
        };
      }
    }
  }
}

#endif


/* digit_to_int.hpp
wF+tzEz7w937d1b4A48t+2Zxy7pRvz6HsYeo/YpNS1Zk7h7yzJzrvvxZ8LuGxxjbQu1Prev7yrj/Wn5s6q/6r270Pvw7xg5R+6xvC8d5jy69eU3VZXkH+t1+LWMT0rH9zfNyNstlZW9ccs7EGQtGSMMY+xm1X7jbd27wiprrPx1wU2j0eNcTjD1D7U890OZ+sc///3nLk2N/ePjeW55k7Di1v/R/63cfH1a15M3Z4Xe3l72xnLHJGdgezb/1yLI=
*/