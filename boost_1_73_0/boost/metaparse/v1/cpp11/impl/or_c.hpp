#ifndef BOOST_METAPARSE_V1_CPP11_OR_C_HPP
#define BOOST_METAPARSE_V1_CPP11_OR_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <bool... Bs>
        struct or_c;

        template <>
        struct or_c<> : boost::mpl::false_ {};

        template <bool... Bs>
        struct or_c<true, Bs...> : boost::mpl::true_ {};

        template <bool... Bs>
        struct or_c<false, Bs...> : or_c<Bs...> {};
      }
    }
  }
}

#endif


/* or_c.hpp
ORmpuemhDecSn8WX3M+icV+HvC6Yb+zxZlJbsH4M+sgjUVkMEwV5UP/Hojyw3NK31xdfB+MS10Hat5TOxDYE+4aFPCfqiIfFO6bNj6cnyodS9HGx5TRZvv0vNW98bry90BbCvjLa2HHpW9mnNxp3W7XCfbA061QlvO//KazT5yGPh/4UX6ewfX7ROm09n+PrEz9+4sfdu3sZl1PsfZT38cXbbp4vNhSk2zRF2yIztzDppWiP
*/