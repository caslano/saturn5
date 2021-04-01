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
+FO2Ws2Apu5JGgAxyM9QdSUj86rYDegjmXJPzw/1qUlMT5TnODvyFZ57MKkO/E9+xgkF0YecnT6xRF4NolFDK1DMqjf67MiS0elR9V1DAHrc6C4KiJjvrvEM4nLYn9sFMdGYG0c5JhWRE8j/oYQe7OJF5uRjXZp4psAw2GETng2bBmodBUYAqQfNBKHrbiSSvM1dE9euQTHqdf4iVSTEjAfA8qKMGFZAzLOXGetfPEBppszGdxQ4yXrWXFUMADOQcGLkctv+S6z35/Elr4wP/tZwLdtW9O2Lee6HtiwCXQ+ek/qSx3PaiQ/dc5olGnlIqnnlHhSaTtxlvi/288HYYVX2N5nORGIRf9alBvWWCm18QA3GlFI9U8wQ1B1SMmMk9WKX03HPhJJbuCmKAdi7F7yQYxKMrubuylsSZjbKqK3EPyenyLcoRNoW11Ihrg3sc5ENSFGhq/+nan43M33qoaAGahs/gyXkoDxR8/m8MbkTMnIXvHWLSfnKDFjjM9nQg3oHVcmNIURMqyiBz8caob0PWNYfm16lQtHx916wLMfTiIEvDF7MvuVKJw==
*/