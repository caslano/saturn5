/*!
@file
Defines `boost::hana::adjust`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ADJUST_HPP
#define BOOST_HANA_ADJUST_HPP

#include <boost/hana/fwd/adjust.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value, typename F>
    constexpr auto adjust_t::operator()(Xs&& xs, Value&& value, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Adjust = BOOST_HANA_DISPATCH_IF(adjust_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::adjust(xs, value, f) requires 'xs' to be a Functor");
    #endif

        return Adjust::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value),
                             static_cast<F&&>(f));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct adjust_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value, typename F>
        static constexpr auto apply(Xs&& xs, Value&& value, F&& f) {
            return hana::adjust_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<Value&&>(value)),
                static_cast<F&&>(f)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ADJUST_HPP

/* adjust.hpp
W9JwPQOdMQutleJevYxgGkk+ifBQojVcPE9Eyk4wLGJ69XinvPkVsD2z+Vl52ppPCpvZA1aIBuwOPV+s1RsHhy9e/nl03HrbPu10i81l0scCD0l8kfM65E+dC/ahjr8GnbQfb/R6cm0JJLi+SxqA+qZq+mERIcmVAiLv5ylKMydPHmSoOheuoa/lx8k6tZXiGppzVcRmeIQInDjWiS/x3wWsOTdg7lcsrTmeT36qsrKi0tlCa9CktYfxIysYWBRFWycJXOgkybJXJCWOUrUmcHj9hOdxfH8/57+OjLG/Ws87fgMnJ3B40/xZ6T+gdte9yet5I/GhOYw9xXjh8y1EjdxWhkuxH1LLmlA++n93H5MG29vPf1BLAwQKAAAACAAtZ0pSN+akWzUDAADkBwAAHQAJAGN1cmwtbWFzdGVyL2xpYi92dGxzL2tleWxvZy5oVVQFAAG2SCRgrVVdbxM7EH3Prxi1L220ZLnlhS8horSlEVGDkiAUUWQ569muuY69+CNpUH88M7spVUtKhcBR4o3Xc86Z45ndfV1ahSWcnfSPTyZi8HEyEu9P5qPxO3HW2ac72uLum3n3340OdOHRIZqvoEFzE/HBu69YxN27hbiG9kNRFzQ/RpLDbci1OITHQ67hoAkRW5bXfC3E
*/