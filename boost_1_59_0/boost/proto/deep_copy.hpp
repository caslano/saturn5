///////////////////////////////////////////////////////////////////////////////
/// \file deep_copy.hpp
/// Replace all nodes stored by reference by nodes stored by value.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DEEP_COPY_HPP_EAN_11_21_2006
#define BOOST_PROTO_DEEP_COPY_HPP_EAN_11_21_2006

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/expr.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Expr, long Arity = Expr::proto_arity_c>
        struct deep_copy_impl;

        template<typename Expr>
        struct deep_copy_impl<Expr, 0>
        {
            typedef
                typename base_expr<
                    typename Expr::proto_domain
                  , tag::terminal
                  , term<typename term_traits<typename Expr::proto_child0>::value_type>
                >::type
            expr_type;

            typedef typename Expr::proto_generator proto_generator;
            typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;

            template<typename Expr2, typename S, typename D>
            result_type operator()(Expr2 const &e, S const &, D const &) const
            {
                return proto_generator()(expr_type::make(e.proto_base().child0));
            }
        };
    }

    namespace result_of
    {
        /// \brief A metafunction for calculating the return type
        /// of \c proto::deep_copy().
        ///
        /// A metafunction for calculating the return type
        /// of \c proto::deep_copy(). The type parameter \c Expr
        /// should be the type of a Proto expression tree.
        /// It should not be a reference type, nor should it
        /// be cv-qualified.
        template<typename Expr>
        struct deep_copy
        {
            typedef
                typename detail::deep_copy_impl<
                    BOOST_PROTO_UNCVREF(Expr)
                >::result_type
            type;
        };
    }

    namespace functional
    {
        /// \brief A PolymorphicFunctionObject type for deep-copying
        /// Proto expression trees.
        ///
        /// A PolymorphicFunctionObject type for deep-copying
        /// Proto expression trees. When a tree is deep-copied,
        /// all internal nodes and most terminals held by reference
        /// are instead held by value.
        ///
        /// \attention Terminals of reference-to-function type are
        /// left unchanged. Terminals of reference-to-array type are
        /// stored by value, which can cause a large amount of data
        /// to be passed by value and stored on the stack.
        struct deep_copy
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef
                    typename detail::deep_copy_impl<
                        BOOST_PROTO_UNCVREF(Expr)
                    >::result_type
                type;
            };

            /// \brief Deep-copies a Proto expression tree, turning all
            /// nodes and terminals held by reference into ones held by
            /// value.
            template<typename Expr>
            typename result_of::deep_copy<Expr>::type
            operator()(Expr const &e) const
            {
                return proto::detail::deep_copy_impl<Expr>()(e, 0, 0);
            }
        };
    }

    /// \brief A function for deep-copying
    /// Proto expression trees.
    ///
    /// A function for deep-copying
    /// Proto expression trees. When a tree is deep-copied,
    /// all internal nodes and most terminals held by reference
    /// are instead held by value.
    ///
    /// \attention Terminals of reference-to-function type are
    /// left unchanged.
    ///
    /// \sa proto::functional::deep_copy.
    template<typename Expr>
    typename proto::result_of::deep_copy<Expr>::type
    deep_copy(Expr const &e)
    {
        return proto::detail::deep_copy_impl<Expr>()(e, 0, 0);
    }

    /// \brief A PrimitiveTransform for deep-copying
    /// Proto expression trees.
    ///
    /// A PrimitiveTransform for deep-copying
    /// Proto expression trees. When a tree is deep-copied,
    /// all internal nodes and most terminals held by reference
    /// are instead held by value.
    ///
    /// \attention Terminals of reference-to-function type are
    /// left unchanged.
    ///
    /// \sa proto::functional::deep_copy.
    struct _deep_copy
      : proto::transform<_deep_copy>
    {
        template<typename E, typename S, typename D>
        struct impl
          : detail::deep_copy_impl<BOOST_PROTO_UNCVREF(E)>
        {};
    };

    namespace detail
    {
        // include the definition of deep_copy_impl
        #include <boost/proto/detail/deep_copy.hpp>
    }

}}

#endif // BOOST_PROTO_COMPILER_DEEP_COPY_HPP_EAN_11_21_2006


/* deep_copy.hpp
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
*/