/*!
@file
Defines `boost::hana::Constant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_CONSTANT_HPP

#include <boost/hana/fwd/concept/constant.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/value.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename C>
    struct Constant
        : hana::integral_constant<bool,
            !is_default<value_impl<typename tag_of<C>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_CONSTANT_HPP

/* constant.hpp
dAIufnVqdBg9KU46GSHsKT1RCpD6NAp4+7eCFgyzNYGHxVQPOtmVMSW038dL+FM8LurByNnvaZmDMHZ+JHCCYzwm9X42/3iksB1fRQuz6IWV/pbIDU/aQhfGFjpsC3dvDKsr/ZNacczzahayh2+/5kISHinE2N5ZRsMCk4A+uL9FRfbJbEzzIaXB74/O4i7OQ3d+TmBzvooqSw9+LXBl6eg28i/8E3CRF4AdSIme7fOolSfv5a1sjdOED3j3D+3da3HY8o7oCtZhvLRoUylNqaQxhI907TMazjlPbwGWyTODzPkngfIppdsJCPoZIkRcMTxC2GwnprQPN1XU90TwWf5lFJ/1vRo+R27TXIyZNZ68k0vK5XmX+5I9vVkoWWxnKVoLTpnpsxPfPaL158d4dGNIS3jqHv7ybbPGRFqIiexjc6NVOP5FtApz9SpsfYZU3xbPgMa7cjD+aIm3tETcGY97aKbhydcTPTnZ/PPAKZprifTTMC+klJuMwUPoWRBPi4NUfodTdbTIASPQh5M91SPoXuxlX0R7dfsprVfjEBC6Ed7oLV0JYKQ4uckcNAFcBMS+MtOacQc29DENI5+gsRvXMq2baZ0S6D8m1Vot1RsmDR2HaUjtY5d8FUHH4e4oOi45paHjvt/gktej2RyrT2/mYHwm2nOyCyMNfQ9DbvT0Vt9sCr1+OVYt0ldLNKgX4WHJuCC7nb2hdd8I
*/