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
GZ34r78B23syyMR2TC991H+d+ycRAWh9EnIyWMFWg3qXI2KrMOB6g0Kf/x3HM/BzadJ+83j78fb1mZ/fLjI//zLc/HzLMPNzzyBLeY/5efcc83O+x4LPb4Efan7eemXzc9tg8/MllvxfSi31lVrwW/gdv5IFf64lv8jSXhZ+Fw1KI49oPU5zozwS8Qm5IQyB/qaDmWv8Fw5F60hYgD+RyFdpn3gKR9vf6804ukbbo9hM7zwt/7y97fBzrwv5MTFCmSvmNPui0z7S0SzXV2qnvs009TlbQtHqeC+fntUE2VSrNUjVaxtcouIkBaOT3+FNvDAUQOu5FiV7VQ4TiBYMI3WJElWv9C5Dwyf4GzbYoh9D7NivnZxcXupd3tOfYzw0mGQGJqETGKEhQ3JIgAkHmUrzp7LopJI+9gQsjSIDeOwEhsPVUmXCEayZ9wqpjji33649nLkFPG6NuKqXkuDVRFba3bK+qXR1zbzXael7oLQc9a7G0r/+3BsfOKtG2nNUjkU/Lc/zPBb5tuh3j/xcq5pfNeH5z0TISIfAMIJyw86DXbDE3YZ3ImEpe9/VyfYqzaotKhN5PlOe05RnmPJcUp4pww0ZMJh5MPgAbQ/tTlKqIIX8hhxMXFohJ8zPqYWHeigQhLsGuAuj0EQPIrksvNyM41Q034sRl6Z+dxC7ZHsM7a2N//+Jrcyjgn4gCUNeR+f0wSQvkoeyE3NVdmFAyE58Hu2HK4E4BIjR16xjk0CYddXD7B9qeuGzXktNqPgZnBeOFc79I12FYV5jbiY12q1/Jfv1773s9Vu67/LfsVJ5OcUfff3dXm30rlai34xqR4oKP61Wi0yYsR7+TK+NmKAF6e+/KeiL/azHhKRZkDxEkSBRZkwjvpQx2fH3EeFBDKGCy4d6GMb08dUyiiVR9lavfj2QF4r9atK3oNA3l6t/+nZuAnEIEOv1be+PM5A+vbyvmbZCIe8XfpRBjXbrv+YX2/V/vez1W7pv9C9J8hyMHvjWsujbR0vV+sax/v5Eb+b6Nnupgr4T+zLTt62WyvomY7r3895l0befftboW5AsVNnWt7splkTZCUUqfRMCcgqFj9ZADI8vtgfoeuUMAPicAIB4lEIwVVqDcMX2nDcMANb9WkwjnVLgpy1s0OUGB1zzBgNo/CvuErdv7QNwCIBzn9aIul5nzmGsiI73i4mTm4EYatv3Zqj8wp9Yy+Sc/usI/iopLq9M/ZLyHgJvhU/GQ46WURAFDqHfOOieVYaTF89qyMP8FuBnDLrDxEj0eDFmx06H4P4mepZ15Al2pnWKFdYz3Rijyul5B7GSPoJ3GOtp5qyFOMPO6XmUZJLXIbsw2jezDUsjzpC/HQ4JD0ZGAmU7UMqGImXHmynrJMoca2UBLyi6tb8WXKkdjXAHrDV/vA4sAVM8u1A8Lw0HPFea8TQDHgPaBY3CyNp2TjOShBb9ibcxuuvicJzZqS/2xttJCrzIOIe9yPiuC7fd3fz3bruT5H1On2QQ+aaEhAgOepmFxWyub9QwdBgCjRh0/aClApr1Ydqsdw+DZj0NmvVE0azDloBg97yfCPw0R78hUX5cdc2ny3r1PCxTD2EZhnQBRbonIq0xI33qQ0Q6CxKGI68wTPM1Nr4Lg+pjbIKIm15IpH/G0uGRAOBfSPH/5gf8J5jxT0H8sQqBSszNYDRJhE8baMBojTd74wMym7K53oTm754fePdyyW8L+6k6R8I1nbfRldFV/XwrxDMP9YptV2V82xVbYd1CrL+FEtPMi8r9DoE9TLCjwax2REqoiVs1KhA6be8Hsl6S1VryPbdaL/0orNbFDqvJAWleiBMqvGA+GOY3DezbFPXst8k=
*/