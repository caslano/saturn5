/*!
@file
Defines `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIRST_HPP
#define BOOST_HANA_FIRST_HPP

#include <boost/hana/fwd/first.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) first_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using First = BOOST_HANA_DISPATCH_IF(first_impl<P>,
            hana::Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Product<P>::value,
        "hana::first(pair) requires 'pair' to be a Product");
    #endif

        return First::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct first_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIRST_HPP

/* first.hpp
ExsGiiU5qNd8aLS0gAP5FTZSn8IMoDiBBgd1tUz9znDQfgsf7vExNKx7v//u4ePzznnP9bz1bmA+LkzfoXkWOxBz5rUo3iHiKJib6C6MpRs1zJAaCtJNziEoYoE31h6We57XoeZI6yIEOAAnNzE57gYaXkOigfRR7YuNee7M9hIH1R60o+ViRmhMREMAh07p/IF6irCUT7rQjSZhgP7R1JbtxNM0DGt1jVCvd0kiDgSRl4xBg88aIBk0TxH+DWDZxFrqzCuAmXIQr1TcTeaCbxznbskwTyQ/4mc8tXi9l4CUHd8yP4efYVEDiiIWR1LSIBxvK8UzDEKUSmkWBqB7iGAz1E+zWZDdnqBATMO/L6M0tCUrvcYFLdaU7iXWikyGfs7P958rZTlWO1c8TdQGgiEHgPArk7sMqL/Ckf7XbY998S1+OPG2jePO9gLRY6vMr9t7+9QKtcdEBUJho19j2IsIMx5/FV30Bn4fPoetQFIXZRKoJxROltBP9NjCPU3m3CFRxGAaufzQwX5/GZNPPTqlLwAaRY2gpzgoDJPhLMlPH8jYQrvNfZJ+8oKUVJ80GKO5Bg6daGSinSvG8yS28TsZhUDAHp+BLg2NxwEzebZYplECB0vYRf32YNAb+N2eP+q9b3eB88+hczxH
*/