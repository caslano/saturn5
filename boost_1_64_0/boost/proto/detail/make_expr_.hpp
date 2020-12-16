#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/make_expr_.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_expr_.hpp")
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

    template<
        typename Tag
      , typename Domain
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
            BOOST_PROTO_MAX_ARITY
          , typename A
          , = void BOOST_PP_INTERCEPT
        )
      , typename _ = void
    >
    struct make_expr_
    {};

    template<typename Domain, typename A>
    struct make_expr_<tag::terminal, Domain, A
        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, void BOOST_PP_INTERCEPT)>
    {
        typedef typename proto::detail::protoify<A, Domain>::result_type result_type;

        BOOST_FORCEINLINE
        result_type operator()(typename add_reference<A>::type a) const
        {
            return proto::detail::protoify<A, Domain>()(a);
        }
    };

    template<typename A>
    struct make_expr_<tag::terminal, deduce_domain, A
        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, void BOOST_PP_INTERCEPT)>
      : make_expr_<tag::terminal, default_domain, A>
    {};

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/make_expr_.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()
    #define M BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N)

    template<typename Tag, typename Domain BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make_expr_<Tag, Domain BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
        BOOST_PP_ENUM_TRAILING_PARAMS(M, void BOOST_PP_INTERCEPT), void>
    {
        typedef
            BOOST_PP_CAT(list, N)<
                BOOST_PP_ENUM(N, BOOST_PROTO_AS_CHILD_TYPE, (A, ~, Domain))
            >
        proto_args;

        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, typename add_reference<A, >::type a)) const
        {
            expr_type const that = {
                BOOST_PP_ENUM(N, BOOST_PROTO_AS_CHILD, (A, a, Domain))
            };
            return proto_generator()(that);
        }
    };

    template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make_expr_<Tag, deduce_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
        BOOST_PP_ENUM_TRAILING_PARAMS(M, void BOOST_PP_INTERCEPT), void>
      : make_expr_<
            Tag
          , typename BOOST_PP_CAT(deduce_domain, N)<BOOST_PP_ENUM_PARAMS(N, A)>::type
            BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
        >
    {};

    #undef N
    #undef M

#endif

/* make_expr_.hpp
uRD3QZqbrCo7+6cKF4Vl70Cs05VpIj4JM6Wy5sQlhrpTJUHecK+40PPFaipV1zqsl1AfsmYKTPeKKJ1gXKiCJ5mNEpKn9hTPkDSdTFnRiDTX9fKlFnqbPoCzTh7/Q8qnZlVps6KqmbtfY50XfVD/OiqzhbdKa3KF7TYl7hypy11kFPL+B+VjWJ6WVS0z2frS6+f+GBwvF3tvAdoomRUSzi6okgSjnYzTnbCG0LSiYFmlilymvG/suHwpWknCnhLxAedwmW4kjaM79No9mHgGu93Micri+Kzvuxj3oeGKZ2VSEJ9EhIV/yAr3dkZ0CKPypKypG6PrsmCbXQCG59FQBKCf6TYGML6k+pnPfEyvfZStZF1UlM9OezWfYI18NXs6Ba+hfGQCuupJnqZzRbfNuVgFtDGl11k/HvsgPsYtUMQ+8QsRH8EKqYXRBvaQ9rjpnu1bJ3nrIC5fuKtOYj1LykulrBQqSSsrHK+2VF6IThUe4K403AZpOdU9vfDYuEylSI2tVYX33GO0YPOSQSzb+CAoJnYyiz3K64JywyivEsv8/X6I7tOILk6E15mSRjaCoZF7wAddnKisitkst0Zq5fvBFxhVqqDxHIvQep5pp9/xBcprPTXWVI3UrB0EuD6EPYlihWKyMCY1ReXzdee+nSFc+vtFeD5cedq3ChKL8w+UVyqYqCqdl7xcVoedycgLF2DRH2MUt1l7jgsxnx9H+J3NNc8gOiuEPYz3+ZziVM140cisMtWSfL0K0RjM9N0tDppv9vwRnEFDvDjKS1RMyaxOK21wzOB5nIwVqsQKstsoBvfXorJJZh07mTYcykb8H8J2jzFK+/OCBT2ix9OyGbABLpTKCwxO6lgeza8Nwz1YIOH4F1ZIMi8oH8mZLAut6iJHPpvxARlbcHeIjBmJXRTxSpmAS6bJGqLzT4PBkvPWaX8OH5A7M/JC+Qi3eSO4xrHohq+b9ygBgvJgmIKJO+R24/+nlM95mRZ1mRrOlL/vx3prv46x3MrMqtRrN/Wxv6PY9dw0jWlq9mRUXop0qf8Y1SVhVVpUTVMpt4ZFQwgudv7oBY2CoZEW7zS3fEJ8bqsTbauirNlWOw6X/DmDR8CoDqcon/UGjo22qtkxBJft2/4+pJenqYvGNKVkTxlOiRxvctDLi+P87ae3RosyM/OemELSE4r7ACxD0+ORpiKtG5UyHKSo535CGXZ66a3OdQ1n7pQcs/HPCTxe0OdRCVlkomG4Pbab4SIDqqf/ZspDSZaXSZbougD7rKNrMxjYy+b/dXNjhGhN+SnyQj8OpklABw102Y5gwi+qoaH4CwvGUpQdRrw0E1KkUpgS1wJQ7IWDViyiGuMBvTvnPzHWZculArXXOpJ3AbNFcdcRo7KEiE/FdJEUoiz+bz6ziE/OMpEnZSOS/1QvFIxCc+P4ex/lwzNWiqQWWabic58czcBypLNhP0pRzh+VI2N5ooq0KGWcfhz6PCzXUL3j7iz9a8qnZrzSJVcqY535Pexu/tYiiliO8YeoDoY1vCyyxNbtWRFPhaQ4D5CNDx177YmnD9qgsWcW/NDclMVrtdKut6XJyN3cOTZ8ioYQxcZuuZul++ecptywCfYarCcrSBKja/4/sllJ19A2kfX8qNo8r4qEHU2eD11M452YEHuUprlYcmNrzblPMj0cbs8TJMEfKotlLboySVNVloFcBQ9kXuuS7HNhLUjDWTniUzBuZG6TpsZLGUzavTbqI/br5ErvRv/EED+ZxfKkXKV5rtMU7lh+dTs9D6F+OBwfoRg8CqsW7TMrSXyv0JmudF7wJTGPjNPm2x4ewjWhKRPh2oysB49I4vWA52lpeFqzXiriqMQ=
*/