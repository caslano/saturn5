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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_STD_RATIO_HPP

/* ratio.hpp
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
*/