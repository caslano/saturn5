/*!
@file
Defines `boost::hana::and_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AND_HPP
#define BOOST_HANA_AND_HPP

#include <boost/hana/fwd/and.hpp>

#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) and_t::operator()(X&& x, Y&& y) const {
        using Bool = typename hana::tag_of<X>::type;
        using And = BOOST_HANA_DISPATCH_IF(and_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::and_(x, y) requires 'x' to be a Logical");
    #endif

        return And::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }

    template <typename X, typename ...Y>
    constexpr decltype(auto) and_t::operator()(X&& x, Y&& ...y) const {
        return detail::variadic::foldl1(
            *this,
            static_cast<X&&>(x),
            static_cast<Y&&>(y)...
        );
    }
    //! @endcond

    template <typename L, bool condition>
    struct and_impl<L, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::if_(x, static_cast<Y&&>(y), x);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AND_HPP

/* and.hpp
hCNr8ktvNO4PB9bgEp6M2KuXrH3XPmw/a8PH0EvAUysJnY88Tagn7ifcXE0UB7AeDOVJ4gtAygUOj2XPlaK7H9p/xxJDEY/jMDa34kEaw9KsGS2NLTe+ujaXJjP78Ifncsgqxs47/z4khB1u/Y0xQdoCIfAxFJS7JYLSiIxJ/Ig/GuMA37h2aiPX5A8TqDYtPvKQHlGKZNUfy6GKD28qT0Bggvi1U1587IRBAFshPGTAY2qtyKcs9eY8hNUBXKaD5osWOhALP/W8qREyK53F3HZ94CRaGfs7JKJ9O0nZU5ZVx6WcqAV4xcXe4KE0QdFWgICWWhR7QVoakQrmfB7G9yVQ+FySAgAAcbeAyQFfWlc2sHfgWkgA9q8txhTMilssQEXK71KmHhxrlSS/ZXXkb70KDqKK4TsWAdiwI8SwRq2pq9dFprcc2NccG5eGuQg3UmOZz+A//Xn0MRs5+miAaepdM/EHC+Eb0AN2c8B1FIdp6IR+8tvTD8dbn4+JZnYU+fdM0BIk1E+CJCizUCy5DZR0k7ejXudkbF0Mx/13oAl9Mpb+2h88PWxuKYEmHsM2ZY0vLy6Go4m2RvLuK7WaQEc7BSlfR400e3S8peoi7lU9L/BS+sezfe+fsPmBOBRThcpCuyhUncMOeddo
*/