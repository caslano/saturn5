/*!
@file
Defines `boost::hana::value`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_VALUE_HPP
#define BOOST_HANA_VALUE_HPP

#include <boost/hana/fwd/value.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename C, bool condition>
    struct value_impl<C, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };

    template <typename T>
    constexpr decltype(auto) value() {
        using RawT = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;
        using C = typename hana::tag_of<RawT>::type;
        using Value = BOOST_HANA_DISPATCH_IF(
            value_impl<C>, hana::Constant<C>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Constant<C>::value,
        "hana::value<T>() requires 'T' to be a Constant");
    #endif

        return Value::template apply<RawT>();
    }

    template <typename I>
    struct value_impl<I, when<hana::IntegralConstant<I>::value>> {
        template <typename C>
        static constexpr auto apply()
        { return C::value; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_VALUE_HPP

/* value.hpp
QzyV3yUyEKfaRPrEwx/fpQja3PWBlRO8KL+CmMhnNGCJvZx00eRMPl5Y+tuwpoJaENeKXZGFNJsjM8HlFH0txTfySisW13XSfbXyHnH7PqzsutD2wssUQQqTJXOeFaETy2Rlo3nhEGWO5sUm1lj61uoSpchM4w/S2t13g1Bn9wVLgR+S+EAD/R84gtjZ+B86BN+LkT9xlSKKSUZhEzIgC61754GeFI7dCnAIQ+eyzcz5rnTF0Y7Sebh0iyRM+9+/pIDBeLv2EvVVzV+8FixT2Ll17hgFDqllquKlx9xdE5+TuG4r7/71lU1WSEhLJVBk2HZTDEhJr8ov3mVTqIPv/7E30lCtF6vcd7lcT0qnpJttQzrnqqHzff3xJL1NENZI3uhuOC04QI7isryx/P57VPq2jVm8/UQPi8paliDNQXZ4Emgg5aKvK8V+UWTNwor0/Y/giqPumegeHvC6jBSLCeKKZ4lUHJrr6IpUa+SODQwr3g2w/Edys7HwWuoXQw0qwQ2KPJNhxYUHfyosPvgzP6yLf1Q+OKA7L9CdHk0KLT5X40Y5j9YlWDVMgekvK7mpk8XFuXDxqK2FKOLY6wKazulK6CYkUl6N/0was4J1dgHrX3BhNxdlIaN9QYZKIrm1UyLJmXn/u3l63HZR
*/