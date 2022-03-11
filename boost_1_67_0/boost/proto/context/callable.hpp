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
        private:
            callable_context_wrapper &operator =(callable_context_wrapper const &);
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