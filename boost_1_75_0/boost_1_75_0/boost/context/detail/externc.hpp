
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>

#if defined(BOOST_USE_ASAN)
extern "C" {
void __sanitizer_start_switch_fiber( void **, const void *, size_t);
void __sanitizer_finish_switch_fiber( void *, const void **, size_t *);
}
#endif

#if defined(BOOST_USE_SEGMENTED_STACKS)
extern "C" {
void __splitstack_getcontext( void * [BOOST_CONTEXT_SEGMENTS]);
void __splitstack_setcontext( void * [BOOST_CONTEXT_SEGMENTS]);
}
#endif

/* externc.hpp
2BQlWDXnD3EVGu6i3Q+HZQvGlQhg6z2joQQMxphIeQSzP6p3CZDnuYt9AHw8xoROc+D1W77gz7FuCwDQPRsbXXRAAAiQmWxpR1Uv0PMB7rGHOPWTOVX/Jm+svcbexrfRmcbcgGG2Qf3qfeT5gPmsBJHFQhkwpWXvYMZwPMLOf4i9i4q7PvTPUZPPsv3CTzObvwMRZ8Z5CEIpffA9VTgOKSU+lt/JqHGEjP5dTA4Kgk/U/uFFk28SzcAwHdQ1jT5d0vhWNLkCzoZefcI5MGFSjowCm8qCfeIAYkEPycxPXEJMKDImWhIx1OhjgU1KTPLNs4NqyM0bivxUSS4Nk/ku9awE4yhrS2VsyGcvHbN4QyPDOLbaWhalg9qRWbAGShvSrK++cY0v/PH/S5ZpijzjvlM9PvzeowwGaxS9k2xsnWA+X/DcK/s88+weX/7aFV54ec72jZLFdA0jxjAYoXsnULqHUAq8gXoX7CS6ETME1TKnEAFhyZ8nyaikzRVIyjxFJCLQNzdEBxTa/9Leq99tRVK6NnDsSA+lIu/U3vCiEwnwAAcHB0IIkaIA8YC5BFz77l/43ddtAQAK4V1E3q4vFpZvWOG6rKiLjPzaJrv/+D2A5Oh7z+He8wVm2YLBWFLsnsRf2cRrQzW36EKBDf6otx5feiZ7C0ZjmN64kxe//GMMj9xA1BVSOAZK4EuBQeAU9AZBvqrKIRQhDu7C
*/