#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/lazy.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/lazy.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file lazy.hpp
    /// Contains definition of the lazy<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/lazy.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    /// \brief A PrimitiveTransform that uses <tt>make\<\></tt> to build
    /// a CallableTransform, and then uses <tt>call\<\></tt> to apply it.
    ///
    /// <tt>lazy\<\></tt> is useful as a higher-order transform, when the
    /// transform to be applied depends on the current state of the
    /// transformation. The invocation of the <tt>make\<\></tt> transform
    /// evaluates any nested transforms, and the resulting type is treated
    /// as a CallableTransform, which is evaluated with <tt>call\<\></tt>.
    template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct lazy<Object(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<lazy<Object(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (BOOST_PP_ENUM_PARAMS(N, A))
            >::template impl<Expr, State, Data>
        {};
    };

    #if N > 0
    template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct lazy<Object(BOOST_PP_ENUM_PARAMS(N, A)...)>
      : transform<lazy<Object(BOOST_PP_ENUM_PARAMS(N, A)...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , BOOST_PP_CAT(A, BOOST_PP_DEC(N))
                  , detail::BOOST_PP_CAT(expand_pattern_rest_, BOOST_PP_DEC(N))<
                        Object
                        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_DEC(N), A)
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    #endif

    #undef N

#endif

/* lazy.hpp
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
*/