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
HV+njj+s4iXKv14df0TFj6p4luIfU8f7quOb1PEnVPyUip9R8WYVP6fi0ep6L6jj56vjL6rj16rj29Tx7Soer/znqvgl5a9Qx2er+JDyr1bHX1bHd6l4t4qnKH6POv6Ziusq/yvq+DJ1fLluP1T8puI/UfERFR9V8UEVp6nzv6uOd1THx6o4U8XjVPy+Ot8kdXyqig8of311vIGK71TxHBV/rM6Xr47PVfE8Fc9X8RAVp6u4s4oTo2R8KlLdjzo=
*/