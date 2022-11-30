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
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
*/