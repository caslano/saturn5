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
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
*/