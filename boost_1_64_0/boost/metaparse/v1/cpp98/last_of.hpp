#ifndef BOOST_METAPARSE_V1_CPP98_LAST_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_LAST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/nth_of_c.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct last_of;

      #ifdef BOOST_METAPARSE_LAST_OF_N
      #  error BOOST_METAPARSE_LAST_OF_N already defined
      #endif
      #define BOOST_METAPARSE_LAST_OF_N(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, class P)> \
        struct last_of< \
          BOOST_PP_ENUM_PARAMS(n, P) \
          BOOST_PP_COMMA_IF(n) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, n), \
            boost::mpl::na BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : \
          impl::BOOST_PP_CAT(nth_of_c, n)< \
            n - 1 BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, P) \
          > \
        {};
      
      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_LAST_OF_N,
        ~
      )
      
      #undef BOOST_METAPARSE_LAST_OF_N
    }
  }
}

#endif


/* last_of.hpp
zSfT+Cmd1XhJKNwEORU1r6yGNxwTNQB14CqcW4GEYpqNqsK/Krr7dVwmFNS0jb3S36mE22mMssyhudZpiiuwQgS7RhyDCxa0EbNXj/IPqgbNJ2WfcrkANG4WYMYd+TPnxYz6G/VSBeMOirHbmPRDdM3Z1znu3cfWe7yuED0CV3BcreC3gYLc5tOvTH60SJT2DfplkX+Jm2KmK94XFumbB9fcEo+EY3ke3pKD/VHYI0h07SGiby2PRI8Kum00EkZC6V6T2EhC6/MkHWLMLqY0S/fr6U2UUgicU7Je7yPNLjFZpjaUDuR1v4itsAk5UebdlrT9mhzUKZVGvHijt8dt3sVzNqQUbhYvgbM31/ZVJfOBjvkPWWxjRXml1Gp7i/1xPSKzyjevE4BPGW7yrbnXHOa7m5JksyYqI/S01DDlQmJbNKN3f3ryKjTnPvFwJFstBSsU5vKI/8MXmANnR3B9JgZ+pnrUiOLeK2wxmpVyT1M48djstUzcjpSSUyjt4WZavznxKAlfwBh2qb+E7Mtk6Ky8LYp/xA8bwkIIZu4V32SKBTJIllW/f/9Cfw==
*/