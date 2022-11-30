//  (C) Copyright David Abrahams 2000.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

//  Revision History:
//  04 Mar 01  Some fixes so it will compile with Intel C++ (Dave Abrahams)

#ifndef CONFIG_DWA052200_H_
# define CONFIG_DWA052200_H_

# include <boost/config.hpp>
# include <boost/detail/workaround.hpp>

# ifdef BOOST_NO_OPERATORS_IN_NAMESPACE
   // A gcc bug forces some symbols into the global namespace
#  define BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE
#  define BOOST_PYTHON_END_CONVERSION_NAMESPACE
#  define BOOST_PYTHON_CONVERSION
#  define BOOST_PYTHON_IMPORT_CONVERSION(x) using ::x
# else
#  define BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE namespace boost { namespace python {
#  define BOOST_PYTHON_END_CONVERSION_NAMESPACE }} // namespace boost::python
#  define BOOST_PYTHON_CONVERSION boost::python
#  define BOOST_PYTHON_IMPORT_CONVERSION(x) void never_defined() // so we can follow the macro with a ';'
# endif

# if defined(BOOST_MSVC)

#  pragma warning (disable : 4786) // disable truncated debug symbols
#  pragma warning (disable : 4251) // disable exported dll function
#  pragma warning (disable : 4800) //'int' : forcing value to bool 'true' or 'false'
#  pragma warning (disable : 4275) // non dll-interface class

# elif defined(__ICL) && __ICL < 600 // Intel C++ 5

#  pragma warning(disable: 985) // identifier was truncated in debug information

# endif

// The STLport puts all of the standard 'C' library names in std (as far as the
// user is concerned), but without it you need a fix if you're using MSVC or
// Intel C++
# if defined(BOOST_NO_STDC_NAMESPACE)
#  define BOOST_CSTD_
# else
#  define BOOST_CSTD_ std
# endif

/*****************************************************************************
 *
 *  Set up dll import/export options:
 *
 ****************************************************************************/

// backwards compatibility:
#ifdef BOOST_PYTHON_STATIC_LIB
#  define BOOST_PYTHON_STATIC_LINK
# elif !defined(BOOST_PYTHON_DYNAMIC_LIB)
#  define BOOST_PYTHON_DYNAMIC_LIB
#endif

#if defined(BOOST_PYTHON_DYNAMIC_LIB)
#  if defined(BOOST_SYMBOL_EXPORT)
#     if defined(BOOST_PYTHON_SOURCE)
#        define BOOST_PYTHON_DECL           BOOST_SYMBOL_EXPORT
#        define BOOST_PYTHON_DECL_FORWARD   BOOST_SYMBOL_FORWARD_EXPORT
#        define BOOST_PYTHON_DECL_EXCEPTION BOOST_EXCEPTION_EXPORT
#        define BOOST_PYTHON_BUILD_DLL
#     else
#        define BOOST_PYTHON_DECL           BOOST_SYMBOL_IMPORT
#        define BOOST_PYTHON_DECL_FORWARD   BOOST_SYMBOL_FORWARD_IMPORT
#        define BOOST_PYTHON_DECL_EXCEPTION BOOST_EXCEPTION_IMPORT
#     endif
#  endif
#endif

#ifndef BOOST_PYTHON_DECL
#  define BOOST_PYTHON_DECL
#endif

#ifndef BOOST_PYTHON_DECL_FORWARD
#  define BOOST_PYTHON_DECL_FORWARD
#endif

#ifndef BOOST_PYTHON_DECL_EXCEPTION
#  define BOOST_PYTHON_DECL_EXCEPTION
#endif

#if BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
// Replace broken Tru64/cxx offsetof macro
# define BOOST_PYTHON_OFFSETOF(s_name, s_member) \
        ((size_t)__INTADDR__(&(((s_name *)0)->s_member)))
#else
# define BOOST_PYTHON_OFFSETOF offsetof
#endif

//  enable automatic library variant selection  ------------------------------// 

#if !defined(BOOST_PYTHON_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_PYTHON_NO_LIB)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define _BOOST_PYTHON_CONCAT(N, M, m) N ## M ## m
#define BOOST_PYTHON_CONCAT(N, M, m) _BOOST_PYTHON_CONCAT(N, M, m)
#define BOOST_LIB_NAME BOOST_PYTHON_CONCAT(boost_python, PY_MAJOR_VERSION, PY_MINOR_VERSION)
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#ifdef BOOST_PYTHON_DYNAMIC_LIB
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#undef BOOST_PYTHON_CONCAT
#undef _BOOST_PYTHON_CONCAT

#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
#define BOOST_PYTHON_SUPPORTS_PY_SIGNATURES // enables smooth transition
#endif

#if !defined(BOOST_ATTRIBUTE_UNUSED) && defined(__GNUC__) && (__GNUC__ >= 4)
#  define BOOST_ATTRIBUTE_UNUSED __attribute__((unused))
#endif

#endif // CONFIG_DWA052200_H_

/* config.hpp
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
*/