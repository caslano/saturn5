//  boost/filesystem/v3/config.hpp  ----------------------------------------------------//

//  Copyright Beman Dawes 2003
//  Copyright Andrey Semashev 2021

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM_CONFIG_HPP
#define BOOST_FILESYSTEM_CONFIG_HPP

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

#include <boost/config.hpp>
#include <boost/system/api_config.hpp> // for BOOST_POSIX_API or BOOST_WINDOWS_API
#include <boost/detail/workaround.hpp>

#if defined(BOOST_FILESYSTEM_VERSION) && BOOST_FILESYSTEM_VERSION != 3 && BOOST_FILESYSTEM_VERSION != 4
#error Compiling Boost.Filesystem file with BOOST_FILESYSTEM_VERSION defined != 3 or 4
#endif

#if defined(BOOST_FILESYSTEM_SOURCE)
#undef BOOST_FILESYSTEM_VERSION
#define BOOST_FILESYSTEM_VERSION 4
#elif !defined(BOOST_FILESYSTEM_VERSION)
#define BOOST_FILESYSTEM_VERSION 3
#endif

#define BOOST_FILESYSTEM_VERSIONED_SYM(sym) BOOST_JOIN(sym, BOOST_JOIN(_v, BOOST_FILESYSTEM_VERSION))

#if BOOST_FILESYSTEM_VERSION == 4
#undef BOOST_FILESYSTEM_DEPRECATED
#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
#define BOOST_FILESYSTEM_NO_DEPRECATED
#endif
#endif

#define BOOST_FILESYSTEM_I18N // aid users wishing to compile several versions

//  BOOST_FILESYSTEM_DEPRECATED needed for source compiles -----------------------------//

#ifdef BOOST_FILESYSTEM_SOURCE
#define BOOST_FILESYSTEM_DEPRECATED
#undef BOOST_FILESYSTEM_NO_DEPRECATED // fixes #9454, src bld fails if NO_DEP defined
#endif

#if defined(BOOST_FILESYSTEM_DEPRECATED) && defined(BOOST_FILESYSTEM_NO_DEPRECATED)
#error Both BOOST_FILESYSTEM_DEPRECATED and BOOST_FILESYSTEM_NO_DEPRECATED are defined
#endif

//  throw an exception  ----------------------------------------------------------------//
//
//  Exceptions were originally thrown via boost::throw_exception().
//  As throw_exception() became more complex, it caused user error reporting
//  to be harder to interpret, since the exception reported became much more complex.
//  The immediate fix was to throw directly, wrapped in a macro to make any later change
//  easier.

#define BOOST_FILESYSTEM_THROW(EX) throw EX

#if defined(BOOST_NO_STD_WSTRING)
#error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
#endif

//  This header implements separate compilation features as described in
//  http://www.boost.org/more/separate_compilation.html

//  normalize macros  ------------------------------------------------------------------//

#if !defined(BOOST_FILESYSTEM_DYN_LINK) && !defined(BOOST_FILESYSTEM_STATIC_LINK) && !defined(BOOST_ALL_DYN_LINK) && !defined(BOOST_ALL_STATIC_LINK)
#define BOOST_FILESYSTEM_STATIC_LINK
#endif

#if defined(BOOST_ALL_DYN_LINK) && !defined(BOOST_FILESYSTEM_DYN_LINK)
#define BOOST_FILESYSTEM_DYN_LINK
#elif defined(BOOST_ALL_STATIC_LINK) && !defined(BOOST_FILESYSTEM_STATIC_LINK)
#define BOOST_FILESYSTEM_STATIC_LINK
#endif

#if defined(BOOST_FILESYSTEM_DYN_LINK) && defined(BOOST_FILESYSTEM_STATIC_LINK)
#error Must not define both BOOST_FILESYSTEM_DYN_LINK and BOOST_FILESYSTEM_STATIC_LINK
#endif

#if defined(BOOST_ALL_NO_LIB) && !defined(BOOST_FILESYSTEM_NO_LIB)
#define BOOST_FILESYSTEM_NO_LIB
#endif

//  enable dynamic linking  ------------------------------------------------------------//

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_FILESYSTEM_DYN_LINK)
#if defined(BOOST_FILESYSTEM_SOURCE)
#define BOOST_FILESYSTEM_DECL BOOST_SYMBOL_EXPORT
#else
#define BOOST_FILESYSTEM_DECL BOOST_SYMBOL_IMPORT
#endif
#else
#define BOOST_FILESYSTEM_DECL
#endif

//  enable automatic library variant selection  ----------------------------------------//

#if !defined(BOOST_FILESYSTEM_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_FILESYSTEM_NO_LIB)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_filesystem
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_FILESYSTEM_DYN_LINK)
#define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif // auto-linking disabled

#endif // BOOST_FILESYSTEM_CONFIG_HPP

/* config.hpp
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
*/