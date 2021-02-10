
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONFIG_H
#define BOOST_FIBERS_DETAIL_CONFIG_H

#include <cstddef>

#include <boost/config.hpp>
#include <boost/predef.h> 
#include <boost/detail/workaround.hpp>

#ifdef BOOST_FIBERS_DECL
# undef BOOST_FIBERS_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_FIBERS_DYN_LINK) ) && ! defined(BOOST_FIBERS_STATIC_LINK)
# if defined(BOOST_FIBERS_SOURCE)
#  define BOOST_FIBERS_DECL BOOST_SYMBOL_EXPORT
#  define BOOST_FIBERS_BUILD_DLL
# else
#  define BOOST_FIBERS_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_FIBERS_DECL)
# define BOOST_FIBERS_DECL
#endif

#if ! defined(BOOST_FIBERS_SOURCE) && ! defined(BOOST_ALL_NO_LIB) && ! defined(BOOST_FIBERS_NO_LIB)
# define BOOST_LIB_NAME boost_fiber
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_FIBERS_DYN_LINK)
#  define BOOST_DYN_LINK
# endif
# include <boost/config/auto_link.hpp>
#endif

#if BOOST_OS_LINUX || BOOST_OS_WINDOWS
# define BOOST_FIBERS_HAS_FUTEX
#endif

#if (!defined(BOOST_FIBERS_HAS_FUTEX) && \
    (defined(BOOST_FIBERS_SPINLOCK_TTAS_FUTEX) || defined(BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX)))
# error "futex not supported on this platform"
#endif

#if !defined(BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD)
# define BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD 16
#endif

#if !defined(BOOST_FIBERS_RETRY_THRESHOLD)
# define BOOST_FIBERS_RETRY_THRESHOLD 64
#endif

#if !defined(BOOST_FIBERS_SPIN_BEFORE_SLEEP0)
# define BOOST_FIBERS_SPIN_BEFORE_SLEEP0 32
#endif

#if !defined(BOOST_FIBERS_SPIN_BEFORE_YIELD)
# define BOOST_FIBERS_SPIN_BEFORE_YIELD 64
#endif

#endif // BOOST_FIBERS_DETAIL_CONFIG_H

/* config.hpp
yNZA6J0qK2k3Di9dKxf3NFy6xLa7HKlet0Q6SJAShZC2TChj60PUoKB8OKMbUpUpKBz6r/0T66AmOO3YDr80hBGxn0cJvDD0tRs9M6KZD87Rof/qv+lx32RUD5bgHR27BjDEF9Pk2dHxAQpTwcKqT9GxTOpYQ3qgbBAg0i71AyF13+woEZ8QG8uffeZbScIGVpoSUfn7hJFynZ6j/lDWs2A1Tx2bHztDZEijaTRPnMC0H5oJPwSX8Tx0fFE6PYGsCH5/QC8uuB4RU3g5MpNj+NuB/7PPTNyzjl4euPvOineM1I5+LrcTlzx919yS9oEDW/+nW+7pTh56tvkNbn/cvFeLzd4P2V6EBvsn3P1gWLKLgyS5on7pqpO8Rd0b0+BRQeg2MPTvq/HYe14jE12zX/rH8Utu6xy8D2bz4N1sPkvXTlAU/a3b9zrHmZWw6XitIZ0ngMLcjEXPoWWYrpYLeB/MV6GzRE1XjLKwwyy6AF5aC3Nj7JXpDaurxcUiulpkkW0rZicR2gjGGaxXaRadZZfhZbRcm2VzQSDcUlPhQnUltQbbJypkDbVSlmMPyE3CEIJ5EhGj3y2/XjhwRydjSuJXS7NffGT+sHXv1/8FUEsDBAoAAAAIAC1nSlJKqJ/mPwUAAPgLAAA6AAkA
*/