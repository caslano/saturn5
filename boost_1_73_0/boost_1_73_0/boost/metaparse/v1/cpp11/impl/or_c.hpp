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
LE1HDGW1FTmX7/jtiz9F1nYdMZTVyVjlXcr/3Hb2Kci6UUcMZXWJrpP/9ePS3dcjOmIoq5exyhnA/d4nBsja10AMZc0S1tyay3Yi61MGYijrOEXuX9cevSyWYsNADGX1M1Y5ET3zyB9Je+XFBmIoa0BsuPX435yMrIcNxFBWSmLj+jtPlGrUywZiKGuYscr7jd/f+aJ0t7zSRAxlbc1YHyhwc4+eL919rTURQ1nbFDm/TqudKN1vnGkihrLmMlY=
*/