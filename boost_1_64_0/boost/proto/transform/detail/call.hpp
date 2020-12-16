#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/call.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_NTH_RESULT_TYPE(Z, M, DATA)                                                 \
        typedef                                                                                     \
            typename when<_, BOOST_PP_CAT(A, M)>::template impl<Expr, State, Data>                  \
        BOOST_PP_CAT(a, M);                                                                         \
        typedef typename BOOST_PP_CAT(a, M)::result_type BOOST_PP_CAT(b, M);                        \
        /**/

    #define BOOST_PROTO_NTH_RESULT(Z, M, DATA)                                                      \
        detail::as_lvalue(BOOST_PP_CAT(a, M)()(e, s, d))                                            \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/call.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file call.hpp
    /// Contains definition of the call<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/call.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_NTH_RESULT
    #undef BOOST_PROTO_NTH_RESULT_TYPE

#else

    #define N BOOST_PP_ITERATION()

    #if N > 3
    /// \brief Call the PolymorphicFunctionObject \c Fun with the
    /// current expression, state and data, transformed according
    /// to \c A0 through \c AN.
    template<typename Fun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct call<Fun(BOOST_PP_ENUM_PARAMS(N, A))> : transform<call<Fun(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            BOOST_PP_REPEAT(N, BOOST_PROTO_NTH_RESULT_TYPE, ~)

            typedef detail::poly_function_traits<Fun, Fun(BOOST_PP_ENUM_PARAMS(N, b))> function_traits;
            typedef typename function_traits::result_type result_type;

            /// Let \c ax be <tt>when\<_, Ax\>()(e, s, d)</tt>
            /// for each \c x in <tt>[0,N]</tt>.
            /// Return <tt>Fun()(a0, a1,... aN)</tt>.
            ///
            /// \param e The current expression
            /// \param s The current state
            /// \param d An arbitrary data
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(BOOST_PP_ENUM(N, BOOST_PROTO_NTH_RESULT, ~));
            }
        };
    };
    #endif

    #if N > 0
    /// \brief Call the PolymorphicFunctionObject \c Fun with the
    /// current expression, state and data, transformed according
    /// to \c A0 through \c AN.
    template<typename Fun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct call<Fun(BOOST_PP_ENUM_PARAMS(N, A)...)> : transform<call<Fun(BOOST_PP_ENUM_PARAMS(N, A)...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value // BUGBUG this isn't right. Could be pack(_child), should use arity of child!
                  , BOOST_PP_CAT(A, BOOST_PP_DEC(N))
                  , detail::BOOST_PP_CAT(expand_pattern_rest_, BOOST_PP_DEC(N))<
                        Fun
                        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_DEC(N), A)
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    #endif

    #undef N

#endif

/* call.hpp
VKjZ/MtyibumA1LusbFTrZ3kUatSkHelaVP7MbBlz5rZZ0FAlNvkQbmjosyI2U1CZluemqexhJXNUFavg9aToH4HTYFFLFSJBT61nZ09NMLkTFpP85GeKaGhjQEEJEOpGdorQI4LMwIso/ConZqFFZiJfBieVt6zSnORZcdSRb03aHoS1B9JUGARx81SxmX7S6ckF3WHiTJZ1dWyGf2XtnHCa7ZuAyckytqLbqOnwIixTJnYovEFBFVrUw60W8mNLSPsSTAUmYl1RlIs4sEJSWvLZOWrpPewX88hK0Msla1MczKq90phSYIJViebXufQk4OpmExybYXme9aR8WR1rQ8EuDzhnnK3ORHRWM+zmt1kBUZxMJyVGeCsWb6/m3pHMPlem/o+JBrz1RyjRPpRfllzMaGAJOvrNRcTynJhmhSJNqVaG5NVbdWa0oK2BEplZD5KUwGQnKsZzboWEIy9sOYaUTkezGiuxJRU855CZ3vQ7OKEwZ6LEzTXOSZd/aDJQLlV1d6gbAw3HhMQ5YYblPu/yoyY4Q+ZfnD4HSB5pR/Q80Wt5EwRTfgi42N8ciN6kix6W7rmmglpBvq9FX5HDvDUq4eeBPU/dqLAQn+9TcRCc4gW6ZnKNPTOkIBkKAlDrxHJcTHwZlHUNVEfwmYI8HqhPmKdiGhYet290ZUZhXVmZg917Vf7O9o/M+/xC0gysYzmAhlZLvEgj8xGJRUfCwySzEWMOBUsFlLd2KLj65Z7YFFvYCXbEhBsw1mQpFksqK9nUm5tRjv+rF4b35OgfvOlwCI2c4nhF8fz/EB5swH1nULi9LxxyOxI6lRG3IqTkpzvCVceyM/2ZDWdBpeeEYLyuroEJEO5ar4Dq8Yl1GEjb8pqTrQswTppE9MqHQR7TqKMPYuwOqSXlToVW9ZqMHrm2CrfvImckrGhjihu0VxLgvSjfKtmCyMgyfprzWZHlguzQWeysIOveKfn53ubKmU31k3INyVpM8tDOgb6DW3QLiAZStrQnu1yXOKRI5m1+Y7yVuq6w7xIz5TP0BomAclQZIaWNclxYZY1SIQwCIi17EZzom9JtsduZF3SvxA0stevAot4P2CJVWAavRTNriuSx2Uz8RqHgGAoLBMvdkixiFd7SIQrhWLyNXmFEV9hNzvjrxv3JKi/5kOBRVhD0u912V4pW1sqkfBtT2GuLSqHcgclTs+7a82uh4AkK27N+Q1ZLnGtysyr22XpD1zaZYVoP/HnzfSEJsHAlKEZfyPz3wga2aa/yUJ3HRDSM4LWHPNJQDIst5lRZUkucRXIxAm2Wys6nq/q8pbQHYpAen6gQHfoQUCSWeSjqVayXOKNZWQGOWzlII7vYuPOkoYtU4qF/kc2NBd/Gt/BqifBUCx6S3QVWJjausfgF3h6EjS13aYUC1MbcJo3q7E0orSZDxwgPR/vafbARCQbkjAUYctxiW1wmbF7/9q2VNZ1KiwEMvUVhUxa02YiAtzAlGYoISDaEpCpD6RKM2rXBe5JdFstv5LBsIF0t2eoPjzseKqfY2C+EAGgWkk0dh7+Z2LmPrCLlnLOWUK7NQmZN9fwP3WDVVnurzlPpD7h207P5EhzwjcByVA0mhO+alzCKtCc8O29iFlz7aQ0A/3IueX1NOcWQYDtMpnaEkZEtCEwU9vESDMKJa+7dUzPgaAwg3rhuQIL/a/6RfP9yhNzcXp+UYHmxJzB3ltPgmPRV+vJwtTOq4OG90VeSnfaCen5GTTNhk9Akp2V02wLZbnEOw8oN4+aL9IYf4OsJ0F9JVNgoR9/Dfab/UTUYO8XmI1MTSyh6fOQftTgqKaPE5Bsl9vAJ3ckuYR1YuTDPBn1kJMhwMc=
*/