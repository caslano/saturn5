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
EbXUwAgLWs5bjqwoUCTAK8JePjRunohVN2gya9MBacuvUvgcyfVl8EoQ472aoVMbth3/DvwPmqZ3H3W3U9tDL2V+S17ZTmQvy/RE5C9aXauRUFMrgT8uLqt4+Cim0MbJB54501eMTPQDTr6QD1CfS5CsHqbPPh7q99Z+IujjperUKBTHgyl4m0KIZv7SUmV432f14Op0XvP7vtQ191912JSggCX5+MIWj1ufUnuG70xSJkveJIhQUBM2dzv6zlZHHJTqHDX4xatCYgkkdetuFrzl7GLf0Zmdy1D3fvE8v+aThEOYk+djM+OkPHqBcpScE53FvLMAzLUVHyinAYQHHB8ytHH8zs+17roZseEdKSfsAmjf7qn22G0UwFFu+4mwHIAuFfyqkiLFXyiKa34po2UDRO3/oPlgOZ4zp1JEWI2TKPVBcKQx9IhJMpq+4+iabw2iYhUP5t4rq83xfOvIm57UZWUqHiukprvzdwtcksqP1ta6rcqPBMjpQ16a5y7CXlb3oD0g6AKbbfQ8u9wCBjd5uLI2/weM7a4EuwZYSBP9QRP8+IS1jT5dHg==
*/