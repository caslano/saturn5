/*!
@file
Defines `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLACE_HPP
#define BOOST_HANA_REPLACE_HPP

#include <boost/hana/fwd/replace.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/replace_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename OldVal, typename NewVal>
    constexpr auto replace_t::operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const {
        using S = typename hana::tag_of<Xs>::type;
        using Replace = BOOST_HANA_DISPATCH_IF(replace_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::replace(xs, oldval, newval) requires 'xs' to be a Functor");
    #endif

        return Replace::apply(static_cast<Xs&&>(xs),
                              static_cast<OldVal&&>(oldval),
                              static_cast<NewVal&&>(newval));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct replace_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename OldVal, typename NewVal>
        static constexpr decltype(auto)
        apply(Xs&& xs, OldVal&& oldval, NewVal&& newval) {
            return hana::replace_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<OldVal&&>(oldval)),
                static_cast<NewVal&&>(newval)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLACE_HPP

/* replace.hpp
nOEsB8UXHe+VHI7KghRqf0AD69/cNjMtCw0SsRE9X0RDGk5T7yqHoR8xRiDCqrAo0edLksANk9lez+PQ4gtgfYrJY6Vd8RSCP6yaBjfOwJBhvy+nDnPpNeq1bzZRf/YHtdNxLOC3HMC3jg4GKg89uyNP4s2EAWhreVB3dPGLDWtfStqleehzVwapwaCbnz680/85GwUVzgkv1bjlnnjUuZ4mgrOUkFKiNFibXkmQVe9lrCrcq+OidW8J+6Evk8qLviyprnc9UgbqZaSyThQksQCT9C0z/iUSsUvd1w+Rxrlmc9k4yiIbwm4/DZ5C4UZL2r8ziaI3bqtDmf3rsYXfmErKqtaGk/fVplDF3CI0qv+j2I9BrA5slv3WwvMVvBNk0vJWaqLTolQkPhtoE0HOEXrAFOf4MiyJCurArmR8RncVy6ismW9yRLZ4PRFXO9tPryAfVAxdLj7kz0UhKOgcbd2djhlPxfCIRzHYn0ovhHCxGNHuQGb6kbyeIvxiMbfpMANiu/QncG7wU0oJey69EZAE1P6tKPPql80RpnQtzbYGIncftOXz4NnAUA==
*/