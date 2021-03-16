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
nafrEfVDPfJI6mLD6/yMx5ftJKp1PHkkdQlSzT1f2asp9xI1Lp48krrU8Hr4V3E6W1m6Lp48ksoyvI0qOLptLVHPxpNHUjMMr71t1raKJ+pYPHkklW34U+7epNUGopokkEdSMw2/1uKBr7JZwPAE8kgqB6nWnm/imvpsHFWRQB5J5RrebtywpvJXojYmkEdSeYZf68uoL9nz+jKBPJKaZXhpbLrj3dNENU0kj6RmI+XPbu7a81kTokYmkkdScww=
*/