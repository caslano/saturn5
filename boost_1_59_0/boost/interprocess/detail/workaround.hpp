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

#if defined(BOOST_INTERPROCESS_FORCE_NATIVE_EMULATION) && defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) 
#error "BOOST_INTERPROCESS_FORCE_NATIVE_EMULATION && BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION can't be defined at the same time"
#endif

//#define BOOST_INTERPROCESS_FORCE_NATIVE_EMULATION

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
   #define BOOST_INTERPROCESS_WINDOWS
   #if !defined(BOOST_INTERPROCESS_FORCE_NATIVE_EMULATION) && !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION)
      #define BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION
   #endif
   #define BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME
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
   //    BOOST_INTERPROCESS_POSIX_ROBUST_MUTEXES
   //////////////////////////////////////////////////////
   #if (_XOPEN_SOURCE >= 700 || _POSIX_C_SOURCE >= 200809L)
      #define BOOST_INTERPROCESS_POSIX_ROBUST_MUTEXES
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

   //////////////////////////////////////////////////////
   //posix_fallocate
   //////////////////////////////////////////////////////
   #if (_XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L)
   #define BOOST_INTERPROCESS_POSIX_FALLOCATE
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


// Max open or create tries with managed memory segments
#ifndef BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_INITIALIZE_MAX_TRIES
   #define BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_INITIALIZE_MAX_TRIES 20u
#endif

// Maximum timeout in seconds with open or create tries with managed memory segments
// waiting the creator to initialize the shared memory
#ifndef BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_INITIALIZE_TIMEOUT_SEC
   #define BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_INITIALIZE_TIMEOUT_SEC 300u
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
#elif defined(BOOST_MSVC) && (_MSC_VER < 1900 || defined(_DEBUG))
   //"__forceinline" and MSVC seems to have some bugs in old versions and in debug mode
   #define BOOST_INTERPROCESS_FORCEINLINE inline
#elif defined(BOOST_GCC) && (__GNUC__ <= 5)
   //Older GCCs have problems with forceinline
   #define BOOST_INTERPROCESS_FORCEINLINE inline
#else
   #define BOOST_INTERPROCESS_FORCEINLINE BOOST_FORCEINLINE
#endif

#ifdef BOOST_WINDOWS

#define BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES

#ifdef __clang__
   #define BOOST_INTERPROCESS_DISABLE_DEPRECATED_WARNING _Pragma("clang diagnostic push") \
                                                         _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
   #define BOOST_INTERPROCESS_RESTORE_WARNING            _Pragma("clang diagnostic pop")
#else // __clang__
   #define BOOST_INTERPROCESS_DISABLE_DEPRECATED_WARNING __pragma(warning(push)) \
                                                         __pragma(warning(disable : 4996))
   #define BOOST_INTERPROCESS_RESTORE_WARNING            __pragma(warning(pop))
#endif // __clang__

#endif

#if defined(BOOST_HAS_THREADS) 
#  if defined(_MSC_VER) || defined(__MWERKS__) || defined(__MINGW32__) ||  defined(__BORLANDC__)
     //no reentrant posix functions (eg: localtime_r)
#  elif (!defined(__hpux) || (defined(__hpux) && defined(_REENTRANT)))
#   define BOOST_INTERPROCESS_HAS_REENTRANT_STD_FUNCTIONS
#  endif
#endif

#include <boost/core/no_exceptions_support.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_WORKAROUND_HPP

/* workaround.hpp
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
*/