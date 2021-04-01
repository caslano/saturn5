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
weykgMCdQJd4TPXUPq2RIoff3lCZTwwbMq3yPRb8OW17hUkHxBmKlNVXJJKWUD/PNwouALjqDdDvjzrc/ITmpx7gYT0sBT5LJw9vO6G1WnOF85AQ/NjQI7RzgqzR2+bVxs/R36mVvz24vaQaMe9T0KLKVGFTiQb7f1DBiFcTid8KsIg6+uEbbCHnpc2preyEKDvR7N6jt9ldmR4j/IgYF4RuwZT66b0CtJJhIFg0NVV/ckpbrWnSRyR0WzGBq5MUReFrmC2d1ye/KnUTS0fjARfSYJWVDd22Tm3AbNGNdsVIpYSFsYPE+X653t+1cDEIncaDO8LkoQuD8mpEm9xbAInh/bC5NcD7rArKHfRdqblN59B9Iyjy66EBkQcBaWY3C3r8ttdXLQcn3/ULsYjnBJ9XB+tqWm1tCWiv3SMFnVcR+yExN+TPN0MD3cmFkSY/iawRbIOgOYs1pV7rT6dVPj86O7aVGmK729RANagiUMjSTn7VsCCpqmXDKSpOfxXnIyYyH0qJXZ5WJYtoJs7KeVITlGAUG0g5lk+93HDk6tMREyQHpmrDWCmT3w==
*/