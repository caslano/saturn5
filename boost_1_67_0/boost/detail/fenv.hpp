/*=============================================================================
    Copyright (c) 2010      Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <boost/config.hpp>

#if defined(BOOST_NO_FENV_H)
  #error This platform does not have a floating point environment
#endif

#if !defined(BOOST_DETAIL_FENV_HPP)
#define BOOST_DETAIL_FENV_HPP

/* If we're using clang + glibc, we have to get hacky.
 * See http://llvm.org/bugs/show_bug.cgi?id=6907 */
#if defined(__clang__)       &&  (__clang_major__ < 3) &&    \
    defined(__GNU_LIBRARY__) && /* up to version 5 */ \
    defined(__GLIBC__) &&         /* version 6 + */ \
    !defined(_FENV_H)
  #define _FENV_H

  #include <features.h>
  #include <bits/fenv.h>

  extern "C" {
    extern int fegetexceptflag (fexcept_t*, int) __THROW;
    extern int fesetexceptflag (__const fexcept_t*, int) __THROW;
    extern int feclearexcept (int) __THROW;
    extern int feraiseexcept (int) __THROW;
    extern int fetestexcept (int) __THROW;
    extern int fegetround (void) __THROW;
    extern int fesetround (int) __THROW;
    extern int fegetenv (fenv_t*) __THROW;
    extern int fesetenv (__const fenv_t*) __THROW;
    extern int feupdateenv (__const fenv_t*) __THROW;
    extern int feholdexcept (fenv_t*) __THROW;

    #ifdef __USE_GNU
      extern int feenableexcept (int) __THROW;
      extern int fedisableexcept (int) __THROW;
      extern int fegetexcept (void) __THROW;
    #endif
  }

  namespace std { namespace tr1 {
    using ::fenv_t;
    using ::fexcept_t;
    using ::fegetexceptflag;
    using ::fesetexceptflag;
    using ::feclearexcept;
    using ::feraiseexcept;
    using ::fetestexcept;
    using ::fegetround;
    using ::fesetround;
    using ::fegetenv;
    using ::fesetenv;
    using ::feupdateenv;
    using ::feholdexcept;
  } }

#elif defined(__MINGW32__) && defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) >= 408

  // MinGW (32-bit) has a bug in mingw32/bits/c++config.h, it does not define _GLIBCXX_HAVE_FENV_H,
  // which prevents the C fenv.h header contents to be included in the C++ wrapper header fenv.h. This is at least
  // the case with gcc 4.8.1 packages tested so far, up to 4.8.1-4. Note that there is no issue with
  // MinGW-w64.
  // To work around the bug we avoid including the C++ wrapper header and include the C header directly
  // and import all relevant symbols into std:: ourselves.

  #include <../include/fenv.h>

  namespace std {
    using ::fenv_t;
    using ::fexcept_t;
    using ::fegetexceptflag;
    using ::fesetexceptflag;
    using ::feclearexcept;
    using ::feraiseexcept;
    using ::fetestexcept;
    using ::fegetround;
    using ::fesetround;
    using ::fegetenv;
    using ::fesetenv;
    using ::feupdateenv;
    using ::feholdexcept;
  }

#else /* if we're not using GNU's C stdlib, fenv.h should work with clang */

  #if defined(__SUNPRO_CC) /* lol suncc */
    #include <stdio.h>
  #endif

  #include <fenv.h>

#endif

#endif /* BOOST_DETAIL_FENV_HPP */

/* fenv.hpp
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
*/