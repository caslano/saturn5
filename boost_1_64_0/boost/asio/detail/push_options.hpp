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
SvOEr36teeCr32gW+Ophzabx1W8jm9hXj2gb6yu8s78jJmv/H3V/23qM/ZKkp9eRPwam37nHoeGd47lYaNO9K38AD9+VP5Ier0l/Erp7h6D/yekIH3n9M+n0i5XsnqK/9bZ+7I0k3W3rJ9unSWOn0osJ22e03uiQ7bNK0+cpPxfqJlr7HeL5gg2YraVmbLsscV7yCwneQLgvxszNibxErDy0oHfZSGnpiLfO/K8Bs3sA/ubr7h36O+uYd6kM9i4seWn8R8xdGv8ZM7dO/V8ek/7j31rn5JH+H0+XuYmXPZ3r2ZQ6v2mtdQwv99rOlcJaG1p5wPmb9FeITm2nLe9Xiu7Sv47ScmX7Kuh4V8h2XdZ0p0u260Gv8/o4sl3faf4aoQ2sbmpo/3zWNoSmy2Mj1oJ2g331amapTpbalY2n527/wiZsozth0l+jdD3eeK3T0SggLZtCjztRfm4z5tE5Y69zum+/OevSiSL+LZSu5xdeDz3uSNmPW0acKhU9uxWzVEdKz74h4Hq+duuAoToQ28ZnaLSZvTFkxsemnCg924YMibG+3i7gXK7maYS9fcCpNuLZHVKsqPFdzuuOAdfnEO+kmD5T801az2Pf7xzwGcr3u3gs9v2uAde+3y1i4vvdA6Z9/+aAad/v4bHY93t6PPb9XgHXvt/bY7Hv9wk4fE/93r7MXHu1n/yN94bbkBnQ9dn1PVpT54jPZN0fEOCZ/S0L3v9ZVg/e/wOcnn7/D7Q8eP9nsx6dkXSQ6F7+Dmad3QrbQ6CJO9n2LU4/MbO2b2UtOgfobdD1OUBvZw3FwM8fypoaRLDeq3X2NPl4jtalBIj1EVtk9naZ85D7Ky3TpeX5BIfXD2a2I/MmSjunxzrOCOLPr/w2cZrnMufJI6RtHrR63hpdXRxoC9v50PW4aQCa7oMOgzaeufgcO9yyidZodcIedYh9mcx4CQu0hdAms/a4PddhkDVXtxfx33Q8LyeY4xqCnmdxvo8AQ/lROMNGK/X1u1/oB/RwOGXWg1/H/MwIs7KMJlhfDF1GE6wv0bo6z+dIT8+d/VLoMkrgNC0LdfOWuPMpFUNl5P2ZVqcH2PZoT5Nzg48hPXxLsGdTsROR34rVgrP6jyV9qHe419Ta0nBZ311SDRnuLhkNdL2Wr8bs8CBEYvWYuTY8i5iMIccsk+EOmkPm4yGXF5PCXk48pPxsI8nkN8BxxOncHKy/93+DrbCc99wDMpsQZvo4yzjcSceCYOH7JvjwosVD+KpEY8BWpFfqjbzWbkw2mlW0UVPaRlZuULjHe2zSjcPaStf7I3Ol63FbR+l63NbVOhayj1VrZpaD+cqQYzRrDHhuK+JmfX/GbFXE8iyDP1cHjI4wppaQ+YkhN7NCjZxWhxJ/V8gl2cRPini3vTKjekH85On4FD//7iSngRPl7ZSQ17Nxe2fDqSHLavrzHNmclrBZIVY89xXYcI2Vcd17A86ux3xXyEznZraUtCYb1Qn2Jea7IruWeZ/QveWN4tDAVnuSffKBwJaKs/hssBbH+cGQd9oNP0bMeWm75VU66imzfcFkd8K2MR/WdjiQtWXP41RMn2H70UA386iq6LDfNLAJ68bHp+PY5/cJxd20pS5k+PaTKbuwoJHX05UtlyONBilPZygWuwpzXNomj9+nMwMe5vmsJJf34ewkl7nfTwdcmgn2xTkhT9czngcLbLnZYHYuM3NxBYZt1JhxuZwXsvCrK3x1ftKu0bR73y+IufxIQRgXxjb4QcFhXJTiQV9+cWhDFZnz8tmI5cm8XJK0k7x8LuZRXi5N2khePh9zlxc3ryY2+DTE+uWi16pNCpTyfoXT3dSl88uVjulPPDiP1DE=
*/