
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_CALL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_CALL_HPP

#include <boost/phoenix/core/detail/cpp03/preprocessed/call.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_CALL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_CALL_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/call_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define M0(Z, N ,D) \
            typedef \
                typename proto::result_of::child_c<Expr, N>::type \
                BOOST_PP_CAT(A, N); \
/**/
#define M1(Z, N ,D) \
    BOOST_PP_COMMA_IF(N) proto::child_c<N>(e)
/**/
    

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_LIMIT,                                                \
    <boost/phoenix/core/detail/cpp03/call.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef M0
#undef M1

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, BOOST_PHOENIX_ITERATION>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;

            BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M0, _)

            typedef
                typename boost::result_of<
                    Fun(BOOST_PHOENIX_A, context_type)
                >::type
                result_type;

            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _)
                      , boost::phoenix::context(s, d)
                    );
            }
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* call.hpp
0pCnk0/QvVif0KPvoynMJd7v/zTwT4fvjvYP/fcukaPLBIwAElkmoB2l/keD8RB+/eFRaUwiiwh+N6Lk3nE7LQN3Wkbuj072fRrrjguyRbCBI9vnO3hdnSm8cHqvfA+dAYIYHO2/Phz4bz6ODn/xT0bDo/FbpN48+CRJ/9C+3IgZcB/UQ40J4lgsQBaLqdcFXWapy5VtsaN8YIoQIOA5PY6SvEAhKmkAdQQBFjAnCRWOBthXAdge0ABQ7aw84lIWaDlL6tJBWviLAmxnqVlrR13jQCaCMMzKD8GcJDGov1Yo/WAu56G8WILqiTjIizI+9mHHCNfH04H/8/Do9PjNP1e+R8M2FWIApB1ZsuM39GfPcOUyy5IUoF8F8VISeD1o/93+8MiOoq9CbG3dPero+MPgg8Ni/Aqj+nePGh79tH/oYghfhei3jKrI0cHg7f7Hw7F/cjwai60fftjGUWhAtGazqVEaSDPqIYfH79CU1ECpdtGJ08uN+e9FEa7Dp46dugLnzfHR2+G7GhhuBkYRBLZRnRr+iKr/4fQddj8avBkjbzZvtjabO+y/+Sd36Dd0OPn4+nB4+p47bDd3UACgw7OGDqcfX5++GQ1fD7DDD/3GDhbC3xsgHAxP9UI2b+RmZZ1qCf7h4Eg8Kz9i
*/