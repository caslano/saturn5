//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2019 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CONFIG_HPP_INCLUDED
#define BOOST_NOWIDE_CONFIG_HPP_INCLUDED

/// @file

#include <boost/config.hpp>
#include <boost/nowide/replacement.hpp>
#include <boost/version.hpp>

//! @cond Doxygen_Suppress

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_NOWIDE_DYN_LINK)
#ifdef BOOST_NOWIDE_SOURCE
#define BOOST_NOWIDE_DECL BOOST_SYMBOL_EXPORT
#else
#define BOOST_NOWIDE_DECL BOOST_SYMBOL_IMPORT
#endif // BOOST_NOWIDE_SOURCE
#else
#define BOOST_NOWIDE_DECL
#endif // BOOST_NOWIDE_DYN_LINK

//
// Automatically link to the correct build variant where possible.
//
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_NOWIDE_NO_LIB) && !defined(BOOST_NOWIDE_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_nowide
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_NOWIDE_DYN_LINK)
#define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif // auto-linking disabled

//! @endcond

/// @def BOOST_NOWIDE_USE_WCHAR_OVERLOADS
/// @brief Whether to use the wchar_t* overloads in fstream/filebuf
/// Enabled on Windows and Cygwin as the latter may use wchar_t in filesystem::path
#if defined(BOOST_WINDOWS) || defined(__CYGWIN__)
#define BOOST_NOWIDE_USE_WCHAR_OVERLOADS 1
#else
#define BOOST_NOWIDE_USE_WCHAR_OVERLOADS 0
#endif

/// @def BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT
/// @brief Define to 1 to use internal class from filebuf.hpp
///
/// - On Non-Windows platforms: Define to 1 to use the same class from header <filebuf.hpp>
///   that is used on Windows.
/// - On Windows: No effect, always overwritten to 1
///
/// Affects boost::nowide::basic_filebuf,
/// boost::nowide::basic_ofstream, boost::nowide::basic_ifstream, boost::nowide::basic_fstream
#if defined(BOOST_WINDOWS) || BOOST_NOWIDE_USE_WCHAR_OVERLOADS
#ifdef BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT
#undef BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT
#endif
#define BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT 1
#elif !defined(BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT)
#define BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT 0
#endif

//! @cond Doxygen_Suppress

#if BOOST_VERSION < 106500 && defined(BOOST_GCC) && __GNUC__ >= 7
#define BOOST_NOWIDE_FALLTHROUGH __attribute__((fallthrough))
#else
#define BOOST_NOWIDE_FALLTHROUGH BOOST_FALLTHROUGH
#endif

// MSVC 2015 (1900) has reasonable C++11 support (especially auto-generated move ctors)
// libstdc++ < 5 does not support movable streams
#if(__cplusplus >= 201103L || (defined(BOOST_MSVC) && BOOST_MSVC >= 1900)) \
  && (!defined(BOOST_LIBSTDCXX_VERSION) || BOOST_LIBSTDCXX_VERSION >= 50000)
#define BOOST_NOWIDE_CXX11 1
#else
#define BOOST_NOWIDE_CXX11 0
#endif

//! @endcond

namespace boost {
///
/// \brief This namespace includes implementations of the standard library functions and
/// classes such that they accept UTF-8 strings on Windows.
/// On other platforms (i.e. not on Windows) those functions and classes are just aliases
/// of the corresponding ones from the std namespace or behave like them.
///
namespace nowide {}
} // namespace boost

#endif // boost/nowide/config.hpp

/* config.hpp
40F9GGA0OAWV8M88C9/PenoTsUoe3EW7lFRkhtkaYguet0BOVEkpVYBtLNK28wC/7pSdUsQxyXegHsWc8DaGZXSumRHvZnn24yTMOh9sh3UB+B6m+yMSNA/N4Gs3mNDI7dlHUQrlPGcvuZGFf7a6frSof0kpJ6WK83BKnnBvOx+82K1uKRvFVpCpHHQAPnOLHHmS6ERlZSSFYni8VvKdt9jnHKMDYV39KqLboSU520SviiT269CmIKUKyVSMuLcVZUHYvDIZz1Hfb4AJIi/n0dXHz6ioe4OWqKdHPo9u2AMluQvSJzcaxIV0asub8Kat6lj4JJEtPXBWYAZhyPIud0q15KuwKYt/w+OjV3AADs33uw1b7C+IpH7Ntng7t9gWQ6r4o3Ngaivd/l6Sb71Ncv5lLx1LJm6MakPBIUaHzmBUbcMGHuCB7RBwJaAU0u8x1ef4Y4HmzFTs7SMA9dbb2w+O9/iletqmVSahB5EUKYC59+DXudFbReruTcqvxCtVhtlYJ4bvX6BEy0m2B4guJ1BcD1RrpCTX5cgK5XXc6An0X0OQtYboWV998sx7JLWcbgBIK36JlALXY3A5gIx+XeAYhq30nbIjgmLMDQlEXiulbAVIUCqoZD+wpVLKfikFkMsO2DnKB6QVryRY+UZ5lewUH0xKDLalbbVTeRpfC4yxuVYjmOQ4f7H78GPuwMx6IctPFuuS6Ml4NIGW
*/