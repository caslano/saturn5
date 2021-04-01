#ifndef BOOST_METAPARSE_V1_UTIL_IS_LCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LCASE_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_lcase_letter : in_range_c<char, 'a', 'z'>::apply<C> {};

        template <>
        struct is_lcase_letter<boost::mpl::na>
        {
          typedef is_lcase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_lcase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_lcase_letter.hpp
neu3/eD2xfQJyDeMukZM9Q+Z8qD+wL9W2kHycqlHb1RQ/bL+fdgnC/SMvd4OOmokifAEZA1gwrvesPbL/ZWNrU2JVrcYVpEGim/GGBUsyN8etqfke8lz1sGw4bSLLnUWrp7SeoC4/HaBCV/ROTvx/d3dcndK2XIW5yNJzgXUtr8N0VsFpn1t1+WLsxGtmT6yGG30EWeWUNa8Wui4Lx6oE7jvTuCOMhd6yDaaBsRsrQvQuQn+OBmom1KyuiB5Q2ZxlPbw0IMA9zH3Tc8wk7nPghUVn0OcFY0/xOuo/eX5uk4U2+RlTZhaZIJV2hGO6nNfbYSv2ieN3I4hNaK53qIxTCGqtKVkuQsA+ig0rh6vYtiVi0/vrf7bEUjVaflBxj/JMRFPJ6qMsSuzbWynmwkAcWrXEfYPAmDRKlfYXHEvGYEw06xOvjCSb8WE8hHOpbSZDvETZL5mFcO09FI1qApgj/5Lv2ETlUe2uepFJ40b9DB5E0K4FliFT/Nz7cZpZdB4nUH3KTG1rEQf7gLVfaAoRiFpBSJ/nBUi/DHGQw0ot1jA9VfvsJj5ounNPA==
*/