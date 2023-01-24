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
r7iCwZel1UU0tRpYTyViyegjp86A2l8jfPy72Vh5bkaTPPVb+aCHpxGtdbmxEZA+N7f+tohaJNGvb5qu5NuhvYeopRg1fKdkUB0RYak2lcA/Z++hcj/pJ2kvlc3n5SHncivndDZdStDfPhH1zfZdE0WHgaZ+P2+at5EIzZQ+9UlAl8amuJltKeH44d9roRjz+cJwxt3TZ38Or7KhoUN82e2CcMXepzuFf0W0OB/rbCC91qniOkzdRL2wHdb0XuKIQmNhcIfN5yGZqf+3ZYmEuWh/yTgNr7BDtgZbdHbf8afTokC/3zktntztRq8INons94eO1+FoT5YJi2UpvK++MpzOPVHfJFvbzlp/P22NN1P+uVleQHdOoJhrU+rWOPZk+Wpy7tcFe86WXZ79nW8CsVll+ZEs5Bck7vYvy4KJHdxjej+o5m6IvxoNgj6S309jm8oecn87v5uUBd7HK5oRUuGdfIk8hexKOPVdlGyN2pDkC2KefD0Qs5nVsJ+vy2Bcx1IO/C1owzwpihH6CD5VfRI4SuqNOYGUV3iTKMdTvPWbjrG86OybQmnHpho6i4uLc2BYEREYbOqxm/3Vn5RbPydBMOB5XjFe0xCXo8OO/2hN7f7p9mu9+XWR/VD9tH9wcepeunjm5sNYUCw/bq6R/eVhigrRQSUmvwxuiHpiKVZt7W/92OY28oOsnKbLobKnPrZ6wbG6W1MjKf47
*/