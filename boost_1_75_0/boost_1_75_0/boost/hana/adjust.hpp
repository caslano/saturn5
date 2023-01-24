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
A68GQw/lDONX0JIfXJ4KpDR41NUYqbkkC5+pqNGQg6unssLjYXW30t2vBuLZHoEEge7vCSt/yTXKqpmiLR2B0cDY/GgaO8JL75YlFAK5bAjl4k3etKPk9WIF3ovSb34jQqUN1HcVT9sR0gistSL6us0TaLXNee38M4xjhgptHlu58aNrD0Jvb8WzHuI6pou6M90KVgn20g1OOMsGkfqLXGc7ztkD9KhW39f3e5AnWW98ODV7oFBT5EG8/sYu40vXT0EYXmyS+IJwt3ovYVQvuFXZaAj8ws2yxxfo9RkW4PW1JMMCBsfr6VdMNnuE4G1g+7F+Fjg/1hvyCUSa7ET82eiUp+FF6SsQE0/K/RRMBjoXAVGp8GO90hbeC0eC3ErbTNfI28Zff674IxKom8AmJa1bq8+yt4x5v0a2pDIQSFtbhYF+NGAEbO3VFtZBgeg66WOzpLpYUEN4OXCrviodXDlc6L1/+fM1Z/zW1HVHSaXun8NeqYpGrxD6rSvXCP0OJW7E5LVffFHCeje/o25r1hjc0Z+y5OfarG3RFovySYn6XIxed9rsV2DkSAaAgJJgBTpjrZjQckj7VOW7GIkxYFMnL8S0GLE1XVMmwxtuUdgUSVmn6xpuuqM5z5q/Q/sl+EPVTlyrFF4uHThhFLTJCTl5qVnzbuOEXuKe9sHG9R9VTseCl5OVkvPkffUyVh6L50VgN235g5k5NsO2
*/