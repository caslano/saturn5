#ifndef BOOST_METAPARSE_V1_ALWAYS_C_HPP
#define BOOST_METAPARSE_V1_ALWAYS_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/always.hpp>
#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C, class Result>
      struct always_c : always<lit_c<C>, Result> {};
    }
  }
}

#endif


/* always_c.hpp
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
*/