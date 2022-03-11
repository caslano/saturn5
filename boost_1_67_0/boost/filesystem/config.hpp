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
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
*/