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

// `BOOST_HANA_INLINE_VARIABLE` expands to `inline` when C++17 inline variables
// are supported, and to nothing otherwise. This allows marking global variables
// defined in a header as `inline` to avoid potential ODR violations.
#if defined(__cplusplus) && __cplusplus > 201402L
#   define BOOST_HANA_INLINE_VARIABLE inline
#else
#   define BOOST_HANA_INLINE_VARIABLE /* nothing */
#endif

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