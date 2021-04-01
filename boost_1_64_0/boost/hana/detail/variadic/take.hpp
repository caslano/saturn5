/*!
@file
Defines `boost::hana::detail::variadic::take`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP
#define BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/split_at.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/functional/reverse_partial.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    struct take_impl2 {
        template <typename F, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, Xs&& ...xs) const {
            return static_cast<F&&>(f)(static_cast<Xs&&>(xs)...);
        }
    };

    struct take_impl1 {
        template <typename ...Xs>
        constexpr auto operator()(Xs&& ...xs) const {
            return hana::always(
                reverse_partial(take_impl2{},
                    static_cast<Xs&&>(xs)...)
            );
        }
    };

    template <std::size_t n>
    struct take_t {
        template <typename ...Xs>
        constexpr decltype(auto) operator()(Xs&& ...xs) const {
            return variadic::split_at<n>(static_cast<Xs&&>(xs)...)(take_impl1{});
        }
    };

    template <std::size_t n>
    constexpr take_t<n> take{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP

/* take.hpp
LH0jeF2j+Httt5f91h4xXuvECQhRL+Ym+/juQcQ9KDPB6NhBOT/yk1qaExj5XT4pik8eR9Dp5OUJ6Tpak8rvVdVwhM27Cv1PfgMAw+Xnc7DkVt2XXfqdfvu1rOyWEuIpPkATOkg/7dI2/57F5OYMFBKx4j/krXAlcsGecz7qDCdARtwztpJPGjkBJ8RkRZ+5HOLG+6CVAWaYQqUVmFniyXbt48A1ousL1irBmeYQylzEWU+1thlW0j9bbD84N4mbS/RlvEYenxlAnGBtdgPq87pD2NCs9vV0i4Kh6nR/rRzzls00WLgm2GY/yp5Nw5p/eDP8N64Ylwm0Zlcf1FqZjUXAsJmjVcXNLFsCarP89+0yHwErbJjCcSu1L+aA2D1A6ESAo4ld+2ZO8eYY/4+K2gJnWWZe1RQVQUdhmuF7FU+csreWGBF78JtGwT0+5ysBPO+2xvwMZr/OaYt6F2ZtmJNzXJp8zqYKriptj228IWr6z25CHJ7dvXAGgHnU7AOMwkBc3itKObYeky0bSmtPT6bRHWFHAOE7gBz0S36L8jnrSqzHnNDRlZdotQ==
*/