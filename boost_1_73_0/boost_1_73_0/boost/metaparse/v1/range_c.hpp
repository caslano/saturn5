#ifndef BOOST_METAPARSE_V1_RANGE_C_HPP
#define BOOST_METAPARSE_V1_RANGE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/util/in_range_c.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char From, char To>
      struct range_c :
        accept_when<
          one_char,
          util::in_range_c<char, From, To>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* range_c.hpp
ydkRYcZRtKEimnVXqG0kGl22R92UZZT0Bj3iUG23vMqmLLyE4NssR8MAwobyIdAxr7kxu+zAT7iCUm0omE16o6FHJMDjy/lyNVuMjx2hi/n7VeS+EkUPSGnuCybGJsEXAYIp8+zRz6kPO4SmLhXPWiHcCuTEmFBVBqWskLmDqNGILFeN9owXFLjZrlGDyr2VcVoTnluR9/1C9HxELfN9C8RzS/bO1QtXcANrJNYDUygbsPTG21KAWiurhCqnzPWJrwvup4PmRBk7hkfld9gHJ9n5hqDH4Ok//njxfjmbv+uwcyGwptfPomffmb5fQnKLQmn5ye+Zh03h1GvZ9kLSovip3XECjZaTwIN7H1OrypBNJpLRcDh6ng1x1D9L1v3Bc8Q8ORuIHu+L7DT4/ZJHww67uKXuJgPaqiGJTRPRoGPiLzXHQdQ0elA6OvwtfwZQSwMECgAAAAgALWdKUrt7WC8jBAAAYgsAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjg2VVQFAAG2SCRg3Vb/T9tGFP/dUv6HNxNEAjgXQ0A0OKkQpWuktiCSgbRCp4t9jm/Yd+buTBYq/ve9sxPcqZSpW6dpixLn7Hvvk8/nfbsEhmkTUs2GTsBFLPHrhi3mUkV6
*/