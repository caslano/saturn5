#ifndef BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

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
        struct is_ucase_letter : in_range_c<char, 'A', 'Z'>::apply<C> {};

        template <>
        struct is_ucase_letter<boost::mpl::na>
        {
          typedef is_ucase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_ucase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_ucase_letter.hpp
iMPVE5RgeStzEI54mTyHI5BSJN3ivfyxDEBY043qNb1Qtz4mF/mL2mRvleoaBcWvTRQmwRP4RJWhmBIhQVlPyhwzu3iPwXypiDyKv0VPesRCjtHM861OKCGly2zYEzBLI2FoMuGlUgCekAdHRXSzAyTgL/BTk9q/fTbRTYNGiU4sGLBS6uff6ZRKgTR9vj8FJ7IBWxrrTxJP1BLcUzlT3M2xcpXhcn5iAcepSsRP94pF+r2odTp7O7h7/p5OPZyyT1GDQCTQ4gQYPqoKOSZBfkwlwsTY4wmQR+neDN9JQ8R7uZQCzO5qa4SpuJf2Emcp3z7zfujRl3hmFtgeGo03Hj56yCqTuvDcKdctETZIcsnfTVS4hXIz5NqnuXfITi2PKscpXOhZlCwqRk0ued0JMcxxeOg3s9bAuhkHKwbp2EuwFlA9A7WgXJUjUvCEdxUlt89euDj67uxX5niCSce+9NC86Pt7aes9aPQxb1GPlMFtN5LsMbABNKxI31zH7MO0Fimen99uGDmaHGbXONVQExW/SPJqIn/XYyun8M5Pz89+V1xeQWQ4qPPIOQ==
*/