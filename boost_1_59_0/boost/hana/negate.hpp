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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_NEGATE_HPP

/* negate.hpp
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
*/