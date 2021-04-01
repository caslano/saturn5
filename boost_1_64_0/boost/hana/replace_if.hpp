/*!
@file
Defines `boost::hana::replace_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLACE_IF_HPP
#define BOOST_HANA_REPLACE_IF_HPP

#include <boost/hana/fwd/replace_if.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/always.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred, typename Value>
    constexpr auto replace_if_t::operator()(Xs&& xs, Pred&& pred, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using ReplaceIf = BOOST_HANA_DISPATCH_IF(replace_if_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::replace_if(xs, pred, value) requires 'xs' to be a Functor");
    #endif

        return ReplaceIf::apply(static_cast<Xs&&>(xs),
                                static_cast<Pred&&>(pred),
                                static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct replace_if_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Pred, typename Value>
        static constexpr auto apply(Xs&& xs, Pred&& pred, Value&& v) {
            return hana::adjust_if(static_cast<Xs&&>(xs),
                static_cast<Pred&&>(pred),
                hana::always(static_cast<Value&&>(v))
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLACE_IF_HPP

/* replace_if.hpp
X1PdT002hvsEPQQewG2Ek5AQxGCNoXxKEDwqwKydfOpKO9W3qt6CXRg0HvcvlnebUpsgPla2B1E/eCt+OCiHn/Rb1C8XatFjvTxrGOowTvvekVN/5eKhu39zQTmK+LNL46ezBgJnznw2ziorzpfoT1GJY70gjqFN2jXy54YNAOXgmttl7elR6ndvjOwdDz9eJBoblhquX7b8AzX3i45gsSsNzXvWNoUYJyFpGxXPzEYhEwGOBysrHCC4AQE8tSiGhUBymZt0ck0JgL/KP/4oeEoYNr1UaocCXnZuQi/Q4R4AHRF2cB57/NSETQh8+bT2SFE2pgcidh0j75dPAQ1OscRDXnECpFylPrUx7SyJqdASzvwDMLMQam1eFq4mA5G6Sm7fJ86aMm5Z+CJ8bQUeTXcbXH3tG4sPq56lq0XE9x0SLL7xsCjExUEcoQNLkniFlEgFxysV5+vUf6VBL8XuhHmAB4MhJbgzCXfHDWyomOTAvm7lMeSOywFg/YPasgmsIm11b6wHkduajndzI7n8zhyezim3LynZR0UvHpiaGyn46IXtKkT3PdSHNQ==
*/