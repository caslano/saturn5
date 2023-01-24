#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/deduce_domain_n.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_COMMON_DOMAIN2(Z, N, DATA)                                                  \
        typedef                                                                                     \
            typename common_domain2<common ## N, A ## N>::type                                      \
        BOOST_PP_CAT(common, BOOST_PP_INC(N));                                                      \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/deduce_domain_n.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // deduce_domain_n.hpp
    // Definitions of common_domain[n] and deduce_domain[n] class templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (3, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/deduce_domain_n.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_COMMON_DOMAIN2

#else

    #define N BOOST_PP_ITERATION()

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    struct BOOST_PP_CAT(common_domain, N)
    {
        typedef A0 common1;
        BOOST_PP_REPEAT_FROM_TO(1, N, BOOST_PROTO_COMMON_DOMAIN2, ~)
        typedef BOOST_PP_CAT(common, N) type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };

    template<BOOST_PP_ENUM_PARAMS(N, typename E)>
    struct BOOST_PP_CAT(deduce_domain, N)
      : BOOST_PP_CAT(common_domain, N)<
            BOOST_PP_ENUM_BINARY_PARAMS(
                N
              , typename domain_of<E, >::type BOOST_PP_INTERCEPT
            )
        >
    {};

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* deduce_domain_n.hpp
hIFCmqW5syo9FVI4jpHu2N6zzeu/v9Mb8wW6/bEufeR4rMfX3R3zdfu3eQM94a7w9j5vRyeD4wgHMN5hLJp4ZsRie8MEY0bykH6sL5WAtzPfhwNaMqmbgbFx14e8nd2/HtET4xW1a41mjJNa0lL3FD2OWVTuOniN12oKq0c9aZhWRk9c2hHRtTj8uSJBtBXGvrRjvdfb6V3v7ez0wgqucIY1po2717KWw7vLnyoot7OkHHz2Q8FU2uo3kjpPqpzgQCo+4S1NsbxgWcy1oKP7hsJHK3bo19VxMzVqamNjsz1MPamp7rNuqjPmQ72iJtr0MSynEZ2DkArx1bRj4w51Sf2S+oFUxkSfafor6ohuqbNoNqsjCeOJjH4GxKba4s5SS4d6Azm/zyRn06tx4/jxayaeNqu4mDwQBE+mxtQRoz2OZZPKpDu8jhEQ1KK6NaSZo7rF8TA6rp1KOj46w/qx6InUqWEO6TLi7G4ZGnwo3MKNc3fr8/dHwy0RI64PI/ZyhB8w9ZMGJCi5aM8j/EpO4o2zHuPuCOtpjh+H53h/9IB+ypF7jk6IOXAeDoPhJF/nCjj700YkZRpnIKaWYFdzwkbQ1N2gEUo5O9rBjHXwOPskbDei7/ZW4M8Ly+Wv+g+E1Jkku/Z4B3UE42Q4Gb+pCsUh2A6Vx6hknSLV0UqaboOmXl6s1xK61ATLC/6lVQytA5n0iUDGslLJyhEi
*/