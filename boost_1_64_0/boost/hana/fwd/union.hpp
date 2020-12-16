/*!
@file
Forward declares `boost::hana::union_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNION_HPP
#define BOOST_HANA_FWD_UNION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct union_impl : union_impl<T, when<true>> { };
    //! @endcond

    struct union_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr union_t union_{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNION_HPP

/* union.hpp
aEjjeGKG+MEymNpHOLmc4k5O4cF0CFiN9ogLhjCAeei6GQbeRvjh3N/IGmrr/utUIr7Rr2lCv7b0w8PnH1Mk/SgMRYq2o7+8/Ch5Ci4XuWDA1yc81HMb+Y7cm7D6mVtHyiOeBuLIyEQSP/+Mweic2GN1XzqTlqk9NvelETjwPlIPoEaRSVdOQGBY3HcsChQIokdiqznoRgpqRRBow2jCaUoZgd3xaeYszbdKtg9V1dTAuH4QSNjyRUq9DNwZ0XI8NfWu9yF6Dp1OlM7CXJXTkjkdBEb00ukRnsKc9wWL8Tq06oF5F+rEnJECQyPNWdjLqUkVl6SOR52JdJ2/JOQ6Xhxh1tgjq8bYeaSAQIHVqLFa1RibxirPjY7SUZIn9MLvP28F6cdKpBw+TOF4MWBiJG8+klpPtkhqjPk7ujpI/4fFi+dQan8SKZsdVEhIvAtiHhFbjzTeZF6L8qgOMk6D8fsevn4s38cfFwY+EkYVhtUT+WLQLHpuffggWk/C2O75xWC40RK0lzHjJTnH/TXi8rCJLo8hkI7w82hlDISJmum5IYw8nxPyQKgh1HNpBaUkxTK2piaiRiqm54aZFvpllBkxLYSng/uOU08HT6J0NVgbVBoPAo9HYDor0E5lHsBvWIfEm2NbU0UbuAS2+uueQPrz3roZYbH+MB4xDxCrFuP1zR77OojfKgfP/9OM/vaH1ZwXfzqd+ntNQK7fTlq/HzQ608fqEOFQSM811kFzGbwCHtncPBlTY3bDPNWHBVl9OAMRKKttp1V11JNFFJiaXy4LSA9Pvxr04jVjOupFD/Xiz6kVaBj34tTvsg+N9+9rWlPUMfkhs/saAooaHM7m1AvFdSOwMMlVSIdTPeA3g2Yh63qURMRyM1cJ0VPGV/FkjYHOILq1nJxWXDBBvxvNeEf2exPbbEYc0fHSGrFrJrFhtoH4n9mN1gHSlS8+hgsJKZRGbC9zQkHRcpw5aQSCqHpouzC34w9nTZdGKxPQ9FiGQmEz8h5EUoMxJFYJIIVek50lkkF55yOSSBoSVBtTszodO1UWWALe6o+jzALHywLVVM4o7QiOITzl6iQOSQA9mWsEAJyZLm+XRQHobd+m16gGpC9Mp28wbAW1aVR1Bti/SyeolvPhqrbtukTWyNymUaWKjGkGKNRuGQdXuRl9kuS5sE6Im05QxKc4uztMIlOAroufkJ4etjSRqRFn9qfJwdwkvSn+PVwUvsFvFS3cInVKa4q3Qmo6qlVkaQpPt3Qig/8abYlmabfILdHZ5WpLhP8b6EZR2P3wcFxh2GZNEt34675Yv8Q+W6xHYp+D/suJ5WrdUUzzAATEuy6th78n+bvDMPzYRMoaO1zzmdWcpapxqGpquR7CCvoTA+QM51CewHk1otdQhNXnYlRuSLyXSwrcdgYFUNjs9aWjWmN52uD2Vdw6nquYVqvasiCvGK12i6C/NcU8Riug3RaKiE3TiTfY1pe6Sogt9EV8uXixr6IPAcLS3YzGmM6EjmXV4uYfmFNgK6Jg0D8kBvYxaMcFAW1ke5i6SZia7oUX8McP4eMt3lrUiJumtqaafo4YXngnkTAM9QTta4KiWFUVi6EapoV/9qmacrUJ1OHXYDDiI3Q73SKL8JZGzrNwjZoAJWGxooLJ6kiUjOe/SV7SNDUlNfVKDDBODKmX+530bImV5pCYiK7gR46Tg9S2wTljGg/Tf8kckfNhxyTJ3+eFwkW7k7R9Tey1xUoSex2xosTenNjR2uUWNWqadqsctUiZ8Xzu5Ydx78lHfKjpTO8WgKqIx9TAx1gDF99jEljIrOcPxlOK5ixTJXaSJfIrZVzQM6xdwMsg+/FYT15HWO8FuIQ=
*/