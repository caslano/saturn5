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
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
*/