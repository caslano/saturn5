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
NqY8TQa/1CQPefx9Fj6Tkg5rV+CKRAYIyw5VS9SB2+WHzZeV7QWiznxtMmMpXVgnbMb6V9Py7wOEmTCt7aQHPHfDnMZIoeBnjvxpKsVGND9jSsLwR3WOBoBpXRlVwPCxoyTHAAliZ+WdmJiwWWRlFjGPD35u+Ez54KC8Wltcuf7ksaHqC/m6I80Ey68aopV/GRV/L6BzD764yp0LNtPc4Xm1q2FC/NYHdL/xNDdBiHlskqhxfnnF+JocBQrYkLh/tvOA0lG89AOunWDziAjME2nD6ieSkDVSv1+fdGKLKXL6kZ/Y1ymgHLCjWzMaATvgV2heANhW1LLgTCzO6+vvdEY1AgaPxr6dQv9Up2fYygFTe2m30n+H+bYRTn9jqqbup7oHAzy3tHxNnPtyk7yLDegRwQ5MFrgLNDSpPSZ93ZwhrI38TFQsLU3vd4nKr9A3yl+BWIF6dpsxMrVFsFVyVZw5XkWPkRUcSfC942yPP3XrAXuNRXAIFyIgFOyhyqYVtOU+YWd46W7OY8waejpx9tFO/nHWnPVlNEUnhHNMncan+/RwVcP1a5U58E5l93uqI0p2kCav5yvoQHpttOmmERisEnffJO2+HJyXDGIvuCAYf9//CZdHVOFe8SZOATte+reXEP85KeqRRldnvU1Kn7A4aJMcxcocqRziZ73llwACFvPS3soYJhrz8wftlmPV30dM2oKgoNybRLJV
*/