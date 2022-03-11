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