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
/0zYbsTYDaNTS/luSTk05jwFTJCLAY4dJd9YbggMa6YTXul2U0tuL9AcsrkTJrWJ/gpSdAkL7x55bGXbHJQirnwLe3pye2Q5Sll3BxgQnTBcD2S44s2gQ5ra+Js7cu6MxhdlQwkaF9sM3FlV12BXwtJ2wFOqtcNiW4BjfPjr0ZhtruUtwiQh7WuezfDVyLtNfMSM0ihcXlo12CvV6/H4V7TcjTEyOXj26YY1vvgRfnESeObCfu978T7go0nrpMR5Ehfj6eWSWBYMNgKIUVeTct+/gLov10dTCbiSU78fxUeF0t52asaEWPpip7TZTx5JMWlHHSry7gHcTHIWC/Of8tdm4hyBBQ0MVVO2YSk3AUhxbGVPGh2eDvlGyKbkWFX3ypMcasDRFnQK+yGQhUk4kHfVWGkkL/lkxv+dwRIi2UjL5npXJPq9KXkMsKcfQRxS/OPTrN+YypgZ8AYxLSArJ1bPi11mVFg+eKZpqksaeNBS3HfbNiNGGKW9uAUku1c4sSa3csIVr7/m3OUzznDAB37shVPOQwqUsXLsYd6Tlca090eRqv1bhcYs0Q==
*/