//  endian/detail/intrinsic.hpp  -------------------------------------------------------//

//  Copyright (C) 2012 David Stone
//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_INTRINSIC_HPP
#define BOOST_ENDIAN_INTRINSIC_HPP

//  Allow user to force BOOST_ENDIAN_NO_INTRINSICS in case they aren't available for a
//  particular platform/compiler combination. Please report such platform/compiler
//  combinations to the Boost mailing list.
#ifndef BOOST_ENDIAN_NO_INTRINSICS

#ifndef __has_builtin         // Optional of course
  #define __has_builtin(x) 0  // Compatibility with non-clang compilers
#endif

#if defined(_MSC_VER) && ( !defined(__clang__) || defined(__c2__) )
//  Microsoft documents these as being compatible since Windows 95 and specifically
//  lists runtime library support since Visual Studio 2003 (aka 7.1).
//  Clang/c2 uses the Microsoft rather than GCC intrinsics, so we check for
//  defined(_MSC_VER) before defined(__clang__)
# define BOOST_ENDIAN_INTRINSIC_MSG "cstdlib _byteswap_ushort, etc."
# include <cstdlib>
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x) _byteswap_ushort(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x) _byteswap_ulong(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x) _byteswap_uint64(x)

//  GCC and Clang recent versions provide intrinsic byte swaps via builtins
#elif (defined(__clang__) && __has_builtin(__builtin_bswap32) && __has_builtin(__builtin_bswap64)) \
  || (defined(__GNUC__ ) && \
  (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)))
# define BOOST_ENDIAN_INTRINSIC_MSG "__builtin_bswap16, etc."
// prior to 4.8, gcc did not provide __builtin_bswap16 on some platforms so we emulate it
// see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=52624
// Clang has a similar problem, but their feature test macros make it easier to detect
# if (defined(__clang__) && __has_builtin(__builtin_bswap16)) \
  || (defined(__GNUC__) &&(__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)))
#   define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x) __builtin_bswap16(x)
# else
#   define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x) __builtin_bswap32((x) << 16)
# endif
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x) __builtin_bswap32(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x) __builtin_bswap64(x)

# define BOOST_ENDIAN_CONSTEXPR_INTRINSICS

//  Linux systems provide the byteswap.h header, with
#elif defined(__linux__)
//  don't check for obsolete forms defined(linux) and defined(__linux) on the theory that
//  compilers that predefine only these are so old that byteswap.h probably isn't present.
# define BOOST_ENDIAN_INTRINSIC_MSG "byteswap.h bswap_16, etc."
# include <byteswap.h>
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x) bswap_16(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x) bswap_32(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x) bswap_64(x)

#else
# define BOOST_ENDIAN_NO_INTRINSICS
# define BOOST_ENDIAN_INTRINSIC_MSG "no byte swap intrinsics"
#endif

#elif !defined(BOOST_ENDIAN_INTRINSIC_MSG)
# define BOOST_ENDIAN_INTRINSIC_MSG "no byte swap intrinsics"
#endif  // BOOST_ENDIAN_NO_INTRINSICS
#endif  // BOOST_ENDIAN_INTRINSIC_HPP

/* intrinsic.hpp
LX7XyKpcyIE7urfE9RUWoqxUoWxZbY4oO8d1/NOytuoUlFXW5oYy6U0yrTSYZ8RW4uzcsNWx9OWNz8hmzYI/RpR9/+wcUdbz7p6/sbZsRtnXz84NZdKr4uXHnx9rxNaQs3PDVsfThSc9yFxkJrD2GTmi7Kri373Jqx0zyr41IzeUSc3n1dIZXzJia+yM3LDVURB/8acsBc0Etmd6jijbf+s/3pO1NaWgbMX03FAmvcCezbtkthFbk6bnhq2Oq6uPXSWbFU4hsNcifaOMF3aTJ77Ta+ZHh0LXbZG+0cXTz9K35l0la4pSTZrb0IxI36gipLPoOuq8718s0ORSaBod6RtNrL4U+V9Ss2FIoehwhaLfnJUDioKvbL+NpbwZRUvPyh5F0n3rp7997itG7Ew6K3vsdES/cv9b2vLHiKI3zswBRfXbHtjOyqsZRZvOzB5F0plt55L1XiN2zj8ze+x0vHPMxld4ojET0BFn5oCiFb5/PMWiyYyi334jexRJ176CT7Q6jNi5+hvZY6dj4q6nnuX1j5mAAt/IAUUv3fTHl5nvzSh6qyZ7FEkdaP+iH33KiJ17arLHTscFZ971EEtHMwHNrkmLovJ9u4bDE8vs4FGfftNsxB2iEPSpmrQI8op63NQpdtz/Xu+xUwRmhinM/GlaWsx4RBXlPKv9ZNyaO82aJvsxrpmWXtMU9XhZQk/ccIOaOKoVakYr1FRPyxY1cqny4PSzLzBiZei0bLHScf1jRddq3GBETdcZWaNm8Zv/4LVuCmouOyNr1Ow+Z/kKlqdm1Hz2jBxQgyrD15dsusSImtemZo2avS+XH2C1z4ya26dmjZrSKfZbWXU3o2bm1GxRo5yCRzq/ZsTKx6dmi5WOZUum7WPd08xLe8JZo+bENz7/a17+m1HTFs4WNdLUf/+Tvz/WiJVQOFusdFy358oEy08zwdjClqjRHYfd2fkau3X35Gx9jQ0Oytn6GhsclLP1NS6P3/nioK/x4G/wN/gb/A3+Bn8H8bP0Dx8/WvmHjz4ig3/4/i+a/cMTr8X68A8fW2D2D3+n1OAffnEsZukfXnvUIfEPt4yH+blS1d+jy0R/OdRivW1+EfR0PPYUXR6ojfUj2A3+JApHCL5fUYI5PsEdBMUztv5ArHerm3t37d9ivXwTbQD7tXxsvDeHyJbm0BjfGcWuiSFyzRKPdK+uR1zbvLAQ/njy5s+kP2Xq0tfQzqDd0Zy8eLfdiVeeoyLbCVBxY3wIY906gsI7feaXyBsvBC5wjirMrGLzhmKn5tsYVmSABWJurVxphx1Bcx5xYu0B8j/k/LF/B4tt2QZqzvKnuYKGP5YMDcSXNKOX6Rj8JH13Tqe8cnlV0C47svUMGWXvHG6dnqtU5jpa5joJcuXgsWoZ7+T2kdzSQJtNu5a8ZPlzACd8TcBUjFXcMFkLdQ3XvDuQJMM0fNCgDVOKbbKmfEwX0aXs5EN5uB3+azNWiWq5RYVervDrUCE7SoaTjpJhTtTjuIuqAN1mFAcQeQ4TrRywsWPr3v1avxeUYhOIJCnnUyqqg7ER7P55sgRyYxTlUVxRpGvqFtLd4skKRXiTtPMQk2BOPzM9xMT9zyVKPq0YxfJ4l4x+GKKAaIrFnIR1FdJ0IryUtPSClU1F0Kc9Tq96FVuP9KiSeLPTi5uU2WR25ZK5rI/M7Q5JJmI0qh1+c0IgWR0dWM2iK+X4wWwyu3LJXJY5M3fFjvm4K1pCQOMJDNaL9YLkORqDprT0BDSiXSOgrcFhRZZFSmURt1WRUmwaPqN4Rhbe7o736mk4YYURsPgPsV5yAaekVchrqw8z5C7FjIvcxjSu4eTUGvyxr0ENyVEMOvxkQaU=
*/