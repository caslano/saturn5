/*!
@file
Defines `boost::hana::Group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_GROUP_HPP
#define BOOST_HANA_CONCEPT_GROUP_HPP

#include <boost/hana/fwd/concept/group.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/minus.hpp>
#include <boost/hana/negate.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename G>
    struct Group
        : hana::integral_constant<bool,
            !is_default<negate_impl<typename tag_of<G>::type>>::value ||
            !is_default<minus_impl<typename tag_of<G>::type,
                                   typename tag_of<G>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_GROUP_HPP

/* group.hpp
qS2WpPdCbG24ihXjljNCWRsnpkHP4eV7PdG99KOk5wJYcVVg1ap6oBTV+CqTkRRO4a4K/6Nf9JxSURUVPOlv4j6KS+qqsI00S07UaxV3xzaf0rK/22ex7NSIomGW8+nFqNiMcos0eO69IsI/ZE/csh8KlPVdQ6DQ/QvUtXVLp0ffCY+zCyD0KwgsyQTblhuhgQOEqyuOFR3ErAAyUugR3RTArCyKEdhZAqiec0z8EQNssHHArsGHpqhwWOkqSTnzw/UScnIE5Yh6i6H0hnNktxK6E7ydA74ABFrM12czrF0hOs24ZC0qhiJsHWKagOi9D4hZZDA6bBIA4Bs0EBoli7wMcOqG9OOf4yAs59Bi5sfDk9mo0YMUSvrDtDrb/Mtt9KmMW0qu12mSccp3tquZDuUFK6rG/g7cSx0CCZZBUWY3POsUUodcLcAAWKK8PqRSRv4nA71ISMogdS5I7kCbkazlUKB7kjZJE+yuCYYZhtiGDuqBWr2pj9eQhmJupfNQrEiz3/RW/k2FdisbKsVmZp+sGwYUvHVieQziuWGL1Cu2q0lqpT1yfCP7otRSpZSggUt4pcqdoBLpBBqzyz8ndaQdJI0gvsmWcqPeKSA5mNqaSfy5smlLEbEo+lkpIiVKV0m4+H+i+LUSRVFL
*/