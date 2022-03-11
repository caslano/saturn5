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