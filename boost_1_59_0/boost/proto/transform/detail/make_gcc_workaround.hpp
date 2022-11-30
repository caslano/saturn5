#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #if BOOST_WORKAROUND(__GNUC__, == 3) || (BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0)
        #include <boost/proto/transform/detail/preprocessed/make_gcc_workaround.hpp>
    #endif

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_EXPR_MAKE_ARG(Z, M, DATA)                                                   \
        detail::as_lvalue(                                                                          \
            typename when<_, BOOST_PP_CAT(A, M)>::template impl<Expr, State, Data>()(e, s, d)       \
        )                                                                                           \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_gcc_workaround.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_gcc_workaround.hpp
    /// Special workaround code to make the make\<\> transform work on certain
    /// versions of gcc.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #if BOOST_WORKAROUND(__GNUC__, == 3) || (BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0) || \
        (defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES))

        #define BOOST_PP_ITERATION_PARAMS_1                                                         \
            (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/make_gcc_workaround.hpp>))
        #include BOOST_PP_ITERATE()

    #endif

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_EXPR_MAKE_ARG

#else

    #define N BOOST_PP_ITERATION()

    // work around GCC bug
    template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make<proto::expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<make<proto::expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;

            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    BOOST_PP_ENUM(N, BOOST_PROTO_EXPR_MAKE_ARG, DATA)
                );
            }
        };
    };

    template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make<proto::basic_expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;

            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    BOOST_PP_ENUM(N, BOOST_PROTO_EXPR_MAKE_ARG, DATA)
                );
            }
        };
    };

    #undef N

#endif

/* make_gcc_workaround.hpp
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
*/