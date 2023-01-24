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
yuZcnfjGUm+iWi7u1P3xk5iOyqmKVsrcZyoJ69GSwgFFJxNpC8OsCy8wN+lfQfRbz6CKtdoNNU1Nn+5Cs+77Eh/k9kVax7MieB2Go87hXxaxwS08G/ZLeDufc/IHzfHjmUWdvgP3S0lH6RhPKMWic0ZznFfLTeYSOmVIbA/z1oct+i2LLa+ek86XlGLriKbNZLML93SnEFVxedbw9o+WcybvF+qzj8f8c8/26g7k6xHjx15m1punkHEpGZVg9fnrfpwFXUW+sem/9PxuvA+NJtoaSeDiNigrrZjeVIIQAz24JC/Qz2e1O0XgvZ0/e1K3mg6FoiWLOenVQQMdmjUpL4geHe2Cbh/oSX7upUcCYA7Y8CwVY/14fy5FrRxBC7k5ukwFHOaRXzeA03ERXpI13ygQOXr0J1DF4Klrj8fOiDeI0j5KeBMG8C/SZF0MLeKX69NDYm51VNcNtVZA32rYd7n9FsOCbnbYpweVPTWrb/M/DQ/oghvDpIddhDHj9jt4oDvIBLTpN1taWlffEUj8AfHPq/5Mlwpb6j1ZyivPDlsUW4Z5BB2Yyyrs36qGEbrmlK7oVxvMEIwOfF8JVwEQ9TLqGtopBjwkaEvXnOySYEvYvFkE6r3mg+KD5oPq33n3BuuS6hrSN7dBfZd70Yf4thW0hbr1fovOXOYy0BT49hy9xz/kHi3e9+xePetmqZpKUGECddd3VtKchV9Z
*/