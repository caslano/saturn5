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
3MoADvF/mKIDR5rRB/DDGSaaiyC0AeXwMTpwBjJtb23ejAGcpcYdAHpvecV2TJ52qMjNAE7ZUSkQKfshGheYO+EFpOEO4NCtmUBCiaZ486raQDqIAUDP2ObxWDpbVq0Mm9D5tqpuDypVNGznUFk6M41/51GChao5NXA8L5bR/l7zGwfA+QjDmvCg9MPptRdrxkxfZhK5fzix+alXq41Y6O2Sc8KaImPAxzLstFsdrdBI/X3DhX1HcbkN7p1ya8FSbyJtj1uVRJOrrcnQSPc9879QPOjfyyGJeucQREhQDRhcg/WAG6qC4yoIFtnp6je4/Z3fd/5xKLUQj7ypUJF8WCDN1rz7PoBi5dy4cOl25XnrSaot2Gw9ZEb+ocPYRq0v7re/pUcogW9lT7h/L6EH45mvB0fYZEQ2JNEwjDQn6GXXZOiqF55vgpzo0tMxExXGIVqkJ3/oa/VqaYOe+gXShIWXYvIel21fpAWOZTtlCwe1L4CX6YHRZiXgeVa4cA960j2fKFe3KrSfMzSt95V8UFavUp+yORACvDtKsgCGSYUpQYoAP93n2444j+uP6keaWcPkEF+QEcg4ZG6oDMBsAasd9Z5kGwCxwB8NU0pHfQ4j1UF6/94XME6HfEY9Nl3V17OiAgsRKBiNX85pZU+Aa9/kg3ozToKzSdNfQIvfxZ9ZIVtXiLvVQHHD8vP5W4enFvlWxLrkObcvhchn
*/