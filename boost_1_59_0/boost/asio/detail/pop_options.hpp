//
// detail/pop_options.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#   pragma GCC visibility pop
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)

#elif defined(__clang__)

// Clang

# if defined(__OBJC__)
#  if !defined(__APPLE_CC__) || (__APPLE_CC__ <= 1)
#   if defined(BOOST_ASIO_OBJC_WORKAROUND)
#    undef Protocol
#    undef id
#    undef BOOST_ASIO_OBJC_WORKAROUND
#   endif
#  endif
# endif

# if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#  if !defined(BOOST_ASIO_DISABLE_VISIBILITY)
#   pragma GCC visibility pop
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)

# pragma GCC diagnostic pop

# pragma pop_macro ("emit")
# pragma pop_macro ("signal")
# pragma pop_macro ("slot")

#elif defined(__GNUC__)

// GNU C++

# if defined(__MINGW32__) || defined(__CYGWIN__)
#  pragma pack (pop)
# endif

# if defined(__OBJC__)
#  if !defined(__APPLE_CC__) || (__APPLE_CC__ <= 1)
#   if defined(BOOST_ASIO_OBJC_WORKAROUND)
#    undef Protocol
#    undef id
#    undef BOOST_ASIO_OBJC_WORKAROUND
#   endif
#  endif
# endif

# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  if !defined(BOOST_ASIO_DISABLE_VISIBILITY)
#   pragma GCC visibility pop
#  endif // !defined(BOOST_ASIO_DISABLE_VISIBILITY)
# endif // (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)

# pragma GCC diagnostic pop

# pragma pop_macro ("emit")
# pragma pop_macro ("signal")
# pragma pop_macro ("slot")

#elif defined(__KCC)

// Kai C++

#elif defined(__sgi)

// SGI MIPSpro C++

#elif defined(__DECCXX)

// Compaq Tru64 Unix cxx

#elif defined(__ghs)

// Greenhills C++

#elif defined(__BORLANDC__) && !defined(__clang__)

// Borland C++

# pragma option pop
# pragma nopushoptwarn
# pragma nopackwarning

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

# pragma warning (pop)
# pragma pack (pop)

# if defined(__cplusplus_cli) || defined(__cplusplus_winrt)
#  if defined(BOOST_ASIO_CLR_WORKAROUND)
#   undef generic
#   undef BOOST_ASIO_CLR_WORKAROUND
#  endif
# endif

# pragma pop_macro ("emit")
# pragma pop_macro ("signal")
# pragma pop_macro ("slot")

#endif

/* pop_options.hpp
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
*/