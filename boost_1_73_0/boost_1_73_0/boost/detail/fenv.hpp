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
xl/AIP1v5yZ5tzojOHhgYMg3NsJS5DnVUdxJpVF9tUBrVK/pogt/NgyddyvMPmVYvxoENiANMZjXaDYcejCqt5XUAONJEAa9YDh1ZnTsqegjeVQP+3/41+Nhv3oR4BBCNcD/myUOTUzUaIkH1UqvB0LBGbR3ljqN9SnairSNMHB29vTs7FQjGCAnUtopxsOjIPGLJIed0+oZZqwRLlJpSjycwVG93uh2896i5S/O3oONmk+dL3sbqFmgn+S+Nx9p4flz8XkApGQXvt9E7lBiXiqqmvnv8U3ovxsMB+GN4ydJfXx95R2/9E4qg0k/nE1G8N4fzvrOpNqrqQIQB+tu3TSFKYtCaeyJ+sBXGzacREE1v8kJm6UWVAvpB384DfAo8m6ynzm0UPMutOCpdlg/dP4BUEsDBAoAAAAIAC1nSlIomp6n/gMAAOkIAAAxAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9JUFJFU09MVkUuM1VUBQABtkgkYK1VXVOjSBR951fcyr5EC8m4WuM4604tE5mRnUygAOOmKlVUBxrp3Yam6CYxtc5/39tAjFG39GHQ2OT2vefcj9OttRjA4U97DEvDwatP3H5ifHDdBvm1+Jsm6uWAOL6H7gcD
*/