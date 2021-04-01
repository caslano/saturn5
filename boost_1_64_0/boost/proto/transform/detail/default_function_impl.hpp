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
lFIRzlDIjMqnlLo2dkCPcJnAzymxdsIuDu2IQj0jhB2gUfbhEI1fM3X/qhGt0TOphAUxuwgxzSAWFv7GIMonLH230Rlo5lNCkq2I136mO01nh32POvP34OTkkKmmgp3HkgtSBU0p0waZXY50o8sOEcUedCZ4i9HFPwgwHhGiFC6g3U0zJloBmiJgzlnMmaBtUa0oMWHQkqPFTOGXaSo+yrIlkIsm8Fs2ETWwEsGM0FnRjZRk9zRSypN5Je5p7PLImkm8fon9m/UHVAdUMP165DGAA23I4tiC/FKiwOQeLHnJ90Xw8sW3mzwQjWu5Bq29PBwUYCnXprXefaRBg0cs4Nfbb7uvTXfiELqnSaSaAzgv7JWWzEsq3kEzc+fKF7EmHiIYoTqXuZcu4IFIG/FEuB5RhI//nvA2v4ZKwWISZKV+uqi+s7oxxs69sO09cJmz1GSoIzueFy5cr/DEQlj9H1CCn6u0awCr2N7WNzxwOuCqiVl9LKNmroorIOry+ZC8TbH4tTkUNQ7lmJV2qGVUdX5g0Oqr3YhJh2IUg4zMJADw67WL7KpKje6dqA==
*/