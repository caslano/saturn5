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
ThyzHVsRcli/++F4c2rW4t4cKaw+aDMUXyiQFQaYAmeIjLn+O7qmCpT7ZGDDpCvob0uGHalQRKjyW4KiTYqjMDuLnZIk1Nu1erScX4unHpxnKS9jrbIPDt6Egc3iuo1HFMVPf9gDErykzG2mYVgFtljpZ8lKXdlXuoV/pCix7GfiXAlRNWf5G1SF3KZjqvfQNr71yJi8osUNVp7lbWTMFLsK6PamHtiveaIM5mp81ptgccuX29Hm/M/xPGlez14ISJpqdIUgwEFvzuj8t9H9VFS8raEw13JKQame4e7+kZLFhDkNzHPcERmriRJc3PHi5Ck3Sn+TiDn4REklWF9/MfJruiB2rM5dsfGZTDWYdtguhLXB70mwfWRPaTmNy3UANGeIeKSvHjoZNCRDlqUWcVWggn2u3Jupz3OQt+3TWQOsjEbKEfIOGCjAVas3NPREF1nTiEjUJXHW5rfy98BLl3fm/emxD6h4clPWk3x73sOunEqbctoZD5pIpE9p0kAkNJs4kJle5OePswHvY2ju0rOKvgJoed322FaCpl8hPOJt5pgdQJoTaUCHUw==
*/