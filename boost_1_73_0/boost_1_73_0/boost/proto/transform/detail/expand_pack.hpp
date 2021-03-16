#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/expand_pack.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/expand_pack.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file expand_pack.hpp
    /// Contains helpers for pseudo-pack expansion.
    //
    //  Copyright 2012 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/expand_pack.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else
    #define N BOOST_PP_ITERATION()
    #define M0(Z, X, DATA) typename expand_pattern_helper<Tfx, BOOST_PP_CAT(A, X)>::type
    #define M1(Z, X, DATA) expand_pattern_helper<Tfx, BOOST_PP_CAT(A, X)>::applied::value ||

        template<typename Tfx, typename Ret BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct expand_pattern_helper<Tfx, Ret(BOOST_PP_ENUM_PARAMS(N, A))>
        {
            typedef Ret (*type)(BOOST_PP_ENUM(N, M0, ~));
            typedef mpl::bool_<BOOST_PP_REPEAT(N, M1, ~) false> applied;
        };

    #undef M1
    #undef M0
    #undef N
#endif

/* expand_pack.hpp
Oig0K5JoTv0Zf4zEwWyjPr99+K0i7yVVAkuWAQt2KCyYC/wxlfrRizSrgcwWHC/t4dau1JEPae+/cX7uFNhKzOjelLZBmx18HnA4be8CLbcdAmP/JfEMdfD7eRI/HCqwsgTo+YjC9/UE5vVRWEu9yV0gMfELgTM4jnb7Spz9J33cCRL/6itw3XvUH8pu1QTq+ZsSA86kLIkVl48BulH3K34i31cFzllMW3iB46H9i3nAiRsk9n5R4o3TgNefA5I=
*/