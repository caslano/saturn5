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
4DbsL35WA1juR7tVlhvNw+ziHyG7/fMTRrOr0Wh+H45LjhvN5XDIcHwIx5C/GPFTs7myIy5Pxvyw0mU6lzXOqZTPpPSPhWbhZV22bQG77yJKCJkqpeAmbDU6hks3TnEMy7bPZLn8EWz1yvrj0o26RZjVNs4VveTfx4E3GcOt0aEcOPLek3yI1Zvx78Ht+HffLfh3xy76XUp/d9PfIh/KXFfAqnJv85HFcQXeiZqKLPht+PPV9ZwFj8LdwI0wkdb/HXe5d+V6ed8MhLN1Lf2tpHr3+Ejvgwo5hAnkvWEY2ozKfMT9beInqg5TC1bhS+6d8HdjrGvrUgKUT39L6O+jPmSOn6e/W3ycRV6CJu6t+E66dBDr1rnoSti0RR/G0L9cUR3C0LsR+t3VscLLm4zNcL/GY3DRPalDLzg/o4mMYGRqXcX0S4XKLxDxHYojzz7I7UbcZNnYJ7/u4F/yKb9Odq6gkhMdV0gHseM6x2hLdUkq8ESwqPZ24Cpd2+PD4g1OBMrZB2gL8NDbtJoxQQLAJ1iwtLAJbC1UIlONbpviTtO7eMs4dmEVbEU8wvqcBBJRVT660iRPFJwLIrjd0D0HfqRsRZSXR7vozDvlvUTqMAIzRIo/gtURsyZdfWbitzhm5R2IGWXijrJ/GJEQREFT0SQB7c00EFIE52yDBgbkMZpqvUbKeRt5SS2laSPGQmWC838oxRAhQ3BuFdBR
*/