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
Np/8GcOu0igIZ2/783yyiKj+p5QsCSjQiRzHLzv4QjXBdRfT34t56jAG9PvdDjTXKvxXeG3XANETjsYH2P4QW4bnHs7hGX9YteEF/gCtgK+a+HtaY5qAk+OS+OnGyWe5oiVaIjYY9OBCgrASz6Qsa6hNBaUpS5mhcF8hwaCLDgX2WgbMqaKoATXijEb03QeIeQzKQVpZiycPmbIy9cbWhHaBjmanbFelqXQur4ojquwjjDWqgqZiKpxTNxJ+mExCy3mrqII263e7MIGNyUhI4VRROFTGrcDQDFl6A+h1I9bDVF+VFrbRW2q0xjJwkCA3FsIAtNrQ6nXhskYJtkMF7+GUptVboV2O+sRCUVheRs3x9mnoqZhm4/jf1v/rXrbaR29bS7y1+Zv73uPuNd7c9x85fTD2mLaqGeypxvkMx72RzTb9gPz402jw5w/jP1BLAwQKAAAACAAtZ0pS0ImTungBAABzAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzOFVUBQABtkgkYEWSYUvDMBCGvwf6H46JHzWKCCKhKFpxIK6uVdFvWXO1wTQZSeacv95rWjaa0ssl977PJRURQ2xkwJwJbVtHn2/cbZ1XIWcPdcmWRb1kgh+Sgo/7jqBC/4P+
*/