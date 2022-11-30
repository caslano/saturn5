//  (C) Copyright David Abrahams 2000.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

//  This file serves as a wrapper around <Python.h> which allows it to be
//  compiled with GCC 2.95.2 under Win32 and which disables the default MSVC
//  behavior so that a program may be compiled in debug mode without requiring a
//  special debugging build of the Python library.


//  To use the Python debugging library, #define BOOST_DEBUG_PYTHON on the
//  compiler command-line.

// Revision History:
// 05 Mar 01  Suppress warnings under Cygwin with Python 2.0 (Dave Abrahams)
// 04 Mar 01  Rolled in some changes from the Dragon fork (Dave Abrahams)
// 01 Mar 01  define PyObject_INIT() for Python 1.x (Dave Abrahams)

#ifdef _DEBUG
# ifndef BOOST_DEBUG_PYTHON
#  ifdef _MSC_VER  
    // VC8.0 will complain if system headers are #included both with
    // and without _DEBUG defined, so we have to #include all the
    // system headers used by pyconfig.h right here.
#   include <stddef.h>
#   include <stdarg.h>
#   include <stdio.h>
#   include <stdlib.h>
#   include <assert.h>
#   include <errno.h>
#   include <ctype.h>
#   include <wchar.h>
#   include <basetsd.h>
#   include <io.h>
#   include <limits.h>
#   include <float.h>
#   include <string.h>
#   include <math.h>
#   include <time.h>
#  endif
#  undef _DEBUG // Don't let Python force the debug library just because we're debugging.
#  define DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# endif
#endif

// pyconfig.h defines a macro with hypot name, what breaks libstdc++ math headers
// that Python.h tries to include afterwards.
#if defined(__MINGW32__)
# include <cmath>
# include <math.h>
#endif

# include <pyconfig.h>
# if defined(_SGI_COMPILER_VERSION) && _SGI_COMPILER_VERSION >= 740
#  undef _POSIX_C_SOURCE
#  undef _XOPEN_SOURCE
#  undef HAVE_STDINT_H // undo Python 2.5.1 define
# endif

//
// Python's LongObject.h helpfully #defines ULONGLONG_MAX for us,
// which confuses Boost's config
//
#include <limits.h>
#ifndef ULONG_MAX
# define BOOST_PYTHON_ULONG_MAX_UNDEFINED
#endif
#ifndef LONGLONG_MAX
# define BOOST_PYTHON_LONGLONG_MAX_UNDEFINED
#endif
#ifndef ULONGLONG_MAX
# define BOOST_PYTHON_ULONGLONG_MAX_UNDEFINED
#endif

//
// Get ahold of Python's version number
//
#include <patchlevel.h>

#if PY_MAJOR_VERSION<2 || PY_MAJOR_VERSION==2 && PY_MINOR_VERSION<2
#error Python 2.2 or higher is required for this version of Boost.Python.
#endif

//
// Some things we need in order to get Python.h to work with compilers other
// than MSVC on Win32
//
#if defined(_WIN32) || defined(__CYGWIN__)

# if defined(__GNUC__) && defined(__CYGWIN__)

#  if defined(__LP64__)
#   define SIZEOF_LONG 8
#  else
#   define SIZEOF_LONG 4
#  endif


#  if PY_MAJOR_VERSION < 2 || PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION <= 2

typedef int pid_t;

#   if defined(__LP64__)
#    define WORD_BIT 64
#   else
#    define WORD_BIT 32
#   endif
#   define hypot _hypot
#   include <stdio.h>

#   if PY_MAJOR_VERSION < 2
#    define HAVE_CLOCK
#    define HAVE_STRFTIME
#    define HAVE_STRERROR
#   endif

#   define NT_THREADS

#   ifndef NETSCAPE_PI
#    define USE_SOCKET
#   endif

#   ifdef USE_DL_IMPORT
#    define DL_IMPORT(RTYPE) __declspec(dllimport) RTYPE
#   endif

#   ifdef USE_DL_EXPORT
#    define DL_IMPORT(RTYPE) __declspec(dllexport) RTYPE
#    define DL_EXPORT(RTYPE) __declspec(dllexport) RTYPE
#   endif

#   define HAVE_LONG_LONG 1
#   define LONG_LONG long long
#  endif

# elif defined(__MWERKS__)

#  ifndef _MSC_VER
#   define PY_MSC_VER_DEFINED_FROM_WRAP_PYTHON_H 1
#   define _MSC_VER 900
#  endif

#  undef hypot // undo the evil #define left by Python.

# elif defined(__BORLANDC__) && !defined(__clang__)
#  undef HAVE_HYPOT
#  define HAVE_HYPOT 1
# endif

#endif // _WIN32

#if defined(__GNUC__)
# if defined(__has_warning)
#  define BOOST_PYTHON_GCC_HAS_WREGISTER __has_warning("-Wregister")
# else
#  define BOOST_PYTHON_GCC_HAS_WREGISTER __GNUC__ >= 7
# endif
#else
# define BOOST_PYTHON_GCC_HAS_WREGISTER 0
#endif

// Python.h header uses `register` keyword until Python 3.4
#if BOOST_PYTHON_GCC_HAS_WREGISTER
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wregister"
#elif defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 5033)  // 'register' is no longer a supported storage class
#endif

#if PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION == 2 && PY_MICRO_VERSION < 2
# include <boost/python/detail/python22_fixed.h>
#else
# include <Python.h>
#endif

#if BOOST_PYTHON_GCC_HAS_WREGISTER
# pragma GCC diagnostic pop
#elif defined(_MSC_VER)
# pragma warning(pop)
#endif
#undef BOOST_PYTHON_GCC_HAS_WREGISTER

#ifdef BOOST_PYTHON_ULONG_MAX_UNDEFINED
# undef ULONG_MAX
# undef BOOST_PYTHON_ULONG_MAX_UNDEFINED
#endif

#ifdef BOOST_PYTHON_LONGLONG_MAX_UNDEFINED
# undef LONGLONG_MAX
# undef BOOST_PYTHON_LONGLONG_MAX_UNDEFINED
#endif

#ifdef BOOST_PYTHON_ULONGLONG_MAX_UNDEFINED
# undef ULONGLONG_MAX
# undef BOOST_PYTHON_ULONGLONG_MAX_UNDEFINED
#endif

#ifdef PY_MSC_VER_DEFINED_FROM_WRAP_PYTHON_H
# undef _MSC_VER
#endif

#ifdef DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# undef DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# define _DEBUG
# ifdef _CRT_NOFORCE_MANIFEST_DEFINED_FROM_WRAP_PYTHON_H
#  undef _CRT_NOFORCE_MANIFEST_DEFINED_FROM_WRAP_PYTHON_H
#  undef _CRT_NOFORCE_MANIFEST
# endif
#endif

#if !defined(PY_MAJOR_VERSION) || PY_MAJOR_VERSION < 2
# define PyObject_INIT(op, typeobj) \
        ( (op)->ob_type = (typeobj), _Py_NewReference((PyObject *)(op)), (op) )
#endif

// Define Python 3 macros for Python 2.x
#if PY_VERSION_HEX < 0x02060000

# define Py_TYPE(o)    (((PyObject*)(o))->ob_type)
# define Py_REFCNT(o)  (((PyObject*)(o))->ob_refcnt)
# define Py_SIZE(o)    (((PyVarObject*)(o))->ob_size)

# define PyVarObject_HEAD_INIT(type, size) \
        PyObject_HEAD_INIT(type) size,
#endif

#if PY_VERSION_HEX < 0x030900A4
#  define Py_SET_TYPE(obj, type) ((Py_TYPE(obj) = (type)), (void)0)
#  define Py_SET_SIZE(obj, size) ((Py_SIZE(obj) = (size)), (void)0)
#endif


#ifdef __MWERKS__
# pragma warn_possunwant off
#elif _MSC_VER
# pragma warning(disable:4786)
#endif

#if defined(HAVE_LONG_LONG)
# if defined(PY_LONG_LONG)
#  define BOOST_PYTHON_LONG_LONG PY_LONG_LONG
# elif defined(LONG_LONG)
#  define BOOST_PYTHON_LONG_LONG LONG_LONG
# else
#  error "HAVE_LONG_LONG defined but not PY_LONG_LONG or LONG_LONG"
# endif
#endif

/* wrap_python.hpp
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
*/