#ifndef BOOST_METAPARSE_V1_REPEATED_HPP
#define BOOST_METAPARSE_V1_REPEATED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated : foldl<P, boost::mpl::vector<>, impl::back_inserter> {};
    }
  }
}

#endif


/* repeated.hpp
11L5qvczXh1fq99Xdf2g8qfr+quOV6r8QiqeoZ5/SNcHdb5MFR9R9zNDX1+dr1Lzuj1R5bdK+UO6fHR7oJ7PDnX+Tao816rzb9LPS8UHdP4qPq5iU1vFqvzj1fGgilM1r9sX/fwbq/tR9x9Scbo6f6XigyrOVP5Vun6q+hDS59e8Pq77G3V8h24f9Puo6s8Bdfy4ikPKf0TVp+Pq/ox+f1W8Q9dPlf8RFYdUf1Cp8qlU5zuu+OM6X1V+Jk7lq+I=
*/