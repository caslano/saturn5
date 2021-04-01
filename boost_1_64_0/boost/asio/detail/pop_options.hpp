//
// detail/pop_options.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
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

#endif

/* pop_options.hpp
ZrWQgqZCzTz7qO/0t7wI8Oc1Qgl2cdROhxxTXrp1OF8zYwxY0MxM4KQeRJt5s2LZYVsM3nDg0mAgnI+Zp9S7IS3u6tGGw5/RDWu783pQRhW4LpsowuIJ6xsvB9yOP/o7RIc7OUzeoJsnwyjU2Ax4+tWLtnJCJZpLjwurFNhnQ5v3J0hgHo4f6mI82bnwfX0qmb3JCh9JLrRfJjyYA794MKx1/wkp3B3NBa7Ufi8ptOG/mM5y4i4K78gB7mqDr66h+Vj5TcrZxB9CmPgT1BECiTkTjCNz1kmrM/a0o7hiOwd1x//iVH9UrSNjtiIpHGsch6opnb5PRfQDCvhuDtq1teruvq90+7M0YqtJW1QBZF4Uqr0zC2wtjJux9kKYBcpS+BUruo4ioLo8IiY2rmEnNDn75sZCB9+mZStu98VFBjZj6FYFajA4FL1euOcRHT0VXEht/sjca1Lgi7oqLgu9j5cO3WvQvWT2VZ0Xvip9VLNG2kLQPmYwDJVnwKjgRFfRo0edVBNQbkV4vYZq+UMT+NsFGcSherHb3B3U+cXjRhgnQq2NQJKaMgPAJQ==
*/