/*!
@file
Defines `boost::hana::negate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NEGATE_HPP
#define BOOST_HANA_NEGATE_HPP

#include <boost/hana/fwd/negate.hpp>

#include <boost/hana/concept/group.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fwd/minus.hpp>
#include <boost/hana/zero.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X>
    constexpr decltype(auto) negate_t::operator()(X&& x) const {
        using G = typename hana::tag_of<X>::type;
        using Negate = BOOST_HANA_DISPATCH_IF(negate_impl<G>,
            hana::Group<G>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Group<G>::value,
        "hana::negate(x) requires 'x' to be in a Group");
    #endif

        return Negate::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename T, bool condition>
    struct negate_impl<T, when<condition>> : default_ {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::minus(hana::zero<T>(), static_cast<X&&>(x)); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct negate_impl<T, when<std::is_arithmetic<T>::value &&
                               !std::is_same<bool, T>::value>> {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return -static_cast<X&&>(x); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NEGATE_HPP

/* negate.hpp
eobsL90D7rkXzpITPe76Q8/ckXsR8lrdrX/PcYVj8AFiJxcBhYxL2Ot2e5tTBHNTg9vAppsucteyyk+fzBA18hBZ9lrVlk9JOCAHJ6ADOWEe9gTc9PUu2wXQlnABv0gd49We3+nUOxbyk5ADp25v0WywEe9Q+CqBNYJgrnj9k8MC1jWCM56sL2kM1U89JarUkrS5mfCgw53Xhua6N7YCzpkahFX5ZrzwEsgTph2XD2u1odC/bX6zgzf75SIJYAK/it1wsxF/3t+AqzDrtTteYiLdiZpYKoZajnY/ONmAvvdf0ngDWLd3F0ld4zppGneaR2KGB71d70o6JLisYusVx+na+uVJLxCfHUYhClFv1iCHeLCvtrsikmbFvOyECxaZn+svf4w9k6w9A8M3sTKMypw+Nvz8DGeDcK3kL7v+viH0xmdjTIrpnM0KtkW1s/5r9iqg56kF9QHvt+RtlDaufgfNEzy9TjhqIsrS2LA2rwbm2z7tG6kBUpxnTxdp237tTtHjKmVw9AsKP+2P4V3NdW690zY5+bEa21JLo35d8eJS93gil22KIAmnXA==
*/