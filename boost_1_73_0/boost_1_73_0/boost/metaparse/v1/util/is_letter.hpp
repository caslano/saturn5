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
ucGA31Swv2Ib4XvUSPkgP1oc7VN/Pf5/uR77fxz/314/Wvn1Op3jeD32v8T/X7+e6vEPx3o9/ah478j1Xv9t8UerX/pR8nfxEfh7UaA2F8C/L1NqKfz7KqXWCX6XmiNq4d9VlDoM/75BqXjogrcohe+DW0epbEhtoFS+4+YyynFzKXXcXCKOm8t8lcsilctSh98tBjWA1HauAaR2cg0gtYtrAI34imsQ4K1gqAGk6ihVEOA3l0O5AQ6aobQAv3U=
*/