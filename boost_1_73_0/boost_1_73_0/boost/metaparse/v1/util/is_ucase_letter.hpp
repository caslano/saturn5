#ifndef BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP

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
        struct is_ucase_letter : in_range_c<char, 'A', 'Z'>::apply<C> {};

        template <>
        struct is_ucase_letter<boost::mpl::na>
        {
          typedef is_ucase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_ucase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_ucase_letter.hpp
0BGLIfUvStVA6hdKbUVP7ZBtRfFc4IjUKJ5xIOconmegRVF43p3aEcW/1gG1j+JZAvKL4jdCQ50h1ZFSONxP4fyC/J5WyC+I/UD5BfnddpAfpLpyfkF+nzDkF+Q3ATtiI6QWcU2D/DZuKANSvSl1AFKPsoYg1Y/LjeYZEXQFqScolQypAVwXSA2iVAaknqJUFqTO5/pBKo9S+ZBaQqkCSA3lOkNqGKVKo/lNto6ohNTFlJoPqQ8otSCa34MKLYI=
*/