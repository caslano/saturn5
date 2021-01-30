#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_whitespace_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_whitespace : is_whitespace_c<C::type::value> {};

        template <>
        struct is_whitespace<boost::mpl::na>
        {
          typedef is_whitespace type;
          
          template <class C = boost::mpl::na>
          struct apply : is_whitespace<C> {};
        };
      }
    }
  }
}

#endif


/* is_whitespace.hpp
2a68bPYdtwA+GAHxuV057+5N5rybZeVdKE1QAtCBvGTOZ24JJHOORZI52XOh7E3mZY0HzvNCNtfded5F
*/