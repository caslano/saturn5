//
// detail/push_options.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// No header guard

#if defined(__COMO__)

// Comeau C++

#elif defined(__DMC__)

// Digital Mars C++

#elif defined(__INTEL_COMPILER) || defined(__ICL) \
  || defined(__ICC) || defined(__ECC)

// Intel C++

# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  if !defined(BOOST_ASIO_DISABLE_VISIBILITY)
#   pragma GCC visibility push (default)
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)

#elif defined(__clang__)

// Clang

# if defined(__OBJC__)
#  if !defined(__APPLE_CC__) || (__APPLE_CC__ <= 1)
#   if !defined(BOOST_ASIO_DISABLE_OBJC_WORKAROUND)
#    if !defined(Protocol) && !defined(id)
#     define Protocol cpp_Protocol
#     define id cpp_id
#     define BOOST_ASIO_OBJC_WORKAROUND
#    endif
#   endif
#  endif
# endif

# if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#  if !defined(BOOST_ASIO_DISABLE_VISIBILITY)
#   pragma GCC visibility push (default)
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

#elif defined(__GNUC__)

// GNU C++

# if defined(__MINGW32__) || defined(__CYGWIN__)
#  pragma pack (push, 8)
# endif

# if defined(__OBJC__)
#  if !defined(__APPLE_CC__) || (__APPLE_CC__ <= 1)
#   if !defined(BOOST_ASIO_DISABLE_OBJC_WORKAROUND)
#    if !defined(Protocol) && !defined(id)
#     define Protocol cpp_Protocol
#     define id cpp_id
#     define BOOST_ASIO_OBJC_WORKAROUND
#    endif
#   endif
#  endif
# endif

# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  if !defined(BOOST_ASIO_DISABLE_VISIBILITY)
#   pragma GCC visibility push (default)
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
# if (__GNUC__ >= 7)
#  pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
# endif // (__GNUC__ >= 7)

#elif defined(__KCC)

// Kai C++

#elif defined(__sgi)

// SGI MIPSpro C++

#elif defined(__DECCXX)

// Compaq Tru64 Unix cxx

#elif defined(__ghs)

// Greenhills C++

#elif defined(__BORLANDC__)

// Borland C++

# pragma option push -a8 -b -Ve- -Vx- -w-inl -vi-
# pragma nopushoptwarn
# pragma nopackwarning
# if !defined(__MT__)
#  error Multithreaded RTL must be selected.
# endif // !defined(__MT__)

#elif defined(__MWERKS__)

// Metrowerks CodeWarrior

#elif defined(__SUNPRO_CC)

// Sun Workshop Compiler C++

#elif defined(__HP_aCC)

// HP aCC

#elif defined(__MRC__) || defined(__SC__)

// MPW MrCpp or SCpp

#elif defined(__IBMCPP__)

// IBM Visual Age

#elif defined(_MSC_VER)

// Microsoft Visual C++
//
// Must remain the last #elif since some other vendors (Metrowerks, for example)
// also #define _MSC_VER

# pragma warning (disable:4103)
# pragma warning (push)
# pragma warning (disable:4127)
# pragma warning (disable:4180)
# pragma warning (disable:4244)
# pragma warning (disable:4355)
# pragma warning (disable:4510)
# pragma warning (disable:4512)
# pragma warning (disable:4610)
# pragma warning (disable:4675)
# if (_MSC_VER < 1600)
// Visual Studio 2008 generates spurious warnings about unused parameters.
#  pragma warning (disable:4100)
# endif // (_MSC_VER < 1600)
# if defined(_M_IX86) && defined(_Wp64)
// The /Wp64 option is broken. If you want to check 64 bit portability, use a
// 64 bit compiler!
#  pragma warning (disable:4311)
#  pragma warning (disable:4312)
# endif // defined(_M_IX86) && defined(_Wp64)
# pragma pack (push, 8)
// Note that if the /Og optimisation flag is enabled with MSVC6, the compiler
// has a tendency to incorrectly optimise away some calls to member template
// functions, even though those functions contain code that should not be
// optimised away! Therefore we will always disable this optimisation option
// for the MSVC6 compiler.
# if (_MSC_VER < 1300)
#  pragma optimize ("g", off)
# endif
# if !defined(_MT)
#  error Multithreaded RTL must be selected.
# endif // !defined(_MT)

# if defined(__cplusplus_cli) || defined(__cplusplus_winrt)
#  if !defined(BOOST_ASIO_DISABLE_CLR_WORKAROUND)
#   if !defined(generic)
#    define generic cpp_generic
#    define BOOST_ASIO_CLR_WORKAROUND
#   endif
#  endif
# endif

#endif

/* push_options.hpp
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
*/