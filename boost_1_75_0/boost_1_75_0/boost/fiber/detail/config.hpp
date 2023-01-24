
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
h2y9bemWKNcV4LKGjQoyC39sjnfIBhw6AwtWrMYBObBx6GMKOH9bAmDAAcfYMsACZMKwrAP2CJ7zOKAzRneewsIMJt1hicCAGptH4qLLR9m6YyINoG80/3i3+vGibjiF+BFjZloYkSKnMrKE3dmSmXp/L1eyQx6V4Byw28LqGWnaEmEYsNtltLNqSve5mkurihjoDGazBxR274goQ/MQU1RYIts7IU1nznm9MN1s1mF6jGyam8pQRaBr08PnIXhBD/gClgH3DdpDzBU+cNAhZfFHCZbpe3zoBBcECidU0Sk/g5XiGNUd4NUjwB3gsjTbrJa84iXzz091XauMKFANmJPz3HMLzuMBAO4rE+6L0XtV+HxknMT98MyFPhRSH2ag7boR2kejpGQ5/NAocOxzpsLguoKdEf89NU5iW4GdDlPYL3f4P1gum4NwDz0jN2Dp8GXskXKQcS3p4d1YOXBPET4fstLDQ9l7IeNkrpmMRT+Gu3/wDOiJNEyFPtVkekYwvuU/tjhJrmdrd5l3j23WHtvuxjBb6MeAi9MjK6ewKqvx6JIe+S68bIOxZMDczsWBJM/AuSw9yEknCWNYM9nkXwuUE57/IEH410LG/rTNPYHtpdktEvhn8mS3MIDl4kg8pxXPViQIZwNxd3bASdjZqFx3j/CUbFWEo+QJqeigtpGzH3NGoIPaOSImQx6rqFHSQgSe3dqbBy81lZEC
*/