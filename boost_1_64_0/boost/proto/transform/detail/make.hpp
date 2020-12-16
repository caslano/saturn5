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
Pn9lY8Z2Nmb8TcTzf2msfS/3aeAxr6nmM076GT2vMfdfsWZC8fzf+bqioa2w03w2Lc7AiHVeWsQdgkJynveSCJ//+qew4X+JcedZ0oVqClpvwSQcfGwcNpreibS7DjS1icdgtdd0gs/GBMfveh23HrwXKl2m2uvOMQHTeUbLm52bpu78gnCgBY7vMhBugWkf4GhXgc9T5mi4t7PgwKeBV4OGu7sLoO+g/YXprM4tKldMjZbZ9gJLizO+Yn6OSbEdySzEjmMzm/zz8VlIY+1uzHx8dhPt6xH9GXw+Lube9WzuPQf0M2nu7VDZNd45ZNt2TSVdGl6ivDM1LTqt55Pk2w9kOpk3qfo5tthF/RJlGlucS3VpaJKxgOwH5oAQ6wIcZnW4W8S+zU1+22+h8lqbpP+W7cWuhbtFCnDt9b9QV1c4kcBNokRXPOIcLSc2YzFW/nlNnvz4bv3TIfjO63Uo1etg/Kup5lO9XkB0i8Zb48CRklifEcNNeH7jhU2+cQHt7j//NgN+9HAqZ2FN/Tl3bEOmapgw6+sapsgAuDt3b6o1/vErrNjO1Hcqu5zxLxBDPI8U9XkJ0rI+R1F9XurqF55goSK9u9+n2O+HTUV7U387xui+r5Af7iFf7vSXYw28P1sqw5Fk81489zIH7mx40FmzOvSlRU37tjZzmG+Ptcfr3y83fMre2vjipsnFhV/38Vvv21NaYHj0FwojTt3ON361y/nFqlV2D/dFoJvjg3el85nsSFd6ZGQQIYqrA+gfviUOT909MkJlvBh5W1QIGoRiUHQXe4PiaODmqZ5cHjvvZzpY4uiUuwT4+aqqVtN+UwfT5YJxfupyCbcciSPbmcXm07PFeHoc9b1l1PeWkw0d32TzrBMx1olke9b3TVUrKN8rWL49oqyTqawbaV1gJeU5hfmJbeysTaip1rnUoXLadUL46o3T1P43svNd6kkeA5SzpZwT38UpDujmcQDF9k5OM7txMrhljYem8qMo342xlH8cQtmlbAV3/f3zEgB0aMbfQ3HfKQHMjb96mIwNNe800zkTFiP3Ct8RQRofX0y5mtpiDWu/W+SeIOVZ20h7gpQnxvI8SnkmuG9kVhoQ3tNFZl/4L5FeneJN/jW3dUgrxKIjI1bPCQMrZUfS6IFZB+76kOQkfcjycfbXBkx+WxZsDO03VNQQ844B+cD1rK3mqO4IzpmYm9q+bSoBtuNvTb2FEtElKeQJ40qfVZrEUL/f2BS0RlkoDafz8D/Wx28y9XLue+QLZeWus5/m6xfOjRRcEndrYAEke/A4jekhC5IpYehL/rNLwNEJB+DY2r+G619ZVa5fryfakcIOfZzAwE838WDZ5e/RznNg5QyWJxBcqU6Kg1/F6jZ/H+e4nZOw7VDfqphtIQGn9klR+yyfmN9YTsQjTTxWTswj1RV3gqUxUOKVIV7xCc74rulKHG+uCuOKozjmG4T2+m+W+YkLKLbdzmxTngF5jbFLZ0JdJtigaWd7vn5Ij9XsHP1mM/dhFyoIPqzHZfd8aRl7bhT7b+Gx/yTXJzuC47oYzgL2YT8i3G3ysTTp9wwR975TzGVHyJ+OMj39hd0tKgg/XkS6KPz4NuJRqmVbzCeNdUc2fq8Ieati/rGdytrB5D1dzPsQJ2BMk3OlOnUm5T2L6CfoU2LjKgBOMp89Ju63ZZ8DnNbR66js3WNoxR0s0J5HtK8PoAU/H+35RPtGoh0k236tKXc4W0n53ys7V9u3A89mKtbu32BsXJ9HogwEv0DbOsEpg3fO+UIeHzzHuy9ZMd6/mer3XhrvL6L6Xczae3PDxOvqzzWW0vzfSmXla/iJS40ex7BR7jmymeZ8lzxLpnU=
*/