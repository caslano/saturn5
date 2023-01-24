/*!
@file
Defines `boost::hana::remove_range` and `boost::hana::remove_range_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_RANGE_HPP
#define BOOST_HANA_REMOVE_RANGE_HPP

#include <boost/hana/fwd/remove_range.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename From, typename To>
    constexpr auto remove_range_t::operator()(Xs&& xs, From const& from, To const& to) const {
        using S = typename hana::tag_of<Xs>::type;
        using RemoveRange = BOOST_HANA_DISPATCH_IF(remove_range_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<From>::value &&
            hana::IntegralConstant<To>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::remove_range(xs, from, to) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<From>::value,
        "hana::remove_range(xs, from, to) requires 'from' to be an IntegralConstant");

        static_assert(hana::IntegralConstant<To>::value,
        "hana::remove_range(xs, from, to) requires 'to' to be an IntegralConstant");
    #endif

        return RemoveRange::apply(static_cast<Xs&&>(xs), from, to);
    }
    //! @endcond

    template <typename S, bool condition>
    struct remove_range_impl<S, when<condition>> : default_ {
        template <std::size_t offset, typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto
        remove_range_helper(Xs&& xs, std::index_sequence<before...>,
                                     std::index_sequence<after...>)
        {
            return hana::make<S>(
                hana::at_c<before>(static_cast<Xs&&>(xs))...,
                hana::at_c<offset + after>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename From, typename To>
        static constexpr auto apply(Xs&& xs, From const&, To const&) {
            constexpr std::size_t from = From::value;
            constexpr std::size_t to = To::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            constexpr std::size_t before = from == to ? len : from;
            constexpr std::size_t after = from == to ? 0 : len - to;

            static_assert(from <= to,
            "hana::remove_range(xs, from, to) requires '[from, to)' to be a "
            "valid interval, meaning that 'from <= to'");
            static_assert(from == to || from >= 0,
            "hana::remove_range(xs, from, to) requires 'from' to be non-negative");
            static_assert(from == to || to <= len,
            "hana::remove_range(xs, from, to) requires 'to <= length(xs)'");

            return remove_range_helper<to>(static_cast<Xs&&>(xs),
                                           std::make_index_sequence<before>{},
                                           std::make_index_sequence<after>{});
        }
    };

    template <std::size_t from, std::size_t to>
    struct remove_range_c_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const {
            return hana::remove_range(static_cast<Xs&&>(xs),
                                      hana::size_c<from>,
                                      hana::size_c<to>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_RANGE_HPP

/* remove_range.hpp
YsYY3WiNd0Ry0wt4vheNZd1o09M18aIfIH6tGhLg0pVWhhyVrrwC66Nq/3j/rvTZdS369LwP9kfFl0Z3pdWrMjqO/OABcJ/A5K709EF2Wb7OvYHezom5Xen+FwZNrZmD9UcwiXKn14aMjeloD+dfVMsne7rTwVlnz73sjvubIpviTpdNvPBaOxrz22FKAipvb3SwbYH1d2dIujttET83u5vjIGwfprHutL3TiA+dZ2D9F95yaMW83dO/x5ErbhAvuH7rUUtmYOEszcLTEK+jAvKYlkw6k7T3cQuIz1G2+d+1ZP5qxws6ch6ed1KZ+WEtGYOtX1abO7h+zO2+LZkzKXZV1+dA/IbyvmNyZuZeON7ibmuIN1Gv7txwZvqntl/6975+AO+/e8CZWTqzzSXpTxA/oQILFjszp6nrb7v6wvkAin+PdmYcX4TpPH/B5SvvdXRmvOd2HfDiKG7P/e93TkzA1n2+8xMgPkLl/c04MT4/9zMNjYd4FBV3/zsnpl+WsuWwq04A9ygMc2L0Z39rGlJdCX/K72ZhXyembNvmw707Doby6AemFsxNj9vqGRcgHkW1f3ijBVO2Lvndn7ch3kRtfPh7C8aa+ZCfVADxGqrPo7gWzMkWg0OHTPDD8ns0oQXTZWVY1L3vcPuLijq2YI4mbujeSwLxIsru8TtHps8r2dqYsPYApzxmHJmS9sNis8Ig/kYNf/KdIzO2
*/