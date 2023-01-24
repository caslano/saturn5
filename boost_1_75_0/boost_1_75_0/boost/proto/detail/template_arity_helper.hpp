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
b5jdgj2VvP+GQVuIRMl6lvXXkS0vVpRN/RFZ3Fh0bZNFQI3OT54cZUmbfJmzUKl0W4FjYrSSn5qfxJLlGJxkQ8oli6KmmQebp1iyhFOUqIs7BliirkoGb3U4/FzF4x3fEt8yN8j1CubrQNVDSr1+pjYr7alVfRF9MIouvTmRnxv1HLveSA7IbpTgpOwgLpAzz9bwEkQYC50QT6tM5fDUUA9k9VQWh8xgtDjNtGaMLrfyjNugeJormh3/kKMrngjA1Oh0ymtoiK+kfL+DWUJGVWMno4dWtMObxjtW4htlSX0AmlJpkIuNFlCKypxhgjvSVnCwrYGL4+OpEKR2FZqXHmPMU2LQIQn3JQxe0uZ1KANdwtinyqLRwFespcX3ot7TpAFfF3dGNyQ/2FJ5ebDBzzQLNQNUL9kiKE7nn7dPAkGofYfE65/URAdvKXsF3CTMYP5vFBCSAfnZBfX8ui8pFHh6j+pBFWBqduhije4zAQBZaKYe2gxlCXIHM9Ucqx5hBUlD8NLdOZl7r/IsCe8vPqD/w/nthltds+j+ImXs44vvf/lqbnXtoU86abd8KrvsEw3DwdnbioOje2sxrg1ebeP/qf3kCDFWHrL0+NHr2TUVlm/JltIf8Hl/qokNUxG9p/Ugb4eFwcV8M5XDuBQbi1dSV9CdMpoUDCuqvgza8TANLlfMegdSuRR5Dp2Y367oGFRjJWcZh5NJnkwF
*/