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
OfKucsx8G7hRfVPkxJkdJEu3GSvySFJaj+xE4/teJ3YxV4z1Prao17C66uu2E/z/qXeP0npE76RRptHRx+d0L+e2z3cOwuKerPpguRQsADSMbcoYtj8e3kSJIZ/4toJORI+t56GVTE+nZzvlxsZ1im8ZHytwFVO1Db5x7fgsQn4hoQ+xQb9Y4Ec0XTteCcHW47aYHGC0hzGJwXeJ4q+qru2U0ILNnLrH8Zd/WNTlmTZt8L1vaFuH9Z1IkGOMXUI6FwrerhMG8t7pOP5LWdHD/AZTzG3T+V5pE3nR5w986FaOWf/ukh/yPTdtLQJz8/GAizAiQuBrCMUTFxcYAcxuyrPj4cx9MKVzWXXBGu2i7DG6uw9xLV+m8KJm0gRj6qYq6p0jz888iJt1fLok79kBpbVqrTOVblsWH7SvnY75sNOiv5yZ3gfVyr6oFxAXOxtvHzb46VE6j+SKuxriPp3AITO+Xz6GsPmMN1LzvqMKja3lV+oJ7ed3KJ1H+KYyVSV6dkJ84lbzGhzNq5Ky595rUmd5Mg7sTuw69hMMcwr/yboWDp4QT4bLbKjzhhSWdyyC9tJ2FfMAvHiNEQFzFis0v3lTOg9Xvha9hzi8zx/Fgb9M4UTDdLy4m6rB3Hn0GZceUnNhcujjcdFHW4c4sMGyvRglF/t4tUbbCwoL7HIjhOmNZbNJEC6F8FlNuLHaJEmV5/g7i3YLZkzXVMD/VofXUtuaRWPktPgZyc/13GT/Vms/RB2MnzmWb78My8FAb2bsF+2dou0o4g/l0820wzLtzx0XuHNl2YD7nXm5i0EaN1+yc3IUz+sHoi3d6ZCXrJFOrlW9froUG9pK0KgWeXS+SmAJwAbSeuHLzqWFea8zrS+9INvUpTeTyfZzISJurouUX30+Qgy2gi972VCesjedXQG1zZX902lMdXWIdnMHqc0bT40K+RojBs6O8iEnz+FJpvXkh89Ur2X+r9e8jJbHZbIJq2cof3sqhys1Tu7hNghUYGWJbXjPsvL41EHzNH1nOsCsySdu8o2n4vhPsc8fQjoDTAqrGAlCNxDup4u0Ut61tNpzuz9F6MGeh5cpaDfS+Rwpnx/xic5MsTes7S9SOnAlJ4Bc/hVSDln1ER/7/vUl9cDWhz4hzLcIDB6Am+lqzu39zhKYlFosxpje38pw3x/BpQWUNVcZ7qdjuN24cLBSYv/6i4X+Iy8+zO9vBhgY5v0ZJ5WeQaa4f36/ZBzia1H8E61WV06wbX8+HxZ6k9v29wGOlsc2rFxFmJWX07alcgjBE0syzA0QhowtptrCNt10gEkjnlYLDlheD7degIOxH8bhjqR8Xbuml2tyPSRi8Y6HRF65f3cjsHW1rjmAzlbxYDt776UwsLsGmAcSGCj2bl0CGRo7dOPlmCcs760nxefF3K+np/LYvLIcx+c5UL58DYM1dO7TLsLhvlwCc0BgwOIkzsT06HAGkmFOEGZoC57DGeYV47kgsWGyb8Vb4J0SE9LFMPtpcVybbfVvD+XpVJ2frbtY9oGD4m6KprYruzn+d8GH1KzvNOh11X9pSwwhER4BwnWOo1/c+Q1zXehdpzD2Gj7NgFEQqInhcQpth6Yo+6y8d5RDqA0eAg+w/fNkn8HG+Id3Kf2se6c4BBZYIgPsONSHF/UFpjvbgFae2f1paiVwK8AODcwKZWHGubseQelxy2QN0SM1iT+HTBcG7UQGGgLQxZbGbzSnxHOQHuriGtlAWHXMlYVZJEYC5aWxXPiygk7DlBUi2LZm+Di3dGiH2KjvKfqlmKnq2nobsB0HR/N2LKFH9ShfLtrhWAdZC4SztB2JZ16S25/056ej/mjvelk1nNKhqafH8s0=
*/