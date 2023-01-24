/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_PP_IS_ITERATING)
#if !defined(BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_KEYED_VALUES_CALL_04122006_2211)
#define BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_KEYED_VALUES_CALL_04122006_2211

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define FUSION_HASH #
#define FUSION_DEQUE_KEYED_VALUES_FORWARD(z, n, _)    \
   BOOST_FUSION_FWD_ELEM(BOOST_PP_CAT(T_, n), BOOST_PP_CAT(t, n))

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/deque/detail/cpp03/deque_keyed_values_call.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_DEQUE_KEYED_VALUES_FORWARD
#undef FUSION_HASH
#endif
#else

#define N BOOST_PP_ITERATION()

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::call_param<T, >::type t))
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
        #if N > 1
                        , BOOST_PP_ENUM_SHIFTED_PARAMS(N, T)
        #endif
                        >::construct(BOOST_PP_ENUM_SHIFTED_PARAMS(N, t)));
        }

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        template <BOOST_PP_ENUM_PARAMS(N, typename T_)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(BOOST_PP_ENUM_BINARY_PARAMS(N, T_, && t))
        {
            return type(BOOST_FUSION_FWD_ELEM(T_0, t0),
                        deque_keyed_values_impl<
                        next_index
        #if N > 1
                        , BOOST_PP_ENUM_SHIFTED_PARAMS(N, T_)
        #endif
                        >::forward_(BOOST_PP_ENUM_SHIFTED(N, FUSION_DEQUE_KEYED_VALUES_FORWARD, _)));
        }
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef N
#endif

/* deque_keyed_values_call.hpp
RzqnxIYod8Y64ohFooTgRrB5s5OVrXQpKrZYb4XLFrvV916NhAJpYDtHHYMyY4Ni5Q0aPtMjDMVsLWs3y0q0ZvuxY+wZ9pTpIq5cuIv1e5fbn3SHL3szRqq0xeId5QpRjrCob96A84DNs8100huz/7F4Sc35LFqq2xpSFPMJt26r9ulNE5Ako+03sJEoK1/aleraj5pJgF18OZR3pHax5YyXxjJ3JuCE4Y9CA64QNjIQmbEjfsDO7hDu5iLZgCT4yEJs/LltI7IQxx70p6XK7uEm9fFmeLQM0EiN7z3YFEmIXjf5SEKwY8PqbugLgCMv1+gdS9ThVIDnbQ/q4EmAmSA0x6yxnRuAZwKAJzplsxjBM+EK4NlRQzGKkgzaT7mEZzDYzHkWsD7uhwiec0JhIBNwqUyGc4Gb8kylVu4RpyHL18tnT4Dy2OYLoTKbnc3qQDmMYQk2k9wjJIDd0c/5jyg5tdIybyko9LvlkEwXun6wx9p7ZJHYu2Xtl4C67DsB0NNji5y647EWaM1Qrtx8kj22PTfL7mZRbGLsqZtly6AdcmqVZf4olJs6x1Lsstv8hYQgC2VKzkmxkvSIRf3dfMabqdSAK6EETweky6kD2E7V4sIy+vyIZTJd94J3r2bj7e6bt8mo3O6eFE/madHEHLijsSkSf9rY3bJJXfeC8WmDtGrn5lj1ZYqORalhu5JhQtzUrjgkaCQt0zW1
*/