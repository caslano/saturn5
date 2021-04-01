///////////////////////////////////////////////////////////////////////////////
/// \file eval.hpp
/// Contains the eval() expression evaluator.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EVAL_HPP_EAN_03_29_2007
#define BOOST_PROTO_EVAL_HPP_EAN_03_29_2007

#include <boost/proto/proto_fwd.hpp> // BOOST_PROTO_CALLABLE
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace proto
{

    namespace result_of
    {
        /// \brief A metafunction for calculating the return type
        /// of \c proto::eval() given a certain \c Expr and \c Context
        /// types.
        ///
        /// \note The types \c Expr and \c Context should not be
        /// reference types. They may be cv-qualified, but the
        /// cv-qualification on the \c Context parameter is ignored.
        template<typename Expr, typename Context>
        struct eval
        {
            typedef typename Context::template eval<Expr>::result_type type;
        };
    }

    namespace functional
    {
        /// \brief A PolymorphicFunctionObject type for
        /// evaluating a given Proto expression with a given
        /// context.
        struct eval
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename Context>
            struct result<This(Expr, Context)>
            {
                typedef
                    typename proto::result_of::eval<
                        typename remove_reference<Expr>::type
                      , typename remove_reference<Context>::type
                    >::type
                type;
            };

            /// \brief Evaluate a given Proto expression with a given
            /// context.
            /// \param expr The Proto expression to evaluate
            /// \param context The context in which the expression should be
            ///     evaluated.
            /// \return <tt>typename Context::template eval<Expr>()(expr, context)</tt>
            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr, Context>::type
            operator ()(Expr &e, Context &ctx) const
            {
                return typename Context::template eval<Expr>()(e, ctx);
            }

            /// \overload
            ///
            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr, Context>::type
            operator ()(Expr &e, Context const &ctx) const
            {
                return typename Context::template eval<Expr>()(e, ctx);
            }

            /// \overload
            ///
            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr const, Context>::type
            operator ()(Expr const &e, Context &ctx) const
            {
                return typename Context::template eval<Expr const>()(e, ctx);
            }

            /// \overload
            ///
            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr const, Context>::type
            operator ()(Expr const &e, Context const &ctx) const
            {
                return typename Context::template eval<Expr const>()(e, ctx);
            }
        };
    }

    /// \brief Evaluate a given Proto expression with a given
    /// context.
    /// \param expr The Proto expression to evaluate
    /// \param context The context in which the expression should be
    ///     evaluated.
    /// \return <tt>typename Context::template eval<Expr>()(expr, context)</tt>
    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr, Context>::type
    eval(Expr &e, Context &ctx)
    {
        return typename Context::template eval<Expr>()(e, ctx);
    }

    /// \overload
    ///
    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr, Context>::type
    eval(Expr &e, Context const &ctx)
    {
        return typename Context::template eval<Expr>()(e, ctx);
    }

    /// \overload
    ///
    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr const, Context>::type
    eval(Expr const &e, Context &ctx)
    {
        return typename Context::template eval<Expr const>()(e, ctx);
    }

    /// \overload
    ///
    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr const, Context>::type
    eval(Expr const &e, Context const &ctx)
    {
        return typename Context::template eval<Expr const>()(e, ctx);
    }
}}

#endif

/* eval.hpp
0t+Y1gGglFtS2TdH+/lJiouHxRSi+uFeyEDqTZ29ZOAQHS8k8rsYfek7sUCavtKlp9o6ErCo8APxXMu3D43eIFLVm4vtDG/48srZPyW+CbDgrflp4r8EndY+Xg0LjwduAp6w4/fSsmjZm3gAp8SpNWH6ID8s20/RLb83+4Skh/z2KCa9prZkfi3XSy3dJspOMnsuhnF805DWDzCiobMQftJTynttdlz7hBGmH6qUjQN2Ycp7PD3bQG9HeGUlqatIxe5uIZ7C1ChNoKSE7N5BJHHShg7O33WA40GteS48u/OEX5DhiIJ/C9rsXUy7WCkoBq9puNj+huCwVG9DNtXBYkZGjAxOJk6sKKXHRZoIgCn/ao2000ELqO9u/f+ZhJzGC/DefAGJ9vcWqRXlK2Ib7RQf7EyBML75Vugc159LGUktrjEn6LW2p3ccwqCv2/rnqNSufZ26diPGsDkAh02FQ0SOVxfFihBoCdxvT3WzuHWXROI0r0rbnCyuDgMZ3FMXNyyssS7r8/B0NqwOLLChYVxn0/7mSBHRVeXYEdwTfJoiMH0Wx6KFq1ZZGA==
*/