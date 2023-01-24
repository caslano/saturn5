#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/make.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_MAKE_IF(Z, M, DATA)                                                         \
        make_if_<BOOST_PP_CAT(A, M), Expr, State, Data>                                             \
        /**/

    #define BOOST_PROTO_MAKE_IF_TYPE(Z, M, DATA)                                                    \
        typename BOOST_PROTO_MAKE_IF(Z, M, DATA) ::type                                             \
        /**/

    #define BOOST_PROTO_MAKE_IF_APPLIED(Z, M, DATA)                                                 \
        BOOST_PROTO_MAKE_IF(Z, M, DATA) ::applied ||                                                \
        /**/

    #define BOOST_PROTO_CONSTRUCT_ARG(Z, M, DATA)                                                   \
        detail::as_lvalue(                                                                          \
            typename when<_, BOOST_PP_CAT(A, M)>::template impl<Expr, State, Data>()(e, s, d)       \
        )                                                                                           \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make.hpp
    /// Contains definition of the make<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/make.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_CONSTRUCT_ARG
    #undef BOOST_PROTO_MAKE_IF_APPLIED
    #undef BOOST_PROTO_MAKE_IF_TYPE
    #undef BOOST_PROTO_MAKE_IF

#else

    #define N BOOST_PP_ITERATION()

    namespace detail
    {
        #if N > 0

        template<
            template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class R
            BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<BOOST_PP_ENUM_PARAMS(N, A)>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(N)
        >
          : nested_type_if<
                R<BOOST_PP_ENUM(N, BOOST_PROTO_MAKE_IF_TYPE, ~)>
              , (BOOST_PP_REPEAT(N, BOOST_PROTO_MAKE_IF_APPLIED, ~) false)
            >
        {};

        template<
            template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class R
            BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<BOOST_PP_ENUM_PARAMS(N, A)> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<BOOST_PP_ENUM(N, BOOST_PROTO_MAKE_IF_TYPE, ~)> type;
            static bool const applied = true;
        };

        #endif

        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct is_applyable<R(BOOST_PP_ENUM_PARAMS(N, A))>
          : mpl::true_
        {};

        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct is_applyable<R(*)(BOOST_PP_ENUM_PARAMS(N, A))>
          : mpl::true_
        {};

        template<typename T, typename A>
        struct construct_<proto::expr<T, A, N>, true>
        {
            typedef proto::expr<T, A, N> result_type;

            template<BOOST_PP_ENUM_PARAMS(BOOST_PP_MAX(N, 1), typename A)>
            BOOST_FORCEINLINE
            result_type operator ()(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_MAX(N, 1), A, &a)) const
            {
                return result_type::make(BOOST_PP_ENUM_PARAMS(BOOST_PP_MAX(N, 1), a));
            }
        };

        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, N>, true>
        {
            typedef proto::basic_expr<T, A, N> result_type;

            template<BOOST_PP_ENUM_PARAMS(BOOST_PP_MAX(N, 1), typename A)>
            BOOST_FORCEINLINE
            result_type operator ()(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_MAX(N, 1), A, &a)) const
            {
                return result_type::make(BOOST_PP_ENUM_PARAMS(BOOST_PP_MAX(N, 1), a));
            }
        };

        template<typename Type BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        BOOST_FORCEINLINE
        Type construct(BOOST_PP_ENUM_BINARY_PARAMS(N, A, &a))
        {
            return construct_<Type>()(BOOST_PP_ENUM_PARAMS(N, a));
        }

    } // namespace detail

    /// \brief A PrimitiveTransform which computes a type by evaluating any
    /// nested transforms and then constructs an object of that type with the
    /// current expression, state and data, transformed according
    /// to \c A0 through \c AN.
    template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make<Object(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<make<Object(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            /// \brief <tt>boost::result_of\<make\<Object\>(Expr, State, Data)\>::type</tt>
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;

            /// Let \c ax be <tt>when\<_, Ax\>()(e, s, d)</tt>
            /// for each \c x in <tt>[0,N]</tt>.
            /// Return <tt>result_type(a0, a1,... aN)</tt>.
            ///
            /// \param e The current expression
            /// \param s The current state
            /// \param d An arbitrary data
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(BOOST_PP_ENUM(N, BOOST_PROTO_CONSTRUCT_ARG, DATA));
            }
        };
    };

    #if N > 0
    /// \brief A PrimitiveTransform which computes a type by evaluating any
    /// nested transforms and then constructs an object of that type with the
    /// current expression, state and data, transformed according
    /// to \c A0 through \c AN.
    template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make<Object(BOOST_PP_ENUM_PARAMS(N, A)...)>
      : transform<make<Object(BOOST_PP_ENUM_PARAMS(N, A)...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
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

/* make.hpp
v5HmGf9vQ2VY5Q3w64exehQX34CkZPl3F2Tp79/d19YsPaYyzXma8XgVT87632lpeiHNOEdnOfUuII/6O7edpkHqnc3jfYDD4KZ6mpOVqAV71gvCIFIts8k3mF1XGF3UK4sOTNwfOjFHhNvxUluIdQ12z2ibvIK6BxuuMN2BQsoSJionrvuPAKT9rHuGzWoyHwWicFgx5zT/7oQePKWn/OT4+6Vo5oYnwNaoheTCkClcfKXpbctfs6uT6heUDB433j0tASRZgxbR9Pxvhaw3MLscUwhUmoZuuS+oT44I3sWvnp11M39aDm0Dzy3Fvh1eVvSZRHsldVgb8t51dFoP1YMSqeGKEg+4dMMGzwKVHoLIX3wonvvQExbqhQy8qicXrcnUypdsKetjV0pO+04L3J/ab/ebygPlvcVTjnbHEEdMy6a04Ycaa2mfk88jaBzsQ1vUG2ewGo+IieleowiGsXBGf5j4xCL4meFY/nuLRtVfRX5lDUxafF9mFf65OkjTw1+n5VQgtcNtGPeEXyALTtkGYAO5+qFjl5g9uCSXafP0ck05qT+L0bwTTOgzB6OLtmrZtzisHxzIXxT6mA0ZMwfWPf9C2hzz8CINiYbYVO29bktLzr6fQXgm0/QQnIVOoOofMB/uEx4KcsbVloJKZPJoZ5HT8ebx3T/iNkrohzp/+ObP6Oi7kcnjztxAWu3yuchypqdIPGaMG7d4
*/