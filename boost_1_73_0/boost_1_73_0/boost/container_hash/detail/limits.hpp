
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// On some platforms std::limits gives incorrect values for long double.
// This tries to work around them.

#if !defined(BOOST_FUNCTIONAL_HASH_DETAIL_LIMITS_HEADER)
#define BOOST_FUNCTIONAL_HASH_DETAIL_LIMITS_HEADER

#include <boost/config.hpp>
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/limits.hpp>

// On OpenBSD, numeric_limits is not reliable for long doubles, but
// the macros defined in <float.h> are and support long double when STLport
// doesn't.

#if defined(__OpenBSD__) || defined(_STLP_NO_LONG_DOUBLE)
#include <float.h>
#endif

namespace boost
{
    namespace hash_detail
    {
        template <class T>
        struct limits : std::numeric_limits<T> {};

#if defined(__OpenBSD__) || defined(_STLP_NO_LONG_DOUBLE)
        template <>
        struct limits<long double>
             : std::numeric_limits<long double>
        {
            static long double epsilon() {
                return LDBL_EPSILON;
            }

            static long double (max)() {
                return LDBL_MAX;
            }

            static long double (min)() {
                return LDBL_MIN;
            }

            BOOST_STATIC_CONSTANT(int, digits = LDBL_MANT_DIG);
            BOOST_STATIC_CONSTANT(int, max_exponent = LDBL_MAX_EXP);
            BOOST_STATIC_CONSTANT(int, min_exponent = LDBL_MIN_EXP);
#if defined(_STLP_NO_LONG_DOUBLE)
            BOOST_STATIC_CONSTANT(int, radix = FLT_RADIX);
#endif
        };
#endif // __OpenBSD__
    }
}

#endif

/* limits.hpp
NcmpxCEXNw5YBie1ZAlhWMzerVnELnGi5v57Zxeo4+Tay4cjcoDdmffevpldrGUH+t/tMiwFB9+8Qv0L8cJ7mzQt+ScSy68nhOET1H+YuMT7G6gGsMt6Cnvwpqwn6OqssOE6Vc9h+Aa6pRKp/g1U8jJUjzhSZzb5I148lnSdSeiOejB8//43OIB3h8NjEy6inBIGviT5ipRrE04TPfJHFj08WIJ8MIFIiJi1BxhkVIDgqdxGJQF8ZjQmuSAJRAISIuKSrvCF5iAzAillBEbedDF2P5qwzWicNTiPvAKR8YolkEX3BEoSE3pfwxRRKYGniID4CRUSMStJeW4hPQFJyo1oYJSIiAkO0X1EWbRCukhCJmUhfh8M4qpkuJJBwmMxiFsrrExuXqxqgWo20SPwQoLkUAligoo3YcMTmqo7WoSDRbViVGTmThYS5smAlyAIYw0cplIi6iUQ8Bu3TBUJBaqnUt0Ez4Vi22Z8sxeItjZAaVXmSIe2YFzC0XgTqjwhpY7XRrQsjcva8m+UbKc9AZ6jKujYPoz9DqwiQYUJd+PgypsHcGfPZrYbLMC7BNtdNHjXY/cCe4MiawnkoSiJQBUl0E3BKEn2yL/rTjes4ApG89nkxpsGYTC+cWYXdmDDEXSGx/BnlavO/qUD
*/