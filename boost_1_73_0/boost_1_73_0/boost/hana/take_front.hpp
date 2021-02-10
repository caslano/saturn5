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
qqFnM5vY4kOW0bOUNjX/q2RgFdT6qbT6dSh1SzplOI4e3DPDHECfmmMsdWNaC6kmjQn82fzxzKlhgPeK8hSN6Gfzhyq/8YywdKkoSgQE/jveyptuXCuY726aFpEhd3Wz3pYvoS0XUB6/TRu/teLaevZ7LtybpXjB2LoA8z69ppGwJ2JVtyyKwdPyjTOfb3dLfl8+2zp84lZMYQMFFNwgSBA+6bhnVjyI3AozepT9JOCb1x+g115ZBFHFYsErFXluc4u5StSc4q1BPKzDQx+5PvuNCugShMpnH3WOuYpAUeI/K8UU48FuJ8Xj0zLHWQ61tQXLHJ7Tzs+80jj1YpOmMUAeGWaRvxFCUT3WYfVyag4/r29zCryFAdmI5MfSoxEZ85F0ITPN1zkEFrFtQAbX4FJNMxhZk+HS+dn7i6570X0LDLvChYMXN8JEolCoMzd3QXu17xxQrMWrPqr52bCWq1cydiXrR7ZsjYlAMsKoEsmXzoOEFDs777yiYZy87p68+av0KV5uLvUZchwJ9WavfANrKvKO6augaRi1flxChH4PD5ECde0+SJI17uMSCAHUU/TZkLNbSv9Fl3/RbquGuIqjycJfJhLxgzbOvQTj3fLNH452sPRnmAowaTlO37/14+w+f3bUqzSoGV4v
*/