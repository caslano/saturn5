#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/deep_copy.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEFINE_DEEP_COPY_TYPE(Z, N, DATA)                                           \
        typename deep_copy_impl<                                                                    \
            typename remove_reference<                                                              \
                typename Expr::BOOST_PP_CAT(proto_child, N)                                         \
            >::type::proto_derived_expr                                                             \
        >::result_type                                                                              \
        /**/

    #define BOOST_PROTO_DEFINE_DEEP_COPY_FUN(Z, N, DATA)                                            \
        proto::deep_copy(e.proto_base().BOOST_PP_CAT(child, N))                                     \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/deep_copy.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file deep_copy.hpp
    /// Replace all nodes stored by reference by nodes stored by value.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/deep_copy.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_DEEP_COPY_FUN
    #undef BOOST_PROTO_DEFINE_DEEP_COPY_TYPE

#else

    #define N BOOST_PP_ITERATION()

    template<typename Expr>
    struct deep_copy_impl<Expr, N>
    {
        typedef
            typename base_expr<
                typename Expr::proto_domain
              , typename Expr::proto_tag
              , BOOST_PP_CAT(list, N)<
                    BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_DEEP_COPY_TYPE, ~)
                >
            >::type
        expr_type;

        typedef typename Expr::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;

        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_DEEP_COPY_FUN, ~)
            };

            return proto_generator()(that);
        }
    };

    #undef N

#endif

/* deep_copy.hpp
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
*/