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
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
*/