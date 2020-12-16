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
ZPHSWTRmRAV/yCp8GrWDGOvXMTnuE/FLAjiKP+wYS9+hE/zLx9LpaqDVf05vbpOV+/XNwe9IbGS2xs+E38PuqXyW9Mlj11ci3+mtNu4GvanPq0Tf+liTrR9ofGP/a2x7Ajc2nhukvv5DNl4MCf+SRZrH2JtbbQzO7fpqluZjlBx7z0B+Mc7hX86zTo0IGvfD+0ae0eh8i5rHxtjFVn8csFzUv0T2fDjbc71fnFWsgKaKD+IM3zi4XfiQheIOzW42Vuv2RBm+ss9ksmnc03ysB/61DF+H71eLvn+OxYP/2L69W9Td9S0LyF+fBzz/XcDdbE5UUf61x/NZH3pQ9KELSIfHiHmga2tvAl7TvdnhATpraxez8b1OxClvQfoS9uHzt7eKuiOvf92BZOpi9+3eIeQAzv52QKu/zd8VWG6dulyUK/vTe5hNntxk58/cH7xPtIu8+/F+hr8xAH8l8HKOCxzs36+jq0kHZXYv5UOAyXkbYGPKuEaUATm9c6jct36E9AP7tXyR3hMwZ9hIMba2v6pYS/gEs689wr4+CRybn8MWuT/EPE2M828WbXSP6BefFfi7Bf4GFvfJfqzr2SzGxJtAfwjw0yw/5rO4bNPUF4XvnivWYV4r9hgTwse8hulpjsB9ldr7S8J/Q15fjPV1oruN6E6b4r41jVsQ/X2hTXqVN7IqlegKRfH0QjgVi3eHzZrlQDTRj1vUPRGc36P3qCfM0x+PrYrjHm1kfZjyTJ0wD65h6HOBXSjmyX3PkxrAgcI4hOzr7onEE0mXR92+8OiLbQjioXY/OxGTnlgcJ4kHwGtph1qP97Sn03va32ydUMPOK9sTEOm3t8d5b7Yn0hdORuitci9F7z1vo/47E9Njnp6POdP0KfzM6NCOntxINuS9vKuc84YoEe8bV7pKWXOjOpmj370m3Bzg+tLlSiiTyZbLBuvhWgi3oZSrZIFi+58oP6+LS2BX1BwzdeELLLyvsEN59EdAPvz8dba0PTu0mPE5isGXEHwPyj5WZTQf7/e17wBs2dRMaMQcgq1kPSTqspLO63+7lb3CMTW1IRJd2gF9RrvNFvUGR78SSu8ycj1C8O401dg7fwu4rqiHeNK+0/BdVu7MGu352P/BG7JmD61Bt7OLx1u9BRjILt7WaH7Y0Wpql+8z/Rw1zp2EpY62gnGnnrpP9xsm4OWcTW2tdc5m8rZjzrMaXnaMmKHXANz5gpiDb6PYgo9F94rx5Xw21nVC7z8kPNoUvHGulcaCnxHvI0E7UznrSgspT4XtA3RRHGnlm6l+QTx+KeTTZVTF2sL9RPsA0Vqcreevx/KB3KxM8Pkt8XkwQF/fJz4PsdjyGbleB54PA8/n9I8Qz9PE+PlHodNHWYwH/aAdbFyEfyED9pPddSYmH+iAs/O/Jxiuqvy4PxPu7ejnNO7E+pP6qIxyxiFlkrEebxzW6d5wX7+Dn2rSnfSbEPp7t/le7+Qz36eZ7z30OxD6e8x8n2G+95vvM8339eb7LPM9pDowph1AY9pTrZDEeRsjY+7oOyOYD+T+bvF2iiGvUkiTruR88Qx8V8Kmn+HxH9FzfndhPIvXPx89haOrMMDaOAEw9Pf+ULLXhdUTDC7Y0Fn9RWNEudfTI2BEudfqcwDvBA8kkghprF4JAtmsfnGnVWcl2GwXluqObYj2xULdDs8DDDzRG9uQ6uoNRaKuTHfNMO2VSjlRi4H9gGDO21EO7G4XNhDvjyUce/ghwej3wnFV14Hf44d3h/utXn5EOJzdwMDk8L7XT98bSyQ9Xj/248JrQ5E+l9dP/LhIP+ngpwTHc62xeBjKiOhfxu4z/H7m4hIJPNUEXYS71iQo388JB+0=
*/