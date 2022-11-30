///////////////////////////////////////////////////////////////////////////////
/// \file default.hpp
/// Contains definition of the _default transform, which gives operators their
/// usual C++ meanings and uses Boost.Typeof to deduce return types.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_DEFAULT_HPP_EAN_04_04_2008
#define BOOST_PROTO_TRANSFORM_DEFAULT_HPP_EAN_04_04_2008

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/ref.hpp>
#include <boost/get_pointer.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/is_member_object_pointer.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/transform/arg.hpp>
#include <boost/proto/detail/decltype.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Grammar, typename Tag>
        struct default_case
          : not_<_>
        {};

        template<typename Grammar>
        struct default_case<Grammar, tag::terminal>
          : when<terminal<_>, _value>
        {};

        template<typename Grammar>
        struct default_cases
        {
            template<typename Tag>
            struct case_
              : default_case<Grammar, Tag>
            {};
        };

        #define BOOST_PROTO_UNARY_DEFAULT_EVAL(OP, TAG, MAKE)                                       \
        template<typename Grammar>                                                                  \
        struct BOOST_PP_CAT(default_, TAG)                                                          \
          : transform<BOOST_PP_CAT(default_, TAG)<Grammar> >                                        \
        {                                                                                           \
            template<typename Expr, typename State, typename Data>                                  \
            struct impl                                                                             \
              : transform_impl<Expr, State, Data>                                                   \
            {                                                                                       \
            private:                                                                                \
                typedef typename result_of::child_c<Expr, 0>::type e0;                              \
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;           \
            public:                                                                                 \
                BOOST_PROTO_DECLTYPE_(OP proto::detail::MAKE<r0>(), result_type)                    \
                result_type operator ()(                                                            \
                    typename impl::expr_param e                                                     \
                  , typename impl::state_param s                                                    \
                  , typename impl::data_param d                                                     \
                ) const                                                                             \
                {                                                                                   \
                    typename Grammar::template impl<e0, State, Data> t0;                            \
                    return OP t0(proto::child_c<0>(e), s, d);                                       \
                }                                                                                   \
            };                                                                                      \
        };                                                                                          \
                                                                                                    \
        template<typename Grammar>                                                                  \
        struct default_case<Grammar, tag::TAG>                                                      \
          : when<unary_expr<tag::TAG, Grammar>, BOOST_PP_CAT(default_, TAG)<Grammar> >              \
        {};                                                                                         \
        /**/

        #define BOOST_PROTO_BINARY_DEFAULT_EVAL(OP, TAG, LMAKE, RMAKE)                              \
        template<typename Grammar>                                                                  \
        struct BOOST_PP_CAT(default_, TAG)                                                          \
          : transform<BOOST_PP_CAT(default_, TAG)<Grammar> >                                        \
        {                                                                                           \
            template<typename Expr, typename State, typename Data>                                  \
            struct impl                                                                             \
              : transform_impl<Expr, State, Data>                                                   \
            {                                                                                       \
            private:                                                                                \
                typedef typename result_of::child_c<Expr, 0>::type e0;                              \
                typedef typename result_of::child_c<Expr, 1>::type e1;                              \
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;           \
                typedef typename Grammar::template impl<e1, State, Data>::result_type r1;           \
            public:                                                                                 \
                BOOST_PROTO_DECLTYPE_(                                                              \
                    proto::detail::LMAKE<r0>() OP proto::detail::RMAKE<r1>()                        \
                  , result_type                                                                     \
                )                                                                                   \
                result_type operator ()(                                                            \
                    typename impl::expr_param e                                                     \
                  , typename impl::state_param s                                                    \
                  , typename impl::data_param d                                                     \
                ) const                                                                             \
                {                                                                                   \
                    typename Grammar::template impl<e0, State, Data> t0;                            \
                    typename Grammar::template impl<e1, State, Data> t1;                            \
                    return t0(proto::child_c<0>(e), s, d)                                           \
                        OP t1(proto::child_c<1>(e), s, d);                                          \
                }                                                                                   \
            };                                                                                      \
        };                                                                                          \
                                                                                                    \
        template<typename Grammar>                                                                  \
        struct default_case<Grammar, tag::TAG>                                                      \
          : when<binary_expr<tag::TAG, Grammar, Grammar>, BOOST_PP_CAT(default_, TAG)<Grammar> >    \
        {};                                                                                         \
        /**/

        BOOST_PROTO_UNARY_DEFAULT_EVAL(+, unary_plus, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(-, negate, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(*, dereference, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(~, complement, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(&, address_of, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(!, logical_not, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(++, pre_inc, make_mutable)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(--, pre_dec, make_mutable)

        BOOST_PROTO_BINARY_DEFAULT_EVAL(<<, shift_left, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(>>, shift_right, make_mutable, make_mutable)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(*, multiplies, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(/, divides, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(%, modulus, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(+, plus, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(-, minus, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(<, less, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(>, greater, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(<=, less_equal, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(>=, greater_equal, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(==, equal_to, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(!=, not_equal_to, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(||, logical_or, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(&&, logical_and, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(&, bitwise_and, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(|, bitwise_or, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(^, bitwise_xor, make, make)

        BOOST_PROTO_BINARY_DEFAULT_EVAL(=, assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(<<=, shift_left_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(>>=, shift_right_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(*=, multiplies_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(/=, divides_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(%=, modulus_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(+=, plus_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(-=, minus_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(&=, bitwise_and_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(|=, bitwise_or_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(^=, bitwise_xor_assign, make_mutable, make)

        #undef BOOST_PROTO_UNARY_DEFAULT_EVAL
        #undef BOOST_PROTO_BINARY_DEFAULT_EVAL

        /// INTERNAL ONLY
        template<typename Grammar, typename Expr, typename State, typename Data>
        struct is_member_function_invocation
          : is_member_function_pointer<
                typename uncvref<
                    typename Grammar::template impl<
                        typename result_of::child_c<Expr, 1>::type
                      , State
                      , Data
                    >::result_type
                >::type
            >
        {};

        /// INTERNAL ONLY
        template<typename Grammar, typename Expr, typename State, typename Data, bool IsMemFunCall>
        struct default_mem_ptr_impl
          : transform_impl<Expr, State, Data>
        {
        private:
            typedef typename result_of::child_c<Expr, 0>::type e0;
            typedef typename result_of::child_c<Expr, 1>::type e1;
            typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
            typedef typename Grammar::template impl<e1, State, Data>::result_type r1;
        public:
            typedef typename detail::mem_ptr_fun<r0, r1>::result_type result_type;
            result_type operator ()(
                typename default_mem_ptr_impl::expr_param e
              , typename default_mem_ptr_impl::state_param s
              , typename default_mem_ptr_impl::data_param d
            ) const
            {
                typename Grammar::template impl<e0, State, Data> t0;
                typename Grammar::template impl<e1, State, Data> t1;
                return detail::mem_ptr_fun<r0, r1>()(
                    t0(proto::child_c<0>(e), s, d)
                  , t1(proto::child_c<1>(e), s, d)
                );
            }
        };

        /// INTERNAL ONLY
        template<typename Grammar, typename Expr, typename State, typename Data>
        struct default_mem_ptr_impl<Grammar, Expr, State, Data, true>
          : transform_impl<Expr, State, Data>
        {
        private:
            typedef typename result_of::child_c<Expr, 0>::type e0;
            typedef typename result_of::child_c<Expr, 1>::type e1;
            typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
            typedef typename Grammar::template impl<e1, State, Data>::result_type r1;
        public:
            typedef detail::memfun<r0, r1> result_type;
            result_type const operator ()(
                typename default_mem_ptr_impl::expr_param e
              , typename default_mem_ptr_impl::state_param s
              , typename default_mem_ptr_impl::data_param d
            ) const
            {
                typename Grammar::template impl<e0, State, Data> t0;
                typename Grammar::template impl<e1, State, Data> t1;
                return detail::memfun<r0, r1>(
                    t0(proto::child_c<0>(e), s, d)
                  , t1(proto::child_c<1>(e), s, d)
                );
            }
        };

        template<typename Grammar>
        struct default_mem_ptr
          : transform<default_mem_ptr<Grammar> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : default_mem_ptr_impl<
                    Grammar
                  , Expr
                  , State
                  , Data
                  , is_member_function_invocation<Grammar, Expr, State, Data>::value
                >
            {};
        };

        template<typename Grammar>
        struct default_case<Grammar, tag::mem_ptr>
          : when<mem_ptr<Grammar, Grammar>, default_mem_ptr<Grammar> >
        {};

        template<typename Grammar>
        struct default_post_inc
          : transform<default_post_inc<Grammar> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
            public:
                BOOST_PROTO_DECLTYPE_(proto::detail::make_mutable<r0>() ++, result_type)
                result_type operator ()(
                    typename impl::expr_param e
                  , typename impl::state_param s
                  , typename impl::data_param d
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    return t0(proto::child_c<0>(e), s, d) ++;
                }
            };
        };

        template<typename Grammar>
        struct default_case<Grammar, tag::post_inc>
          : when<post_inc<Grammar>, default_post_inc<Grammar> >
        {};

        template<typename Grammar>
        struct default_post_dec
          : transform<default_post_dec<Grammar> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
            public:
                BOOST_PROTO_DECLTYPE_(proto::detail::make_mutable<r0>() --, result_type)
                result_type operator ()(
                    typename impl::expr_param e
                  , typename impl::state_param s
                  , typename impl::data_param d
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    return t0(proto::child_c<0>(e), s, d) --;
                }
            };
        };

        template<typename Grammar>
        struct default_case<Grammar, tag::post_dec>
          : when<post_dec<Grammar>, default_post_dec<Grammar> >
        {};

        template<typename Grammar>
        struct default_subscript
          : transform<default_subscript<Grammar> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename result_of::child_c<Expr, 1>::type e1;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
                typedef typename Grammar::template impl<e1, State, Data>::result_type r1;
            public:
                BOOST_PROTO_DECLTYPE_(
                    proto::detail::make_subscriptable<r0>() [ proto::detail::make<r1>() ]
                  , result_type
                )
                result_type operator ()(
                    typename impl::expr_param e
                  , typename impl::state_param s
                  , typename impl::data_param d
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    typename Grammar::template impl<e1, State, Data> t1;
                    return t0(proto::child_c<0>(e), s, d) [
                            t1(proto::child_c<1>(e), s, d) ];
                }
            };
        };

        template<typename Grammar>
        struct default_case<Grammar, tag::subscript>
          : when<subscript<Grammar, Grammar>, default_subscript<Grammar> >
        {};

        template<typename Grammar>
        struct default_if_else_
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename result_of::child_c<Expr, 1>::type e1;
                typedef typename result_of::child_c<Expr, 2>::type e2;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
                typedef typename Grammar::template impl<e1, State, Data>::result_type r1;
                typedef typename Grammar::template impl<e2, State, Data>::result_type r2;
            public:
                BOOST_PROTO_DECLTYPE_(
                    proto::detail::make<r0>()
                  ? proto::detail::make<r1>()
                  : proto::detail::make<r2>()
                  , result_type
                )
                result_type operator ()(
                    typename impl::expr_param e
                  , typename impl::state_param s
                  , typename impl::data_param d
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    typename Grammar::template impl<e1, State, Data> t1;
                    typename Grammar::template impl<e2, State, Data> t2;
                    return t0(proto::child_c<0>(e), s, d)
                          ? t1(proto::child_c<1>(e), s, d)
                          : t2(proto::child_c<2>(e), s, d);
                }
            };
        };

        template<typename Grammar>
        struct default_case<Grammar, tag::if_else_>
          : when<if_else_<Grammar, Grammar, Grammar>, default_if_else_<Grammar> >
        {};

        template<typename Grammar>
        struct default_comma
          : transform<default_comma<Grammar> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : transform_impl<Expr, State, Data>
            {
            private:
                typedef typename result_of::child_c<Expr, 0>::type e0;
                typedef typename result_of::child_c<Expr, 1>::type e1;
                typedef typename Grammar::template impl<e0, State, Data>::result_type r0;
                typedef typename Grammar::template impl<e1, State, Data>::result_type r1;
            public:
                typedef typename proto::detail::comma_result<r0, r1>::type result_type;
                result_type operator ()(
                    typename impl::expr_param e
                  , typename impl::state_param s
                  , typename impl::data_param d
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    typename Grammar::template impl<e1, State, Data> t1;
                    return t0(proto::child_c<0>(e), s, d)
                          , t1(proto::child_c<1>(e), s, d);
                }
            };
        };

        template<typename Grammar>
        struct default_case<Grammar, tag::comma>
          : when<comma<Grammar, Grammar>, default_comma<Grammar> >
        {};

        template<typename Grammar, typename Expr, typename State, typename Data, long Arity>
        struct default_function_impl;

        template<typename Grammar>
        struct default_function
          : transform<default_function<Grammar> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : default_function_impl<
                    Grammar
                  , Expr
                  , State
                  , Data
                  , transform_impl<Expr, State, Data>::expr::proto_arity_c
                >
            {};
        };

        template<typename Grammar>
        struct default_case<Grammar, tag::function>
          : when<function<Grammar, vararg<Grammar> >, default_function<Grammar> >
        {};

        #define BOOST_PROTO_DEFAULT_EVAL_TYPE(Z, N, DATA)                                       \
            typedef                                                                             \
                typename result_of::child_c<DATA, N>::type                                      \
            BOOST_PP_CAT(e, N);                                                                 \
                                                                                                \
            typedef                                                                             \
                typename Grammar::template impl<BOOST_PP_CAT(e, N), State, Data>::result_type   \
            BOOST_PP_CAT(r, N);                                                                 \
            /**/

        #define BOOST_PROTO_DEFAULT_EVAL(Z, N, DATA)                                            \
            typename Grammar::template impl<BOOST_PP_CAT(e, N), State, Data>()(                 \
                proto::child_c<N>(DATA), s, d                                                   \
            )                                                                                   \
            /**/

        template<typename Grammar, typename Expr, typename State, typename Data>
        struct default_function_impl<Grammar, Expr, State, Data, 1>
          : transform_impl<Expr, State, Data>
        {
            BOOST_PROTO_DEFAULT_EVAL_TYPE(~, 0, Expr)

            typedef
                typename proto::detail::result_of_fixup<r0>::type
            function_type;

            typedef
                typename BOOST_PROTO_RESULT_OF<function_type()>::type
            result_type;

            result_type operator ()(
                typename default_function_impl::expr_param e
              , typename default_function_impl::state_param s
              , typename default_function_impl::data_param d
            ) const
            {
                return BOOST_PROTO_DEFAULT_EVAL(~, 0, e)();
            }
        };

        template<typename Grammar, typename Expr, typename State, typename Data>
        struct default_function_impl<Grammar, Expr, State, Data, 2>
          : transform_impl<Expr, State, Data>
        {
            BOOST_PROTO_DEFAULT_EVAL_TYPE(~, 0, Expr)
            BOOST_PROTO_DEFAULT_EVAL_TYPE(~, 1, Expr)

            typedef
                typename proto::detail::result_of_fixup<r0>::type
            function_type;

            typedef
                typename detail::result_of_<function_type(r1)>::type
            result_type;

            result_type operator ()(
                typename default_function_impl::expr_param e
              , typename default_function_impl::state_param s
              , typename default_function_impl::data_param d
            ) const
            {
                return this->invoke(
                    e
                  , s
                  , d
                  , is_member_function_pointer<function_type>()
                  , is_member_object_pointer<function_type>()
                );
            }

        private:
            result_type invoke(
                typename default_function_impl::expr_param e
              , typename default_function_impl::state_param s
              , typename default_function_impl::data_param d
              , mpl::false_
              , mpl::false_
            ) const
            {
                return BOOST_PROTO_DEFAULT_EVAL(~, 0, e)(BOOST_PROTO_DEFAULT_EVAL(~, 1, e));
            }

            result_type invoke(
                typename default_function_impl::expr_param e
              , typename default_function_impl::state_param s
              , typename default_function_impl::data_param d
              , mpl::true_
              , mpl::false_
            ) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename detail::class_member_traits<function_type>::class_type class_type;
                return (
                    BOOST_PROTO_GET_POINTER(class_type, (BOOST_PROTO_DEFAULT_EVAL(~, 1, e))) ->* 
                    BOOST_PROTO_DEFAULT_EVAL(~, 0, e)
                )();
            }

            result_type invoke(
                typename default_function_impl::expr_param e
              , typename default_function_impl::state_param s
              , typename default_function_impl::data_param d
              , mpl::false_
              , mpl::true_
            ) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename detail::class_member_traits<function_type>::class_type class_type;
                return (
                    BOOST_PROTO_GET_POINTER(class_type, (BOOST_PROTO_DEFAULT_EVAL(~, 1, e))) ->*
                    BOOST_PROTO_DEFAULT_EVAL(~, 0, e)
                );
            }
        };

        #include <boost/proto/transform/detail/default_function_impl.hpp>

        #undef BOOST_PROTO_DEFAULT_EVAL_TYPE
        #undef BOOST_PROTO_DEFAULT_EVAL
    }

    template<typename Grammar /*= detail::_default*/>
    struct _default
      : switch_<detail::default_cases<Grammar> >
    {};

    template<typename Grammar>
    struct is_callable<_default<Grammar> >
      : mpl::true_
    {};

    namespace detail
    {
        // Loopy indirection that allows proto::_default<> to be
        // used without specifying a Grammar argument.
        struct _default
          : proto::_default<>
        {};
    }

}}

#endif


/* default.hpp
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
*/