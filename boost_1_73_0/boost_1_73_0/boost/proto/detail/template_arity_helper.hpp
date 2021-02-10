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
SCRgUEsBAgAACgAAAAgALWdKUlbSmuEvAgAAnwQAAB4ACQAAAAAAAQAAAAAAeB88AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDM1MlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIH8OAhKAIAAJcEAAAeAAkAAAAAAAEAAAAAAOwhPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzNTNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSbvnD60kBAAAZAgAAHgAJAAAAAAABAAAAAABZJDwAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzU0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUq3cnbDJAQAA5AIAAB4ACQAAAAAAAQAAAAAA5yU8AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDM1NVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJzIykXsgIAAIYEAAAeAAkAAAAAAAEAAAAAAPUnPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzNTZVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSZgPO6xoCAACNBQAAHgAJAAAAAAABAAAAAADsKjwAY3VybC1tYXN0ZXIvdGVzdHMv
*/