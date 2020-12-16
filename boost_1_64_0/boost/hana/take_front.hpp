/*!
@file
Defines `boost::hana::take_front` and `boost::hana::take_front_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAKE_FRONT_HPP
#define BOOST_HANA_TAKE_FRONT_HPP

#include <boost/hana/fwd/take_front.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto take_front_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using TakeFront = BOOST_HANA_DISPATCH_IF(take_front_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::take_front(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::take_front(xs, n) requires 'n' to be an IntegralConstant");
#endif

        return TakeFront::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct take_front_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...n>
        static constexpr auto take_front_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t size = decltype(hana::length(xs))::value;
            return take_front_helper(static_cast<Xs&&>(xs),
                        std::make_index_sequence<(n < size ? n : size)>{});
        }
    };

    template <std::size_t n>
    struct take_front_c_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const {
            return hana::take_front(static_cast<Xs&&>(xs), hana::size_c<n>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TAKE_FRONT_HPP

/* take_front.hpp
SosFZRldyohO9J0cfFxjqQxdZ9+UZBB7T3SDbRu3ev9VdMcDQnzig/Ec1ldb28/wstpWQedIw/hE9WxCu3OgoX8qaITMLFxt4vPb5lhEqfrtCvkT5puutvSO6+Xy3PXzO6Q95Rr/v0/CR3KzQEu7RMQXflFhE3Cm4xY6KtpJYMu/dwDReNP94CepjOhYYytZSe3KOJKgIaytSQnmWWdY9n12i7go2fZdHXLcjhMjlH6GvmtLvP5SZqh75YZWowypMZ4j2W4x5oxvKw613bu2wC3qLI8BvVuOASskcLdLn0MxbEXswfM9utZdxTsZKn+Ze2s49CiDAbdLQiI3znJ7Tij/wBrJm773ehRIOBtTmddRGceslLrjbcfGBWOHXtmgzNtKGd50smmdyzK0pDOMgSjaolrrzdBwhKpC3G3Est0t99Gq6pyMKTMLEVzLv7Bb2oaGrnbQXTZnQzjYl6EX9tflO/jhRFZ5aeuhnYgW8Ngb6F9S9oVXzqpOSBYRscviTnAfe6XAVYMx0QyDYruLvdkMvqqrGd82j7mP7hU4pFYPzjgRbMGz/czLc7/tlXc/Eb6hNjrhip/HSJ50hJntA9BvsNadlraovxY6BOtgVhVcRhS8aK49LgYG9sXt94vvyUhZ11L0QWz37OwUZYpzHJVRnEHfGc61YPX4hcezYPq64NCN8Tr7Iywe2wBxzOG8X75H57nvjTUsfcnwRb/sPIxQPFyQmPKDcg0bWtt4YXTcoOVPdTNPP5tRUc7NkMu/UOhQTPZ1NUAdpuUHCPScAzHL6oOy7r1TIUdPNZFN+ecm+bao7OO7oVaN7KHVe2fLG0o8E03rqEUAD2HYNHpinuBX/vBgGn9p+7p3hgVDFXwm043//gwqD26T6ZUz9NG7St+5Ymbwzsnqv77z5LMV3znel7+4wN3vBt4YGQGaYMpfBpovcP2n/AHKs60DtBIK4CdFfMg0lXGsCbnFOzOwE1i/dxDeusT7fnYpUwvorCEAzKQPKMLaJRnEsT4sfT27vnFCGRFezuxkBlKxh+lLQuzfkAcT5xeq5/LQVy23smXR+EPXDcxtdTj1aded9MowsXydBXj2NK8Elb8ke+m4lhH3GO9t8fy2MSvv77q65nVfyWh/oLHzE6/BxXhzW3zvD5mV62tth6rqZD39ZqLBK93NZFlWyEqmetEPpupXZM/miLGP42Fexni0AWhBS7Z7sHjMdZef9oRXnGJwHdo/nj0v78Na2TurTD/Oy5XaAsm8KQRpipFwjOt7We5QDabzTR/KBRCxotxTntf3able2844h+WC5H8r9z1luXXX1Z3wIpQLIGLry/3opFzXuUF2TmK5IPnvykW7ybz4tl1VK8XrkAnvsbTQOc92k6LMlnV103SD5GOZj5Vq62lPUFKtKxbv4e8TbeHVln3MzpiDMHni0VwVD5ryjEfVsM3Cc+gXfpTv0qG6Owf7B4/dCSUi/ctI3wU6vPyRjPSvFXR4SRP6tws6dOaE/pdIb5RVm1Ufj7olJuc/Vujos486bvjjKc9WuDdAHTdfpcdCqI7bRp5duFugfMu+vFOkw+q6I8aJ0UDGoaQl2wXuhjxplUrLb2KTme8+a3XFZkF61VdinR7045V7CBDaOMV47x/n+xB4PF5iiFzf636c7CaZBvjUoCVgdO7kelxG/RhvELgzJ9bjqZFvazCDijUJTEFPpktCj5pGhp18n9Nie68W/h0en4dz07K8Z+JzeiJb6ns+0uNQRszRK/icnCRIPQ+RXpwasNzjCT1pwPd7hvS1m3XkexXyrd2ZY8zI65AvVQS6EvFEJjTsBYKx+lbkQRMULELLeJW3Iz2VTOJc3oO0VHs=
*/