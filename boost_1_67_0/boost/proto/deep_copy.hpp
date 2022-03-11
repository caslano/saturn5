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