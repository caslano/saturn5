/*!
@file
Defines `boost::hana::at` and `boost::hana::at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AT_HPP
#define BOOST_HANA_AT_HPP

#include <boost/hana/fwd/at.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/integral_constant.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr decltype(auto) at_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using At = BOOST_HANA_DISPATCH_IF(at_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::at(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::at(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        return At::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename It, bool condition>
    struct at_impl<It, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <std::size_t n, typename Xs>
    constexpr decltype(auto) at_c(Xs&& xs) {
        return hana::at(static_cast<Xs&&>(xs), hana::size_t<n>{});
    }
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AT_HPP

/* at.hpp
2nbU3OtLcA7rF1xmHSrbtxhZzxg1XrCoCBZGvOwf4/3iX29IBMcfeR4NOMes+gD81g8S7VRpdKeMPg+NMzcPnwt760I2HNGRfaaxpS/CtadeU4U6HUiWW7BPlQy0GdrC9mkXZFTT7T12k0f0Hd3LtObG6fN4blQxmQbnCobZvwr3u3Z6MUZpfsGxr7O/OfZYIahPGumWaq/G7HB7/8A03ILxLcJgUMVS6vH1XC2c8NyQxfz9Mgzt3jewC+TdNcXHnpb7TFPGavqn0zLVeKFfL5cq9I18ZEBCq/XHvce866uCP8xdphGuZW8aVCvPYu3KzdCb1cqcyo0isIyT0bzhtVUN7A6z/AYxyl5Vk4n8AKWYi+TWHwOma1Up/uILWG3o81r03oOL+148RlCDLGmvyiAhYUW56eY/7rkcp9Qb2/z4jOpsO+kDpDI4dhcP+VwpjAL3pP4AFTiHsSImPnqBp571H3vpVsS6laCG8Y9C8OIJRDwEAaAGGVrG8yagydzd0nWN9rGOSY3umMnU82qnsEGWDLFST6oHCEYj1Bjux3fnNN+hun4y8CfbVP+Y3yKBRzkxrhBuvJQ7FfZghHcmBbdLm2R59MeYulcPJ8CdznZNHfJh7PqJO9vxXoq3QImML88Qwy8kxtTiwQv7i1c6xxxo1uPPnA5BQ7pJUj01vbjY3qgNq5J5ddOlTl94NTJxi6LmVlyZKEhtySu+
*/