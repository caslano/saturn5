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
9yEboQG06jKdth9dM1t9Pg/xo5hFe8X9Lb0i9tiPrv4BaxgU2Im9PLo5iZl7dWzYVGpTnqKDsje/M7/FHlhfCJVnK3QC+p70puNIAAss9NOt9zYU+WiMQqez/eSaZUonq45N+gHPWRodLfg6K3hTvCDNxorY96/Jgv6ioAbyz8ZHhEUxEKgyTAP3TlAeptAUgKbXNjgSidwSfXHtZ08nHmGoDz6qrpcBqy6jsCxdmgbc7RXeDnESe+FwHKTxjWO1Ad0AqNXAkdkHoop9d9H7IuYhM/+E0u1WhuXTEWls7LWaGbJmkE5oU2IRqRAhmtF29Lj3IFQvmVqTuVXew7dID2HJDKjV42xdYohwK7Q/Y2V7uqhO4K91o+Ul0LY4fcINR5f/4dOky9OBRjYZU/1iitxsEF7i87QTqMgfaUpKRW3rVoPwHJ+35gTaWuzOXdnREvPETXciNMaLe6OHvYj6+8kk13TF6NAD+1FKo/1U9+EzjlwST1sFaZq5ULLQVwuvxQNwWZD8DZh1YDHk+2F3yFFviFxXWGZZlypsMwwusU7ipaDSmh+Q+wz5wRvO07tkHUtmt+FNU4NfeCygBGKnC5t/vkFMt6OX0KK6hYDnqegOTBrRSYFk8SWRAIp5S/jE17DQ4wP1uQY5IvPI0iHo0LU8eXsI33gIOcn2iG5+bneEpHSUuDhGqJUBughI5Md0BxsIi9nrxB5luoxS
*/