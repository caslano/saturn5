#ifndef BOOST_METAPARSE_V1_GET_REMAINING_HPP
#define BOOST_METAPARSE_V1_GET_REMAINING_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_remaining_impl;

      template <class T>
      struct get_remaining : get_remaining_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_remaining.hpp
WeQYL1gWBT7T/DbvZTn4Y4XAT3I/0+YV3E+E+/AaRX67v9ZeDxZs6y5Jwx2D4V/b58fbLXkbqBhr/9yOCdxvPsyDYdLTgvZKie1nKkb3YAftkj2474CMjHA5r/O3YDkHfRbEPzuC4wW5Pe3Tgn4Tom1qz58pee2/b1Dn9knt37RUfgPuFkcFbtT+mcYP2j//QzRo/8p78Wyd/vMLtnfPpOEu8/+59v/V9T9o82CNDp73G7Vt
*/