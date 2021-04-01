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
Pm0YNJVAI4cKFk6hMRlU1FMkxCmOvGhmkcZfl074Pgd3uZ74SQC+baeXcOT2XJCWCz/DIIAFrX1wuIJEqK5hm2SqWjFMRdpJ7w5kSTOtObeBhUG0RBYjfqIEPINcJ0vLPg+cX9qrMQijKLR0SmjJUzieLDwVTgVFD3kMQ3I3M0pe7TNtuugTPZKdfwJLCR8vlgyrIO8OjseX7Y9OscWxI+dCychi28iGaRlxBn/IqA3FiPd6Iu5DPbzKQAucl8FipHZEGLMCjjWfMDdP0MiblRR4jKI+cexXIY0CP+3StkBFdtPWlBeJ2dpspqpbYwMg7mSbRIch9z5ZuCQlhkA+RZPKsHNJPECQaYvJ9upGj3qfMcSpdUKIvSh6naUCLbCIXJ0rVM2d37kdA4OMFAYxe7E+FuwML9xyrf2zfTXFcQ5TNp9puQtpnrEiWO4Dw4zLaCg+yLTNj7UPdwfH1IoUdjOBgEMOYK+rx4H8ldbhahyO8NUK80tdycM0vMbkI+fXfaqUIIXImdob6Wv8uid0w4PGUDRHeYqMnTah25mZh/Doj98EkT07bv+gyg==
*/