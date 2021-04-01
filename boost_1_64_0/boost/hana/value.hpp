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
KRaaFmOLmEyNCvxrLLmSPjQyI43zUea1tA+lSWJ1OaWAMoee7jq9sfaDWQRXgDdozrr6POY4Epq+xRJk3cO40/b2Bg1C25/l9QmfxI1Jdaqlzwr8/MoJVm4amcG6rtW/mbice668AG0n/smJ8a1UTin6co5hFvAevvJohFk4fz3ANlHjtVYailmSspB9SuLRO5Iv75+0m+h/B0w1NYNyvurfy2QMFS7e9FIrkPLHwt+rgcf9tzsIZlooPIkdcFtoxw0eQH4BMQG6XU00ybjBmcjf95FJ0UGAx+OT/vPKTfr9/hXrG4imv5LcB2l8KSIrZ5tj64vXZvFL0mwLHj5oxbxDotXQ0/NLTBJzWphvhKTtepzgTT2zanu/ULTubz1Dd4m+bdZMUOtdBaRzR8i+FSdd/fiqglVnnWOk3Hg5aWefzU45btTxhVPcsSxsqpogdDkYjQJz4uxS+orlmivI1EDqEmp8MSuj7hT4SGm6KX6o5KhP1Z4xXjLcJm29clXZkqkelF9OSXKbT3/d9hzigglWSNmSs2YPELJcjnz+AGouTVDDyzC8ZfvedA==
*/