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
bsB348nWbxkfeYwTdM8Hwcfqng+Cj9I8H6Qj3k94yzxl/gH/TBn/y/XH0/B/JJj/SDfjPx1/10h+fSiXzvMlmufbjMZL8GT7NwYvxJPtX/3HrN9Rxydy/RIeVFxe33oVL1dcrh/chU9RXK4f/Bo/UXHZf8n9hPGhoXm+Pf5ugvxNsfYff0Pz/JOx+Gua55+Mwzdr1jdm/oProx7FxfhtIF6KY7ar65Oz8dMVl+ePHHyu4vL8MRSfrbg8f9R9SvlV0ifP/5/g75m/443mN6d9xvyKcF+6sr4PX6i4fH5jPX6R7v5pvEgzf/MRPlWzPsT4nPGD8N/iVvyF+NO6v4+Cb9L9fRR8g2Z9XvYXrL/W3D9WiCda/3W46ZX45cIpv/bzcUP474VTfu3n456H1yguy+/5+CLVZfn9ysP9x8nvn+iH39H4+NjX3wbjdZr2czh+lOJy/rQev0b3fBL8YjxN8W2jnG/vwqPSlfLxNR4WnnOyE/83eEj4atyef9/F+UVNn7z/ER+By+dT2/c/4kPxZM+n3vg1/Xc86f0r+JGNnt+h3L+C5wj/CLfvX8GHCB9+irP/Gf9s6J/J8tnFun8dX4KL6wv2+DUTrxJ+F26NXw/DK4Xvxq3x6wC8zKu5vsDg+UfN8/HW4j9ono/3ML5LUz7fx18Q/uo05fmF+DPCj5yupO875q+U9cuyfV2Hv664fD7B4/iLisvzfz3+gOry+Zvfs75AaX9k/lyOX6a4zJ8r8d9prn9k/pv1EZr7C3rhWZr1FXn4cZrjNws/WtP+r8A76saP+GTd+i98kub+PeMHjzFLs70Hn6HZvhB/2Ei+vteHP6S4vH+qCH9AcXn/VBl+l5G8fZ+P32lo2ncuXr+p+ftSA/HnTbNcbV8n47cLn5/nhJaH1wlfr/SPA/hS4T2mKf33Hxvm5+0txPXd1viCxtef7PNzOl4s/ITxTvoG4CcIv3GKE9tAfKxwz1Tl+thPzK9q8u9i/H4j+d9/uxu/SPgPJzqhrcF/J/zEyU76cn/m/KbEL88/k/ESZXt5/snD81WX5x98kOb5Vh/jP4vt75ns7N/4X1g/Lfwz3Ho3AT9F+Cgl/3fiIc31kS6c6UarLusfPlSZ/5b97wX43zxK/OL6SQh/X3E5v7mQ395VXM5vhvEtmr/PV8fDk57U/P2rTfgqfk5UfNU0Zf+YXH5Rs75nAf6EZn1POf6IZn1PBb5Os74nit9rJN+/7FSv8UqC9LU1tzkW3yi2p/7a/cdRuEw/9ddevzUaf1j4FbiVW2fii4V/h9vtC4t/TtC17/hQ3d/vwY/T3T+Nj9Kdv/DbjeTzi1fj1ysu17ddj1+luFwfcQN+hery+THNvTy/Pfnz4Sbj9zUqP8r6GfwexeX473J8nuJy/BdbnLW8uVL+xf3/h+J+vLPX8dcmOvMjXXCf8PaTnOfX9MVnCZ+HW/XzMHyG8Jdxe36rjdeeX+mcoP37Fj8MT1Vc/fuLmSzu/ycLSM5NVcrviaTL3IPM48k/5fjI+38n4Iv4WU6KLU8Z74Rfj29udPxQ87UZ/6vicv7jVVytn3L+4zX8JcVl/+J1/EVD8/zBXK+xVHN+XI9XmGZ5+QBn/7JHU340/dccvFjTfx2On6Hpv9bhLZXzm1xfehPeQnFZ/27GUxSX60vvwH/SPL9pzRivMUgzvluPd8cx2xlf2eO7J/DOwu/Crfq/Ae8ofDduxb8V/0bk/xkTlfuHmVyv0qTvM7y08fnTTt/n+DzF5d/3+AIvxpO1D4UneI2vNe1jKf4PTftYgW/XtI9B/ANN+1g43mvkp2jWj+CjSX9/xR8/Xrk+ih8v/N+4fX0U/43wE3OV66P4scI=
*/