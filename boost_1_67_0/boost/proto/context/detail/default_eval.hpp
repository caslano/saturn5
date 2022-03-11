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