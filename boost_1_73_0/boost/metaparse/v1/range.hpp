#ifndef BOOST_METAPARSE_V1_RANGE_HPP
#define BOOST_METAPARSE_V1_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/util/in_range_c.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class From, class To>
      struct range :
        accept_when<
          one_char,
          util::in_range_c<char, From::type::value, To::type::value>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* range.hpp
OjtwAC/jJbyXGXyDg/k+M7mBQ7mVlzP38/0K/oEj2ZGjeBZHcwRzOJZjeSev4gxezTkcx0d5LZdyPLfwBh5s3Z/AhpzIVpzEjrydfXkXr+HdXMhpXMnpXMdZ3MHZLOa4+H6W5VweywfYmPPYig/xHC7kpXyMo/g4r+ISXs9nOYPPcTaXcgFfyrW4fSE/4EfcxL9zK9fzO37C/Us4jmYKN/JIfsbjuJkt+AVb80uezq1M5XYO
*/