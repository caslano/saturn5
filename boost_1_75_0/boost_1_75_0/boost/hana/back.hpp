/*!
@file
Defines `boost::hana::back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_BACK_HPP
#define BOOST_HANA_BACK_HPP

#include <boost/hana/fwd/back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) back_t::operator()(Xs&& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using Back = BOOST_HANA_DISPATCH_IF(back_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::back(xs) requires 'xs' to be an Iterable");
    #endif

        return Back::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename It, bool condition>
    struct back_impl<It, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            static_assert(len > 0, "hana::back(xs) requires 'xs' to be non-empty");
            return hana::at_c<len - 1>(static_cast<Xs&&>(xs));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_BACK_HPP

/* back.hpp
Im0/UVmHUu73VfbwpmON6fAprZNhxxn2Csvq7BkbGJ+HVmMiKn5RCewPPTccGdwVbhOtiEGt+oLbePx5utwFQ6ckiVIH7GevPQnNeS+ECw7TnH644NU7eJ7iANg/PxV+uq9zeP5h0PLka1xG1gCrvyiMIuJ8Juf50Xu/nEku0u05+6Vd+d5yo4V3XuBaf0xS+GPfD4NfLHRvxXu6xoIPXRu0aMolo7V+EtTjNtsbZXOSQxoOIX55rKLVHoHrXIwtiOpAR/nxqNSofFPg3BItKoFhrNub9y2anbjBql9poLa7yV/cRnvSL84GCACrtx07khMr50WJCx2whSCZP6/zqba0e6yWHRevJg/Tt+mMjTIpLDh02rGsl12lFZQ9K25xP0bpVe3a/laoAqdPZ66jVOuLzLVlWUcUzNO0OaT0laT2IzR6ezSNHKA3anyK8h1XGuYwF2bF+qU5nEZsSme0KbUKJIXPaEt6TkBdaQHTENmsoTd2hd42054t0xqeRXa5LqxN0+6rYgAnG12wSGZVXzoENWo7SwnkIOEAfHadoUjMeYM3A1EROEzbLsPIaSVZ13YNefpljd+NzlQ5DJB974un8vFlhTfkPcuh8PSfXAaho8SfFN9mUccWFJPuYstZX4id+Rx93Ph5xRLY8Ketl+SkkjonBQ3jzqz1NhhGXQupqwhcCI5SdEhknURZyBO3n1q7tBnkv3Br/GR+
*/