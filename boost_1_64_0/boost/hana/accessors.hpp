/*!
@file
Defines `boost::hana::accessors`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ACCESSORS_HPP
#define BOOST_HANA_ACCESSORS_HPP

#include <boost/hana/fwd/accessors.hpp>

#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct accessors_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Struct<S>::value,
        "hana::accessors<S> requires 'S' to be a Struct");
    #endif

        constexpr decltype(auto) operator()() const {
            using Accessors = BOOST_HANA_DISPATCH_IF(accessors_impl<S>,
                hana::Struct<S>::value
            );

            return Accessors::apply();
        }
    };

    template <typename S, bool condition>
    struct accessors_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    namespace struct_detail {
        template <typename ...>
        struct is_valid { static constexpr bool value = true; };
    }

    template <typename S>
    struct accessors_impl<S, when<
        struct_detail::is_valid<typename S::hana_accessors_impl>::value
    >>
        : S::hana_accessors_impl
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ACCESSORS_HPP

/* accessors.hpp
XietYWyNkdyOrWjqhqLbQvDsCEcAU40sOzNcQItpMhH8NOWThg/9IGsCplI95fmfG0Fz2JQFkUgCjsdLrMmXJlc3w28kasrfdU1soNWUGFnwDIBVTS2O7i9Rhzk3TeiQTjifNEzDJNW/qZzLB3IQg0x4hjPvLVB3gfk2jAyhVp2al9UHAAw8HfnSXBLCI4GKfPhQIkHPpo85fnGyrwzPdOEmQSed09vEAz4ANANYy0FkKYK5pE59JqXDDeOzqG802/vMSS3nVc5DfU/Rb1eSrYcRAN41AzpRrtRP1sMUHsV3my0SiqYV+u0CCAEwYOkeBCZvg9oBqsLA/LoLvimow7/psTWa4HuNSNLHAZ8byb4yD0XvvDH0KI0Jme7PkIJV9Y5pW3CaKcfVH41Zuqb4KxOJtEvPmrPZp+Cz+3EUA3JFWjWpm+jhEu0SB6u79/W6JLeeSM8WkpxVNb/Lfr0/hXcAIj31QMPVZKYY+6tA+oweXD7YdRBZqcHHN9SLegVqUJ1duTRYlGzt/KPTa5gnab02E/HQfw+pta+i7fu1fDsfzecpUM+XftvFTw==
*/