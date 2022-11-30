#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/context/detail/preprocessed/default_eval.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEFAULT_EVAL_SHIFTED(Z, M, DATA)                                            \
        BOOST_PROTO_DEFAULT_EVAL(Z, BOOST_PP_ADD(M, 2), DATA)                                       \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/default_eval.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file default_eval.hpp
    /// Contains specializations of the default_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (3, BOOST_PROTO_MAX_ARITY, <boost/proto/context/detail/default_eval.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFAULT_EVAL_SHIFTED

#else

    #define N BOOST_PP_ITERATION()

    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function, N>
    {
        typedef
            typename proto::detail::result_of_fixup<
                BOOST_PROTO_DEFAULT_EVAL_TYPE(~, 0, Expr)
            >::type
        function_type;

        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFAULT_EVAL_TYPE, Expr))
            >::type
        result_type;

        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }

    private:
        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return BOOST_PROTO_DEFAULT_EVAL(~, 0, expr)(
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFAULT_EVAL, expr)
            );
        }

        result_type invoke(Expr &expr, Context &context, mpl::true_) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (BOOST_PROTO_DEFAULT_EVAL(~, 1, expr))) ->*
                BOOST_PROTO_DEFAULT_EVAL(~, 0, expr)
            )(BOOST_PP_ENUM(BOOST_PP_SUB(N, 2), BOOST_PROTO_DEFAULT_EVAL_SHIFTED, expr));
        }
    };

    #undef N

#endif

/* default_eval.hpp
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
*/