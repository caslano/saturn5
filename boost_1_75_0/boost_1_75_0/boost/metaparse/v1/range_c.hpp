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
Cegv2PGhjIoe7Qa0ZM/rimPQFLWxe8hQjKOhmByQQxFVKO1SjKpyEyA3INMTzH7FiEn89VKxYY2yEBZEaDhkgNcuGya9QJb71XAFaypDtvtHNnRAjILBWTyTKGythcK4H6KjYpmP24hiRZnMGl4mk7Hr2EcLOAmWK2DL7uyFIDg2jmxflChOOgWLAdtfnEXOnxHshROrSNQaYUZxmiO/Ek1f8TvYV+LoK3k30nYZbcXDc1/jVX2CYDtPxcqw7DeXwEcYYjnn7Y2/nRLVJBfMkxMxex7nfwsMzJc4k3NMaG7zDtAKjxp7iRTHqJhA+2Q6XBFVWvyXu4Kjugu5KDKfpoLszAJTYlYK58sTN6eL0MC1hBJYwLSn2E6z+Xi/JX1ta0PKkoJ8tgKGe4WWeDcSbcEKEgg0gXWYn42FvIb6tUfT2d1lsLOXpfMowrGz4M1YmCbvvHRA62FN2QOBDAimW1SZF/UJLnF2PU4OalPUJ0Ts8R5UbtStjT2I2B97Uo5xwlwrBr45J+QbAxvy6AAxsn18AhDfjVZa/yUQOuHrAwO4+VFa6Ih6ySEFLaVfl9DwLSBCmriYDV/V43z4VogSmu4FIcNXDgl6ScTcGiZyV0oSKdTNHlnvZDp7gXvhycKCZpvjySvQLYYCl/ZiMj4DEZXaykTgng3eQM5+H75gPxtGF09NSI6AMM3DmA/I7tgoxDGmojORLOjTdWfp
*/