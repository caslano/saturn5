#ifndef BOOST_METAPARSE_V1_ALWAYS_C_HPP
#define BOOST_METAPARSE_V1_ALWAYS_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/always.hpp>
#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C, class Result>
      struct always_c : always<lit_c<C>, Result> {};
    }
  }
}

#endif


/* always_c.hpp
VAUAAbZIJGC9U1Fv2jAQfrfEfzh14qVacJMybTMGCbGqVN0GKlnf3eQgFokdxQcl/35OQgtT1T7uJRfn7r6778tnSegoUQ4nTGqztj5ssX62VeombB7Hy/YBtzdx91JW9lCzxNqtRneMUCrKmOSnRsmPWBWWee1jqkh1eDwchBBdXcHinv1QhALiHX6G6AussGwSIYTfxfVXMRzC7a+YrZCCWTtGtHPCcWUtjSC1hdJmPMCDKsocB2u1xVFbMeajN13ROMXSN3/cl9kNjtjMGkJDwU80G8oEXA8ZizPtwGG1xwqcqh2cMYdGQk+54yj5kTP7BLNcN0BOp8hk0h58QQczYRlR6ctfjiCNKrAT6R/4QlGS+TTv8iATWxTKpB2C4PycSsuBh1H0Dd7L+jwET2CswYN2pM0GggP054tVfLcU/Wb+cvEQ+9VeB8k1KtpV6H9tZwDJT1983ZGap/yIlV7X0GgBak1eLsqwVQgy5eAJ0cCFyyxdMLlvaz2AxySb2HzCvM/e3btj9eKhHptbRwLOy3rsj1czmG78NgKSXZXz/uPNw+pu8bvHpkniLSDgkl/22LJh4R1iDCakrRFwj1gG01zvPUrvwz0a/f7HFm9d32wm+UktyV8l5Kd7/BdQSwMECgAAAAgALWdK
*/