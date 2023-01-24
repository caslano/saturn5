#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/config.hpp>
#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/mpl/char.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

        #ifdef BOOST_METAPARSE_STRING_CASE
        #  error BOOST_METAPARSE_STRING_CASE is already defined
        #endif
        #define BOOST_METAPARSE_STRING_CASE(z, n, unused) \
          template < \
            BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C) \
          > \
          struct \
            at_c< \
              string< \
                BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C) \
              >, \
              n \
            > : \
            boost::mpl::char_<BOOST_PP_CAT(C, n)> \
          {};
      
        BOOST_PP_REPEAT(
          BOOST_METAPARSE_LIMIT_STRING_SIZE,
          BOOST_METAPARSE_STRING_CASE,
          ~
        )

        #undef BOOST_METAPARSE_STRING_CASE
      }
    }
  }
}

#endif


/* at_c.hpp
x8fEXTQoknDagElX3nyDjuX3hYvZbJBU3hAcJGm7wgdJ97FgzVSrFtjqyDfISqAUD/NP1udMzZzbO2NqJiuwiWtFaGlEZe2F+/che5Sn4N/AzapbAUl8SzTFj8Qp5texrebA2Ny8zHnJGXnYjNQkfxrR0GAJ73zjlCZhFEKq3J/ed1crDaIBGNCXB9ylstTUbxhLcWliCYag1apx+5haNFqqDSRqluuAsZ6TNqlajqLlBk8Mc9/BIBgIygD3WyU5fPemOHxzU7ngOAZE712OSXXGyYq5+T9hQkOUbgIOHZ8uZqwXyik9HjSbpBL80//gBBa40wZP2DLWq6SRrjfJ72JaAyxme6/UhKKiYRfTTqn8NFy+mb0zPhXdD05MHHdTKr6HFgDu71c/kf8fTaDyOkSUh4HJkpduA1myZirqHqOMgKD8+G1YC2X1xpDc1eE1JLAW0O9fo0AYlw6Q2jLGpaLnZnIqSGECX/6VMg55koHFUsWciemYSbv2a+rdaF8M9A8HrOJrBMwd7B+1jkTXca6upmaSr7+DVDLF/MDXmHg4L92KpfmAVmg0ZeSlukcBB4DBMzXVf71C+qi03QpiSb4pCsGuZvx2NYNoqH+8YsutnmeCG2sf0THjygTDFebMtDzcLxNr9Vv0Vl8MCAcTbhLXfc3YqpCBnc/iuvnkzHIH3xrm47wX+GUu8MtCJq94wCbFKALj7ClTGee1
*/