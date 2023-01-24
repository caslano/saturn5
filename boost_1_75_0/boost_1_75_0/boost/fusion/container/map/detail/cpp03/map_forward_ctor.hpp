/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAP_FORWARD_CTOR_07222005_0106)
#define FUSION_MAP_FORWARD_CTOR_07222005_0106

#define FUSION_FORWARD_CTOR_FORWARD(z, n, _)    BOOST_FUSION_FWD_ELEM(U##n, _##n)

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/map/detail/cpp03/map_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_MAP_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_FORWARD_CTOR_FORWARD
#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    map(BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::call_param<T, >::type arg))
        : data(BOOST_PP_ENUM_PARAMS(N, arg)) {}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    map(BOOST_PP_ENUM_BINARY_PARAMS(N, U, && arg)
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES) && \
    N == 1
    // workaround for MSVC 10
FUSION_HASH if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
        , typename enable_if<is_same<U0, T0> >::type* = 0
FUSION_HASH endif
#endif
        )
        : data(BOOST_PP_ENUM(N, FUSION_FORWARD_CTOR_FORWARD, arg)) {}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* map_forward_ctor.hpp
YFRBHP6OO1FqwHap2Q6f9L7WodTwxsMkUdq06384Rw7SFhybsckeixSPNe84HrbSXon+6pUSIpCeIRqkEnecUVfbmT/JO45/APTkerQAsQudkKrU/0mlb6aEd595ZK0ZBF6CvZquMo9OL8psYkiccKikla5JkcOhsNsc66dEwoMqaB6eIT+nhMoKC7KRxA2OlOhkIxy/WSip7kEuCNJ510exh4D+USCvpPm7ewIf0H6N9glaeUp7SApW0HOvdzqoNXYVWRqazTJNZGGb22nqvVcJ+pO/UtVnrgRqVHQyT/K+8nAI0OwyOVGPRjV+3SMAUZwgpV0qyGSLc/oHvN8UqpmXH9OqEJfx85IrjmlcvACJRkU+m2EVk0QVvb/qd1ty7iOXe4imbL8PdgG4sGYpO7LR0DfcWo/xPjkUKJ4NjdtMCwVIagINm3y4px3ftKUH9jbq01vtiIoVVh3M45facVyv8QReJaHoeB607vqgSVu2AqnEgePLgzugs+ILC/qlCLyqNlesIVKxN8wP3gmaK9kWZ5FjHlFYTZfHbG2Wx6Q341wybICUG/i//QS5ibC2QkXWVyVJTuIHSbSxjeyBW9nQHqwDT5+zObV3Cn5elmLymYYMjgjPN72n6jhejOIyx7N6/4aLF+iZ7MrxcGBHGZxU5LsP4peBNDWvwY6ZUlBEdQQ9fKapK96OxWgPr0SPwYU9h6vN8CrD0vh2
*/