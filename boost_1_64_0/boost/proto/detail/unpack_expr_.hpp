#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/unpack_expr_.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_FUSION_NEXT_ITERATOR_TYPE(Z, N, DATA)                                       \
        typedef typename fusion::result_of::next<                                                   \
            BOOST_PP_CAT(fusion_iterator, N)>::type                                                 \
                BOOST_PP_CAT(fusion_iterator, BOOST_PP_INC(N));                                     \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_FUSION_ITERATORS_TYPE(N)                                                    \
        typedef                                                                                     \
            typename fusion::result_of::begin<Sequence const>::type                                 \
        fusion_iterator0;                                                                           \
        BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_PROTO_FUSION_NEXT_ITERATOR_TYPE, fusion_iterator)    \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_FUSION_AT_TYPE(Z, N, DATA)                                                  \
        typename add_const<                                                                         \
            typename fusion::result_of::value_of<                                                   \
                BOOST_PP_CAT(fusion_iterator, N)                                                    \
            >::type                                                                                 \
        >::type                                                                                     \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_FUSION_NEXT_ITERATOR(Z, N, DATA)                                            \
        BOOST_PP_CAT(fusion_iterator, BOOST_PP_INC(N)) BOOST_PP_CAT(it, BOOST_PP_INC(N)) =          \
            fusion::next(BOOST_PP_CAT(it, N));                                                      \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_FUSION_ITERATORS(N)                                                         \
        fusion_iterator0 it0 = fusion::begin(sequence);                                             \
        BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_PROTO_FUSION_NEXT_ITERATOR, fusion_iterator)         \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_FUSION_AT(Z, N, DATA)                                                       \
        *BOOST_PP_CAT(it, N)                                                                        \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_FUSION_AS_CHILD_AT_TYPE(Z, N, DATA)                                         \
        typename detail::protoify<                                                                  \
            BOOST_PROTO_FUSION_AT_TYPE(Z, N, DATA)                                                  \
          , Domain                                                                                  \
        >::result_type                                                                              \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_FUSION_AS_CHILD_AT(Z, N, DATA)                                              \
        detail::protoify<                                                                           \
            BOOST_PROTO_FUSION_AT_TYPE(Z, N, DATA)                                                  \
          , Domain                                                                                  \
        >()(BOOST_PROTO_FUSION_AT(Z, N, DATA))                                                      \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/unpack_expr_.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_.hpp
    /// Contains definition of make_expr_\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    template<typename Tag, typename Domain, typename Sequence, std::size_t Size>
    struct unpack_expr_
    {};

    template<typename Domain, typename Sequence>
    struct unpack_expr_<tag::terminal, Domain, Sequence, 1u>
    {
        typedef
            typename add_const<
                typename fusion::result_of::value_of<
                    typename fusion::result_of::begin<Sequence>::type
                >::type
            >::type
        terminal_type;

        typedef
            typename proto::detail::protoify<
                terminal_type
              , Domain
            >::result_type
        type;

        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return proto::detail::protoify<terminal_type, Domain>()(fusion::at_c<0>(sequence));
        }
    };

    template<typename Sequence>
    struct unpack_expr_<tag::terminal, deduce_domain, Sequence, 1u>
      : unpack_expr_<tag::terminal, default_domain, Sequence, 1u>
    {};

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/unpack_expr_.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_FUSION_AT
    #undef BOOST_PROTO_FUSION_AT_TYPE
    #undef BOOST_PROTO_FUSION_AS_CHILD_AT
    #undef BOOST_PROTO_FUSION_AS_CHILD_AT_TYPE
    #undef BOOST_PROTO_FUSION_NEXT_ITERATOR
    #undef BOOST_PROTO_FUSION_NEXT_ITERATOR_TYPE
    #undef BOOST_PROTO_FUSION_ITERATORS
    #undef BOOST_PROTO_FUSION_ITERATORS_TYPE

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()
    #define M BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N)

    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, N>
    {
        BOOST_PROTO_FUSION_ITERATORS_TYPE(N)

        typedef
            BOOST_PP_CAT(list, N)<
                BOOST_PP_ENUM(N, BOOST_PROTO_FUSION_AS_CHILD_AT_TYPE, ~)
            >
        proto_args;

        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;

        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            BOOST_PROTO_FUSION_ITERATORS(N)
            expr_type const that = {
                BOOST_PP_ENUM(N, BOOST_PROTO_FUSION_AS_CHILD_AT, ~)
            };
            return proto_generator()(that);
        }
    };

    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, N>
    {
        BOOST_PROTO_FUSION_ITERATORS_TYPE(N)

        typedef
            unpack_expr_<
                Tag
              , typename BOOST_PP_CAT(deduce_domain, N)<
                    BOOST_PP_ENUM(N, BOOST_PROTO_FUSION_AT_TYPE, ~)
                >::type
              , Sequence
              , N
            >
        other;

        typedef typename other::type type;

        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };

    #undef N
    #undef M

#endif

/* unpack_expr_.hpp
l83ROS+xPH+AwsFiEVjhdZOUNatqsa6eZ6OCiPXNHS9npsnz5DbJLr0hV1iEJS/MIQ2+O73HYfDed3VDfVVWemtC3i1XHmy368qTkvY3u89hQBakqf2X7vEytIbucVtRepLD5OpsDzruMmvlDXWiDcVQt/KFX4dXhdl2VW2hO1Vtmz4RZmFIlXiPFeZKpYrWx95wy0LjgGXddBnc2iPJ3EExn6BzqI1mpVevduJdtX7T99ROi8PwKttcynDHbEnLOWNzmB+WU3msDF/IiyP/ak31SJbj5/T78VY4jN/mBngO0HvapM3AN41TiuqU1oyPE3PGFTscX7ubbTa6yk1BATY1vJe7arF0UV/67HrEyyxhvpbQxF3qZtYt3vTQEb2N12VeLh9zaXX80hHfoVfZLHrrqPHYtMJpypB3WnI2g0oFaqomcQU/R2aaTT73tzg6osT6Bg2M/n5fGMyWOp23qwWx3ttvDuRBtH5DuBVg5XlixmbguIpKJL5H8z5OrCc/Y4dTLxb7pmsWg0eH2P7yXeXLXg681rVqvnfAbnp5tx9O0frcw08I+VTrUof7gSFxoOZJ/nWLFV23v7ZQNDi4ETrai3acJRIN0VDjcJTWK4PZs6V2DdOBJMTbnJeC8dysyfq6Zcczq1ZY/um54WlD4tAdOd6fDuRpjE2w/NMWT2dl1UoSOjCNcuZPDeYrVYs/ZPMwS1JNCQ9FrGMfxGNhy6x7NL6fiXxBr3mavGeymYAN6kW59ji2PKe6JOy3DRvUQzstZiGFL5EK5nkeBvQo0sb0sI/BsrVYT7tdMlm4cJPIZyeL6WwhdTy1FLGPr1GTgxroj7kUf8v3mUw7viQ6qd9Bs9Jqdao9dQ7ULqmTaLatHTEZ2gez3fF+M5yWxvw2324jHAyXaS3OtskHrXxA1fIe2iwDrFrgrUUOH7Pi1jrFd1Tb+p706b12OBRhA96AZhnJfQ7TrFT03N0y2i0L1z9B31llWwozDbG3oZSiMr+db+bX2dcUTFkwsOK0qK5yVl7hDhrFrVv5XGlMqaxq2R8ZdcKVeB3+5O1O+EqtocNHrLZWgXHe+FzZTB+meOyTUldj9afjqezsMei9grngY3DA1Vi/5mPQZqS9Jse3l8P7SfxtNuvUsXnIuOHUbizj0W2SSS+i/wyxTx+1wtWppP1Gw5F9FtNpqo1oF2+2ij7yfT+n1ziecLgh3uzVK/GF3/N6Lr3lY/HkrELMdIBZbWrm4TabacRTxao837AY8YhthfdmIx6mrDZwK8oNGbSt2HNPDGJF2xx28l+Mr6JT+H0nX7C1jDh82knH9IP4M0c+qG0b8ExPmcs+ajPg7Vc9+yrmht/b+QB7eHHP4a4drnSFHRH+tJ1OeGddhF9w4mMLcb+y8ghOAOT+Y8IuJ16thSfC1aXvc8w9utvk6LYKDAn1Tdd+VP0cFlueKVjpwuCkPs8276MeBhQEcJlf2KHc3ubhVlu6Lb3h0Nra5/4LffmprIHT4lW2x/DIoV4h83PHw0m/jTettOgxab6H4YTXOlDHvIexw3Hl1a6LPeAfrTzANCr9XnVJhgjHeaRvOSH86v1jr82645ft6ex0YVItKlaMid/6GOEb4nn77PB4uoynVzk/nxpxuI2K0FONjTrheOQt9Mk/cxjoXasGk9npMGDkevSI2DPe2WUxlZ76Fzyj0jDy/LS9Hk6e6VtlQuUb17Zew9l1iO1f5u+tVYein65wWhaDLxbhIJRj9ScWh7Mc2FEJnxU2k0gml9Sy8+2tZrwx5TdD9gY4tbCIt8aiDPe9LNqnsr9fH4MdqsJvSvnyls7O4Ucv3kaWWc8SYuFtom6z3Kzrb9XVIAvWIZo=
*/