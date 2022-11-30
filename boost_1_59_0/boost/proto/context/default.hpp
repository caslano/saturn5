///////////////////////////////////////////////////////////////////////////////
/// \file default.hpp
/// Definintion of default_context, a default evaluation context for
/// proto::eval() that uses Boost.Typeof to deduce return types
/// of the built-in operators.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_CONTEXT_DEFAULT_HPP_EAN_01_08_2007
#define BOOST_PROTO_CONTEXT_DEFAULT_HPP_EAN_01_08_2007

#include <boost/config.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/is_member_object_pointer.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/eval.hpp>
#include <boost/proto/traits.hpp> // for proto::child_c()
#include <boost/proto/detail/decltype.hpp>

namespace boost { namespace proto
{
/// INTERNAL ONLY
///
#define UNREF(x) typename boost::remove_reference<x>::type

    namespace context
    {
        template<
            typename Expr
          , typename Context
          , typename Tag        // = typename Expr::proto_tag
          , long Arity          // = Expr::proto_arity_c
        >
        struct default_eval
        {};

        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, tag::terminal, 0>
        {
            typedef
                typename proto::result_of::value<Expr &>::type
            result_type;

            result_type operator ()(Expr &expr, Context &) const
            {
                return proto::value(expr);
            }
        };

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_UNARY_DEFAULT_EVAL(OP, TAG, MAKE)                                       \
        template<typename Expr, typename Context>                                               \
        struct default_eval<Expr, Context, TAG, 1>                                              \
        {                                                                                       \
        private:                                                                                \
            typedef typename proto::result_of::child_c<Expr, 0>::type e0;                       \
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;               \
        public:                                                                                 \
            BOOST_PROTO_DECLTYPE_(OP proto::detail::MAKE<r0>(), result_type)                    \
            result_type operator ()(Expr &expr, Context &ctx) const                             \
            {                                                                                   \
                return OP proto::eval(proto::child_c<0>(expr), ctx);                            \
            }                                                                                   \
        };                                                                                      \
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_BINARY_DEFAULT_EVAL(OP, TAG, LMAKE, RMAKE)                              \
        template<typename Expr, typename Context>                                               \
        struct default_eval<Expr, Context, TAG, 2>                                              \
        {                                                                                       \
        private:                                                                                \
            typedef typename proto::result_of::child_c<Expr, 0>::type e0;                       \
            typedef typename proto::result_of::child_c<Expr, 1>::type e1;                       \
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;               \
            typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;               \
        public:                                                                                 \
            BOOST_PROTO_DECLTYPE_(                                                              \
                proto::detail::LMAKE<r0>() OP proto::detail::RMAKE<r1>()                        \
              , result_type                                                                     \
            )                                                                                   \
            result_type operator ()(Expr &expr, Context &ctx) const                             \
            {                                                                                   \
                return proto::eval(                                                             \
                    proto::child_c<0>(expr), ctx) OP proto::eval(proto::child_c<1>(expr)        \
                  , ctx                                                                         \
                );                                                                              \
            }                                                                                   \
        };                                                                                      \
        /**/

        BOOST_PROTO_UNARY_DEFAULT_EVAL(+, proto::tag::unary_plus, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(-, proto::tag::negate, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(*, proto::tag::dereference, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(~, proto::tag::complement, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(&, proto::tag::address_of, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(!, proto::tag::logical_not, make)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(++, proto::tag::pre_inc, make_mutable)
        BOOST_PROTO_UNARY_DEFAULT_EVAL(--, proto::tag::pre_dec, make_mutable)

        BOOST_PROTO_BINARY_DEFAULT_EVAL(<<, proto::tag::shift_left, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(>>, proto::tag::shift_right, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(*, proto::tag::multiplies, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(/, proto::tag::divides, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(%, proto::tag::modulus, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(+, proto::tag::plus, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(-, proto::tag::minus, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(<, proto::tag::less, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(>, proto::tag::greater, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(<=, proto::tag::less_equal, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(>=, proto::tag::greater_equal, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(==, proto::tag::equal_to, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(!=, proto::tag::not_equal_to, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(||, proto::tag::logical_or, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(&&, proto::tag::logical_and, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(&, proto::tag::bitwise_and, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(|, proto::tag::bitwise_or, make, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(^, proto::tag::bitwise_xor, make, make)

        BOOST_PROTO_BINARY_DEFAULT_EVAL(=, proto::tag::assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(<<=, proto::tag::shift_left_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(>>=, proto::tag::shift_right_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(*=, proto::tag::multiplies_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(/=, proto::tag::divides_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(%=, proto::tag::modulus_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(+=, proto::tag::plus_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(-=, proto::tag::minus_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(&=, proto::tag::bitwise_and_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(|=, proto::tag::bitwise_or_assign, make_mutable, make)
        BOOST_PROTO_BINARY_DEFAULT_EVAL(^=, proto::tag::bitwise_xor_assign, make_mutable, make)

    #undef BOOST_PROTO_UNARY_DEFAULT_EVAL
    #undef BOOST_PROTO_BINARY_DEFAULT_EVAL

        /// INTERNAL ONLY
        template<typename Expr, typename Context>
        struct is_member_function_eval
          : is_member_function_pointer<
                typename detail::uncvref<
                    typename proto::result_of::eval<
                        typename remove_reference<
                            typename proto::result_of::child_c<Expr, 1>::type
                        >::type
                      , Context
                    >::type
                >::type
            >
        {};

        /// INTERNAL ONLY
        template<typename Expr, typename Context, bool IsMemFunCall>
        struct memfun_eval
        {
        private:
            typedef typename result_of::child_c<Expr, 0>::type e0;
            typedef typename result_of::child_c<Expr, 1>::type e1;
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
            typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;
        public:
            typedef typename detail::mem_ptr_fun<r0, r1>::result_type result_type;
            result_type operator ()(Expr &expr, Context &ctx) const
            {
                return detail::mem_ptr_fun<r0, r1>()(
                    proto::eval(proto::child_c<0>(expr), ctx)
                  , proto::eval(proto::child_c<1>(expr), ctx)
                );
            }
        };

        /// INTERNAL ONLY
        template<typename Expr, typename Context>
        struct memfun_eval<Expr, Context, true>
        {
        private:
            typedef typename result_of::child_c<Expr, 0>::type e0;
            typedef typename result_of::child_c<Expr, 1>::type e1;
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
            typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;
        public:
            typedef detail::memfun<r0, r1> result_type;
            result_type const operator ()(Expr &expr, Context &ctx) const
            {
                return detail::memfun<r0, r1>(
                    proto::eval(proto::child_c<0>(expr), ctx)
                  , proto::eval(proto::child_c<1>(expr), ctx)
                );
            }
        };

        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, tag::mem_ptr, 2>
          : memfun_eval<Expr, Context, is_member_function_eval<Expr, Context>::value>
        {};

        // Handle post-increment specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::post_inc, 1>
        {
        private:
            typedef typename proto::result_of::child_c<Expr, 0>::type e0;
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
        public:
            BOOST_PROTO_DECLTYPE_(proto::detail::make_mutable<r0>() ++, result_type)
            result_type operator ()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::child_c<0>(expr), ctx) ++;
            }
        };

        // Handle post-decrement specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::post_dec, 1>
        {
        private:
            typedef typename proto::result_of::child_c<Expr, 0>::type e0;
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
        public:
            BOOST_PROTO_DECLTYPE_(proto::detail::make_mutable<r0>() --, result_type)
            result_type operator ()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::child_c<0>(expr), ctx) --;
            }
        };

        // Handle subscript specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::subscript, 2>
        {
        private:
            typedef typename proto::result_of::child_c<Expr, 0>::type e0;
            typedef typename proto::result_of::child_c<Expr, 1>::type e1;
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
            typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;
        public:
            BOOST_PROTO_DECLTYPE_(proto::detail::make_subscriptable<r0>()[proto::detail::make<r1>()], result_type)
            result_type operator ()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::child_c<0>(expr), ctx)[proto::eval(proto::child_c<1>(expr), ctx)];
            }
        };

        // Handle if_else_ specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::if_else_, 3>
        {
        private:
            typedef typename proto::result_of::child_c<Expr, 0>::type e0;
            typedef typename proto::result_of::child_c<Expr, 1>::type e1;
            typedef typename proto::result_of::child_c<Expr, 2>::type e2;
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
            typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;
            typedef typename proto::result_of::eval<UNREF(e2), Context>::type r2;
        public:
            BOOST_PROTO_DECLTYPE_(
                proto::detail::make<r0>()
              ? proto::detail::make<r1>()
              : proto::detail::make<r2>()
              , result_type
            )
            result_type operator ()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::child_c<0>(expr), ctx)
                      ? proto::eval(proto::child_c<1>(expr), ctx)
                      : proto::eval(proto::child_c<2>(expr), ctx);
            }
        };

        // Handle comma specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::comma, 2>
        {
        private:
            typedef typename proto::result_of::child_c<Expr, 0>::type e0;
            typedef typename proto::result_of::child_c<Expr, 1>::type e1;
            typedef typename proto::result_of::eval<UNREF(e0), Context>::type r0;
            typedef typename proto::result_of::eval<UNREF(e1), Context>::type r1;
        public:
            typedef typename proto::detail::comma_result<r0, r1>::type result_type;
            result_type operator ()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::child_c<0>(expr), ctx), proto::eval(proto::child_c<1>(expr), ctx);
            }
        };

        // Handle function specially
        #define BOOST_PROTO_DEFAULT_EVAL_TYPE(Z, N, DATA)                                       \
            typename proto::result_of::eval<                                                    \
                typename remove_reference<                                                      \
                    typename proto::result_of::child_c<DATA, N>::type                           \
                >::type                                                                         \
              , Context                                                                         \
            >::type                                                                             \
            /**/

        #define BOOST_PROTO_DEFAULT_EVAL(Z, N, DATA)                                            \
            proto::eval(proto::child_c<N>(DATA), context)                                       \
            /**/

        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::function, 1>
        {
            typedef
                typename proto::detail::result_of_fixup<
                    BOOST_PROTO_DEFAULT_EVAL_TYPE(~, 0, Expr)
                >::type
            function_type;

            typedef
                typename BOOST_PROTO_RESULT_OF<function_type()>::type
            result_type;

            result_type operator ()(Expr &expr, Context &context) const
            {
                return BOOST_PROTO_DEFAULT_EVAL(~, 0, expr)();
            }
        };

        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::function, 2>
        {
            typedef
                typename proto::detail::result_of_fixup<
                    BOOST_PROTO_DEFAULT_EVAL_TYPE(~, 0, Expr)
                >::type
            function_type;

            typedef
                typename detail::result_of_<
                    function_type(BOOST_PROTO_DEFAULT_EVAL_TYPE(~, 1, Expr))
                >::type
            result_type;

            result_type operator ()(Expr &expr, Context &context) const
            {
                return this->invoke(
                    expr
                  , context
                  , is_member_function_pointer<function_type>()
                  , is_member_object_pointer<function_type>()
                );
            }

        private:
            result_type invoke(Expr &expr, Context &context, mpl::false_, mpl::false_) const
            {
                return BOOST_PROTO_DEFAULT_EVAL(~, 0, expr)(BOOST_PROTO_DEFAULT_EVAL(~, 1, expr));
            }

            result_type invoke(Expr &expr, Context &context, mpl::true_, mpl::false_) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename detail::class_member_traits<function_type>::class_type class_type;
                return (
                    BOOST_PROTO_GET_POINTER(class_type, (BOOST_PROTO_DEFAULT_EVAL(~, 1, expr))) ->* 
                    BOOST_PROTO_DEFAULT_EVAL(~, 0, expr)
                )();
            }

            result_type invoke(Expr &expr, Context &context, mpl::false_, mpl::true_) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename detail::class_member_traits<function_type>::class_type class_type;
                return (
                    BOOST_PROTO_GET_POINTER(class_type, (BOOST_PROTO_DEFAULT_EVAL(~, 1, expr))) ->*
                    BOOST_PROTO_DEFAULT_EVAL(~, 0, expr)
                );
            }
        };

        // Additional specialization are generated by the preprocessor
        #include <boost/proto/context/detail/default_eval.hpp>

        #undef BOOST_PROTO_DEFAULT_EVAL_TYPE
        #undef BOOST_PROTO_DEFAULT_EVAL

        /// default_context
        ///
        struct default_context
        {
            /// default_context::eval
            ///
            template<typename Expr, typename ThisContext = default_context const>
            struct eval
              : default_eval<Expr, ThisContext>
            {};
        };

    } // namespace context

}} // namespace boost::proto

#undef UNREF

#endif

/* default.hpp
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
*/