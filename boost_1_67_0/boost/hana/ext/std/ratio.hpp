/*!
@file
Adapts `std::ratio` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_RATIO_HPP
#define BOOST_HANA_EXT_STD_RATIO_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/div.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/minus.hpp>
#include <boost/hana/fwd/mod.hpp>
#include <boost/hana/fwd/mult.hpp>
#include <boost/hana/fwd/one.hpp>
#include <boost/hana/fwd/plus.hpp>
#include <boost/hana/fwd/zero.hpp>

#include <cstdint>
#include <ratio>
#include <type_traits>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adaptation of `std::ratio` for Hana.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! `std::ratio`s are compared for equality using `std::ratio_equal`.
    //! @include example/ext/std/ratio/comparable.cpp
    //!
    //! 2. `Orderable`\n
    //! `std::ratio`s are ordered using `std::ratio_less`.
    //! @include example/ext/std/ratio/orderable.cpp
    //!
    //! 3. `Monoid`, `Group`, `Ring`, and `EuclideanRing`\n
    //! `std::ratio`s are added, subtracted, multiplied and divided using
    //! `std::ratio_add`, `std::ratio_subtract`, `std::ratio_multiply` and
    //! `std::ratio_divide`, respectively. Furthermore, the neutral element
    //! for the additive operation is `std::ratio<0, 1>{}`, and the neutral
    //! element for the multiplicative operation is `std::ratio<1, 1>{}`.
    //! @include example/ext/std/ratio/arithmetic.cpp
    template <std::intmax_t Num, std::intmax_t Denom>
    class ratio { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct ratio_tag; }}

    template <std::intmax_t num, std::intmax_t den>
    struct tag_of<std::ratio<num, den>> {
        using type = ext::std::ratio_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Conversion from IntegralConstants
    //////////////////////////////////////////////////////////////////////////
    template <typename C>
    struct to_impl<ext::std::ratio_tag, C, when<
        hana::IntegralConstant<C>::value
    >> {
        template <typename N>
        static constexpr auto apply(N const&) {
            return std::ratio<N::value>{};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::std::ratio_tag, ext::std::ratio_tag> {
        template <typename R1, typename R2>
        static constexpr auto apply(R1 const&, R2 const&)
        { return hana::bool_c<std::ratio_equal<R1, R2>::value>; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Orderable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct less_impl<ext::std::ratio_tag, ext::std::ratio_tag> {
        template <typename R1, typename R2>
        static constexpr auto apply(R1 const&, R2 const&)
        { return hana::bool_c<std::ratio_less<R1, R2>::value>; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Monoid
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct plus_impl<ext::std::ratio_tag, ext::std::ratio_tag> {
        template <typename R1, typename R2>
        static constexpr std::ratio_add<R1, R2> apply(R1 const&, R2 const&)
        { return {}; }
    };

    template <>
    struct zero_impl<ext::std::ratio_tag> {
        static constexpr std::ratio<0> apply()
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Group
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct minus_impl<ext::std::ratio_tag, ext::std::ratio_tag> {
        template <typename R1, typename R2>
        static constexpr std::ratio_subtract<R1, R2> apply(R1 const&, R2 const&)
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Ring
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct mult_impl<ext::std::ratio_tag, ext::std::ratio_tag> {
        template <typename R1, typename R2>
        static constexpr std::ratio_multiply<R1, R2> apply(R1 const&, R2 const&)
        { return {}; }
    };

    template <>
    struct one_impl<ext::std::ratio_tag> {
        static constexpr std::ratio<1> apply()
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // EuclideanRing
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct div_impl<ext::std::ratio_tag, ext::std::ratio_tag> {
        template <typename R1, typename R2>
        static constexpr std::ratio_divide<R1, R2> apply(R1 const&, R2 const&)
        { return {}; }
    };

    template <>
    struct mod_impl<ext::std::ratio_tag, ext::std::ratio_tag> {
        template <typename R1, typename R2>
        static constexpr std::ratio<0> apply(R1 const&, R2 const&)
        { return {}; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_RATIO_HPP

/* ratio.hpp
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
*/