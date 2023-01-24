
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
Mra3t+cUQFQOU17DLID2OtBQ7Hu5DhF+AFFKya//718bfPa3H/57SysbJ8dc59qZT8LqLlnWIzOKVBskFdI0o5fkSGWRUYpWioRAAO1VFq90SMRRcH2isGVKpjPKosvmUhfjqpBWLGt0Jj9Cp38dY0Z4SVAqQWEQGWIRNB1SlbFb9XnBbzJKCkg1lRXGo32SokOSdyi4yG2F5akJjPdLeqlmlBhclAmvQvcfJFTbOuuQMmRnKhXy/NEeZWvrrWriJ6ABwmZvd6uRaOYDAm/5wBGeBxSiKL3FVpa1Yx2e+fyEvHOaox++wJFsi52LHb72OY+7sMSf/9eeO35sj/f+nOeFL2Z8+8kx2WqKvwjro2eZJidxNo5G59W4A8y7DRJcFvGBC6itYz0gxLk6YrIo7LV1bBNwbYjf2kltXXDg/e2DpHk470rEe9vc4Nl5wmEzl6N+VbeQSQ3/68rHevyZc5DqKSaBanxwGlDtDrxCJ6Ahr7EKsF6vKwUAAc40ikCE3ckIgC98+slfqSbqx80Rxc3b/pzhibPkA4NWjrTXp5/16BYJqVNYW5IbwaYJqTi8cew4QbSmZ1KM1mSpQRvNYODxUjFR+/Q6N5jurpJm1zB6ifFknU6mMdllQmqEQ8RixJNqHVh2FMuJ4T5f8YxPoZMH29JfAwX7eyVnsgnHO1N+QgvP7nkey4+SLHdJbRg4blS0RaKwlQv5ALVL
*/