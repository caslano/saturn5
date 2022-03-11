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