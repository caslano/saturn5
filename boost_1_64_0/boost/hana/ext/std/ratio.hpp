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
6WQ7BZ7zG0tj3t6QaDuT9y86c3Gj0Zl77+H06FKBfVn0vM0JBJx9Uv/cTIOHpxReW8dyn0Z8MT4L1OUfBqL5sRLl4cfJc9oqPVm5t3XJO4flTfflgfeijM/u6mxstDh+vMXu1zcxnlLz1T67HClVOxl2jV/r0bMVYu6XwRyo8o6V2BNQClqSbO73GbE6WRGL6Hlv0pzp0SsRNvQV28+ziAa2qe3nLLTFFKSNZfDceH1eeIjutnd0or2ggQh/nlePbDm6XEjCR9VrB5n6shE0/lthYFjZv6O6LUkHLiGKQzGo9QEaaEC5t8nlQLQn6aTvRlpCvPgKja1yCYUhVq9tbvTyNUgJ8Lp0b2m7EtAdWzzd4echXyh4at+WTQGnvNR0YUorljKmFI9VJ5WluWznWjfwiEpFAm7tlh6Zo5USzCSIKr/DtE1wUB3p3ET8jaQdVE4LGOE6iQdyh02oTmkzdPZbdUMfB7Tr9QDVidiNHUK2MwaFxpNFy4MhqkN9J8VwLBz6pogZamKmVHY9rZ/juTofbhfMpZ7tUJBtw0iORho5fu8LUjImiJ3gtIqU8n7FbtSRTu9BrmpXb2UYHKT1f698o65f6qP+QH7tCmr7en8po2TbPxeF8YDI4DyNDFbEsytRnwlWau0CqRI1Tz5ixv9WvocGODUvd5t5OZBWe+oUR84pORmwK5d/Hy3srVKOz36MG/qyfpCgxdHvM/CpkooMUgwwa+A4jehoH6JhbqWzubv1xv+cQPKE/9ghxxAnGw2d4ovRcEBz7qGzK4gG+tSOeQhv0jHXcswIbfg6jfle4nZAx3Ll43gvYFrhhqJjxvo9ufTEgKnf01OeLnI8mGE9pImwWomtchi4TviBX1TxdIE9XGDPnO9gjxHYJ+c52OMAmwbs+BMc7AlC90aiexpgCwBrpTYuA2whaC4kumcD9kD8d9c9HOwFUl/lRAd7icBGqX8vl7JvpjYuBwygutcPOtjrpN0ClX2j1HexgtXo9xpZCPm9t8X352gNAtcT68+bvfVHjtS59xOBxx5lTCNFuLc38hlJ3OVMuQjvAE7bLJBB9jP5ODrPE45JcwzRvmXR6GIpLfrsPb3buUxw+hRb/E3Cdzd69wqACco04jVC+fZan8kdItEiZPONUAcS5S3vllM51ViE4H30Kxppj0XwYKzVH1c1Ol0OTyC7D8qc6GzbHwAd+xw2Dwdw+OU8Lu7sf72s61IIix+mrwrrUV4b20MgE6P0IAbF1vPREM1E/I6xT4RoyvkpJOSBLO43R3fLRQsqf891jcZvONCiHe485wJeL/aBFPPXUxk1Pt9LdggurZydzKFLyBKi8XkNykKvabtTKW3/vZDPiN7bjbtDuuUuicOaGu147R/MFGbU8CG4hzSMw8Us1fM51MN7daF3Z29olH2q3L7Eu5M3NlaP7XxB4UqK3dgjgmVoBA00xLsvgUbiM5h0zub6CuDwNUWPxMs8Fzg8O50eK+XoDi22xTCI1MebZHzQit0LW0cxTs/2hXiroZxRs/DWgL1lZyE6HPMH9kr74KUZT8ng4D5+XfVlVw8wyvpytnIP94PjcexfCzfEv/Z8Wu9xZYojfNPzLeaa9yUvhv7Q2QL3yPor36nqL1agwg4oDYm4E8aN1urvB3xG8i6DPqtyVMlm01GP9ih26NXny5ooF7GsHT9+6pUjOaN4ergvoAW7YEmpLYp9Jo5ydsgnDsuTpb3Zo5UAu9v2HnO0vwrS0luxJCe3sF7w3hr+NeO0ie9iELfN4fOG8hduF3qlFygYqcfH5gd5dXoxSzsn/qDWipIMAfX3T+T7cLyU7Vb0Uwpam9LS3EG6jb+H5/+d1IZfV+w=
*/