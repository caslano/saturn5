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
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
*/