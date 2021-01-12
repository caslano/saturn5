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
XY7w7JEZIrldjpNNV5kDuDcH8gCewi4cxIEcHJ+fL5kfTihhfs6p5uc8w2q8kK04jUdyOrvyIm5gZzE0zK9BmN9OInq2fURo3+ZI7s4urMOurM9uie2FhPkcL5LbC7nXdNV5H/fm/WzEB9mRD7EzH2EXPsoNnCTWh/k+FOZbRWSF+S42XWUuYU0+xQP5NI/mUh7LZ3gan+NEvsCL+CKv4h+5gMt4G1+m5WsfLzx7C8/iUpgq
*/