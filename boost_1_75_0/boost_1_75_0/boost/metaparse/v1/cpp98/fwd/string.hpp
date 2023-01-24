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
VQY1XqGQVi22y6v5h8PiFUAnK3k4AW3IQey77kTJYWLpB37ZQw7F9LDc5fzp31bQ05T6IeSVz+AVXswgiYTDZnloAV+X6VL3WoX7yRUsD6pPr5jvxW9KE01Sh9w2hQ4zWUpTMga+n4KWhNuEU6Vjj4pOt/nRLSzZFTQvEqgwfyvmxD2YXxD9ZXW2tFF6VgCThjolycaFFpw3luzRUU6x3HFY5XtcOi6ubZZn0VrGglvZEms6VeQgMyz01XHs1Qy/yEp2+BNE0TcxVQX62WYGdD76LblvTP7lTjRP9t/JypXunwa/Z89diNE1oFc14zw3Kb1sr5UqtEhtNsFeO84/wGTN3TNnnrc2lttv3oMdNJSlgHjyJ9WYu6QA385Ld0ptMAFSFQVnbvX8MaI0NQVXbT54GqHMSxUzsAzMJJO4o8Ppm5/i8EePF315qfB7G/wmyddPBv3h9vSsvXDXFDDSro6ydsAUlNZ/7sY2wOJRuz4yL+HZccRBDeP4ZDPbbSgdsvdvtA9umOQf0cOZe2xeLOWcCTit/hv0uVPT55kzpmIddrnhjKJk7aWKAFcGotHrIoImJWAUAlWK/Eb+5imEaVJKsdU3oCcha9gl+qamsmoBZ8mfuIVSgd2AjFrn0+tsPgeADMOwWjSsd/ocSfA/21busIg+UG18N6TD0My0Y2ZDWznMiTW1XeIcsb/YyBR5JFHMjZEjM2x8TPIF
*/