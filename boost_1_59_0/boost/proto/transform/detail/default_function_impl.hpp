#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/default_function_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEF_FUN_INVOKE_ARG(Z, M, DATA)                                              \
        BOOST_PROTO_DEFAULT_EVAL(Z, BOOST_PP_ADD(M, 2), DATA)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/default_function_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file default_function_impl.hpp
    /// Contains definition of the default_function_impl, the implementation of the
    /// _default transform for function-like nodes.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (3, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/default_function_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEF_FUN_INVOKE_ARG

#else

    #define N BOOST_PP_ITERATION()

    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
    {
        BOOST_PP_REPEAT(N, BOOST_PROTO_DEFAULT_EVAL_TYPE, Expr)

        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;

        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(BOOST_PP_ENUM_SHIFTED_PARAMS(N, r))
            >::type
        result_type;

        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }

    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return BOOST_PROTO_DEFAULT_EVAL(~, 0, e)(
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFAULT_EVAL, e)
            );
        }

        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (BOOST_PROTO_DEFAULT_EVAL(~, 1, e))) ->* 
                BOOST_PROTO_DEFAULT_EVAL(~, 0, e)
            )(BOOST_PP_ENUM(BOOST_PP_SUB(N, 2), BOOST_PROTO_DEF_FUN_INVOKE_ARG, e));
        }
    };

    #undef N

#endif

/* default_function_impl.hpp
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
*/