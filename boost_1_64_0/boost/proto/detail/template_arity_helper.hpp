#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/template_arity_helper.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/template_arity_helper.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // template_arity_helper.hpp
    // Overloads of template_arity_helper, used by the template_arity\<\> class template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/template_arity_helper.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<
        template<BOOST_PP_ENUM_PARAMS(N, typename P)> class F
      , BOOST_PP_ENUM_PARAMS(N, typename T)
    >
    sized_type<BOOST_PP_INC(N)>::type
    template_arity_helper(F<BOOST_PP_ENUM_PARAMS(N, T)> **, mpl::int_<N> *);

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* template_arity_helper.hpp
50jISdqMEMQ21kKXTVobOmCDC1ry7CraH2ZV6AaflVO60p9ir1Gb6nVXpwV3LcTBzVkpb5vLwaxaL7fOS66wM8SVupL7hFfeWbJFY+7giJ/rrNdWu7IcAXmtXmddvr9zNcQ1W86d+4/4WWgS3XZ+BnbZiqvXZdtd8bOUbp31Y2NeDo3ahe/SD+zx+8ykgx6Z9u1dHna9uqmaZkp5wY543tjt59TRVXsqtkoR7/f4ylOpGX4Svu8y+KZGfAYv3uTylVn1wSnVFyUXbfdwmXnoYmCtrs8+9vi5dlVp4qvnzHb2s4ad6Gf8DNkhaTsvP+fanY9KbjY2ymhU1EF1nKqW92iYg+mxynvgPTZHlg7iCEKdHVP9jAzjxT5oLMziWVKpUysL2RNhHtUI4g7duJe1DLGF7IN+HlzbcsZ5HHnYt/WqHTxE1nvewyEOrvdAVaMxcIf4Q8N4NERm/sFoiAd7azJ7iDpUxvuD+IlizXjjbafForYJng3XNtN2fkW5QJzsl0+zWRVOVw3gUW32veHhUB4anLBdns3BZWn4vHfiw7G2TDtyWHjPl+pH7EttDg9F8NgN3lUSMh+OelkSep71wQ6H7w03Vbnkura1x8eJMSb9sXhlKoE4xrtsm2nLxBFFSnfmpv0cHe11+f5dgIPeRoNkitY5DptPZ49nUmBLZFwHEGvLCzKO9F9Il/vEGc58kDX18ZkgZ66V7o663OvYUT8MFJ32yM4AC0mLb9R4kIP7KJobC3GYxTbbg4Y4rND1vk31FPvxlWWXfh771ck68yBn3q05E+Ign9K33L4AR/5sRF8+5ciErVA6GYsU7T3jcMcS+fQsmQdy2skwhyLFHPdboz6PvRYu6U2peyHy7mFyu4dp4PsjT6dxtttiOo0YIRl37HRUGraM2zajwqc6DZbxE1+4kiNl/MzH1PUZ17wVTrYleBVGn03Nb/dxYqzY5cWrkc2ieg4gvrom3k99INPk7W4+dyJN05DwjTkeYnEqYh1DmJOX3qdYZxDmcSCI/lgIsjivUB6iXUFuTeaBv2tB3rSLTobTXzl6BM73mhVwp8T3zXYO5CtVi78u5zm/+gEKqt9n2wLfH1fL1H+iHTIOWFDFIlN8tmyGkyWW4c923GHE1Q3h03jMz5GlFnOVnV6uEbuhKOpz9h2OPCzeU2jOkPvkheTLIrGGHJNtl06m0PgFj2TRWEHcQbZZbRDR4jqwGdOgocrn6jJP8wuJ2SJfA2zxeazDpBs1uMCoGCr7PYeZi4+cScbv7XD65ol0/uhl0McC1eGhfRajhh1/W6UeSPqzxaGq7wPsCHGwWMTtvhzXO0JyMW/nuD+FuDwUVHPjQQ4FUp2elnqG1MkcvLMLtmQU/iOSI8KlPdmr9lvh6gGN6kZl8uiEttd9uNtkUMvVejuNFkpr2pa1UVE+paK38/ufe5zwl0Ui/Igb/wiEs42vXdY1tjldOY82vlW+UztqsuJ9WGTlnnaXycJlqWK1Un2pUq6XWuId0RAH40bodO7ZXElxqlFicYL70ViAA3GCu+uTN/mKKVveo15uapo4fj9nr8XlQEnNFzfKTfXPviOnZT6X2UIcaT/+vEE8ym7zt2sACzLZRmHEx4EBod4PHfLKgs87pCruegc5bdOb2e5jYL0OhxORfot4JMglgeM+6UsT552+yaHeK86PBlkyJWS5mQEs6cGJrfhZoNaq/TridyYGsrqtu77yo5FiqYzfJa0P99Yp2vbwHZWdPmZD7ebhWmXLe25Q9+UV0qZSifG+ORJmZX8742sv3Fc3jtJY9+VVGl/jBIWGJWJdccMre436Vp3PGnYHudQsHC4JG/T7I16W+iGnXfdyaIE=
*/