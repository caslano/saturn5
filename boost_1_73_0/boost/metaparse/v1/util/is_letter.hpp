#ifndef BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_ucase_letter.hpp>
#include <boost/metaparse/v1/util/is_lcase_letter.hpp>

#include <boost/mpl/bool.hpp>
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
        struct is_letter :
          boost::mpl::bool_<
            is_lcase_letter<C>::type::value || is_ucase_letter<C>::type::value
          >
        {};

        template <>
        struct is_letter<boost::mpl::na>
        {
          typedef is_letter type;
          
          template <class C = boost::mpl::na>
          struct apply : is_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_letter.hpp
MrpQriuYFb/FIngTu+MdDMC7aLtvJO++4s8O7ht9JdeZJ7EqnkZ/PItT8DxWY7qLOBJTcRJ+h7PxNi7CO/gu3sNV+AOuwR9xEz7ALfgTpu9f5R3O1Q72r/lysz4xP5bAAlgWPbAKFsLu6InhWBTfwBKYhKVwPpZB2/5N3gHFsk/v33juiXrFGMyLsVgULaieJyfJ9LznaTxP5nk0youjsATOwb/hXKyM89EXF2FrfBfb4xLs
*/