///////////////////////////////////////////////////////////////////////////////
/// \file callable.hpp
/// Definintion of callable_context\<\>, an evaluation context for
/// proto::eval() that explodes each node and calls the derived context
/// type with the expressions constituents. If the derived context doesn't
/// have an overload that handles this node, fall back to some other
/// context.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_CONTEXT_CALLABLE_HPP_EAN_06_23_2007
#define BOOST_PROTO_CONTEXT_CALLABLE_HPP_EAN_06_23_2007

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/selection/max.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp> // for child_c

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Context>
        struct callable_context_wrapper
          : remove_cv<Context>::type
        {
            callable_context_wrapper();
            typedef private_type_ fun_type(...);
            operator fun_type *() const;

            BOOST_DELETED_FUNCTION(callable_context_wrapper &operator =(callable_context_wrapper const &))
        };

        template<typename T>
        yes_type check_is_expr_handled(T const &);

        no_type check_is_expr_handled(private_type_ const &);

        template<typename Expr, typename Context, long Arity = Expr::proto_arity_c>
        struct is_expr_handled;

        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 0>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;

            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(stag_, proto::value(sexpr_)), 0)
                    )
                );

            typedef mpl::bool_<value> type;
        };
    }

    namespace context
    {
        /// \brief A BinaryFunction that accepts a Proto expression and a
        /// callable context and calls the context with the expression tag
        /// and children as arguments, effectively fanning the expression
        /// out.
        ///
        /// <tt>callable_eval\<\></tt> requires that \c Context is a
        /// PolymorphicFunctionObject that can be invoked with \c Expr's
        /// tag and children as expressions, as follows:
        ///
        /// \code
        /// context(Expr::proto_tag(), child_c<0>(expr), child_c<1>(expr), ...)
        /// \endcode
        template<
            typename Expr
          , typename Context
          , long Arity          // = Expr::proto_arity_c
        >
        struct callable_eval
        {};

        /// \brief A BinaryFunction that accepts a Proto expression and a
        /// callable context and calls the context with the expression tag
        /// and children as arguments, effectively fanning the expression
        /// out.
        ///
        /// <tt>callable_eval\<\></tt> requires that \c Context is a
        /// PolymorphicFunctionObject that can be invoked with \c Expr's
        /// tag and children as expressions, as follows:
        ///
        /// \code
        /// context(Expr::proto_tag(), value(expr))
        /// \endcode
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 0>
        {
            typedef typename proto::result_of::value<Expr const &>::type value_type;

            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(typename Expr::proto_tag, value_type)
                >::type
            result_type;

            /// \param expr The current expression
            /// \param context The callable evaluation context
            /// \return <tt>context(Expr::proto_tag(), value(expr))</tt>
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(typename Expr::proto_tag(), proto::value(expr));
            }
        };

        /// \brief An evaluation context adaptor that makes authoring a
        /// context a simple matter of writing function overloads, rather
        /// then writing template specializations.
        ///
        /// <tt>callable_context\<\></tt> is a base class that implements
        /// the context protocol by passing fanned-out expression nodes to
        /// the derived context, making it easy to customize the handling
        /// of expression types by writing function overloads. Only those
        /// expression types needing special handling require explicit
        /// handling. All others are dispatched to a user-specified
        /// default context, \c DefaultCtx.
        ///
        /// <tt>callable_context\<\></tt> is defined simply as:
        ///
        /// \code
        /// template<typename Context, typename DefaultCtx = default_context>
        /// struct callable_context
        /// {
        ///    template<typename Expr, typename ThisContext = Context>
        ///     struct eval
        ///       : mpl::if_<
        ///             is_expr_handled_<Expr, Context> // For exposition
        ///           , callable_eval<Expr, ThisContext>
        ///           , typename DefaultCtx::template eval<Expr, Context>
        ///         >::type
        ///     {};
        /// };
        /// \endcode
        ///
        /// The Boolean metafunction <tt>is_expr_handled_\<\></tt> uses
        /// metaprogramming tricks to determine whether \c Context has
        /// an overloaded function call operator that accepts the
        /// fanned-out constituents of an expression of type \c Expr.
        /// If so, the handling of the expression is dispatched to
        /// <tt>callable_eval\<\></tt>. If not, it is dispatched to
        /// the user-specified \c DefaultCtx.
        ///
        /// Below is an example of how to use <tt>callable_context\<\></tt>:
        ///
        /// \code
        /// // An evaluation context that increments all
        /// // integer terminals in-place.
        /// struct increment_ints
        ///  : callable_context<
        ///         increment_ints const    // derived context
        ///       , null_context const      // fall-back context
        ///     >
        /// {
        ///     typedef void result_type;
        ///
        ///     // Handle int terminals here:
        ///     void operator()(proto::tag::terminal, int &i) const
        ///     {
        ///        ++i;
        ///     }
        /// };
        /// \endcode
        ///
        /// With \c increment_ints, we can do the following:
        ///
        /// \code
        /// literal<int> i = 0, j = 10;
        /// proto::eval( i - j * 3.14, increment_ints() );
        ///
        /// assert( i.get() == 1 && j.get() == 11 );
        /// \endcode
        template<
            typename Context
          , typename DefaultCtx // = default_context
        >
        struct callable_context
        {
            /// A BinaryFunction that accepts an \c Expr and a
            /// \c Context, and either fans out the expression and passes
            /// it to the context, or else hands off the expression to
            /// \c DefaultCtx.
            ///
            /// If \c Context is a PolymorphicFunctionObject such that
            /// it can be invoked with the tag and children of \c Expr,
            /// as <tt>ctx(Expr::proto_tag(), child_c\<0\>(expr), child_c\<1\>(expr)...)</tt>,
            /// then <tt>eval\<Expr, ThisContext\></tt> inherits from
            /// <tt>callable_eval\<Expr, ThisContext\></tt>. Otherwise,
            /// <tt>eval\<Expr, ThisContext\></tt> inherits from
            /// <tt>DefaultCtx::eval\<Expr, Context\></tt>.
            template<typename Expr, typename ThisContext = Context>
            struct eval
              : mpl::if_c<
                    detail::is_expr_handled<Expr, Context>::value
                  , callable_eval<Expr, ThisContext>
                  , typename DefaultCtx::template eval<Expr, Context>
                >::type
            {};
        };
    }

    #include <boost/proto/context/detail/callable_eval.hpp>

}}

#endif

/* callable.hpp
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
*/