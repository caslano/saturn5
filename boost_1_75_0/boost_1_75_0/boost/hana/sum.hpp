/*!
@file
Defines `boost::hana::sum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SUM_HPP
#define BOOST_HANA_SUM_HPP

#include <boost/hana/fwd/sum.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/integral_constant.hpp> // required by fwd decl
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename Xs>
    constexpr decltype(auto) sum_t<M>::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Sum = BOOST_HANA_DISPATCH_IF(sum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monoid<M>::value,
        "hana::sum<M> requires 'M' to be a Monoid");

        static_assert(hana::Foldable<S>::value,
        "hana::sum<M>(xs) requires 'xs' to be Foldable");
    #endif

        return Sum::template apply<M>(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename T, bool condition>
    struct sum_impl<T, when<condition>> : default_ {
        template <typename M, typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return hana::fold_left(static_cast<Xs&&>(xs), hana::zero<M>(), hana::plus);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SUM_HPP

/* sum.hpp
LzFqQ411kWVJOpoSVigHadx/H1BuNfPrgDLQWdXHHE2+Fd4wmvwyvEE0WZkOoWT4g3gJoWnaUKSa2WAWpPLeiF19QC7bZBo31dOx/HtOrZd/TDiR/007UO3YbErRCxmJur1SB/mkNqAQ2axlANnSNdV9AyPyMh/Zem0oqw0t1IYWo0moDyhgXcQgDRaHMOXhXOsJoSmsdmpDBn4KqWegOowwILXDpqFQKo8nXE9qhKRogHTRjNSWQ0Iz8QhB6tgIiW6AtMWM9LwpRsqRyrMJ0quQhkhNGiBNNyMdb4rlw6IxAtEobJG+m+4gcXjIbdoiKpICuUtbwEgdSeZ7QTA7PAxvunGFAJZNfYrW5thCiJIrCwFZYZ1h54y23b1wgmjI5LswkfkNiHyZAURk+gBkeDGBYkph38CKIA6WtOI4ELYDZI8GyOcxMlchoJj1wARyKIU7Mg51g9yaDHIO6zqWDHKLi5IUXom9PLEdaNsajkr39gAswoA2NEuHB7pJpNrHS9k0Uh3N97goKeIpLBJCi/SSLGRVUZILVo0d1B073PLU9tBMIXt6DGoG+egGBIcoLHRo1PUBR9i4x7ACZCEs2CaalEfAIOVgnFQpu2YQF2YCmlmkkDUXzuAK8aoybQzZ0resa9AfZSWEZuCuCS5KMnhygTNX4vGfldviyoy5MsNTxWagjFMJoX86xMNpEi10sAgCHdLgINa2A342
*/