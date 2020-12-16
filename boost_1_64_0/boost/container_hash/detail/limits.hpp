
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
lqYy20XkdjN7B64Hfa3MDbWnM9VPRDO76114SQ9T+u1K/7B7S73Mm9Ymp5GXtlt30Q0OVk5z73R2vplM1ubebPJYl2Z5c295/nzJnHDu3c4eUPoWul4zk4Dbu90ya26Kdq6kfPm6tO3BPcp0by3sqS3InV5hMqP8j3fTVaJf9K6t2rl3mpb3Lo1UnulyTrq5uaplXG1FE2c3d9U8LUUvpwazK3Z6o6d73WgYBaQJ3daaG9fzbV4gO73zDUDwFHHXGeBihyHSIWi8GPZDuO+KcQvlnx1gBwYDxTiEG6H22LV3rrG/zYOvOELQNWHqvEWFixNqh7qmmTDSnmfk5OCTwymEun8amcOsx5PlzqMbg2Qxoy0AYq1LhvG3NoHymwd7V8ymhNVSR0gW1jNaXYn7gxsh18ER5CeQyH/5BuQaOCzwAFG+xybUrBaee9jLzQSClXgmjIzGfFfP54zhhOvQiUCw70pG9BipQwNHuppQNeyQZYQIB04jxJx+Tign2hZMsUQOq19MTgFBleYi0cFO6QKgowpsQRQRBwcOj4AK7W6/mqtzb+dvKmmf5UMECx/k/ISnrIEhvCsOTOep9Zl90KJ++XAz8slObf24SXzIgprE7QNRPL5i4BB2I9I/4+us7/yj60yymFFncxqAjBqPLoxkMaMw3QI1HxkZyYVm9szCKiDljEbDbe3sgwgjN2FQpbYRcbD38YEhAnEZ09PzWc/OZz07Oa1+YmIZTI+Viw28BD3CK8hwYC7uOtBCBCD83+xT1Kn0JQpdHjEYnD0rPBgY9bh9pt2e2mMaQXTloPsRvuhFEKz3F1Q6gkdSwupu0AThnJmOmLRVeNc3UIxXzwiVP87JqvwR03CZUEy4R03PhFW09MyWVwHK6i5KkQk9O9+1ehFrrUAwgUelB+r1zpvovHSlKFMXby2k4uoaVgGKeS7eeRfMMwCYGtk58mbWHNApRBWu7YPwIDowhHvPgSG8dQ4MERTQGEKLPKnRaZQ+1ApxwqD9ICG4pU4gKIfDA5I36LiUkBYO3hoJRLh9OXm4Gp09hkx2Nyv470x15TDy0JsPaab3pEwb/iU1eYkuVyPCxC4aELxbRwQyrTtHHre0iRlQi5vIEG5lIkHMgpFgguIlxHWw04gB2d48EjwnmOk2IpQpabAeWXZ1QUwbI8RsPDr3tl7MQV9ECPO+zi30YoJFRYSJ5hsRriiGEJNmJIjpTw1c7YPYRQ4MsUobmAcOFykLbsBIFDMAKCMtWb8fWJaYA1wU84IWPvGyJOg9Kt79QEHOuC4hYuU9MkUDm1SNUN7DvvQHiBk/A6SWvgK+Dq48pl7r3rxpvHdh2rJ7c8G93GAPQ8S7mkB+laNr3AnVvs+0iAFCV+AT6NDm6DJ0QtWz6mJXwUveCYWP9hOIsB6cUEXpZrQLB0f2HiFmGTNSbGdMlEfnmBEiQvfKsmTZnnbrGi6QAHJlz/IjKqSKCCM+jgizm4sI4xxwRFAryEQ08HIxEsyYHwhGnSUixBweCeLMVc9zVflAvtG9W7JhZKRTI+M7NEh3YhiZ1sAQJ0EDQ1T0yDiqpvWD6PyXxqyPWZdd5gKvzSYg845G6gGKnv9gPCzfD83GTADxk+GGie3VZHjwpIaZZ5ts3bSwTEFSV7BWZrBF1xBOuDF6YGTLSiOORjZzbPE7GqHKojMjHFRUUxcrdCGrqd0ebUR1+SDVk7rEFU7UB4h9EKKVgSGEOOKjRK8ZBPVgb+tFZWIEk8nozgJdxiQiU8+KaNcWRxt6EbOl+gxaVoyUKBBUrPOAEHKlCDDyroAQkqjgZgV3AhrTB9HlY/pg9C0D90P1XUP52Vag1ed/nFRsyIKSio0=
*/