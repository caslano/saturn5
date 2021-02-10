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
wZtdjUfdLEUCOyNk5E/89+Dg5VGv+UKtyEVjT/RCIVZUQpy6Iuk1ojzv45/kuN0XSb1IpozVew+dLT4U0jHY6e9G8ea3LDS73Z3d7Z2dw31aaLaIOwzUrl3ZO+I8Q9qqMoFXENbiN6J8Z1qBYYrzUH/HEKTD9Hd2OUzMpIl5MSznMIsmTjoHRawg4HuzL5CW9y8RnYUdTcoZzx9d9/HrX/7f/62K+Fo0hGFWCcGsSo0fc6HhDnyNcjVihjmAoDaDv0UrwbxfK/ge8eGmqHFbGhPlCqmx1HDYlGjiDnXrICi8XIskxNglfGo8WIYoirW8W5c7CJxs3ULr9dpUDBCJZgwz9YwlLYvaZ+sjwIynDFEhw6U3UrsPROhTp/ez4gp3kfnyX1QBX7D87JiM0R04l0tst1pRNjuBBwe4qQZIspqEYnpgkIksY3ilir6cvWB4J3smVgAPvsY8tVBry9+Cs2A8n4jIOHGJA86X68tJOcpqtRcDn8KUkGTCKxbG3WNIjtU4Zk6AEhHY4qdmnXU4KMgLRPPF+TuRleUIJPKhur9Hn5YuuJ3EmELC84r1IIrsP3cDQWvPWnvTFkPygSh04CY17Unjx0aKVrdK6x0hW6zyFdpkKqbNmrIyJkI0bRlbad7krKNN8WmDPvgr
*/