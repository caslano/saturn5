#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/args.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_CHILD_N(Z, N, DATA)                                              \
        typedef BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(child, N);                                    \
        /**< INTERNAL ONLY */

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_VOID_N(z, n, data)                                               \
        typedef mpl::void_ BOOST_PP_CAT(child, n);                                              \
        /**< INTERNAL ONLY */

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/args.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file args.hpp
    /// Contains definition of \c term\<\>, \c list1\<\>, \c list2\<\>, ...
    /// class templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    /// \brief A type sequence, for use as the 2nd parameter to the \c expr\<\> class template.
    ///
    /// A type sequence, for use as the 2nd parameter to the \c expr\<\> class template.
    /// The types in the sequence correspond to the children of a node in an expression tree.
    template< typename Arg0 >
    struct term
    {
        static const long arity = 0;
        typedef Arg0 child0;
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_VOID_N, ~)

        /// INTERNAL ONLY
        ///
        typedef Arg0 back_;
    };

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/args.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_VOID_N
    #undef BOOST_PROTO_DEFINE_CHILD_N

#else

    #define N BOOST_PP_ITERATION()

    /// \brief A type sequence, for use as the 2nd parameter to the \c expr\<\> class template.
    ///
    /// A type sequence, for use as the 2nd parameter to the \c expr\<\> class template.
    /// The types in the sequence correspond to the children of a node in an expression tree.
    template< BOOST_PP_ENUM_PARAMS(N, typename Arg) >
    struct BOOST_PP_CAT(list, N)
    {
        static const long arity = N;
        BOOST_PP_REPEAT(N, BOOST_PROTO_DEFINE_CHILD_N, ~)
        BOOST_PP_REPEAT_FROM_TO(N, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_VOID_N, ~)

        /// INTERNAL ONLY
        ///
        typedef BOOST_PP_CAT(Arg, BOOST_PP_DEC(N)) back_;
    };

    #undef N

#endif

/* args.hpp
+8N1ZLznOhl/B/C567Fm7TPw+w6v+YIzPodQx3LgrhLMX+DY09A5qyTH+w8tXgM7wfGuQ39kkxzvNfSd29GG4HiHIe86rFVPGPh9hR6rxHvRkwZ+N6F0DWwCx3sIPbAL6/mfG/idgx7G+rUjYuD3C/oEYflTBn6XoFUezJ3geG+gyzTsn8DxjkBftkvO/w+k334H6zbHB27eg7rvN/A+i36yR7YD9lS8b6IzkDNij0SFTxsEYj8kOOMbCIvA8Y5ATx7AngAc7wO856dT4Ixv96J9Dxh4n09vpLHv+r6B9/T0eAb5g2P/Tkt/JDn26rwfp+U/MAh8/QWsU+DYg/M+myx/YRD4jRHJsbemwRexhwHHPppufxl9DY49F++rhP2M2EMJzoj9krCfEXtbwbGH5X2S6GtG7LmFnPHh19AW3QbeZ9OTv8B6CY49Ne+byfqXBoHlb2FdBcdeivdLIi1j6duSM172Dp6Rv0J84EEEG/ihd+RZN36OGK8/Idt/JdDyrrSHcfxd+Xwxvvfvkp8EVr4n4zOOI9QjT8aH34ccHHsf2vEh+gOcseMj9CV4GGg9jecInPEthBPg2Mvxfo3OgDPW/gplHTTwHo33YXQ1OOPnCLeBL/kNUTNCNXgL0PMJygJvBe7/FHmBHwC++6l8pk5+Ks/TZSDns3UvfCbbh8/XvY5w7KA8fzf4uaxXChj9D/T9IYPATxFKwSeA
*/