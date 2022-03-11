//
// Copyright 2012-2020 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_TYPE_INDEX_HPP
#define BOOST_TYPE_INDEX_HPP

/// \file boost/type_index.hpp
/// \brief Includes minimal set of headers required to use the Boost.TypeIndex library.
///
/// By inclusion of this file most optimal type index classes will be included and used 
/// as a boost::typeindex::type_index and boost::typeindex::type_info.

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

#if defined(BOOST_TYPE_INDEX_USER_TYPEINDEX)
#   include BOOST_TYPE_INDEX_USER_TYPEINDEX
#   ifdef BOOST_HAS_PRAGMA_DETECT_MISMATCH
#       pragma detect_mismatch( "boost__type_index__abi", "user defined type_index class is used: " BOOST_STRINGIZE(BOOST_TYPE_INDEX_USER_TYPEINDEX))
#   endif
#elif (!defined(BOOST_NO_RTTI) && !defined(BOOST_TYPE_INDEX_FORCE_NO_RTTI_COMPATIBILITY)) || defined(BOOST_MSVC)
#   include <boost/type_index/stl_type_index.hpp>
#   if defined(BOOST_NO_RTTI) || defined(BOOST_TYPE_INDEX_FORCE_NO_RTTI_COMPATIBILITY)
#       include <boost/type_index/detail/stl_register_class.hpp>
#       ifdef BOOST_HAS_PRAGMA_DETECT_MISMATCH
#           pragma detect_mismatch( "boost__type_index__abi", "RTTI is off - typeid() is used only for templates")
#       endif
#   else
#       ifdef BOOST_HAS_PRAGMA_DETECT_MISMATCH
#           pragma detect_mismatch( "boost__type_index__abi", "RTTI is used")
#       endif
#   endif
#else
#   include <boost/type_index/ctti_type_index.hpp>
#   include <boost/type_index/detail/ctti_register_class.hpp>
#   ifdef BOOST_HAS_PRAGMA_DETECT_MISMATCH
#       pragma detect_mismatch( "boost__type_index__abi", "RTTI is off - using CTTI")
#   endif
#endif

#ifndef BOOST_TYPE_INDEX_REGISTER_CLASS
#define BOOST_TYPE_INDEX_REGISTER_CLASS
#endif

namespace boost { namespace typeindex {

#if defined(BOOST_TYPE_INDEX_DOXYGEN_INVOKED)

/// \def BOOST_TYPE_INDEX_FUNCTION_SIGNATURE
/// BOOST_TYPE_INDEX_FUNCTION_SIGNATURE is used by boost::typeindex::ctti_type_index class to
/// deduce the name of a type. If your compiler is not recognized
/// by the TypeIndex library and you wish to work with boost::typeindex::ctti_type_index, you may
/// define this macro by yourself.
///
/// BOOST_TYPE_INDEX_FUNCTION_SIGNATURE must be defined to a compiler specific macro
/// that outputs the \b whole function signature \b including \b template \b parameters.
///
/// If your compiler is not recognised and BOOST_TYPE_INDEX_FUNCTION_SIGNATURE is not defined,
/// then a compile-time error will arise at any attempt to use boost::typeindex::ctti_type_index classes.
///
/// See BOOST_TYPE_INDEX_REGISTER_CTTI_PARSING_PARAMS and BOOST_TYPE_INDEX_CTTI_USER_DEFINED_PARSING
/// for an information of how to tune the implementation to make a nice pretty_name() output.
#define BOOST_TYPE_INDEX_FUNCTION_SIGNATURE BOOST_CURRENT_FUNCTION

/// \def BOOST_TYPE_INDEX_CTTI_USER_DEFINED_PARSING
/// This is a helper macro for making correct pretty_names() with RTTI off.
///
/// BOOST_TYPE_INDEX_CTTI_USER_DEFINED_PARSING macro may be defined to
/// '(begin_skip, end_skip, runtime_skip, runtime_skip_until)' with parameters for adding a
/// support for compilers, that by default are not recognized by TypeIndex library.
///
/// \b Example:
///
/// Imagine the situation when
/// \code boost::typeindex::ctti_type_index::type_id<int>().pretty_name() \endcode
/// returns the following string:
/// \code "static const char *boost::detail::ctti<int>::n() [T = int]" \endcode
/// and \code boost::typeindex::ctti_type_index::type_id<short>().pretty_name() \endcode returns the following:
/// \code "static const char *boost::detail::ctti<short>::n() [T = short]" \endcode
///
/// As we may see first 39 characters are "static const char *boost::detail::ctti<" and they do not depend on
/// the type T. After first 39 characters we have a human readable type name which is duplicated at the end
/// of a string. String always ends on ']', which consumes 1 character.
///
/// Now if we define `BOOST_TYPE_INDEX_CTTI_USER_DEFINED_PARSING` to
/// `(39, 1, false, "")` we'll be getting \code "int>::n() [T = int" \endcode
/// for `boost::typeindex::ctti_type_index::type_id<int>().pretty_name()` and \code "short>::n() [T = short" \endcode
/// for `boost::typeindex::ctti_type_index::type_id<short>().pretty_name()`.
///
/// Now we need to take additional care of the characters that go before the last mention of our type. We'll
/// do that by telling the macro that we need to cut off everything that goes before the "T = " including the "T = "
/// itself:
///
/// \code (39, 1, true, "T = ") \endcode
///
/// In case of GCC or Clang command line we need to add the following line while compiling all the sources:
///
/// \code
/// -DBOOST_TYPE_INDEX_CTTI_USER_DEFINED_PARSING='(39, 1, true, "T = ")'
/// \endcode
/// \param begin_skip How many characters must be skipped at the beginning of the type holding string.
/// Must be a compile time constant.
/// \param end_skip How many characters must be skipped at the end of the type holding string.
/// Must be a compile time constant.
/// \param runtime_skip Do we need additional checks at runtime to cut off the more characters.
/// Must be `true` or `false`.
/// \param runtime_skip_until Skip all the characters before the following string (including the string itself).
/// Must be a compile time array of characters.
///
/// See [RTTI emulation limitations](boost_typeindex/rtti_emulation_limitations.html) for more info.
#define BOOST_TYPE_INDEX_CTTI_USER_DEFINED_PARSING (0, 0, false, "")


    /// Depending on a compiler flags, optimal implementation of type_index will be used 
    /// as a default boost::typeindex::type_index.
    ///
    /// Could be a boost::typeindex::stl_type_index, boost::typeindex::ctti_type_index or 
    /// user defined type_index class.
    ///
    /// \b See boost::typeindex::type_index_facade for a full description of type_index functions.
    typedef platform_specific type_index;
#elif defined(BOOST_TYPE_INDEX_USER_TYPEINDEX)
    // Nothing to do
#elif (!defined(BOOST_NO_RTTI) && !defined(BOOST_TYPE_INDEX_FORCE_NO_RTTI_COMPATIBILITY)) || defined(BOOST_MSVC)
    typedef boost::typeindex::stl_type_index type_index;
#else 
    typedef boost::typeindex::ctti_type_index type_index;
#endif

/// Depending on a compiler flags, optimal implementation of type_info will be used 
/// as a default boost::typeindex::type_info.
///
/// Could be a std::type_info, boost::typeindex::detail::ctti_data or 
/// some user defined class.
///
/// type_info \b is \b not copyable or default constructible. It is \b not assignable too!
typedef type_index::type_info_t type_info;

#if defined(BOOST_TYPE_INDEX_DOXYGEN_INVOKED)

/// \def BOOST_TYPE_INDEX_USER_TYPEINDEX
/// BOOST_TYPE_INDEX_USER_TYPEINDEX can be defined to the path to header file
/// with user provided implementation of type_index.
///
/// See [Making a custom type_index](boost_typeindex/making_a_custom_type_index.html) section
/// of documentation for usage example.
#define BOOST_TYPE_INDEX_USER_TYPEINDEX <full/absolute/path/to/header/with/type_index.hpp>


/// \def BOOST_TYPE_INDEX_REGISTER_CLASS
/// BOOST_TYPE_INDEX_REGISTER_CLASS is used to help to emulate RTTI.
/// Put this macro into the public section of polymorphic class to allow runtime type detection.
///
/// Depending on the typeid() availability this macro will expand to nothing or to virtual helper function
/// `virtual const type_info& boost_type_info_type_id_runtime_() const noexcept`.
///
/// \b Example:
/// \code
/// class A {
/// public:
///     BOOST_TYPE_INDEX_REGISTER_CLASS
///     virtual ~A(){}
/// };
///
/// struct B: public A {
///     BOOST_TYPE_INDEX_REGISTER_CLASS
/// };
///
/// struct C: public B {
///     BOOST_TYPE_INDEX_REGISTER_CLASS
/// };
///
/// ...
///
/// C c1;
/// A* pc1 = &c1;
/// assert(boost::typeindex::type_id<C>() == boost::typeindex::type_id_runtime(*pc1));
/// \endcode
#define BOOST_TYPE_INDEX_REGISTER_CLASS nothing-or-some-virtual-functions

/// \def BOOST_TYPE_INDEX_FORCE_NO_RTTI_COMPATIBILITY
/// BOOST_TYPE_INDEX_FORCE_NO_RTTI_COMPATIBILITY is a helper macro that must be defined if mixing
/// RTTI on/off modules. See
/// [Mixing sources with RTTI on and RTTI off](boost_typeindex/mixing_sources_with_rtti_on_and_.html)
/// section of documentation for more info.
#define BOOST_TYPE_INDEX_FORCE_NO_RTTI_COMPATIBILITY

#endif // defined(BOOST_TYPE_INDEX_DOXYGEN_INVOKED)


/// Function to get boost::typeindex::type_index for a type T.
/// Removes const, volatile && and & modifiers from T.
///
/// \b Example:
/// \code
/// type_index ti = type_id<int&>();
/// std::cout << ti.pretty_name();  // Outputs 'int'
/// \endcode
///
/// \tparam T Type for which type_index must be created.
/// \throw Nothing.
/// \return boost::typeindex::type_index with information about the specified type T.
template <class T>
inline type_index type_id() BOOST_NOEXCEPT {
    return type_index::type_id<T>();
}

/// Function for constructing boost::typeindex::type_index instance for type T. 
/// Does not remove const, volatile, & and && modifiers from T.
///
/// If T has no const, volatile, & and && modifiers, then returns exactly 
/// the same result as in case of calling `type_id<T>()`.
///
/// \b Example:
/// \code
/// type_index ti = type_id_with_cvr<int&>();
/// std::cout << ti.pretty_name();  // Outputs 'int&'
/// \endcode
///
/// \tparam T Type for which type_index must be created.
/// \throw Nothing.
/// \return boost::typeindex::type_index with information about the specified type T.
template <class T>
inline type_index type_id_with_cvr() BOOST_NOEXCEPT {
    return type_index::type_id_with_cvr<T>();
}

/// Function that works exactly like C++ typeid(rtti_val) call, but returns boost::type_index.
///
/// Returns runtime information about specified type.
///
/// \b Requirements: RTTI available or Base and Derived classes must be marked with BOOST_TYPE_INDEX_REGISTER_CLASS.
///
/// \b Example:
/// \code
/// struct Base { virtual ~Base(){} };
/// struct Derived: public Base  {};
/// ...
/// Derived d;
/// Base& b = d;
/// type_index ti = type_id_runtime(b);
/// std::cout << ti.pretty_name();  // Outputs 'Derived'
/// \endcode
///
/// \param runtime_val Variable which runtime type must be returned.
/// \throw Nothing.
/// \return boost::typeindex::type_index with information about the specified variable.
template <class T>
inline type_index type_id_runtime(const T& runtime_val) BOOST_NOEXCEPT {
    return type_index::type_id_runtime(runtime_val);
}

}} // namespace boost::typeindex



#endif // BOOST_TYPE_INDEX_HPP


/* type_index.hpp
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
*/