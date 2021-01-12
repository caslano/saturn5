#ifndef BOOST_METAPARSE_V1_FOLDR_HPP
#define BOOST_METAPARSE_V1_FOLDR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr : foldr_start_with_parser<P, return_<State>, BackwardOp> {};
    }
  }
}

#endif


/* foldr.hpp
B/NqluP1PJQzWIGzWJFLWJnPsy3fZDt+yPbcxNO5gx1Y/AzLncfzTNblWWzCs3kSO7Ezz2FXdmZvduFgduUV7MY/szsn8zw+wB58mOdzMXvycfbis0zjMqYHv+PPF3nXSwTXT6TwEHGPCPrbzTmO2azNYWzE4WzBy9maV/Am/ol38EpO51g+y6v5Pq/hRxzHjbyeB5rveB7KiazEm9iKk9ief2EH3roXfQO9ltc30Ov13v9p
*/