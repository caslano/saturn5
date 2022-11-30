#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/pass_through_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEFINE_TRANSFORM_TYPE(Z, N, DATA)                                   \
        typename Grammar::BOOST_PP_CAT(proto_child, N)::template impl<                      \
            typename result_of::child_c<Expr, N>::type                                      \
          , State                                                                           \
          , Data                                                                            \
        >::result_type                                                                      \
        /**/

    #define BOOST_PROTO_DEFINE_TRANSFORM(Z, N, DATA)                                        \
        typename Grammar::BOOST_PP_CAT(proto_child, N)::template impl<                      \
            typename result_of::child_c<Expr, N>::type                                      \
          , State                                                                           \
          , Data                                                                            \
        >()(                                                                                \
            e.proto_base().BOOST_PP_CAT(child, N), s, d                                     \
        )                                                                                   \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/pass_through_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file pass_through_impl.hpp
    ///
    /// Specializations of pass_through_impl, used in the implementation of the
    /// pass_through transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/pass_through_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_TRANSFORM
    #undef BOOST_PROTO_DEFINE_TRANSFORM_TYPE

#else

    #define N BOOST_PP_ITERATION()

    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;

        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , BOOST_PP_CAT(list, N)<
                    BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_TRANSFORM_TYPE, ~)
                >
            >::type
        expr_type;

        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_TRANSFORM, ~)
            };
            // Without this, MSVC complains that "that" is uninitialized,
            // and it actually triggers a runtime check in debug mode when
            // built with VC8.
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };

    #undef N

#endif

/* pass_through_impl.hpp
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
*/