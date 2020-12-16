//  boost/filesystem/v3/config.hpp  ----------------------------------------------------//

//  Copyright Beman Dawes 2003

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM3_CONFIG_HPP
#define BOOST_FILESYSTEM3_CONFIG_HPP

# if defined(BOOST_FILESYSTEM_VERSION) && BOOST_FILESYSTEM_VERSION != 3
#   error Compiling Filesystem version 3 file with BOOST_FILESYSTEM_VERSION defined != 3
# endif

# if !defined(BOOST_FILESYSTEM_VERSION)
#   define BOOST_FILESYSTEM_VERSION 3
# endif

#define BOOST_FILESYSTEM_I18N  // aid users wishing to compile several versions

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

#include <boost/config.hpp>
#include <boost/system/api_config.hpp>  // for BOOST_POSIX_API or BOOST_WINDOWS_API
#include <boost/detail/workaround.hpp>

//  BOOST_FILESYSTEM_DEPRECATED needed for source compiles -----------------------------//

# ifdef BOOST_FILESYSTEM_SOURCE
#   define BOOST_FILESYSTEM_DEPRECATED
#   undef BOOST_FILESYSTEM_NO_DEPRECATED   // fixes #9454, src bld fails if NO_DEP defined
# endif

//  throw an exception  ----------------------------------------------------------------//
//
//  Exceptions were originally thrown via boost::throw_exception().
//  As throw_exception() became more complex, it caused user error reporting
//  to be harder to interpret, since the exception reported became much more complex.
//  The immediate fix was to throw directly, wrapped in a macro to make any later change
//  easier.

#define BOOST_FILESYSTEM_THROW(EX) throw EX

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

//  This header implements separate compilation features as described in
//  http://www.boost.org/more/separate_compilation.html

//  normalize macros  ------------------------------------------------------------------//

#if !defined(BOOST_FILESYSTEM_DYN_LINK) && !defined(BOOST_FILESYSTEM_STATIC_LINK) \
  && !defined(BOOST_ALL_DYN_LINK) && !defined(BOOST_ALL_STATIC_LINK)
# define BOOST_FILESYSTEM_STATIC_LINK
#endif

#if defined(BOOST_ALL_DYN_LINK) && !defined(BOOST_FILESYSTEM_DYN_LINK)
# define BOOST_FILESYSTEM_DYN_LINK
#elif defined(BOOST_ALL_STATIC_LINK) && !defined(BOOST_FILESYSTEM_STATIC_LINK)
# define BOOST_FILESYSTEM_STATIC_LINK
#endif

#if defined(BOOST_FILESYSTEM_DYN_LINK) && defined(BOOST_FILESYSTEM_STATIC_LINK)
# error Must not define both BOOST_FILESYSTEM_DYN_LINK and BOOST_FILESYSTEM_STATIC_LINK
#endif

#if defined(BOOST_ALL_NO_LIB) && !defined(BOOST_FILESYSTEM_NO_LIB)
# define BOOST_FILESYSTEM_NO_LIB
#endif

//  enable dynamic linking  ------------------------------------------------------------//

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_FILESYSTEM_DYN_LINK)
# if defined(BOOST_FILESYSTEM_SOURCE)
#   define BOOST_FILESYSTEM_DECL BOOST_SYMBOL_EXPORT
# else
#   define BOOST_FILESYSTEM_DECL BOOST_SYMBOL_IMPORT
# endif
#else
# define BOOST_FILESYSTEM_DECL
#endif

//  enable automatic library variant selection  ----------------------------------------//

#if !defined(BOOST_FILESYSTEM_SOURCE) && !defined(BOOST_ALL_NO_LIB) \
  && !defined(BOOST_FILESYSTEM_NO_LIB)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_filesystem
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_FILESYSTEM_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // BOOST_FILESYSTEM3_CONFIG_HPP

/* config.hpp
CL8/pCTuCNw6P658mvEDS7jleChhpGfb1z5HKBN4/MTXyOPbIJU3eCkB3C8A7mIAyzFVsvP6Z9viqMw/oH332uhzbLGp32db6Oxw7HgozBEaFvb0hC9rPIfB/2FPZ/i/ttG9xtPua9kJv56c7Qjn7N/D+8A7ObtVhqnx70V5L+3h5T2wB8u7bw+Wdzf8D+GM1nhu2SPL68nKWyfK2xBsvTwqKoeKqvOSYtsJxsCE3Uilo7O+E2N4CbBWZHshO19ke1l2XyXbDdkeke1m2clKtguyP/iKsnlvfjjFzE6H7G0iO51lNyrZPsjeKLJ9LPv3U7Lb1MV27X+KtR9mQHfwkOVNngZ066nY7Z0gawgWu8adBl/3wJrJWz5AgfJCVroJtQOhiAEeBcoNWe9/KaHuQSjiw1ulJpQL/e9NqJUIReyoV6DSIet6E+o0hCKuXKNA+SBrEYc6YE61Qb7ckIz6X4MwKj74NDcqgmCUTHekY07lMSdQ9B6EdAe7D1kuxehyh+mZOXub51logEMJdLzN8zhPMUZ8H4OF8z746VTJdWLuTFiX330Xozhv37kQsRYgXaoNiuydl4Isj+mLwF5jnLeBlPOKrSvdK1gtx07C8nwrd9MjSygXZg47ClfKwydmM5NUHuTwqbgekuTL4OztlhJ2s2odOBi7HDQ/V5cQ2nskmARcC49D1bTWcIUbfI+uLEHA2r2Z1cMwNdaoJqZV50nQ+jTAn7tmLcsiUFR5mfq7M0JeXJeiF5ebN+3K6yLcFFU5d83KDESTWpcW6N2BOeu4OEseLNi4UkxyoWRc37Qfx1pP1v5lmSps2SYoD7DXMlBj8dWRGAgvkj+hkvj8cXD+VEwg/lwm+XOMyZ8nsFuIP4XUaJFI/OkmQXkHpllYA1+qkC9VsstrfkNdXiW6XGtPtEdp2DMMvPNRdGLtovkPi6ziSyRDt2emfY5b0leTsA0gcV5GqV99hqkfUKoresEm7DyT2tiJGrVQRxjMdTiYQ16mJm2FudEeyNwHZIyIk4d66F/KK4r22o0ALgf+/tsjqJd5cdIANOwbVwBm7V5XNUviJzSzIQQs+sdt9GAVZyLtm18GgXHsqfDVtaSPnFFdJOH39uKMIio0O4YArHOJx7gHgs9vAp7KVhkXX8mOcUoQGRcAZv+EzRmv5ib/fDU3AfmIiapVj4kF9fQn5SlNATss2oS7DFNTYzk34BCCrnGj9xENL8p4+2iycb1QJ0NBYU+829gWSyBWB8+W1njGfQJiUmL+ecwe+NAmoakFeFCFKudSHin5LwiQVQcA8l4rLLTr+X34WKN6RZZ5jPKrNzUkmf/uJia3BygAf7F26QOwg4iBNSm00qnU6dz5okqnHSV+9xAl0q8TcV5g9jKvaAl2wEGzp5XYxDsrxwV0Yb3o/TP+IrfTAORc+nh+JW5m8G8Zs0Pht2h6eCUkkzkFvtbQV/ZsVpULVUBIR/NEgEXqxgIcj1GAXT53UTXcvJbebUAYLAqHy5+2solb7jqwiUt+OPHtL14nVOXyOtHW6sdlWz/j51C53JBagT+y8Af1DqbgyikkRSn9iEDrbhfkZ1TZ5qMBKgNdrNxVwaGbzRzYHtGfWeA4RY5Tp2mbb0/TaaXpkhKfTtM2356my0ozSeQk6TRt8+1pJllpuqX8qtO0zben6bbS9Igcj07TNt+epsdKM1nkJOs0bfPtaSZbaaaInBSdpm2+Pc0Uoknir/T7oMtwbMFL863L76LIpL5HgADIbxtAzOxUkM7fEHHng4aaAj/rnXw8+R4pzaja+XZwznYoshGKgdUZYN493IRx6TDJCJMFME8qMEk6jAdhcgHmRgXGrcO4mUwIML8=
*/