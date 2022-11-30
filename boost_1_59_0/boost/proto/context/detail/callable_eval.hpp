#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/context/detail/preprocessed/callable_eval.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_CHILD_N_TYPE(Z, N, Expr)                                                    \
        typedef typename proto::result_of::child_c<Expr const &, N>::type BOOST_PP_CAT(child, N);   \
        /**/

    #define BOOST_PROTO_CHILD_N(Z, N, expr)                                                         \
        proto::child_c<N>(expr)                                                                     \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/callable_eval.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file callable_eval.hpp
    /// Contains specializations of the callable_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/context/detail/callable_eval.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_CHILD_N_TYPE
    #undef BOOST_PROTO_CHILD_N

#else

    #define N BOOST_PP_ITERATION()

    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, N>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;

            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_CHILD_N, sexpr_)
                        ), 0)
                    )
                );

            typedef mpl::bool_<value> type;
        };
    }

    namespace context
    {
        /// \brief A BinaryFunction that accepts a Proto expression and a
        /// callable context and calls the context with the expression tag
        /// and children as arguments, effectively fanning the expression
        /// out.
        ///
        /// <tt>callable_eval\<\></tt> requires that \c Context is a
        /// PolymorphicFunctionObject that can be invoked with \c Expr's
        /// tag and children as expressions, as follows:
        ///
        /// \code
        /// context(Expr::proto_tag(), child_c\<0\>(expr), child_c\<1\>(expr), ...)
        /// \endcode
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, N>
        {
            BOOST_PP_REPEAT(N, BOOST_PROTO_CHILD_N_TYPE, Expr)

            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        BOOST_PP_ENUM_TRAILING_PARAMS(N, child)
                    )
                >::type
            result_type;

            /// \param expr The current expression
            /// \param context The callable evaluation context
            /// \return <tt>context(Expr::proto_tag(), child_c\<0\>(expr), child_c\<1\>(expr), ...)</tt>
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_CHILD_N, expr)
                );
            }
        };
    }

    #undef N

#endif

/* callable_eval.hpp
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
*/