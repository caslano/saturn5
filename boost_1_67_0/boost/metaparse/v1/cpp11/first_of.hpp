#ifndef BOOST_METAPARSE_V1_CPP11_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_FIRST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct first_of
      {
        typedef first_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<0, S, Pos, Ps...> {};
      };

      template <>
      struct first_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* first_of.hpp
+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
*/