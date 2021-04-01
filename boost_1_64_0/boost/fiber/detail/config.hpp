
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
mzlXKtH91WtybBMSboVYLxzKFd84a6b3Gh4f71M575DBNfcOgh2Dt6PHWixlMgrJ4c3FoUZNlfSNbqngCqwp+kqgsWY7/1zop+1idaBACDR+E/c7fllm2NlJTakAb/HLDTGQJx+Dy5he25cW0F/N4NgyIVI/FhNxeybxFpMMbyVo2/9gHHHraWYJdjzJ3qjNozQI2ILyqge6nW1zEg6XHP+htJIlOYl4KZXTOYmimNhoAtmCHxKZDX89rCW2tlHMSd2d9gcqJwQVESfcCGrbkc19+qy+spjeuk29Oq46ASuVd8fZ32aXY8aGla1jcZkhI2b6XY8Dq9eu8OzoyQOknuWq2TVe/keBrKOsvqE6ALwH2OR+k72J/4nLROxOVAmDdJ3fSr84eaMwUWSIeF6+qjwYUEt9gEptcLQjCDTOtjBrWE5hUA0U/2yeh858N8Bb4hi5Q3oZOD/PrQXzSxA0jMmGHvSqdAipU5ch6YM/z2m65Qy6VdWJ2RqB8krzIKxNeZkh0xUuXmcuQOm+2fYcRuDg0BdYubV79nwztbjOkLtsQS6Cp9zhibmw5A==
*/