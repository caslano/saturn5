/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_LIST_TO_CONS_CALL_07192005_0138)
#define FUSION_LIST_TO_CONS_CALL_07192005_0138

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/list/detail/cpp03/list_to_cons_call.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
    {
        return type(arg0
#if N > 1
            , tail_list_to_cons::call(BOOST_PP_ENUM_SHIFTED_PARAMS(N, arg)));
#else
            );
#endif
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* list_to_cons_call.hpp
QIa3KfUYzApmSN1AoYjN5XzztEvlktb+eRHDbvUGdInAvbboCSoIWI9cVEmv+gRzn4KgY6ZTskv1HZ/8aB7sKRocSvANh+VTVFW0PzhKb7ieg8L9m/kC0RcK+m20lHRD+7yhNjdnB6xHhDm0445nQOViWTY4bZ5qGde6pLRB+S3QlOvzMkGerqyB9eScSLwOXI0wffFYuP7Yye0m3j6potHcw5VYDbSuQuAjnIzWFED7NuXhHcZRADBn7vgZelXuY0GfapwioYFX9lBX4US8UHNvTE+saF9wb1mSLRIWQ3WmWWPsk8ImsFY/gm5WlTfh281+rRZONP/Yi47NWsq1ldzCqZyhTvzUoVSjbvxTguZkL6yz2tor4iXdn4VZ1vnle6v5Yn5uhsJQqynlYbmgyt9SK/pOWLp1Z9xmYdpLrrI76fhJckPp/40MRLamIYXGgRG0PlOxJ6hoQtLtIXJLlf0MwYvqAiHLxCaDRvpnHpkbc+FeZJpO/ZmLyrrPnI3ihm49UhxTmD0YOpam7F98UXdVDDI7j7s0KNjHcDCfsS/4u0WdWLzIoe+q6A==
*/