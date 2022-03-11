//  (C) Copyright Dustin Spicuzza 2009.
//      Adapted to vxWorks 6.9 by Peter Brockamp 2012.
//      Updated for VxWorks 7 by Brian Kuhl 2016
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Old versions of vxWorks (namely everything below 6.x) are
//  absolutely unable to use boost. Old STLs and compilers 
//  like (GCC 2.96) . Do not even think of getting this to work, 
//  a miserable failure will  be guaranteed!
//
//  VxWorks supports C++ linkage in the kernel with
//  DKMs (Downloadable Kernel Modules). But, until recently 
//  the kernel used a C89 library with no
//  wide character support and no guarantee of ANSI C. 
//  Regardless of the C library the same Dinkum 
//  STL library is used in both contexts. 
//
//  Similarly the Dinkum abridged STL that supports the loosely specified 
//  embedded C++ standard has not been tested and is unlikely to work 
//  on anything but the simplest library.
// ====================================================================
//
// Some important information regarding the usage of POSIX semaphores:
// -------------------------------------------------------------------
//
// VxWorks as a real time operating system handles threads somewhat
// different from what "normal" OSes do, regarding their scheduling!
// This could lead to a scenario called "priority inversion" when using
// semaphores, see http://en.wikipedia.org/wiki/Priority_inversion.
//
// Now, VxWorks POSIX-semaphores for DKM's default to the usage of
// priority inverting semaphores, which is fine. On the other hand,
// for RTP's it defaults to using non priority inverting semaphores,
// which could easily pose a serious problem for a real time process.
//
// To change the default properties for POSIX-semaphores in VxWorks 7
// enable core > CORE_USER Menu > DEFAULT_PTHREAD_PRIO_INHERIT 
//  
// In VxWorks 6.x so as to integrate with boost. 
// - Edit the file 
//   installDir/vxworks-6.x/target/usr/src/posix/pthreadLib.c
// - Around line 917 there should be the definition of the default
//   mutex attributes:
//
//   LOCAL pthread_mutexattr_t defaultMutexAttr =
//       {
//       PTHREAD_INITIALIZED_OBJ, PTHREAD_PRIO_NONE, 0,
//       PTHREAD_MUTEX_DEFAULT
//       };
//
//   Here, replace PTHREAD_PRIO_NONE by PTHREAD_PRIO_INHERIT.
// - Around line 1236 there should be a definition for the function
//   pthread_mutexattr_init(). A couple of lines below you should
//   find a block of code like this:
//
//   pAttr->mutexAttrStatus      = PTHREAD_INITIALIZED_OBJ;
//   pAttr->mutexAttrProtocol    = PTHREAD_PRIO_NONE;
//   pAttr->mutexAttrPrioceiling = 0;
//   pAttr->mutexAttrType        = PTHREAD_MUTEX_DEFAULT;
//
//   Here again, replace PTHREAD_PRIO_NONE by PTHREAD_PRIO_INHERIT.
// - Finally, rebuild your VSB. This will rebuild the libraries
//   with the changed properties. That's it! Now, using boost should
//   no longer cause any problems with task deadlocks!
//
//  ====================================================================

// Block out all versions before vxWorks 6.x, as these don't work:
// Include header with the vxWorks version information and query them
#include <version.h>
#if !defined(_WRS_VXWORKS_MAJOR) || (_WRS_VXWORKS_MAJOR < 6)
#  error "The vxWorks version you're using is so badly outdated,\
          it doesn't work at all with boost, sorry, no chance!"
#endif

// Handle versions above 5.X but below 6.9
#if (_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR < 9)
// TODO: Starting from what version does vxWorks work with boost?
// We can't reasonably insert a #warning "" as a user hint here,
// as this will show up with every file including some boost header,
// badly bugging the user... So for the time being we just leave it.
#endif

// vxWorks specific config options:
// --------------------------------
#define BOOST_PLATFORM "vxWorks"


// Generally available headers:
#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_STDINT_H
#define BOOST_HAS_DIRENT_H
//#define BOOST_HAS_SLIST

// vxWorks does not have installed an iconv-library by default,
// so unfortunately no Unicode support from scratch is available!
// Thus, instead it is suggested to switch to ICU, as this seems
// to be the most complete and portable option...
#ifndef BOOST_LOCALE_WITH_ICU
   #define BOOST_LOCALE_WITH_ICU
#endif

// Generally available functionality:
#define BOOST_HAS_THREADS
#define BOOST_HAS_NANOSLEEP
#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_CLOCK_GETTIME
#define BOOST_HAS_MACRO_USE_FACET

// Generally available threading API's:
#define BOOST_HAS_PTHREADS
#define BOOST_HAS_SCHED_YIELD
#define BOOST_HAS_SIGACTION

// Functionality available for RTPs only:
#ifdef __RTP__
#  define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  define BOOST_HAS_LOG1P
#  define BOOST_HAS_EXPM1
#endif

// Functionality available for DKMs only:
#ifdef _WRS_KERNEL
  // Luckily, at the moment there seems to be none!
#endif

// These #defines allow detail/posix_features to work, since vxWorks doesn't
// #define them itself for DKMs (for RTPs on the contrary it does):
#ifdef _WRS_KERNEL
#  ifndef _POSIX_TIMERS
#    define _POSIX_TIMERS  1
#  endif
#  ifndef _POSIX_THREADS
#    define _POSIX_THREADS 1
#  endif
// no sysconf( _SC_PAGESIZE) in kernel
#  define BOOST_THREAD_USES_GETPAGESIZE
#endif

#if (_WRS_VXWORKS_MAJOR < 7) 
// vxWorks-around: <time.h> #defines CLOCKS_PER_SEC as sysClkRateGet() but
//                 miserably fails to #include the required <sysLib.h> to make
//                 sysClkRateGet() available! So we manually include it here.
#  ifdef __RTP__
#    include <time.h>
#    include <sysLib.h>
#  endif

// vxWorks-around: In <stdint.h> the macros INT32_C(), UINT32_C(), INT64_C() and
//                 UINT64_C() are defined erroneously, yielding not a signed/
//                 unsigned long/long long type, but a signed/unsigned int/long
//                 type. Eventually this leads to compile errors in ratio_fwd.hpp,
//                 when trying to define several constants which do not fit into a
//                 long type! We correct them here by redefining.

#  include <cstdint>

// Special behaviour for DKMs:

// Some macro-magic to do the job
#  define VX_JOIN(X, Y)     VX_DO_JOIN(X, Y)
#  define VX_DO_JOIN(X, Y)  VX_DO_JOIN2(X, Y)
#  define VX_DO_JOIN2(X, Y) X##Y

// Correctly setup the macros
#  undef  INT32_C
#  undef  UINT32_C
#  undef  INT64_C
#  undef  UINT64_C
#  define INT32_C(x)  VX_JOIN(x, L)
#  define UINT32_C(x) VX_JOIN(x, UL)
#  define INT64_C(x)  VX_JOIN(x, LL)
#  define UINT64_C(x) VX_JOIN(x, ULL)

// #include Libraries required for the following function adaption
#  include <sys/time.h>
#endif  // _WRS_VXWORKS_MAJOR < 7

#include <ioLib.h>
#include <tickLib.h>

#if defined(_WRS_KERNEL) && (_CPPLIB_VER < 700)
  // recent kernels use Dinkum clib v7.00+
  // with widechar but older kernels
  // do not have the <cwchar>-header,
  // but apparently they do have an intrinsic wchar_t meanwhile!
#  define BOOST_NO_CWCHAR

  // Lots of wide-functions and -headers are unavailable for DKMs as well:
#  define BOOST_NO_CWCTYPE
#  define BOOST_NO_SWPRINTF
#  define BOOST_NO_STD_WSTRING
#  define BOOST_NO_STD_WSTREAMBUF
#endif


// Use C-linkage for the following helper functions
#ifdef __cplusplus
extern "C" {
#endif

// vxWorks-around: The required functions getrlimit() and getrlimit() are missing.
//                 But we have the similar functions getprlimit() and setprlimit(),
//                 which may serve the purpose.
//                 Problem: The vxWorks-documentation regarding these functions
//                 doesn't deserve its name! It isn't documented what the first two
//                 parameters idtype and id mean, so we must fall back to an educated
//                 guess - null, argh... :-/

// TODO: getprlimit() and setprlimit() do exist for RTPs only, for whatever reason.
//       Thus for DKMs there would have to be another implementation.
#if defined ( __RTP__) &&  (_WRS_VXWORKS_MAJOR < 7)
  inline int getrlimit(int resource, struct rlimit *rlp){
    return getprlimit(0, 0, resource, rlp);
  }

  inline int setrlimit(int resource, const struct rlimit *rlp){
    return setprlimit(0, 0, resource, const_cast<struct rlimit*>(rlp));
  }
#endif

// vxWorks has ftruncate() only, so we do simulate truncate():
inline int truncate(const char *p, off_t l){
  int fd = open(p, O_WRONLY);
  if (fd == -1){
    errno = EACCES;
    return -1;
  }
  if (ftruncate(fd, l) == -1){
    close(fd);
    errno = EACCES;
    return -1;
  }
  return close(fd);
}

#ifdef __GNUC__
#  define ___unused __attribute__((unused))
#else
#  define ___unused
#endif

// Fake symlink handling by dummy functions:
inline int symlink(const char* path1 ___unused, const char* path2 ___unused){
  // vxWorks has no symlinks -> always return an error!
  errno = EACCES;
  return -1;
}

inline ssize_t readlink(const char* path1 ___unused, char* path2 ___unused, size_t size ___unused){
  // vxWorks has no symlinks -> always return an error!
  errno = EACCES;
  return -1;
}

#if (_WRS_VXWORKS_MAJOR < 7)

inline int gettimeofday(struct timeval *tv, void * /*tzv*/) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  tv->tv_sec  = ts.tv_sec;
  tv->tv_usec = ts.tv_nsec / 1000;
  return 0;
}
#endif

#ifdef __cplusplus
} // extern "C"
#endif

/* 
 * moved to os/utils/unix/freind_h/times.h in VxWorks 7
 * to avoid conflict with MPL operator times
 */
#if (_WRS_VXWORKS_MAJOR < 7) 
#  ifdef __cplusplus

// vxWorks provides neither struct tms nor function times()!
// We implement an empty dummy-function, simply setting the user
// and system time to the half of thew actual system ticks-value
// and the child user and system time to 0.
// Rather ugly but at least it suppresses compiler errors...
// Unfortunately, this of course *does* have an severe impact on
// dependant libraries, actually this is chrono only! Here it will
// not be possible to correctly use user and system times! But
// as vxWorks is lacking the ability to calculate user and system
// process times there seems to be no other possible solution.
struct tms{
  clock_t tms_utime;  // User CPU time
  clock_t tms_stime;  // System CPU time
  clock_t tms_cutime; // User CPU time of terminated child processes
  clock_t tms_cstime; // System CPU time of terminated child processes
};


 inline clock_t times(struct tms *t){
  struct timespec ts;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
  clock_t ticks(static_cast<clock_t>(static_cast<double>(ts.tv_sec)  * CLOCKS_PER_SEC +
                                     static_cast<double>(ts.tv_nsec) * CLOCKS_PER_SEC / 1000000.0));
  t->tms_utime  = ticks/2U;
  t->tms_stime  = ticks/2U;
  t->tms_cutime = 0; // vxWorks is lacking the concept of a child process!
  t->tms_cstime = 0; // -> Set the wait times for childs to 0
  return ticks;
}


namespace std {
    using ::times;
}
#  endif // __cplusplus
#endif // _WRS_VXWORKS_MAJOR < 7


#ifdef __cplusplus
extern "C" void   bzero     (void *, size_t);    // FD_ZERO uses bzero() but doesn't include strings.h

// Put the selfmade functions into the std-namespace, just in case
namespace std {
#  ifdef __RTP__
    using ::getrlimit;
    using ::setrlimit;
#  endif
  using ::truncate;
  using ::symlink;
  using ::readlink;
#  if (_WRS_VXWORKS_MAJOR < 7)  
    using ::gettimeofday;
#  endif  
}
#endif // __cplusplus

// Some more macro-magic:
// vxWorks-around: Some functions are not present or broken in vxWorks
//                 but may be patched to life via helper macros...

// Include signal.h which might contain a typo to be corrected here
#include <signal.h>

#if (_WRS_VXWORKS_MAJOR < 7)
#  define getpagesize()    sysconf(_SC_PAGESIZE)         // getpagesize is deprecated anyway!
inline int lstat(p, b) { return stat(p, b); }  // lstat() == stat(), as vxWorks has no symlinks!
#endif

#ifndef S_ISSOCK
#  define S_ISSOCK(mode) ((mode & S_IFMT) == S_IFSOCK) // Is file a socket?
#endif
#ifndef FPE_FLTINV
#  define FPE_FLTINV     (FPE_FLTSUB+1)                // vxWorks has no FPE_FLTINV, so define one as a dummy
#endif
#if !defined(BUS_ADRALN) && defined(BUS_ADRALNR)
#  define BUS_ADRALN     BUS_ADRALNR                   // Correct a supposed typo in vxWorks' <signal.h>
#endif
typedef int              locale_t;                     // locale_t is a POSIX-extension, currently not present in vxWorks!

// #include boilerplate code:
#include <boost/config/detail/posix_features.hpp>

// vxWorks lies about XSI conformance, there is no nl_types.h:
#undef BOOST_HAS_NL_TYPES_H

// vxWorks 7 adds C++11 support 
// however it is optional, and does not match exactly the support determined
// by examining the Dinkum STL version and GCC version (or ICC and DCC) 
#if !( defined( _WRS_CONFIG_LANG_LIB_CPLUS_CPLUS_USER_2011) || defined(_WRS_CONFIG_LIBCPLUS_STD))
#  define BOOST_NO_CXX11_ADDRESSOF      // C11 addressof operator on memory location
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_NUMERIC_LIMITS  // max_digits10 in test/../print_helper.hpp
#  define BOOST_NO_CXX11_SMART_PTR 
#  define BOOST_NO_CXX11_STD_ALIGN


#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST  //serialization/test/test_list.cpp
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL 
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM      //math/../test_data.hpp
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TYPEINDEX 
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_TUPLE 
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET 
#else
#  ifndef  BOOST_SYSTEM_NO_DEPRECATED
#    define BOOST_SYSTEM_NO_DEPRECATED  // workaround link error in spirit
#  endif
#endif


// NONE is used in enums in lamda and other libraries
#undef NONE
// restrict is an iostreams class
#undef restrict
// affects some typeof tests
#undef V7

// use fake poll() from Unix layer in ASIO to get full functionality 
// most libraries will use select() but this define allows 'iostream' functionality
// which is based on poll() only
#if (_WRS_VXWORKS_MAJOR > 6)
#  ifndef BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR
#    define BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR
#  endif
#else 
#  define BOOST_ASIO_DISABLE_SERIAL_PORT
#endif


/* vxworks.hpp
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
*/