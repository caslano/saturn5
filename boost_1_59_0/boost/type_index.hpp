//
// Copyright 2012-2022 Antony Polukhin.
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