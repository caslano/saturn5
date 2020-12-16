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
0WlMRsztDXFm/79yIMglgeNvt6+u8HOW5PJ606Q1DjSkLu+rBrHCjj3j5eAqhHq7rtN/Z13oIeYH8HZfyoVZ4z7NTIAT5WKZySBrlutRb32C7kkMEmHjuu6VC36H9Zqw4mdKnWrc8Td4nb/Hx0H3MfxzdolfHwnzpH2T+vKvBuWbfjlzoyGOdKv6rkBr70BW30MZ83K2Dy3uLy1fHlC3Q+8XZkn26YFsqdXCa7Es+1SQh/m1VpG+1wqDWNW0NL92QxxULc2Z2CAV9ucSjiPzvcp17W1vWquLOzbe7wE9OgjNp8vX3TuI1XaA//C13xSerfP7Fw4DwVNAap2IwxxL0WN0vGexx+BCksz2mKmMOwysWsx3p/c4jKnxEGfU91yWW5mYmRE/s1ER6xa/HOfM56C9Lk/hFIu7QM39dpefo50g68ED8uLdIIDCp3/OLkcy/pyejBeHIFiwhUFsLFz3pft7vCwWSdy/mvfLzKuFYlreWcqEOUxZjNOkn6VqqvN8PR7k9P0nfzmoKvW3fDzMyXsd4/u9nL5n7YRXZV/Q/vNdztsXDns5sy/wHtueg2bj/RyJ3KQyjJFMk9PvD1hrKno/Ur7P8I8AA/cZ6viweYnPvQJs7RyhugwP/Cw5JOiyz7c9Xs6eE1bZ38Gon6cvS0t9vmCvzvcV94d5qe9+oZ+T80SF2Ak/yzM0sHzfxs7vMbhuUmieEHdvbxvz/dISHb/Jl4KkfuzJoyaPWyDEO+A9UdxVH9k+gBX6pmtWHmCteBYx/XaXxUjnvzzm7bzJQhQb+uzXyhe+V0PStLz7OySXPZ7OGv65tS9yD9eursHLo+24J5WVdxYwz5C+vD1xQIFK9+Lk/eh7IVY6MxVr0EddHle/cq086jCo9Fay4ntvneg8+30fwOLSDiJAPYs7Jt44+Ny8vHt72OXk+7YN3te4ZXLetn1aQNZqrd3pijRf5ePE1Wripn0cqbjkO4x+DjZw+g3AEJPIJuU65oV+DjZ5zEyEmHmxZnLry7Fhuusy/LIx3yvyMDDPwLPOND3wG+kDWOmj+raXM+eun3gY8NdTEXPhTWOen8X7Ir1avVtrgJ/vc1Vh73HLZDG8qMqKJ4HneM7a5+cqU8Bq7vuWvNwieExoNdUEN7XSiM7R2P2AxS2kCvOLyX63rNYr/YVsh22xJI/aB3ylvd3steSdf5ejkwr6zrWIzfhZ8B91rqger9kQbM7P4jAHwWLePuWydBg3yWnv9zFVmBF7aubagHmUz81cFr6T0O7YDDgpdPis1E3f+K7OW/JIYyLnWP52SFmSxYovsn8dlzOu8MrxNeOyzrq/4DLiGq/WuV63uONLi8s5aBm8q3r+KK1pQhz2TWhzsh6Fltc2cf54suW5nW54Wbel+E1oH08e35qr7D/+mpdbC+ad7er88cgZB5dxZn+Iq1TXsF143O7YF2BFAeX39Ku7B/PH51raLjTMNldL5S6sQviOY4idoG6naKFPveTjsdet8R0+H4O9TvvMkYxpSk5jvM3zgFmvSfZIIOwaCg5j3t3NWeHzxXiKoEHV4HMMmS8yV6csifXCIT8H/qG77MNHpilyTeEtK5yMqdjHjx2Ot7XftibWYhe8DJRJ5+PBiMnYbwz+xAqHoSZtYCZ2W+Frbj4ekgzBUD74DpXN0MQmVJ1yv3vYTtecCKs8T5ty2Y8Bhf/WCodWKibn9T53hwxP5wv4tXVsgW4ZcuaNrkFpXTUZ0hG1n0JziRlu6Ht+ZIZBFdLmU/vqNRnRFHpMXzOZUDVznj9j8lxuCr9uhuNIFuFXzHDURou9yE2jj6by5JdB2fqDKPDhW+T3eC1W+IAo870km2kYNg9n2Yc=
*/