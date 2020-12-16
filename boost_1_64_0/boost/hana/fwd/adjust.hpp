/*!
@file
Forward declares `boost::hana::adjust`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADJUST_HPP
#define BOOST_HANA_FWD_ADJUST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Apply a function on all the elements of a structure that compare
    //! equal to some value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `U` a type that can be compared with `T`'s,
    //! the signature is
    //! \f$
    //!     \mathtt{adjust} : F(T) \times U \times (T \to T) \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to adjust with `f`.
    //!
    //! @param value
    //! An object that is compared with each element `x` of the structure.
    //! Elements of the structure that compare equal to `value` are adjusted
    //! with the `f` function.
    //!
    //! @param f
    //! A function called as `f(x)` on the element(s) of the structure that
    //! compare equal to `value`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adjust.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto adjust = [](auto&& xs, auto&& value, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct adjust_impl : adjust_impl<Xs, when<true>> { };

    struct adjust_t {
        template <typename Xs, typename Value, typename F>
        constexpr auto operator()(Xs&& xs, Value&& value, F&& f) const;
    };

    constexpr adjust_t adjust{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADJUST_HPP

/* adjust.hpp
rqJqFJ+n4ez1hHjKYfbvIVVrx0WVdlMpsxFW/B6PEPfZeXn4lmckb05s8X3tXC26rdT4uUSpiOz99lbEvQLp72ves2YpFbBJqVjGbwxndh92QJ2LxN/MxOU9atnJ70q5juA8KKDsRuqOZxpntRMIdVK2BUxnE5zMaIM9uFjEt/IITDfF/4zTvdRjM95Psv7O8HtQbN2tj4So0EkgItv/d5z7F9fagtwCn0j1Fsmff8/tCCao4aQYrH+k6fGbIgbLc/P7NHGcL0OULVZckzKMIU4pxPdW+ZR9xD4/zpuJ8PqS4BpSWaN3drEkPghi/VX8L8m8P/Wx4ts53mNO4H3nXpEMw/i5w8NF73LEoxrxXu+GsCVYcEU4Sk8QCM88pDWeUJ/7PAcf6pgRr9gnCfbZc7/hSuyHqlGBWV2znO/90HdDOdL8g7nf+MCl3TM7ycdX8U1isd8+Ep8eyH2OZnSW8PcPjsgvvPLpWEhlb4fxfTLyVYnj/dpw9psJ7y3wQCaPU42WR4gv4AEylMF/wJnYlGjkWVSwN0S+d+KAKDaD79X4vvHObc5Tjmv7B3zf48z3l/74N6gWi8USMoz1DHFWnEiOjsQ+f6rUBi/iUVxFT9nTbbhEvtbF/shWV0toECd8VMo0zpzf9+H9RgznqRP+TjvkI47o52Uq+TyUbV1f2GYj8Q+xXYZ9IL7KWTKrNe8x+fm0HryjMG2jbHKqZqFsXZVlouZ5RKPCBqnMz5bvGxcJPKgr9vOuS/AVewQWc9yMH6k2TI5yXiVL3N3XRTc7QaDIGd5HcIQPgORdZfxNeQQ+7xQYuYT7/IcQx6rzvR9hz3r8XMgd7ICwu2LfFjH8awpRgpukN1fbpaIag+juqnYmVDIXuM/4oR2OJGazz4fv4w9xf/gRnwkXtiaLYZSt6g63kbjHkWB7C+I9XLNp6EMhHAWGeIFWvVkvgcIaoZfYckpZbOL3SwYq9ZDDvPksfv8vgfe2D7g/2MSmfIjQGyel9XdlV5vx+4kMRGQb/Kd3+D6qIfEZdl6z78re4Bv3esVU9vWPjN8h1l+QwNrGAqsuMb/TVHcwvoySn9VQDhzxe7krXtYRmBGt7sfNEhjHc45iHvhzvnGfp6rTK7EgT80Rdvdtpao68f0+HpvvrOyQKfwewDJxnjRNTP12K9VwMfoQIaaBG4lf8inJxm6SdNBXvjfF6rC3VvZyT+6PpexfK5W1TBS2SyLvMQlteQXzfZ61UkbwC7rHfYSeE2hM/JJl232GQFiEyuxnCRy3QR8frLJkHrSXtVKNTL7998AIGXJa2Ri+ADBimE7yG42vVuIvRqGKYsQtMQVHoYM8Gs/554L9y31UkR9uuPdLHZxD5NaF3bh+heq+dKK/jspOXkU8rzvxaVJXuTAicgicf4U9uJR4I6Ee0+3oV6WYXw7BTB6xefAdfSQRxaNXeY9JWV2+mjk2GH9YSQlUjyXfnd/0nDWP+AKe6AUDiHe/xF7wE3Cex/dRtXOgT/J7VenKviwjhJGx6v5gKY/bqml8ijG1sb24NP+qVHGm7FQI709pdzSu8Wkn1GTtO+JiZk78iJP1NZN3lGcQZy1EF0eNi39i70rAo6qu8CyPZCADb4AgAQKMOig0AYODAgYlQBKCQpwYMoNAElc6HVGUzoBLgMRJKpPnKG21rV21tS1t7d5itIoJo0lQVKStRbEWl7YPRyW4QADN6//fNzOZbAra/Zv7fUneu8u555577rnnnnPuCyOJvksXxJKrGT9+Ae1DJNjGR1Aw5naM6L1S/PrOVyiv7sugvzYd+NEtkcPKZ9BmdOoYVPngS0Dt70Tte7SmTN0IDGYxeuLLjQD1s7GDwM8=
*/