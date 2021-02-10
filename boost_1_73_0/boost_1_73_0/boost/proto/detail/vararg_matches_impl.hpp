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
AAAAAAEAAAAAAMNWPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUol8gWf4AQAAJwUAAB0ACQAAAAAAAQAAAAAA4Vg8AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDQwVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUvq/Ni1MAgAA0QQAAB4ACQAAAAAAAQAAAAAAHVs8AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDQwMFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIoC50/bQEAAHkCAAAeAAkAAAAAAAEAAAAAAK5dPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q0MDFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSEp5ArQgBAAChAQAAHgAJAAAAAAABAAAAAABgXzwAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NDAyVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuVJJUBhAgAA8gQAAB4ACQAAAAAAAQAAAAAArWA8AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDQwM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJH
*/