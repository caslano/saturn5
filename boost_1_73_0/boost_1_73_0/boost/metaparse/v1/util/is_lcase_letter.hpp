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
BvvldCmmJZ9kJB9tWpYkAVPlF0K4VwjiXiEMq1Fecb9QBpaeCovpV8bQ+gOCP0FJ4yXFESFGxIoIf3XFArQEVZ9sbyJo/IsfR3133G9WBvzB7fcWnDzJ5EdrvvUx+G7FvHxdBcFvNpT8+Ab4sSa/iag/n9gG5H2fKPur4/ke8HyP8nw/8ov9/WfP9xbyT+ufPye4fE/tsBF4ylL3J3+aufK2GklJnEW2xe+g+HYnxor6FRLXAB/foN6cUpZ61Qc=
*/