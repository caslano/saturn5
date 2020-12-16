//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WORKAROUND_HPP
#define BOOST_INTERPROCESS_DETAIL_WORKAROUND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
   #define BOOST_INTERPROCESS_WINDOWS
   #define BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION
   #define BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME
   //Define this to connect with shared memory created with versions < 1.54
   //#define BOOST_INTERPROCESS_BOOTSTAMP_IS_LASTBOOTUPTIME
#else
   #include <unistd.h>

   //////////////////////////////////////////////////////
   //Check for XSI shared memory objects. They are available in nearly all UNIX platforms
   //////////////////////////////////////////////////////
   #if !defined(__QNXNTO__) && !defined(__ANDROID__) && !defined(__HAIKU__) && !(__VXWORKS__)
      #define BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS
   #endif

   //////////////////////////////////////////////////////
   // From SUSv3/UNIX 98, pthread_mutexattr_settype is mandatory
   //////////////////////////////////////////////////////
   #if defined(_XOPEN_UNIX) && ((_XOPEN_VERSION + 0) >= 500)
      #define BOOST_INTERPROCESS_POSIX_RECURSIVE_MUTEXES
   #endif

   //////////////////////////////////////////////////////
   // _POSIX_THREAD_PROCESS_SHARED (POSIX.1b/POSIX.4)
   //////////////////////////////////////////////////////
   #if defined(_POSIX_THREAD_PROCESS_SHARED) && ((_POSIX_THREAD_PROCESS_SHARED + 0) > 0)
      //Cygwin defines _POSIX_THREAD_PROCESS_SHARED but does not implement it.
      #if defined(__CYGWIN__)
         #define BOOST_INTERPROCESS_BUGGY_POSIX_PROCESS_SHARED
      #elif defined(__APPLE__)
         //The pthreads implementation of darwin stores a pointer to a mutex inside the condition
         //structure so real sharing between processes is broken. See:
         //https://opensource.apple.com/source/libpthread/libpthread-301.30.1/src/pthread_cond.c.auto.html
         //in method pthread_cond_wait
         #define BOOST_INTERPROCESS_BUGGY_POSIX_PROCESS_SHARED
      #endif

      //If buggy _POSIX_THREAD_PROCESS_SHARED is detected avoid using it
      #if defined(BOOST_INTERPROCESS_BUGGY_POSIX_PROCESS_SHARED)
         #undef BOOST_INTERPROCESS_BUGGY_POSIX_PROCESS_SHARED
      #else
         #define BOOST_INTERPROCESS_POSIX_PROCESS_SHARED
      #endif
   #endif

   //////////////////////////////////////////////////////
   // _POSIX_SHARED_MEMORY_OBJECTS (POSIX.1b/POSIX.4)
   //////////////////////////////////////////////////////
   #if ( defined(_POSIX_SHARED_MEMORY_OBJECTS) && ((_POSIX_SHARED_MEMORY_OBJECTS + 0) > 0) ) ||\
         (defined(__vms) && __CRTL_VER >= 70200000)
      #define BOOST_INTERPROCESS_POSIX_SHARED_MEMORY_OBJECTS
      //Some systems have filesystem-based resources, so the
      //portable "/shmname" format does not work due to permission issues
      //For those systems we need to form a path to a temporary directory:
      //          hp-ux               tru64               vms               freebsd
      #if defined(__hpux) || defined(__osf__) || defined(__vms) || (defined(__FreeBSD__) && (__FreeBSD__ < 7))
         #define BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SHARED_MEMORY
      //Some systems have "jailed" environments where shm usage is restricted at runtime
      //and temporary file based shm is possible in those executions.
      #elif defined(__FreeBSD__)
         #define BOOST_INTERPROCESS_RUNTIME_FILESYSTEM_BASED_POSIX_SHARED_MEMORY
      #endif
   #endif

   //////////////////////////////////////////////////////
   // _POSIX_MAPPED_FILES (POSIX.1b/POSIX.4)
   //////////////////////////////////////////////////////
   #if defined(_POSIX_MAPPED_FILES) && ((_POSIX_MAPPED_FILES + 0) > 0)
      #define BOOST_INTERPROCESS_POSIX_MAPPED_FILES
   #endif

   //////////////////////////////////////////////////////
   // _POSIX_SEMAPHORES (POSIX.1b/POSIX.4)
   //////////////////////////////////////////////////////
   #if ( defined(_POSIX_SEMAPHORES) && ((_POSIX_SEMAPHORES + 0) > 0) ) ||\
       ( defined(__FreeBSD__) && (__FreeBSD__ >= 4)) || \
         defined(__APPLE__)
      #define BOOST_INTERPROCESS_POSIX_NAMED_SEMAPHORES
      //MacOsX declares _POSIX_SEMAPHORES but sem_init returns ENOSYS
      #if !defined(__APPLE__)
         #define BOOST_INTERPROCESS_POSIX_UNNAMED_SEMAPHORES
      #endif
      #if defined(__osf__) || defined(__vms)
         #define BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SEMAPHORES
      #endif
   #endif

   //////////////////////////////////////////////////////
   // _POSIX_BARRIERS (SUSv3/Unix03)
   //////////////////////////////////////////////////////
   #if defined(_POSIX_BARRIERS) && ((_POSIX_BARRIERS + 0) >= 200112L)
      #define BOOST_INTERPROCESS_POSIX_BARRIERS
   #endif

   //////////////////////////////////////////////////////
   // _POSIX_TIMEOUTS (SUSv3/Unix03)
   //////////////////////////////////////////////////////
   #if defined(_POSIX_TIMEOUTS) && ((_POSIX_TIMEOUTS + 0L) >= 200112L)
      #define BOOST_INTERPROCESS_POSIX_TIMEOUTS
   #endif

   //////////////////////////////////////////////////////
   // Detect BSD derivatives to detect sysctl
   //////////////////////////////////////////////////////
   #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__APPLE__)
      #define BOOST_INTERPROCESS_BSD_DERIVATIVE
      //Some *BSD systems (OpenBSD & NetBSD) need sys/param.h before sys/sysctl.h, whereas
      //others (FreeBSD & Darwin) need sys/types.h
      #include <sys/types.h>
      #include <sys/param.h>
      #include <sys/sysctl.h>
      #if defined(CTL_KERN) && defined (KERN_BOOTTIME)
         //#define BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME
      #endif
   #endif

   //////////////////////////////////////////////////////
   //64 bit offset
   //////////////////////////////////////////////////////
   #if (defined (_V6_ILP32_OFFBIG)  &&(_V6_ILP32_OFFBIG   - 0 > 0)) ||\
       (defined (_V6_LP64_OFF64)    &&(_V6_LP64_OFF64     - 0 > 0)) ||\
       (defined (_V6_LPBIG_OFFBIG)  &&(_V6_LPBIG_OFFBIG   - 0 > 0)) ||\
       (defined (_XBS5_ILP32_OFFBIG)&&(_XBS5_ILP32_OFFBIG - 0 > 0)) ||\
       (defined (_XBS5_LP64_OFF64)  &&(_XBS5_LP64_OFF64   - 0 > 0)) ||\
       (defined (_XBS5_LPBIG_OFFBIG)&&(_XBS5_LPBIG_OFFBIG - 0 > 0)) ||\
       (defined (_FILE_OFFSET_BITS) &&(_FILE_OFFSET_BITS  - 0 >= 64))||\
       (defined (_FILE_OFFSET_BITS) &&(_FILE_OFFSET_BITS  - 0 >= 64))
      #define BOOST_INTERPROCESS_UNIX_64_BIT_OR_BIGGER_OFF_T
   #endif
#endif   //!defined(BOOST_INTERPROCESS_WINDOWS)

#if defined(BOOST_INTERPROCESS_WINDOWS) || defined(BOOST_INTERPROCESS_POSIX_MAPPED_FILES)
#  define BOOST_INTERPROCESS_MAPPED_FILES
#endif

//Now declare some Boost.Interprocess features depending on the implementation
#if defined(BOOST_INTERPROCESS_POSIX_NAMED_SEMAPHORES) && !defined(BOOST_INTERPROCESS_POSIX_SEMAPHORES_NO_UNLINK)
   #define BOOST_INTERPROCESS_NAMED_MUTEX_USES_POSIX_SEMAPHORES
   #define BOOST_INTERPROCESS_NAMED_SEMAPHORE_USES_POSIX_SEMAPHORES
#endif

#if    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
   #define BOOST_INTERPROCESS_PERFECT_FORWARDING
#endif

// Timeout duration use if BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING is set
#ifndef BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS
   #define BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS 10000
#endif

//Other switches
//BOOST_INTERPROCESS_MSG_QUEUE_USES_CIRC_INDEX
//message queue uses a circular queue as index instead of an array (better performance)
//Boost version < 1.52 uses an array, so undef this if you want to communicate
//with processes compiled with those versions.
#define BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX

//Macros for documentation purposes. For code, expands to the argument
#define BOOST_INTERPROCESS_IMPDEF(TYPE) TYPE
#define BOOST_INTERPROCESS_SEEDOC(TYPE) TYPE
#define BOOST_INTERPROCESS_DOC1ST(TYPE1, TYPE2) TYPE2
#define BOOST_INTERPROCESS_I ,
#define BOOST_INTERPROCESS_DOCIGN(T1) T1

//#define BOOST_INTERPROCESS_DISABLE_FORCEINLINE

#if defined(BOOST_INTERPROCESS_DISABLE_FORCEINLINE)
   #define BOOST_INTERPROCESS_FORCEINLINE inline
#elif defined(BOOST_INTERPROCESS_FORCEINLINE_IS_BOOST_FORCELINE)
   #define BOOST_INTERPROCESS_FORCEINLINE BOOST_FORCEINLINE
#elif defined(BOOST_MSVC) && defined(_DEBUG)
   //"__forceinline" and MSVC seems to have some bugs in debug mode
   #define BOOST_INTERPROCESS_FORCEINLINE inline
#elif defined(__GNUC__) && ((__GNUC__ < 4) || (__GNUC__ == 4 && (__GNUC_MINOR__ < 5)))
   //Older GCCs have problems with forceinline
   #define BOOST_INTERPROCESS_FORCEINLINE inline
#else
   #define BOOST_INTERPROCESS_FORCEINLINE BOOST_FORCEINLINE
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_WORKAROUND_HPP

/* workaround.hpp
fobimwA53d86T/wnStdZqwwjKP5R6qY7Hhctt3x1ZjXp/TloEJtRzxcrnT526bVBWd8+lnX6bniOFp2+A+ucQMdv0fPt42tEDXp+k8gq9HxqRzS2UhnQPFGXja1tb2nAkY6Rsz4yQItQ4CcirbadOXbgGCUFOmXmFmTl5fM9Ae+QXWGBNUacIv5L3do54tL9+aRyVONVqb7f0VuXZAf5L0hw6kJtyL8R+a+h+dosmHH0OfAx5N+R6iMVueqCtHVU9VGvj1G5PhKEZyp4LlE8gZRof4Th5JPxLAXPnUCXgjq7jN/RVdxR8A6V+QLbeDwVmeWeZFhnjt2sbD51dVlnz87NnssFbbsvw1muHE6PO2ynmWvoOyBzyX+uEUHWkypsPXVD7tgyJA46Q16PX6XEcwXaYHurv97BdeJuD9Lpkjhn5mfNKnXe2aJ5rfLvEhvO+Icy1vdeVJrPShmE3vVjyxMVFbtzuujM3z2UDth7EkJ0KNGv5N4c8i8B3ab6h6POZhdB8tdYZydqqLPvyb+A6mx4FXV2Iow680Ypnkko445WnV1Ebue738FRizoLff8ZvnM/N7dE69iOOwD/D+o4eJ+TSm+8Ti/V/ago97p/qxEnqI0krDVoHXgqoirXfR66cs11T+H0XEPqXo9Jy8k/2X2OqcO71buzTok//DqtiKq5joww6+irhr+sjkLHpb3ny1ljcif49aA7EuDuUvZ0Uru9/K157EfEX2xcbsS41AnHZ++PecWIzupH75P/fHyzX9/9Tiv3MnbWhwuvgXehOKz6rxvN9e8xYolnZQzz4BYrFR/dd6jsAYeQsDYon67KHtAiqmPA542LGhzwRfujLX24G/y6y1hWuU7RBcK6l7v6PijlFFq/kne4UVpXEh+ln/rZ59LPNtj7GR/+Q2XFf8pxI3jWRuu6phGRp6miJ1R774CENfnedZTVELyjB+lozrHe2c7d72LBO+WOAXv6NzVh5t6y364X6E7wbtPpt+lPup1q/elx4m3nPk/gvFSpH31E/tFV6kcvkX8Lum9+OcphYpOg7tM6OsKh++h7gHrieSdKpvMvkNeh5ZNxATOul35wh5SPcV6l8inKLi0OQ45SOEd5aBt/PfJfiR47V4Wn9ux2j09n4svidbIE8iucWaRtYC3Jfx7y6iWeq6lss3IMQ+uuQ4mnnzybRio9R9JdC5tRzgeSsJ6gytpMocWjAVXdGSb8J8Dfi9aOUkPXjbROKvXSG9QH1FfqxheGThrSj6lMqD1z2VF9pUl9HZL6Cmh7G50Jv5fytjcTO4uzs/KxpzgnryizNDsL9qOiYrU6WVrtfR0qLbQXuoXqSysMlGrmaA43Dvf7Z83KlXRcGtzjfCGHvEhiaAXahjQf5HaTOb+UX873fuGOK5LfmWnlM2fmlrjLBQlrhvIPksvznPK9Ev+PzD9C5T7Xdcy18xf7iL9/yawRZBVwjLua36rrfrE133mSIPWp0h+v88s2H+0u+dJj8I/krtNvuytQp5Nk9XFKF87+qSSr42Tx524Zl9eAdoDHqEd1knVpXubQjP7p6WMHjhsHV8e4Gux7jYk/zb1/w0/bf5z3lk0l/14YKRtauu1icpO7U/TYaunVaeQ/nsbWyyRcohXOrHa8LUY7XJ8s422TmsfboPxU88z+oLRajrs03jjGWfcxtWk99zF1ZQv5LgCeTencBa6ngy71lDlqgKOeEsTu8hXxrzAaobWWut8zLXEi3fayv9Qw9Bh0c32y1Vjl/iY9N3PUcfBeya8pzkgzAVL8XRDdqZRgr5/DKI/K+wVUVJdS3B6r7v9Bcd2GMo+l2/IdaaA4OO7QtZJW5P9nY4MRVzlvnVg=
*/