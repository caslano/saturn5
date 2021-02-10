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
AQAAAAAA3Nk+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgzMVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKw+y3lDgIAAFkDAAAeAAkAAAAAAAEAAAAAANLcPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MzJVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSUDgzTyACAACoAwAAHgAJAAAAAAABAAAAAAAl3z4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODMzVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUs4rwBfOAgAABQUAAB4ACQAAAAAAAQAAAAAAiuE+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgzNFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIidWUvLQIAAL4DAAAeAAkAAAAAAAEAAAAAAJ3kPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MzVVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSTMH9x9oBAACEAwAAHgAJAAAAAAABAAAAAAAP5z4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODM2VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoIg
*/