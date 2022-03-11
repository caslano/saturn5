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