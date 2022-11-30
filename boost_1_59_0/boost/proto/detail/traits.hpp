#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/traits.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_CHILD(Z, N, DATA)                                                           \
        /** INTERNAL ONLY */                                                                        \
        typedef BOOST_PP_CAT(DATA, N) BOOST_PP_CAT(proto_child, N);                                 \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/traits.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file traits.hpp
    /// Definitions of proto::function, proto::nary_expr and proto::result_of::child_c
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/traits.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_CHILD

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    #if N > 0
        /// \brief A metafunction for generating function-call expression types,
        /// a grammar element for matching function-call expressions, and a
        /// PrimitiveTransform that dispatches to the <tt>pass_through\<\></tt>
        /// transform.
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        struct function
        #if N != BOOST_PROTO_MAX_ARITY
        <
            BOOST_PP_ENUM_PARAMS(N, A)
            BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT)
        >
        #endif
          : proto::transform<
                function<
                    BOOST_PP_ENUM_PARAMS(N, A)
                    BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT)
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, BOOST_PP_CAT(list, N)<BOOST_PP_ENUM_PARAMS(N, A)>, N> type;
            typedef proto::basic_expr<proto::tag::function, BOOST_PP_CAT(list, N)<BOOST_PP_ENUM_PARAMS(N, A)>, N> proto_grammar;

            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};

            /// INTERNAL ONLY
            typedef proto::tag::function proto_tag;
            BOOST_PP_REPEAT(N, BOOST_PROTO_CHILD, A)
            BOOST_PP_REPEAT_FROM_TO(
                N
              , BOOST_PROTO_MAX_ARITY
              , BOOST_PROTO_CHILD
              , detail::if_vararg<BOOST_PP_CAT(A, BOOST_PP_DEC(N))> BOOST_PP_INTERCEPT
            )
        };

        /// \brief A metafunction for generating n-ary expression types with a
        /// specified tag type,
        /// a grammar element for matching n-ary expressions, and a
        /// PrimitiveTransform that dispatches to the <tt>pass_through\<\></tt>
        /// transform.
        ///
        /// Use <tt>nary_expr\<_, vararg\<_\> \></tt> as a grammar element to match any
        /// n-ary expression; that is, any non-terminal.
        template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct nary_expr
        #if N != BOOST_PROTO_MAX_ARITY
        <
            Tag
            BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT)
        >
        #endif
          : proto::transform<
                nary_expr<
                    Tag
                    BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
                    BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT)
                >
              , int
            >
        {
            typedef proto::expr<Tag, BOOST_PP_CAT(list, N)<BOOST_PP_ENUM_PARAMS(N, A)>, N> type;
            typedef proto::basic_expr<Tag, BOOST_PP_CAT(list, N)<BOOST_PP_ENUM_PARAMS(N, A)>, N> proto_grammar;

            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};

            /// INTERNAL ONLY
            typedef Tag proto_tag;
            BOOST_PP_REPEAT(N, BOOST_PROTO_CHILD, A)
            BOOST_PP_REPEAT_FROM_TO(
                N
              , BOOST_PROTO_MAX_ARITY
              , BOOST_PROTO_CHILD
              , detail::if_vararg<BOOST_PP_CAT(A, BOOST_PP_DEC(N))> BOOST_PP_INTERCEPT
            )
        };

        namespace detail
        {
            template<
                template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class T
              , BOOST_PP_ENUM_PARAMS(N, typename A)
            >
            struct is_callable_<T<BOOST_PP_ENUM_PARAMS(N, A)> BOOST_PROTO_TEMPLATE_ARITY_PARAM(N)>
              : is_same<BOOST_PP_CAT(A, BOOST_PP_DEC(N)), callable>
            {};
        }

    #endif

        namespace result_of
        {
            /// \brief A metafunction that returns the type of the Nth child
            /// of a Proto expression.
            ///
            /// A metafunction that returns the type of the Nth child
            /// of a Proto expression. \c N must be less than
            /// \c Expr::proto_arity::value.
            template<typename Expr>
            struct child_c<Expr, N>
            {
                /// Verify that we are not operating on a terminal
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);

                /// The raw type of the Nth child as it is stored within
                /// \c Expr. This may be a value or a reference
                typedef typename Expr::BOOST_PP_CAT(proto_child, N) value_type;

                /// The "value" type of the child, suitable for return by value,
                /// computed as follows:
                /// \li <tt>T const &</tt> becomes <tt>T</tt>
                /// \li <tt>T &</tt> becomes <tt>T</tt>
                /// \li <tt>T</tt> becomes <tt>T</tt>
                typedef typename detail::expr_traits<typename Expr::BOOST_PP_CAT(proto_child, N)>::value_type type;
            };

            template<typename Expr>
            struct child_c<Expr &, N>
            {
                /// Verify that we are not operating on a terminal
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);

                /// The raw type of the Nth child as it is stored within
                /// \c Expr. This may be a value or a reference
                typedef typename Expr::BOOST_PP_CAT(proto_child, N) value_type;

                /// The "reference" type of the child, suitable for return by
                /// reference, computed as follows:
                /// \li <tt>T const &</tt> becomes <tt>T const &</tt>
                /// \li <tt>T &</tt> becomes <tt>T &</tt>
                /// \li <tt>T</tt> becomes <tt>T &</tt>
                typedef typename detail::expr_traits<typename Expr::BOOST_PP_CAT(proto_child, N)>::reference type;

                /// INTERNAL ONLY
                ///
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().BOOST_PP_CAT(child, N);
                }
            };

            template<typename Expr>
            struct child_c<Expr const &, N>
            {
                /// Verify that we are not operating on a terminal
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);

                /// The raw type of the Nth child as it is stored within
                /// \c Expr. This may be a value or a reference
                typedef typename Expr::BOOST_PP_CAT(proto_child, N) value_type;

                /// The "const reference" type of the child, suitable for return by
                /// const reference, computed as follows:
                /// \li <tt>T const &</tt> becomes <tt>T const &</tt>
                /// \li <tt>T &</tt> becomes <tt>T &</tt>
                /// \li <tt>T</tt> becomes <tt>T const &</tt>
                typedef typename detail::expr_traits<typename Expr::BOOST_PP_CAT(proto_child, N)>::const_reference type;

                /// INTERNAL ONLY
                ///
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().BOOST_PP_CAT(child, N);
                }
            };
        }

    #undef N

#endif

/* traits.hpp
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
*/