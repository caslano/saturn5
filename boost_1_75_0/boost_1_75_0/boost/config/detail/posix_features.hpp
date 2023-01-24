//  (C) Copyright John Maddock 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

// All POSIX feature tests go in this file,
// Note that we test _POSIX_C_SOURCE and _XOPEN_SOURCE as well
// _POSIX_VERSION and _XOPEN_VERSION: on some systems POSIX API's
// may be present but none-functional unless _POSIX_C_SOURCE and
// _XOPEN_SOURCE have been defined to the right value (it's up
// to the user to do this *before* including any header, although
// in most cases the compiler will do this for you).

#  if defined(BOOST_HAS_UNISTD_H)
#     include <unistd.h>

      // XOpen has <nl_types.h>, but is this the correct version check?
#     if defined(_XOPEN_VERSION) && (_XOPEN_VERSION >= 3)
#        define BOOST_HAS_NL_TYPES_H
#     endif

      // POSIX version 6 requires <stdint.h>
#     if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200100)
#        define BOOST_HAS_STDINT_H
#     endif

      // POSIX version 2 requires <dirent.h>
#     if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 199009L)
#        define BOOST_HAS_DIRENT_H
#     endif

      // POSIX version 3 requires <signal.h> to have sigaction:
#     if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 199506L)
#        define BOOST_HAS_SIGACTION
#     endif
      // POSIX defines _POSIX_THREADS > 0 for pthread support,
      // however some platforms define _POSIX_THREADS without
      // a value, hence the (_POSIX_THREADS+0 >= 0) check.
      // Strictly speaking this may catch platforms with a
      // non-functioning stub <pthreads.h>, but such occurrences should
      // occur very rarely if at all.
#     if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(BOOST_HAS_WINTHREADS) && !defined(BOOST_HAS_MPTASKS)
#        define BOOST_HAS_PTHREADS
#     endif

      // BOOST_HAS_NANOSLEEP:
      // This is predicated on _POSIX_TIMERS or _XOPEN_REALTIME:
#     if (defined(_POSIX_TIMERS) && (_POSIX_TIMERS+0 >= 0)) \
             || (defined(_XOPEN_REALTIME) && (_XOPEN_REALTIME+0 >= 0))
#        define BOOST_HAS_NANOSLEEP
#     endif

      // BOOST_HAS_CLOCK_GETTIME:
      // This is predicated on _POSIX_TIMERS (also on _XOPEN_REALTIME
      // but at least one platform - linux - defines that flag without
      // defining clock_gettime):
#     if (defined(_POSIX_TIMERS) && (_POSIX_TIMERS+0 >= 0))
#        define BOOST_HAS_CLOCK_GETTIME
#     endif

      // BOOST_HAS_SCHED_YIELD:
      // This is predicated on _POSIX_PRIORITY_SCHEDULING or
      // on _POSIX_THREAD_PRIORITY_SCHEDULING or on _XOPEN_REALTIME.
#     if defined(_POSIX_PRIORITY_SCHEDULING) && (_POSIX_PRIORITY_SCHEDULING+0 > 0)\
            || (defined(_POSIX_THREAD_PRIORITY_SCHEDULING) && (_POSIX_THREAD_PRIORITY_SCHEDULING+0 > 0))\
            || (defined(_XOPEN_REALTIME) && (_XOPEN_REALTIME+0 >= 0))
#        define BOOST_HAS_SCHED_YIELD
#     endif

      // BOOST_HAS_GETTIMEOFDAY:
      // BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE:
      // These are predicated on _XOPEN_VERSION, and appears to be first released
      // in issue 4, version 2 (_XOPEN_VERSION > 500).
      // Likewise for the functions log1p and expm1.
#     if defined(_XOPEN_VERSION) && (_XOPEN_VERSION+0 >= 500)
#        define BOOST_HAS_GETTIMEOFDAY
#        if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE+0 >= 500)
#           define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#        endif
#        ifndef BOOST_HAS_LOG1P
#           define BOOST_HAS_LOG1P
#        endif
#        ifndef BOOST_HAS_EXPM1
#           define BOOST_HAS_EXPM1
#        endif
#     endif

#  endif





/* posix_features.hpp
9BotyoW/Z86WhSXnxbNVwXgCBeNqBy2z8j3DxduZ9tcyna9l5tychX52obMwZ/DZmbiWLmOAzWHods7rMZ+zKyifIApsPpE2RpL7YC3nod7jcIFLDOvjLFT/dwTGATiHssthWTVC1lX2d7NwteR/zFUu/pxl/6XdGOKSfQzZx0VjaJlpSLbJfo8qR9Vnlt8uiqaf8nZOpSuK6NW7OV+A5QjMn0fI/qhZRmQ2xX0Vht3ueGuEyh7xkkuc7cx5xrAPyXTca39P1NgLHaaOGpvUMaWPshrP1m1GMdqMomSbMfmcPHP/aTUsc85R984i3LNoZlbp9cDipjPRLyhR6zvm7BO//2gNezWMfahh7Eb9o/o7qOdQBw1EHST7O7J+uBteysZjHPeA9PsjQ866Dy5BH8I2INXWn5EhstEX0Pmn3LyZGOMVYIyXL9L6BaOyxRnl08QZtsmnjOMKyvLEITkGHALLqDJ5/Qoas+W3y+Tp2QxHi2F/1JCjSMQzJlsMaZouhpT7xRDEZT3HpdZ4gjKeGw37/XoP7HDRew/sljK5HU/Of8ByR5nOT5uBW1eOK08Xbr813AtSz3vGy//E/3Gr/5PS/xBDLk6k+pWuZL+y5Fzk+9n4O+9c2a+cjvJjHJbthOy/dbD/q/3Mkn56DOuxpfpYUB67xrCVutC2DxClHcWJonhhrCCaH+pf7wnY0GYPmCbTYMj5AfP5bxn2
*/