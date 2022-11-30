// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_CONFIG_050403_HPP
#define BOOST_PARAMETER_CONFIG_050403_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

// Allow projects to #define BOOST_PARAMETER_DISABLE_PERFECT_FORWARDING to
// turn off perfect forwarding as necessary.  Otherwise, also require correct
// SFINAE support, needed explicitly by tagged_argument & keyword & cast;
// correct function template ordering, needed by the code generation macros;
// rvalue references, needed throughout; variadic templates, needed by
// parameters; function template default arguments, needed by the code
// generation macros; and the ability to handle multiple parameter packs,
// needed by parameters.  Older versions of GCC either don't have the latter
// ability or cannot disambiguate between keyword's overloaded
// operators.  Older versions of Clang either fail to compile due to
// differences in length between parameter packs 'Args' and 'args' or fail at
// runtime due to segmentation faults.
// -- Cromwell D. Enage
#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) && \
    !defined(BOOST_PARAMETER_DISABLE_PERFECT_FORWARDING) && \
    !defined(BOOST_NO_SFINAE) && \
    !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) && \
    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && \
    !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) && \
    !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564)) && !( \
        defined(BOOST_CLANG) && (1 == BOOST_CLANG) && ( \
            (__clang_major__ < 3) || ( \
                (3 == __clang_major__) && (__clang_minor__ < 2) \
            ) \
        ) \
    ) && !BOOST_WORKAROUND(BOOST_GCC, < 40900)
#define BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#if !defined(BOOST_PARAMETER_CAN_USE_MP11) && \
    !defined(BOOST_PARAMETER_DISABLE_MP11_USAGE) && \
    !defined(BOOST_NO_CXX11_CONSTEXPR) && \
    !defined(BOOST_NO_CXX11_DECLTYPE_N3276) && \
    !defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) && \
    !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES) && \
    !defined(BOOST_NO_CXX11_STATIC_ASSERT) && \
    !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS) && \
    !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST) && \
    !defined(BOOST_NO_CXX11_HDR_TUPLE)
// Boost.MP11 requires C++11. -- Cromwell D. Enage
#define BOOST_PARAMETER_CAN_USE_MP11
#endif
#if !defined(BOOST_PARAMETER_MAX_ARITY)
// Unlike the variadic MPL sequences provided by Boost.Fusion,
// boost::mpl::vector has a size limit. -- Cromwell D. Enage
#include <boost/mpl/limits/vector.hpp>
#define BOOST_PARAMETER_MAX_ARITY BOOST_MPL_LIMIT_VECTOR_SIZE
#endif
#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#if !defined(BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY)
#define BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY 0
#endif
#if !defined(BOOST_PARAMETER_COMPOSE_MAX_ARITY)
#if BOOST_WORKAROUND(BOOST_MSVC, < 1800) || \
    BOOST_WORKAROUND(BOOST_GCC, < 60000)
// Some tests cause MSVC-11.0 and earlier to run out of heap space,
// while some other tests cause GCC 5 and earlier to do the same,
// if the value is set any higher. -- Cromwell D. Enage
#define BOOST_PARAMETER_COMPOSE_MAX_ARITY 20
#else
#define BOOST_PARAMETER_COMPOSE_MAX_ARITY 64
#endif
#endif  // BOOST_PARAMETER_COMPOSE_MAX_ARITY
#if !defined(BOOST_PARAMETER_MAX_ARITY)
#define BOOST_PARAMETER_MAX_ARITY 8
#endif
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* config.hpp
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
*/