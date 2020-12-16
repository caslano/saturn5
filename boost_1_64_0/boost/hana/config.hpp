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
uH02Vkx1GKRZemx0xx3Ldtpp1z3Ky5tzLceazbFMYtedm+P5dhJ0KeS3p3vOnv69x4UmW76ANWg9/gr6F/561uXr88VUJnUi7ebfuCqXyafShklnga4wbuaGpC8RaYhWVUyYUFlRdTBtgz6strG+jn6aIgEmjPtivMUY6+hSLe3ky5JbXd3SpqS/neuRnu8PVixBZ5QUFGPRWEcslbZEFG1dQ/JN7Dtuqc1IJzVU1XBobZi+VzVuPMrnF/t7SfveWiiv2fa9FUNr2Z9z9tMet9i6Nzc0LrQxPVPYfpZ16XeLjuKsEeswCtFCe96SEDYSIWJWjMvSV5+wfyu91Fr02aU3sxXU4maZpS9ZNBy/SeW4Mvr7gf37jcTEby7tZMXIUj7oB1en37OgX9qf2za0Bj3f6spnk7GOnGk9E32ujbiLbe69FHOxU2gy/eopoW2orFcfO9a/mey/ie3nsREhq6zql3LKal26V2Yh7Hvy2aXOyWJLG4R4bZvTfvKl3j1p/qt//HjJ4hMu3GjtB7uOotCOa+z75qSXypa+8ZWnztiv49vkTzvfGAq9bd/f7vK9n/z04Lnfr/37irf9vPD8rUOhZbaw7m/dvWjWpgPL/vxyw/ELjt+guT0U2sm+Py7y/o1HbdmwTnaj5+srdv6MhPUS9v0D6uLrLpq0eNsV8+sPnLbLL0+Tboh9f7dTKxZ/OPTrvjPXmfPt25veuEIo9LR9/7ark41zxnz98ZO3bPnHtdPOuyUUumxN6/6Uyz44Mza4/e+X/GjcOOHLXaqpJa9t3W9fcafVDn8y0Xtdd/cRs59vaaLzmla37nfWvnv/F2usfdOby++w9vPrXLcplbv9+7sfu+ndibprpm/88nM7vHX0Q1RJv61h3X9+wV33XnJhNHxc/40H9izZ8HM612FL6/7lZzf98tg6XZeWPRy9aeUp+7xLZzkvRZVyyLKhsw4mXV/620lXN13P0LXwOGqjdHXT/xug/w41Lhtan67FE0jfk/5uW096MQ0h+izpWjRSG6RrHl0Jeu6uZegzh5Fe0OGkW0jX8CT69xGkw0BX6Cj6S9eazfQZuhJ03UqNahZ9J0K/Oz5Kmgl0bU5v9gS6ZtL1Bl1L6KqJkV4sXW105emz81roXoLu0ZVOENe6Z9Ce+CR9p5X0Xej6jq4ek34zRd+5cExodoqek1iXpil/dLVlqByyxKHvBilIQQpSkIL0J3tXAtxEFYa3R7ACaquAQaD2QC0qWgGxKijYolRRS1tqgEqaJts2kiYxSbVFxaqojKLiDYrX4FHx6iDegh2nnsOgeAweMMqojGBFRBTQ6vi9t/9ukzRpWmhQ9P+Gx9+3eefuS3a////3fwwGg8GIjXjwf0Gq/ao9EMz/E/aQ/x8K/v8tRlc07SIE8LTmo7mYOgHxeQO4VoSPrWWjNZ1B8hGIKU06g0YK53wu0iFyvIjvOAA8ZpemMyguzbcWYk5Om8s5R0VsMvDqwcPlGZM8vjABdWTZEZJDZ0Tn0Ch/aloJyoou386SHNkYR0pi5HF4g8ZRiqvidAuCHXkcN/RgHA8Fj4O4ugi/vGqg4JytU+aeuvX00y747fnM9Ja0vk3ROXBk7tpzDhyNSxdKDrzhzPYFZ81bfHV1ZWvhSaMKlkfXEUTWBUTn0sfL+a7Yvd3ekGlyTyh45sQta39shy5JHn//qj7VfR5ZtGX64uZ5y5rXWKLpIKLrFObIfu9pSf/+25YhCyuG3XlyXt4Pu6LpJqLrIJ6R7VyUcfNnjqt3rLzirsLD1qf/tTu6bgUXV+oHFpaYlCakFqTPSkL1A9tKOusFUkpNpBvQ9QLhOoHu6QOGlnbWCRyPY5H0AtE=
*/