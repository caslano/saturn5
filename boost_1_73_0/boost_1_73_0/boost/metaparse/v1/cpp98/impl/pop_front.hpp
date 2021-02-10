#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_FRONT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_front;

        #ifdef BOOST_METAPARSE_POP_FRONT
        #  error BOOST_METAPARSE_POP_FRONT already defined
        #endif
        #define BOOST_METAPARSE_POP_FRONT(z, n, unused) \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) BOOST_PP_CAT(C, n)

        template < \
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C) \
        >
        struct
          pop_front<
            string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>
          > :
          string<
            BOOST_PP_REPEAT_FROM_TO(
              1,
              BOOST_METAPARSE_LIMIT_STRING_SIZE,
              BOOST_METAPARSE_POP_FRONT,
              ~
            ),
            BOOST_NO_CHAR
          >
        {};

        #undef BOOST_METAPARSE_POP_FRONT
      }
    }
  }
}

#endif


/* pop_front.hpp
1ihs2yBYDaKq9B5a49YGLRSyISbdHHyAFujukVg0B93aurUgVZ8uSLXxinevy+c/2f0qmz0tYScaKd4rojhaUMW9JQGfI0lXmZSV1tZ0ctomSmwx/ewb7KUtnW8k/ZLs4VSgmTS1NtIVrw/RDNbSmfJOgPQpaZeyS7Zpb/F7xiu98YbdeZLr7VaoAnTtlKah0lH3yD6tpMqrtsCw44w57z3OV9nTIu45wsV8mfHheDJyeA5yBiTOSxSFcWGyOaq7bp2a4tv1ho1cH8CPnVhbbHwh3cxAKQy8IyoITaltyJKdzyWJutFW57pKmStN53wa0oA9amNj+A8wYK9U3Oh2Q+Y0ZG1T8d7b/XL1NH8J2G2eY03ha37tBizhZwvqHxV0CK6e09C9y/l95Z+F5z2Bjy7APxvyFek77tGJe3zBbWxBo3gE7/LGLo9/TgQ//wP+A1BLAwQKAAAACAAtZ0pSDd1gXDUCAADcBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzNDNVVAUAAbZIJGDNlM1u4jAQx++W8g6jVFwqsiaUXalRiFRB1VbbLQjS7nHlJgOxCHYUO3R5+x07pVTaF+gFPB/+z88zA6lFYwthMGOpVBtNXzs8vum2NBm7z/Ol/4C7
*/