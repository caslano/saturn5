#ifndef BOOST_CORE_QUICK_EXIT_HPP_INCLUDED
#define BOOST_CORE_QUICK_EXIT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  boost/core/quick_exit.hpp
//
//  Copyright 2018 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <stdlib.h>

#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)

extern "C" _CRTIMP __cdecl __MINGW_NOTHROW  void _exit (int) __MINGW_ATTRIB_NORETURN;

#endif

#if defined(__CYGWIN__) && __cplusplus < 201103L

extern "C" _Noreturn void quick_exit(int);

#endif

namespace boost
{

BOOST_NORETURN void quick_exit( int code ) BOOST_NOEXCEPT
{
#if defined(_MSC_VER) && _MSC_VER < 1900

    ::_exit( code );

#elif defined(__MINGW32__)

    ::_exit( code );

#elif defined(__APPLE__)

    ::_Exit( code );

#else

    ::quick_exit( code );

#endif
}

} // namespace boost

#endif  // #ifndef BOOST_CORE_QUICK_EXIT_HPP_INCLUDED

/* quick_exit.hpp
sTP5FvsU86xg8hfz3LhIBdMXaiQXYdZzZcVHbr3k8SUkn6yU1vL5Gb9VvhcUTqVmTdt9QK7P536R6ls3xr/5NuDuCZ0OV8r1Bb715PVbETLP7n574uP2p+n2qf79WfPnfX/WNGMn8ZIW3+f2kAr0z9Hn9tnObzys9rzDFOSxJphFjzkFvJuZMj1ter6uQ0qL3ovFTzF312N964UwTZufJXXIXue8Zvr3Ede9xsmhqfCMQ1vE
*/