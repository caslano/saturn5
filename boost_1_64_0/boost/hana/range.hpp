/*!
@file
Defines `boost::hana::range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_RANGE_HPP
#define BOOST_HANA_RANGE_HPP

#include <boost/hana/fwd/range.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/iterable.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/back.hpp>
#include <boost/hana/fwd/contains.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/drop_front_exactly.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/find.hpp>
#include <boost/hana/fwd/front.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/fwd/maximum.hpp>
#include <boost/hana/fwd/minimum.hpp>
#include <boost/hana/fwd/product.hpp>
#include <boost/hana/fwd/sum.hpp>
#include <boost/hana/fwd/unpack.hpp>
#include <boost/hana/integral_constant.hpp> // required by fwd decl and below
#include <boost/hana/optional.hpp>
#include <boost/hana/value.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // range<>
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename T, T From, T To>
    struct range
        : detail::operators::adl<range<T, From, To>>
        , detail::iterable_operators<range<T, From, To>>
    {
        static_assert(From <= To,
        "hana::make_range(from, to) requires 'from <= to'");

        using value_type = T;
        static constexpr value_type from = From;
        static constexpr value_type to = To;
    };
    //! @endcond

    template <typename T, T From, T To>
    struct tag_of<range<T, From, To>> {
        using type = range_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // make<range_tag>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<range_tag> {
        template <typename From, typename To>
        static constexpr auto apply(From const&, To const&) {

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::IntegralConstant<From>::value,
            "hana::make_range(from, to) requires 'from' to be an IntegralConstant");

            static_assert(hana::IntegralConstant<To>::value,
            "hana::make_range(from, to) requires 'to' to be an IntegralConstant");
        #endif

            using T = typename common<
                typename hana::tag_of<From>::type::value_type,
                typename hana::tag_of<To>::type::value_type
            >::type;
            constexpr T from = hana::to<T>(From::value);
            constexpr T to = hana::to<T>(To::value);
            return range<T, from, to>{};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct comparable_operators<range_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<range_tag, range_tag> {
        template <typename R1, typename R2>
        static constexpr auto apply(R1 const&, R2 const&) {
            return hana::bool_c<
                (R1::from == R1::to && R2::from == R2::to) ||
                (R1::from == R2::from && R1::to == R2::to)
            >;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<range_tag> {
        template <typename T, T from, typename F, T ...v>
        static constexpr decltype(auto)
        unpack_helper(F&& f, std::integer_sequence<T, v...>) {
            return static_cast<F&&>(f)(integral_constant<T, from + v>{}...);
        }

        template <typename T, T from, T to, typename F>
        static constexpr decltype(auto) apply(range<T, from, to> const&, F&& f) {
            return unpack_helper<T, from>(static_cast<F&&>(f),
                std::make_integer_sequence<T, to - from>{});
        }
    };

    template <>
    struct length_impl<range_tag> {
        template <typename T, T from, T to>
        static constexpr auto apply(range<T, from, to> const&)
        { return hana::size_c<static_cast<std::size_t>(to - from)>; }
    };

    template <>
    struct minimum_impl<range_tag> {
        template <typename T, T from, T to>
        static constexpr auto apply(range<T, from, to> const&)
        { return integral_c<T, from>; }
    };

    template <>
    struct maximum_impl<range_tag> {
        template <typename T, T from, T to>
        static constexpr auto apply(range<T, from, to> const&)
        { return integral_c<T, to-1>; }
    };

    template <>
    struct sum_impl<range_tag> {
        // Returns the sum of `[m, n]`, where `m <= n` always hold.
        template <typename I>
        static constexpr I sum_helper(I m, I n) {
            if (m == n)
                return m;

            // 0 == m < n
            else if (0 == m)
                return n * (n+1) / 2;

            // 0 < m < n
            else if (0 < m)
                return sum_helper(0, n) - sum_helper(0, m-1);

            // m < 0 <= n
            else if (0 <= n)
                return sum_helper(0, n) - sum_helper(0, -m);

            // m < n < 0
            else
                return -sum_helper(-n, -m);
        }

        template <typename, typename T, T from, T to>
        static constexpr auto apply(range<T, from, to> const&) {
            return integral_c<T, from == to ? 0 : sum_helper(from, to-1)>;
        }
    };

    template <>
    struct product_impl<range_tag> {
        // Returns the product of `[m, n)`, where `m <= n` always hold.
        template <typename I>
        static constexpr I product_helper(I m, I n) {
            if (m <= 0 && 0 < n)
                return 0;
            else {
                I p = 1;
                for (; m != n; ++m)
                    p *= m;
                return p;
            }
        }

        template <typename, typename T, T from, T to>
        static constexpr auto apply(range<T, from, to> const&)
        { return integral_c<T, product_helper(from, to)>; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Searchable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct find_impl<range_tag> {
        template <typename T, T from, typename N>
        static constexpr auto find_helper(hana::true_) {
            constexpr T n = N::value;
            return hana::just(hana::integral_c<T, n>);
        }

        template <typename T, T from, typename N>
        static constexpr auto find_helper(hana::false_)
        { return hana::nothing; }

        template <typename T, T from, T to, typename N>
        static constexpr auto apply(range<T, from, to> const&, N const&) {
            constexpr auto n = N::value;
            return find_helper<T, from, N>(hana::bool_c<(n >= from && n < to)>);
        }
    };

    template <>
    struct contains_impl<range_tag> {
        template <typename T, T from, T to, typename N>
        static constexpr auto apply(range<T, from, to> const&, N const&) {
            constexpr auto n = N::value;
            return bool_c<(n >= from && n < to)>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct front_impl<range_tag> {
        template <typename T, T from, T to>
        static constexpr auto apply(range<T, from, to> const&)
        { return integral_c<T, from>; }
    };

    template <>
    struct is_empty_impl<range_tag> {
        template <typename T, T from, T to>
        static constexpr auto apply(range<T, from, to> const&)
        { return bool_c<from == to>; }
    };

    template <>
    struct at_impl<range_tag> {
        template <typename T, T from, T to, typename N>
        static constexpr auto apply(range<T, from, to> const&, N const&) {
            constexpr auto n = N::value;
            return integral_c<T, from + n>;
        }
    };

    template <>
    struct back_impl<range_tag> {
        template <typename T, T from, T to>
        static constexpr auto apply(range<T, from, to> const&)
        { return integral_c<T, to - 1>; }
    };

    template <>
    struct drop_front_impl<range_tag> {
        template <typename T, T from, T to, typename N>
        static constexpr auto apply(range<T, from, to> const&, N const&) {
            constexpr auto n = N::value;
            return range<T, (to < from + n ? to : from + n), to>{};
        }
    };

    template <>
    struct drop_front_exactly_impl<range_tag> {
        template <typename T, T from, T to, typename N>
        static constexpr auto apply(range<T, from, to> const&, N const&) {
            constexpr auto n = N::value;
            return range<T, from + n, to>{};
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_RANGE_HPP

/* range.hpp
EjKzTL7Pjz2vszcIxiQHMVoL0oLf91/O5/Oh7fVv0969O46wb2co994LuHIQQxA+xouWbtxC3vaFkeewR7ydD5ET7csv6vLHILju9Zv7eP/h4i5vY3cMA0PWItS+713K/RwvaGvhA1IV5EffXtaVg9izueNcUqjuK1/epXtDGWr3FUPe0hVc3sMPHjLzO3/VVVz62CA++teNbb4q5TvDpLVRnPSzhcbk2tegMqPr/2ns0PuIbxPyX3RNyp/HtyH/9vNf1/288I5PuDKEP3AjX47bmFA937txkodHVIIFoLZ+8qa8zGL+nW7u8oPpQjRMYt/o5C15fmwvNZPasnGrtNxh+CS8rhPHQpmQF+K50diLW8/yw6WQ87jxObGM/+5+zh8wDILt4zE/fGOKjEZLkHi993a8bDD6Yn1/3h3SfG/muxasfBmfS9+JyvGJTvnVnSmfx0OiuXrsrsgP+wS+MNG9PnPpYQbRspja9w3J8+erZ9qLv/o0rtMbim4odNkJs4Mg7NzYMJ6td3o6128VddW0hewE0M0I2J7uC5/9cSojl4Uz32yIu0NBc4Fu8X5D+GhzPOFffJnrVoq2c1p/6W24Y4XHCWOW1ydboaum6/K+TuojjcT6/v6jIO+wJggWG/byP0nfnzsLvZ8S+FCp7HlllEt8XIre9FATjTGxvRvvI86ZWROT7XdaR2nLrOylwNaSnv3HeLnBvVuqrJX1WMXOLnGP5zbFgOZ0t8UtD5JpqcTewx50QDhqfZTfUTaJtZEVWdc1+VjJ0MgVHM0KTswuqPVxqjIGmn3w+untQ8G+23ZSd5dlZWZkIXbXN/dC3cyXEmWT94XcFLXsF+u2mQ466Q2S3//B2XXA5rEUYdM7hN4h9CoIJskzCMHebbnbu73bxQlVSMaJHWJwbOPfhlD1AAkBQgIhRAchRBcChADRe++9l9A7QvQmYHZvd/7Z+3/TXl5kZ3d2ttyW2dmZb7KyFatBTnbO9tS+OLclye9xF381n6O8UDW3lWTR0SZyoOh91K4AglDS9VMXlZepvRFpwEnJbZxeStsqOIMDu1daglXD/laIGRNm6d5ZCB39EKiTcBHG32O8bwp+W9rui3yYh77uixDbB87ifP7UXx3p4b1ew1PXQVsA9Fh71rcvZd+w6XkntenY+bvd9S6IXYz3i1/m42ht0YFEHNdB0Z/QgIx6t3sdhaKj6bpgUBdE28krHxveqL7wMdG84LUeL/XgAL2+6+OexH9vDKv7VIZ58eesPZr1woJqvdJMRpv7+R8243HoV/mdSVsutNGKiXXKY3Z6AQ+M13sfL8vtTsCOcnOKcLSgMObjV71NXnGiv0tE1vGfg+T/4wez9s6wWaFd8d2DvS6krExArJ3a0jJMH3q4En0NIOt0olFIE3uQiAiNGfNZW5/hszzDB4lOp34sfzOzTQZmMFg+7Fiy4bwkxP1L4xRQiKbxxF79TTovOuaaytSCG1bg2BNczS3AMk8Rv2GCbEzCN0X/6adlOu6+FNZ2TqA5HFHcTlKZ59EyhrWy6LQ1UCaMCCkCZVCn8qvRvqJVqaTlM7GLYNiojRtta0159KzxT4fK1Ozsto+zBWMVCuZr/f60jGNNyWFf0JbF9Z2XgjFGjJhv5PoGp3hZ2Arb6xW50F5cbf7dbhzL4mzWZ8V005Y+6HfoItia7FLlHnl/wPcfWp4LZp2Rrtb/ncnKMHVYwkb7E9zrLhOw6PzaCriFmH7ZkF7L+4v7dM7frWL65UL6cnE/TEtYg/7gmaZdIeEDErorhjR/Vk3TrjTgFMJ2OU27+kB3n1L32J5rhDR/p4PEhQEf7c83mr930LvZ7yEW9q3yNbOANgQ=
*/