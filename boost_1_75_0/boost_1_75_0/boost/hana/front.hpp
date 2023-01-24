/*!
@file
Defines `boost::hana::front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FRONT_HPP
#define BOOST_HANA_FRONT_HPP

#include <boost/hana/fwd/front.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) front_t::operator()(Xs&& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using Front = BOOST_HANA_DISPATCH_IF(front_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::front(xs) requires 'xs' to be an Iterable");
    #endif

        return Front::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename It, bool condition>
    struct front_impl<It, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::at_c<0>(static_cast<Xs&&>(xs)); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FRONT_HPP

/* front.hpp
wBzC4ubAihPMlW6FudAYCvxTN+kl5tPoeesfK55rsE8HECYIP019RBBOF0kvJURi2HgMwLHZALvHRrtUs18GInEiKT3Ue39auYMt4f+Gwk4M7g/HtVqeOl89NQtgczbb5YFeta/GpgfE4qf9xC8q9/Sg1yel8/pumIJ0vjmwEjgQd4G2CkAW/uuRwD+tu9e+erb1wABkp9gQK3LY3sJ7uXVhvOdpeWD/5gLM5vRpARgfpHECtPbyMSF/BEZrQwHvf58QD+c9iYX835ad8f+hWsvSx4Pr36a2dzAY88xrDtBMkRZlmWqzMFbiotVLGzZkk5lskXajvF9cmfqe2cTCeI/vK2Nk3am0u40vI+yU1pbyOiKvyDJm21yKpvWiyQ5fjvqDUhX3XhfaCowpEUf/Ev5abRva8edYnoS23czM7p6Scdp0mwWka7IA4Xpu99kcQW538Cyku9/wKRYAex40jvHdb6j4k3csZtGKpiwJFw+6S8X7tlnjKQFhPwrw6/7Tn7Hv2iTmzDHN8u6ECihsPpAEa4vjNZB8Q6jRZqNagQMFqwzI7oltz23DDl0DcdMIVWM+MdBg4OIrDCdk5PTjp2BmS6vYzjQDDWydko8B6suB7hlAP9B1/RJQbVn+UaQmxk7awGKEaDyl6a1wRMbmaDw5riFJNS2pX+n594Xg1IJv2PGbVhf94/LV/g6kEKHREttX1eZPYgcPA/YW
*/