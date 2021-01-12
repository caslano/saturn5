#ifndef BOOST_METAPARSE_V1_CPP98_FWD_STRING_HPP
#define BOOST_METAPARSE_V1_CPP98_FWD_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_string_size.hpp>
#include <boost/metaparse/v1/impl/no_char.hpp>

#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_STRING_SIZE,
          int C,
          BOOST_NO_CHAR
        )
      >
      struct string;
    }
  }
}

#endif


/* string.hpp
utX8TWSIGWKRWCE2ifoa2+kqMsRUMVdM2dW++o7jUmSIKWK2eMzflot1olx1yxRtRHcxSOSI88VcsUgsF9Vtl9U3lZNRhX1gruspb5Y6R/aVP+/9Om0x5IgD34u3ybDRch+6Nt7eQkYp21z4tfqI/Fe2udC3Ren6gNxWmwtrS2h3oXNZ2wtln//yzz+1/X9FM3Kyx4z8NdoAiNra13++T2Gf4DVZgyMKylKtTWgDICde0KSo
*/