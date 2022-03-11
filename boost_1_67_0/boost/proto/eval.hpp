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