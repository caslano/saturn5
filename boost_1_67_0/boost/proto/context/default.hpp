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