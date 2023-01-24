//
//  boost/assert.hpp - BOOST_ASSERT(expr)
//                     BOOST_ASSERT_MSG(expr, msg)
//                     BOOST_VERIFY(expr)
//                     BOOST_VERIFY_MSG(expr, msg)
//                     BOOST_ASSERT_IS_VOID
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2007, 2014 Peter Dimov
//  Copyright (c) Beman Dawes 2011
//  Copyright (c) 2015 Ion Gaztanaga
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  Note: There are no include guards. This is intentional.
//
//  See http://www.boost.org/libs/assert/assert.html for documentation.
//

//
// Stop inspect complaining about use of 'assert':
//
// boostinspect:naassert_macro
//

//
// BOOST_ASSERT, BOOST_ASSERT_MSG, BOOST_ASSERT_IS_VOID
//

#undef BOOST_ASSERT
#undef BOOST_ASSERT_MSG
#undef BOOST_ASSERT_IS_VOID

#if defined(BOOST_DISABLE_ASSERTS) || ( defined(BOOST_ENABLE_ASSERT_DEBUG_HANDLER) && defined(NDEBUG) )

# define BOOST_ASSERT(expr) ((void)0)
# define BOOST_ASSERT_MSG(expr, msg) ((void)0)
# define BOOST_ASSERT_IS_VOID

#elif defined(BOOST_ENABLE_ASSERT_HANDLER) || ( defined(BOOST_ENABLE_ASSERT_DEBUG_HANDLER) && !defined(NDEBUG) )

#include <boost/config.hpp> // for BOOST_LIKELY
#include <boost/current_function.hpp>

namespace boost
{
    void assertion_failed(char const * expr, char const * function, char const * file, long line); // user defined
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line); // user defined
} // namespace boost

#define BOOST_ASSERT(expr) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::assertion_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define BOOST_ASSERT_MSG(expr, msg) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::assertion_failed_msg(#expr, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

# include <assert.h> // .h to support old libraries w/o <cassert> - effect is the same

# define BOOST_ASSERT(expr) assert(expr)
# define BOOST_ASSERT_MSG(expr, msg) assert((expr)&&(msg))
#if defined(NDEBUG)
# define BOOST_ASSERT_IS_VOID
#endif

#endif

//
// BOOST_VERIFY, BOOST_VERIFY_MSG
//

#undef BOOST_VERIFY
#undef BOOST_VERIFY_MSG

#if defined(BOOST_DISABLE_ASSERTS) || ( !defined(BOOST_ENABLE_ASSERT_HANDLER) && defined(NDEBUG) )

# define BOOST_VERIFY(expr) ((void)(expr))
# define BOOST_VERIFY_MSG(expr, msg) ((void)(expr))

#else

# define BOOST_VERIFY(expr) BOOST_ASSERT(expr)
# define BOOST_VERIFY_MSG(expr, msg) BOOST_ASSERT_MSG(expr,msg)

#endif

/* assert.hpp
YKe1q4K9QNxmfAKeh4VruIT7ddm3fXhA1jhHUwuzY44RN/wWHVwaU5bD4NcXj+GNYUL5fTlX5XF8K57B8X52pdMHdA4TpOSdIZGXCjxW8HMeHivcSX8yhYvhvh6/o+Hx+umQF9Hy2dD4ntRa6tPaHxwm51n5XkTfCo1b3hIrwUzfZjAr0OyxZmLpiAifeMOtyDpbgpiuD57tsCLfOh/1GTow+QLYdvP6SW5QMqfDPyPdIGb+iBkH/zS8ObzneMwW8peokRm3x/6s/jlIh1mDtT1r4HjsYevp6VvOqM6l1kGNAxeOmhxV4OiRkcYP79caB4JZvtkrfkYke6bcbmyPWu/jzJ2iJedtz0IrFnnelfPiDY2OS3OW2dZEOoNVoV0keSVGnkBo/CpsDR49cspYdxJWWP0HkrfXGUfgJKkjUL5PF4xxh3fYbdpbbOJv2iHQ+RnpDu4YXMIvFOTYo8hT8jRnuZnu2ovj/en8+kKYnL/QR+gt4HkPkQBseqx7zHvsfSxsQdPgjLOHaPPMvCcNXyJPjbonX5m/oGCZN7iRxxdguS/IufHgB3773HFpc6w+d1FKMQfcWvHA7Thwt6BsWfZW+GLeT7epX5icQuNqQWKlCy0f0K3kC7cB/tRxm7P5ovM79LrgJ9xiVpN/VyqHjj26TID4oeZdhikMReHAnJQF213aDf545hNTkptnLeotjBm6GavZFzM6Mzwz
*/