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
EjbjTejm67ZNaZjJqXsX9W1c4+u2+QbGu2pL9Wcp4YkfuPUB1zSOGRxOxOQapvvWQeCDhl12wcBGll2W8HZoqr6lyq4rGC/J8ydLuIdXrhp8H2ZgI/m23nRJwKvJLM8M2Xh/9/UaRmeEBvbbN2gYnQmavnz0I/m9+NOLa9ij1PN+Pn4UDiq/csbg/Juzq4DtrCnixd0/NLg7d7229IDAvvf2udIWDaH02n+/Fmr03x53BIK7SwgBgrskhBAgBAjBggcIFgIEd3cL4Tdvbfb92+OA47tr387OrM7OzM7MvvgomBUwOHbuv/womP0RxSf2MqD1kbR5CEEEth+bi8vTmRuRRglUsVh6ubi4/K88aPqw50NrsnSxa1/18EWiLmG2TwTOVOVXOpE8asrV/ZlXNxaITGzjuFGV1Wk5Ud3U/deAbhSESVoXuZDHU76vsUHezadL3gJNVDVCcsKT7Tb1bzuoX0GYjaImEHHEqB9ff96rn4o6gJVE1gnqX6AFrn43oC+bRDYVJjPRFeDpo/1tcdbo6ixvxRqvHwWiToMwi7NcLO1i8pHRBrRxyik0/imokbn4w6d6uDIRw4IaxQ17c7b/Qb+FBHyHO4/awcPD1r8Nb2ro3JWBjT/kOGUkYDVNa1kFDifzUOJ+c2cOD/oy+K4lxlbmjVUhiqaqmritHK4D22mOdm6QZ+RfHp5SRHHc1jBtOTz1yrnN7cNtcqFbx55Dj238zJx/h/BEz3YfwcUnlbGyyXtwN7o7tzkV8PuGPbsj+41/b3BTDnfPNpNBCzOS0B6vPs4re/cXMmnI86eiO3sfbuOVHC4OyrauE/hGDeFu67UxzKKuoGjuFdMXa5fncPN13Eh6YcJZ6vQeObT++Rx+FqY5Se//q7tVDSwM7H047Ewp0zQq05Bgrb+LMPMoAcvnMY9jXPU0nZvHB5gFSsnF9xG7NJGI0KytR9x9GFudBh0ZkOJh9D72ot5JakvOwkTmeNlTvTZFAvOX5LKDEXh/f+U8Lag+0QMSLtlEUFFi7OaDNhSVrOu6kUe3wd/NNDDW1s3xNCKEEaaWcSs28bbWIN3nxpy57+R1WlFmYdc2VUFsLKNga9BGVecrZep926+X15K8icpBvTO2XmLusng9HFlRVCWwaWbiIbuHCEnuEzmubuAl3x3tdmncIXsvShandw8+ZhSTDPerJs7RWZ5/gXtX40jSr3vtuHynj/DwBAKuVl0XRJ0gyQ/k+xSKjo2f6IMnaTK0f7BZm9OGL3B8jWiTqE4pCdCJk9OnZmbn7jl/esUMymFibLxeGxLKARFWZVOLwPpi8vSh48M9RCLaN79d/MYHPDy5SFKMbFtF/xWP6pWX7/N79xjEBoZVVVbm1WyGxXfF1aqT3mZsz06d8GOSI7QtB6s5SsqYoewlDSaflT2G+YSd4Lju2dSYsrgLTRiC7+86f8K/XyAX5C7tYupHtXBS5VfZWlP/6n/uNzO9bnpgzsjqhL9HyyZJWpkGQte3CXE3D2x0lOrAvD6EDWY3X3sn/DMSAkwGB8XcE54mR8WWCnZH+UaOaw7nWlDneSKU3Un72CbmbB6MCVheWtR5o8Zk+qLH5KPemJD8FuBA6LIjx0S35MghGbsx+dFgneBKIkkkqMoLrBPprZPIjMnjUs9/MUuzKuxwd2J9wHn+mZP+mHR9toREDcmp/zoksw80Z6SHpxNdHNdpFkZHjAlr93A8DFr3DlV20l8rDThuk0e5L+9OjgxbK9OJGZdBX+FiV8d51qnOzvzXztpcRCd93om5j7pEHr0neDuP7uxlzFn6bq99gUiSPAjaINKyteulk8tHhVmTg3GqqgpCTxCi7oVWkC0Fshk=
*/