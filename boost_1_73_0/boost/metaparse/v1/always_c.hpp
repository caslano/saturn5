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
Btaen5mwOrffbuUYVYQvR98Vrw/mOzx9aJYCJp7d9r1xM4cOGNh76GXe7/k0BcdLHdg7/1q9cNpdjP9l7t9fib47Xx3eE2Y4Pm6OcYfInfZWNO7KoB+XPhkFx11o3Nw2Cva18vnP7nBdSW7/NH0GD75kQHpW7D3B/YjbjeuzIvGeV/PvRdNO2X36p7t/Kci/Ejzftvew7P7+lhW267Lctg7yKDD97GD6PtsS01/yC9N/5hem
*/