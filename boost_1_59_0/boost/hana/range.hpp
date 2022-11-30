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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_RANGE_HPP

/* range.hpp
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
*/