#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/vararg_matches_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/vararg_matches_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file vararg_matches_impl.hpp
    /// Specializations of the vararg_matches_impl template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/vararg_matches_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, N, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, N + 1, To>
        >
    {};

    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, N, N>
      : matches_<
            typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_grammar
          , Back
        >
    {};

    #undef N

#endif

/* vararg_matches_impl.hpp
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
*/