///////////////////////////////////////////////////////////////////////////////
/// \file integral_c.hpp
/// Contains definition of the integral_c transform and friends.
//
//  Copyright 2011 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_INTEGRAL_C_HPP_EAN_04_28_2011
#define BOOST_PROTO_TRANSFORM_INTEGRAL_C_HPP_EAN_04_28_2011

#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/transform/impl.hpp>

namespace boost { namespace proto
{

    /// \brief A PrimitiveTransform that returns a specified
    /// integral constant
    ///
    template<typename T, T I>
    struct integral_c : transform<integral_c<T, I> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef T result_type;

            /// \return \c I
            /// \throw nothrow
            T operator()(
                typename impl::expr_param
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return I;
            }
        };
    };

    /// \brief A PrimitiveTransform that returns a specified
    /// char
    ///
    template<char I>
    struct char_
      : integral_c<char, I>
    {};

    /// \brief A PrimitiveTransform that returns a specified
    /// int
    ///
    template<int I>
    struct int_
      : integral_c<int, I>
    {};

    /// \brief A PrimitiveTransform that returns a specified
    /// long
    ///
    template<long I>
    struct long_
      : integral_c<long, I>
    {};

    /// \brief A PrimitiveTransform that returns a specified
    /// std::size_t
    ///
    template<std::size_t I>
    struct size_t
      : integral_c<std::size_t, I>
    {};

    /// INTERNAL ONLY
    ///
    template<typename T, T I>
    struct is_callable<integral_c<T, I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<char I>
    struct is_callable<char_<I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<int I>
    struct is_callable<int_<I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<long I>
    struct is_callable<long_<I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<std::size_t I>
    struct is_callable<size_t<I> >
      : mpl::true_
    {};

}}

#endif

/* integral_c.hpp
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
*/