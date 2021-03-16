#ifndef BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP
#define BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of.hpp>
#include <boost/metaparse/v1/transform_error_message.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>

#include <boost/metaparse/v1/error/unpaired.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P1, class P2, class P3>
      struct middle_of
      {
        typedef middle_of type;

        template <class S, class Pos>
        struct apply :
          nth_of_c<
            1,
            P1,
            P2,
            transform_error_message<
              P3,
              error::unpaired<
                get_line<Pos>::type::value,
                get_col<Pos>::type::value
              >
            >
          >::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* middle_of.hpp
Ej6brbX2qDeztMOn8NPzPfB0oGaE8JO/pUXubN7SRJUn5NlVgVL7Yzs7YXRDQayBUD/sCK2wiErD62oFUZpF3UtWePmm0LZP2cXhQhOMtwyVhR8LcYtP5A8vnVBXWCJpKFNvCQYxb+zoitY32iaQNyBg9HoEO3U+iws3q9Hq1iu8uXP4ps6G2Usb7DkhN+hwK4Qz0z3M0VD1wh6vooTsVCD3LG6XTdH83PCynfe+2LF8uBk4C4spCba6McbZTxU=
*/