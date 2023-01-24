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
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && !( \
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
q89dceWrW9/bWk1ZhKXYC2RWy9MHNFCKUr1dcYTGEoA4VMZ5I3e/4A9tfzUhUWnJ9p6z4H2gh+Tde8OCbuyGL1iiY49ijHjK97xmm/DDpbL3k20u7vfzL226YobhX81HX1v9jaQluepOb6Xtl2ZeWWRmppq54j3okL2sWNFY3LqJiFzBOJ6u2CEYV2AZ+phFb6zgroyhrL/nWAjcQuTa2unCtyMEjui6eFx1ABFO/NprPu18HrzydhFK2ERgH9CUGS1XJitnGKge2JkJ+edrbcJpwk0R5xaoSBJkenbybMXWlBWz2a5k9TUjEl91vr+9JhJ/eG4Vw7I3amygGkogcTlom64xt7HG9tIm/MViyJrUHtVHF4prl8AqhW3H+kS4t/m1wW0aa2/5pv/pj9ob0fG2VpwmzMvYOqMhuLNLMmrgyO4qXQh7Nb5t9NwAG4WYXwpB0QSj8C9rDjJSpD441xnGGQAV/Ap5sSnLTcgxWr36181p32BGd6ZgWNNKU3BNdAsLdMivFljqDnJ44ZcOBcKyBKzanKsdT3OsUjZ299m0rh7nZxANCmKrCq72r+k1KTtp566W6X0sjisxoaQVh5VozjEZk7joBT2+m5hGLrC2j2xfrgaN38xKzYYFOqcL1v1b71Bzv2Y7dDjFZloE4tdfcpazYFFMJyAYYR+k4U6lakaZyPdnOY0q1cm61GZadH2gI9l6RqoYShw2
*/