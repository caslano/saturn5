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
a2Hn2LKuoqzbfJRVX03gs8zbmllmVyYmdNH6SeMllHlHbJmlZ0EjMmHfL+bG9bc3SWj12P+aj/ss06Nkptq6L8ms47tdYnXxpc47Z2wdxUrqr1/uaWQbmDJu2qSvyfGUT2yc9bHlO6e2jP+rS2triivOW+5Tf9Q3s5xuXxzRNVYfX+aU/UZvObU61h8p/OrjwI3NK6vL0z0xZRW7cYKylpecW1Lus5y5zSynO25c2k10hURqibvcGYct5eT7mLPpqqLYp44Y08gykp6Vl/0Oi5XPNZQxP7aMzgVdiyKt7o+X+Y0sZzxe7j7Ms+dV2rwwXjlRw5U1pb7KSBpRempII+wE8cpb193e7+vilVe92PnjaV0zeer2+RcPj92zfJUzZ4guY3lFUbEUkr8XFjXqW9NaKWum3iMxfqxcd2QZM+z0lUU1pXHvaPO03dBGtJ3ZJ7LNfcluGcU/TftLWTzv39uOCCd+QjL+gtc585hoPi4vOS+g91gGZY9lD/cOM0U7IrknXKskledwp/M9pXNymn1eI/V220DuWVLpdQIfVeHDknvxfwXuWdxpQW5JSw6qbxwv0/abcp370uFD21Xvx+z5EZoXoRnWAZrMVatcmuE8mzSfQDPCoWmxusil2SbpLOG5i9hCRkLTV+4fGsXfoHLHyR6hnTjneQnuePxG407AnYgbg+uSEXavQzeW50WhiBtnafc0y57QpT+EL2pP6CD1nK+fI3KxV7W1ah9l7346TBO4U+zd7tkG83vEzgk3QbNtXVS7V3MbLF3Gn51727rG9e1474BTj9Tr8FXZu+M2O3M/T9k879G+ykgaWvbuV7TEr7b3Z6HV/XNgE+1h7jzwfsdP5eeZvxwlNg1JKAv3E+obuMVTX8v7pF9dFk7L/O5YAqm13tA2vR2lrvLdhTw8c96jesa+399DXXNj6jqwUfaHXKN+bygddW7lMnv9oI1u1/FN1LtuXckPP/LzyPH6XnK/g8yfnPD3u6APYupaUFReudy5fbmmojq+zXiiilcaOMv+bku6Mv7o+0ElRTsfNH227M1z6Qv0Pauyl1XRnRoYZ78/XNKRtSRiQ/wFzraWpLUPvsp4Jvd8RuqQY96ZbZbVMy/c2Tv2W94Djv6w850/ytlvq17Mrec2ZII7VdyOdp1iyN6zKi5J2XkutJb7Uy183XEQ+uGzYb8F5ncffQeqp29+2UevhdP33W7hv3oP38RWJHfcan7Z3/GM+i4IJeZNfSN4U+/pwxN89GHT3mzeh7kg1DCP3D69t6+WLb2v7SFHf91q55EamfzqsFsj9V+oeKViW3kltLr+ec0cm8gPP5Vf1Nh01DGx7y6PUN8x1vrGvGjF7U8TVPz2dj1m8GFD4v4ErX+ZGXNr8/vTBh/9yZWVlbJQ8kxJfLacH1UYwzuxa6pzE+LroGIVr4v9PdDgw89FdqpsPPPQ1ipOcI6OsW7wQhXeTp6DgS3qOUnNvfsgD7n9ZO7d5qiY/fvyHYl5b+PWEsY/r4p6CF+nCF8/6R/ha0vha5mj3y18RSL198eIVMYfY19XaZweGGUdYyUPGWNzVHydqB4v31Q0U9mTmGQfAxohs0JrfKttcFyd0tC4mqP8dLntcmzarI71zNlEjsf8yMJvprdKjDlhwO/6ENLxyK56U7XyTmi13E30ofcbljGVX5SMrR8ges+zFqYwps5iM29i3Qs99ZnUxPqYOvuKvOh3yFTc4843H0/Zm/Ntos5osyGJdTS0zde7Q1y96/m2UTPQU1d5d1rro66N/bax1m0r3W9r7XagZtQ3Per9qTaqXecPkvtCJJGhIpO3xa2rtieWVfmsI2lp/TZD5VpeUbG0ttIcH34=
*/