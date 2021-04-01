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
nzdXm8LjFt0+TDxysYDWBbv28uiJtSlta5iFEfQ0Zl3LVviKj2ieoSLCSQmBjwvN8H2UxUkNjM2WZime3lahxzP3gemqlWNWWDrZLroG3zRUyTL4ilV2GDmPurzKMxOTMCyNbljVmlNW+h84o5smK4+eUaM1loMuns62g6+DAPf8Cgl76PHlgketKHghVx+n+/P8Ovol1BeeV9krEuNBIccjeWa+QiDrDOQMEyX61i3/hl2YaGXeEPFAEKObReFMMlogXW6eY+qr2ZtSgKhByS8Ggi4B26JKzdSIzEsrPr+8ca/RCOcdGyEVjXHEmE2eQpHn1AYHamswCNGLrSVIFwONWs9AOTCNYnpcG1Rz+nhTPMNANJagTeZZod/fnZ0JSPxlKnaZ/1JyDeIZasHwf6IAxH1f/QjgUzcQFURsyhRAQ7oR7E6TVmUeVjyxCVbpUg5GvE0uEUBbyaO/hJ4FGsQpdm2Ka6Jsz72qi434YlNdbc4YYlgk+T46nCjd2Jy3ZP0RJymbrSK0kZ1xSilBKCNc9N47d/qLMKXF5u5aqKbfkfYl8s44lbKkKQ==
*/