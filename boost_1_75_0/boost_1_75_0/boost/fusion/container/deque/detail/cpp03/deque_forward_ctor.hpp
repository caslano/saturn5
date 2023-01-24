/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_PP_IS_ITERATING)
#if !defined(BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_FORWARD_CTOR_04122006_2212)
#define BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_FORWARD_CTOR_04122006_2212

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#define FUSION_DEQUE_FORWARD_CTOR_FORWARD(z, n, _)    BOOST_FUSION_FWD_ELEM(T_##n, t##n)

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/deque/detail/cpp03/deque_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (2, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_DEQUE_FORWARD_CTOR_FORWARD
#endif
#else

#define N BOOST_PP_ITERATION()

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::call_param<T, >::type t))
    : base(detail::deque_keyed_values<BOOST_PP_ENUM_PARAMS(N, T)>::construct(BOOST_PP_ENUM_PARAMS(N, t)))
{}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& t))
    : base(detail::deque_keyed_values<BOOST_PP_ENUM_PARAMS(N, T)>::construct(BOOST_PP_ENUM_PARAMS(N, t)))
{}

template <BOOST_PP_ENUM_PARAMS(N, typename T_)>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(BOOST_PP_ENUM_BINARY_PARAMS(N, T_, && t))
    : base(detail::deque_keyed_values<BOOST_PP_ENUM_PARAMS(N, T)>::
      forward_(BOOST_PP_ENUM(N, FUSION_DEQUE_FORWARD_CTOR_FORWARD, _)))
{}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef N
#endif

/* deque_forward_ctor.hpp
hqcL+9jtzc6mo/PlEG7ynOEvznOohCwjLIwpVlWgWrrD3/sohtuFAwHEsgnENE9WI9sSBWESHkYvAjMI7s5kUKI+9nU0iRTIIdxJHPF33NaFN1vIRxwUBRfxteC9jUZn61FlmQeGAxGNiRUfiyWOB3KSV62T38jWI7NJ5gaBLk+D+iRSxnejpZ/ts4XLiyRga8vc3xyqlLCsmUIRKglr3DGbrsV/cZhnFTiMjVioOAE2dyOIYDJwto8D5MQGAisokrb5dqKg4akqNKl10dbflwhI/nEJQXDZaxTO1c7VL5cgTE97TTvjbK4WNlJcuuZaENNEGwY6iD90VgPxXLty0mihWjcTWvaEQThkAqCzF1CW9ZUwmOrtbOFaMMTK3uMAiU9Y1pvAp2ysrccOh8kethlcynpKd4Lh+uF5tWjtFQu9/DMWaix7Qe0SLXvUj41mZ2jW8ELPVMr78MVG87ZTBptcQ4o1E5HLZrH1qV0WKpqaXNNo8Zaym5vUHmNSB74dJXk+onJtTzdaLl8uqRQInjV1VjBFxJtm6WpM7OfIWQR1/YRdBVBlEoqIrKLePL0T4HZ/aNP16rFG+9ICpgA1hmr/AnwQy9z/SxPKwJVQu1kr88P5RstMZ2NeLsY85PFgY+7/uM+YJz0eYzg+Go55AE8fLJQZvFbPTHbRXK91a8LBRrs1BNaOS+uqT7wJoroLVYFy/giMVe2stDnO
*/