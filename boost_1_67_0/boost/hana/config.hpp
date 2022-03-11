/*!
@file
Defines configuration macros used throughout the library.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONFIG_HPP
#define BOOST_HANA_CONFIG_HPP

#include <boost/hana/version.hpp>


//////////////////////////////////////////////////////////////////////////////
// Detect the compiler
//////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && !defined(__clang__) // MSVC
    // This must be checked first, because otherwise it produces a fatal
    // error due to unrecognized #warning directives used below.

#   if _MSC_VER < 1915
#       pragma message("Warning: the native Microsoft compiler is not supported due to lack of proper C++14 support.")
#   else
        // 1. Active issues
        // Multiple copy/move ctors
#       define BOOST_HANA_WORKAROUND_MSVC_MULTIPLECTOR_106654

        // 2. Issues fixed in the development branch of MSVC
        // Forward declaration of class template member function returning decltype(auto)
#       define BOOST_HANA_WORKAROUND_MSVC_DECLTYPEAUTO_RETURNTYPE_662735

        // 3. Issues fixed conditionally
        // Requires __declspec(empty_bases)
        // Empty base optimization
#       define BOOST_HANA_WORKAROUND_MSVC_EMPTYBASE

        // Requires /experimental:preprocessor
        // Variadic macro expansion
#       if !defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL
#           define BOOST_HANA_WORKAROUND_MSVC_PREPROCESSOR_616033
#       endif
#   endif

#elif defined(__clang__) && defined(_MSC_VER) // Clang-cl (Clang for Windows)

#   define BOOST_HANA_CONFIG_CLANG BOOST_HANA_CONFIG_VERSION(               \
                    __clang_major__, __clang_minor__, __clang_patchlevel__)

#elif defined(__clang__) && defined(__apple_build_version__) // Apple's Clang

#   if __apple_build_version__ >= 6020049
#       define BOOST_HANA_CONFIG_CLANG BOOST_HANA_CONFIG_VERSION(3, 6, 0)
#   endif

#elif defined(__clang__) // genuine Clang

#   define BOOST_HANA_CONFIG_CLANG BOOST_HANA_CONFIG_VERSION(               \
                __clang_major__, __clang_minor__, __clang_patchlevel__)

#elif defined(__GNUC__) // GCC

#   define BOOST_HANA_CONFIG_GCC BOOST_HANA_CONFIG_VERSION(                 \
                            __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)

#endif

//////////////////////////////////////////////////////////////////////////////
// Check the compiler for general C++14 capabilities
//////////////////////////////////////////////////////////////////////////////
#if (__cplusplus < 201400)
#   if defined(_MSC_VER)
#       if _MSC_VER < 1915
#           pragma message("Warning: Your compiler doesn't provide C++14 or higher capabilities. Try adding the compiler flag '-std=c++14' or '-std=c++1y'.")
#       endif
#   else
#       warning "Your compiler doesn't provide C++14 or higher capabilities. Try adding the compiler flag '-std=c++14' or '-std=c++1y'."
#   endif
#endif

//////////////////////////////////////////////////////////////////////////////
// Caveats and other compiler-dependent options
//////////////////////////////////////////////////////////////////////////////

// `BOOST_HANA_CONFIG_HAS_CONSTEXPR_LAMBDA` enables some constructs requiring
// `constexpr` lambdas, which are in the language starting with C++17.
//
// Always disabled for now because Clang only has partial support for them
// (captureless lambdas only).
#if defined(__cplusplus) && __cplusplus > 201402L
#   define BOOST_HANA_CONSTEXPR_STATELESS_LAMBDA constexpr
// #   define BOOST_HANA_CONFIG_HAS_CONSTEXPR_LAMBDA
#else
#   define BOOST_HANA_CONSTEXPR_STATELESS_LAMBDA /* nothing */
#endif

// `BOOST_HANA_CONSTEXPR_LAMBDA` expands to `constexpr` if constexpr lambdas
// are supported and to nothing otherwise.
#if defined(BOOST_HANA_CONFIG_HAS_CONSTEXPR_LAMBDA)
#   define BOOST_HANA_CONSTEXPR_LAMBDA constexpr
#else
#   define BOOST_HANA_CONSTEXPR_LAMBDA /* nothing */
#endif

//////////////////////////////////////////////////////////////////////////////
// Namespace macros
//////////////////////////////////////////////////////////////////////////////
#define BOOST_HANA_NAMESPACE_BEGIN namespace boost { namespace hana {

#define BOOST_HANA_NAMESPACE_END }}

//////////////////////////////////////////////////////////////////////////////
// Library features and options that can be tweaked by users
//////////////////////////////////////////////////////////////////////////////

#if defined(BOOST_HANA_DOXYGEN_INVOKED) || \
    (defined(NDEBUG) && !defined(BOOST_HANA_CONFIG_DISABLE_ASSERTIONS))
    //! @ingroup group-config
    //! Disables the `BOOST_HANA_*_ASSERT` macro & friends.
    //!
    //! When this macro is defined, the `BOOST_HANA_*_ASSERT` macro & friends
    //! are disabled, i.e. they expand to nothing.
    //!
    //! This macro is defined automatically when `NDEBUG` is defined. It can
    //! also be defined by users before including this header or defined on
    //! the command line.
#   define BOOST_HANA_CONFIG_DISABLE_ASSERTIONS
#endif

#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    //! @ingroup group-config
    //! Disables concept checks in interface methods.
    //!
    //! When this macro is not defined (the default), tag-dispatched methods
    //! will make sure the arguments they are passed are models of the proper
    //! concept(s). This can be very helpful in catching programming errors,
    //! but it is also slightly less compile-time efficient. You should
    //! probably always leave the checks enabled (and hence never define this
    //! macro), except perhaps in translation units that are compiled very
    //! often but whose code using Hana is modified very rarely.
#   define BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
#endif

#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    //! @ingroup group-config
    //! Enables usage of the "string literal operator template" GNU extension.
    //!
    //! That operator is not part of the language yet, but it is supported by
    //! both Clang and GCC. This operator allows Hana to provide the nice `_s`
    //! user-defined literal for creating compile-time strings.
    //!
    //! When this macro is not defined, the GNU extension will be not used
    //! by Hana. Because this is a non-standard extension, the macro is not
    //! defined by default.
#   define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#endif

#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    //! @ingroup group-config
    //! Enables additional assertions and sanity checks to be done by Hana.
    //!
    //! When this macro is defined (it is __not defined__ by default),
    //! additional sanity checks may be done by Hana. These checks may
    //! be costly to perform, either in terms of compilation time or in
    //! terms of execution time. These checks may help debugging an
    //! application during its initial development, but they should not
    //! be enabled as part of the normal configuration.
#   define BOOST_HANA_CONFIG_ENABLE_DEBUG_MODE
#endif

#endif // !BOOST_HANA_CONFIG_HPP

/* config.hpp
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
*/