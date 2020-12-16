#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/class_member_traits.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/class_member_traits.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // class_member_traits.hpp
    // Contains specializations of the class_member_traits\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/class_member_traits.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<typename T, typename U BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct class_member_traits<T (U::*)(BOOST_PP_ENUM_PARAMS(N, A))>
    {
        typedef U class_type;
        typedef T result_type;
    };

    template<typename T, typename U BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct class_member_traits<T (U::*)(BOOST_PP_ENUM_PARAMS(N, A)) const>
    {
        typedef U class_type;
        typedef T result_type;
    };

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* class_member_traits.hpp
2r8NepqfxTS50crCNtXTnJ6dRvO3mKZBYx5ZWEcDreI09yI543WxHW6OCVa6QsPpeR7Cv26s9C2EwG70na5AtIcHtFmX1aY2HaflveO0Rwe0bVLoGg4DRgu9nF6vGtBa0+a10TKmnV7vgwa0cLmsyzyvGC2M1PR6Nwe00hZ4eKmYNq6X5ukzOO0J2+gmN3mB8QG8D8esjwkZ4XZlm9umrhD3wgTuOzjuydyYquxg/u+unrjv6RNH43n7eY57qpFNkUgpkW/U5tOE//UI35ZNVco86fHX1j2+n7Mcv0XVOGpJAkEYVWZ3wWmMyKwsdF7nnuY4I/KxIF/P21WlaVHZNHMkq2d9Py6jOq72+oH9fp3BRDW+Dk5FNDfkNEboVGXGqoa3C4gGMSOjdpmmTWVS99VsT2nX3eJ2pV2huizPfB2cimjm43Y1ncqTUoVmMRrfriVOM19aLTM4OAUYqq3wD5/43OwRPtrBtEljenzo9RB/M8LvcqULm2Q9/vYk/jMifFm3TaI1xA2Fo2hqe14S4Vc5SBOFdeihOQz/tRG+Vo2ReVs4gmnt+UD03WrbFLA0cQ2xPYTzvxThly2ICo2uEX96ez4f4bdoR62tdPjbDH+W1h3HbzC1UNNqmTiCkyeizYlovjegKXRWFalFGtwIPA2Xj37JaU6WZaeT1MCxdzZ02+P+PsKtG62rtssAN3Q5xCSJcLu0khJWD+BSd/lafgOXFdO8UcaoGnbU0d5caHQYy2tF+LKBFldVQvjQ7AH+TSP8sk41yGqe/eRcuCzC17IobJPangCaP+R/b44/n9oGVlcpBRjhnV+Bq4f/tindFzl+WosqbVUBx4hoNkZ9osKRt1zkXJjt3lrEIwEeRapKrUX/ynua0fFYKnucDuaT7SqTJkXD6j6/PkLdb3gw5qy4Xv0VURukUEmV1rbofBu8lWVPyuKUvSNqhxSws9awJ+mD28GNNoPfzDcH4yCVbnCt9Dd6Ng5xfKwfRXSlKDOQR0tTs/odh8nun/M+O4P+lyD5gvTrqx52P6Wz6PJBPget0IJXTal7yOKczwUX8ciFTcq0LJNK9FkATuOlbPIDJBnN2Yi+E2lb5TqtTWhDnE+Ac+Jr92Gcz3yqizozBmfACGytw7Vig/p+btD31JZK2UayeokWnt7Wx7HJKIaDjxucglDFdJS9HaC8MdlHlQBH/WTvd39zsgd6AZR73aQDEs2hlzrY+UG5+Igr39105T7Gw2egnOkjqQ0+lt/nAe50kQ7E4v1f/BbAvC4yru/333Ow0Upc39EfUjkj4n3+CcBRz+ggy77PP+/Lp9S183sH2+qJfM4rKL0C6R37mnz+2msBjHSOQ9h9AOb0jT42n2/HtQHm9Y0x3QcOEczH8few79yYYLsTdDtYX69jHNb3+fsCrNcxDmE7NwdYr2McwmbuADCnYwww8jnkNoxn4bmc6XEPXZHBHjMCX64Qr+MZY5s6Z0DbYX4xCBu5uzkjyWb8eRzufPIBZ239zP4jfUyPlzw58qvHhw5nIL4d6nlljNMU8F7xOOguwV87AUff+hDf4E0T8A0YI+xJiC3yjgmc3XXwegFbxoDz2Z0hDswV1LcwW8D3PdnbyUsMTrqwDDbAEB90eTR2g/O8PhLwWhXjeF6ffHIcdwQ3Bnw+6kOeeF6fPwAPgqvs34VivzD7R2Thoq31HkMr4EcDR6+fmxTPc8frE1b8+o9hsF5CDIOX3HcMcwmR9jfga++d216bWe7bCW8GjnYdhm378QGDx0cRh9z+c257B5is7IJd6/r1aa/IcA676TtL8jbfd42obF7IJlOCPpLsTEa2897fgNNILeq21iDmlv+dzb4D8Pg=
*/