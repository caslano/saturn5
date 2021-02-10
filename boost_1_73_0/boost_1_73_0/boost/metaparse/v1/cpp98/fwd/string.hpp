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
6ai/45BOUhV1V2LY00w4HzzOV/nTIhk4gov5Mufx1dWNI0gcIsI9wrnpnIbgx/OGrVwfwK+ZWFtsvXBuR6ASBt4RFYSm0jZk6d7nEkTTaqsLXWfMSdG3Oi1lwB61sQn8wyhgryRmdLeh5rRUXVvzwdv9cvU0fwnYXVFgQ+5LfukWKuXnFjQvWWMMTsBJSCr5fnT109b58Clv/CWv1/6Y/d99ND3xsSPOP5Xl5z/HX1BLAwQKAAAACAAtZ0pSZU3v2oYCAABIBQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMzZVVAUAAbZIJGDdVNtu4jAQfbfEP4yoeKmghtKt1DREqqBqq+0WBGn3cWWSgVgNdmQ7dPn7HTvcpN0v2JcQz4zPOXNmQuzQukxYTFgs1UrTzyfuvrTJbcKe03QWHvD0mLKYnzIxb4rZBYsNVuWOQrlwApTOCsw+R+0d2naDwAdXA7ju92H6vcUmwmEEaY1d6N/Bm95SZtCHwU10cxdRzdOPtMUWaLZoIvDaejYc+Ep8YouNtXKoXO8V1doVEdyGkMLMSa0iyEptz6rSXYUe5bfjhduUp8RE2kpb2VxayRKV2ODIPwbD4e09ZIUwFt1oVSu1uwdd+cqRdUaoNeG32OB6
*/