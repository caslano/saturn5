#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/make_expr_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_expr_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_funop.hpp
    /// Contains definition of make_expr\<\>::operator() member functions.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                     \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/make_expr_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            >::type
        type;
    };

    /// \overload
    ///
    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
    >::type const
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, const A, &a)) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >()(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif

/* make_expr_funop.hpp
la5FUGwG3AuLlMyovjwQeN+ywnjg9D4Y8DvxYc8sx1Ik7UxqTZ5iBqPAx6z5ScmSE86ZRle21AjTfNWAMoEBWo9JjK/JOMaoWtkUv0e/H+S0mTViz5QdO5ZZf45xJE6jlHlW+vCUKjhLrkWcBO52dh5NPeQ2hjOsllRCvAnAM4xixKP3Kux3jOlWyevMR60k2gvWxBVGawYruOWG6tYfSfPeu335o1NvmvA9xZp2z2fI7g3TMpbGpOVTYEB3/rxKcyarAfcZyu7tJGr6u9uGXNzFEVx/pr/+cgf0mkO7kkvCsI+URYl0PIU9VtYL6742h1YZra3gLg6jVqZt9N7XubqSHkkVboVDsJrRnOLiPPliqltvOUTBkFl6HdiXoxVUGM2r2NEwYkGWw10fw8ERj/vvMxekYzmKSJeb6QlrwFoPz1fKtQGeBlZr5o6QhQabs2KPo1OupGIIwg/zul6EKV5OwTqzpzvrusdKgsQrBLFWBG27LZffcovwag/YYIN5H+qAhtkPH1k6MkJKWmtaW1a1sK2yejtWKKZte18e7sgi4Eau21gAP7bn64e46HnfR2/+jebzAtDhQ/VBeifv3oOFsPS1wjlHopt5XFJn1DPByHOrXUJnUoXRNVt12khHC0PSgx3g22bHRv8+YMOBDgqhMFBBSNJBb9g4PEoeviQ9eNbsrgSYne+NWQrf7TZU/rVb9NixBTPXT2Bn
*/