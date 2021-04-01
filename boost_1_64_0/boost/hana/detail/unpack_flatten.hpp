/*!
@file
Defines `boost::hana::detail::unpack_flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_UNPACK_FLATTEN_HPP
#define BOOST_HANA_DETAIL_UNPACK_FLATTEN_HPP

#include <boost/hana/at.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <std::size_t ...Lengths>
    struct flatten_indices {
        // avoid empty arrays by appending 0 to `lengths`
        static constexpr std::size_t lengths[sizeof...(Lengths) + 1] = {Lengths..., 0};
        static constexpr auto flat_length =
            detail::accumulate(lengths, lengths + sizeof...(Lengths), 0);

        template <bool Inner>
        static constexpr auto compute() {
            detail::array<std::size_t, flat_length> indices{};
            for (std::size_t index = 0, i = 0; i < sizeof...(Lengths); ++i)
                for (std::size_t j = 0; j < lengths[i]; ++j, ++index)
                    indices[index] = (Inner ? i : j);
            return indices;
        }

        static constexpr auto inner = compute<true>();
        static constexpr auto outer = compute<false>();

        template <typename Xs, typename F, std::size_t ...i>
        static constexpr decltype(auto)
        apply(Xs&& xs, F&& f, std::index_sequence<i...>) {
            return static_cast<F&&>(f)(
                hana::at_c<outer[i]>(hana::at_c<inner[i]>(
                    static_cast<Xs&&>(xs)
                ))...
            );
        }
    };

    struct make_flatten_indices {
        template <typename ...Xs>
        auto operator()(Xs const& ...xs) const -> detail::flatten_indices<
            decltype(hana::length(xs))::value...
        >;
    };

    template <typename Xs, typename F>
    constexpr decltype(auto) unpack_flatten(Xs&& xs, F&& f) {
        using Indices = decltype(hana::unpack(xs, make_flatten_indices{}));
        return Indices::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f),
                        std::make_index_sequence<Indices::flat_length>{});
    }
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_UNPACK_FLATTEN_HPP

/* unpack_flatten.hpp
K8zB6DJcTBxhJWRh/2grocSdaHGIQr3yqYCbD1rO7FzN/53E2pXBhLfLol9v3cNty5wm+8qYvGDMKFk9W33aFmvDTR12izUr0486iU5w6V8UwyQGaftCcNS8jjc4z3VyQ0Rj+yNUhZ8z0Xx4cE7XJAFNLDR2cCi56nVtNFOjGUXHu7jMMt/0i+HTIj3Y1G+ByBQ68WSNwN9hmhofB+3RkYvsn9ovT0G1+W9/xOklqS8Lx2Gw8VoHg1EpiIa/Nn9lIZLTF5ovGsrAoj7frsfqfVYZpBTkQicLblYRJolxA4iJyJyDXoDaulyQ2r9iOFQrBNesp5XWvM1d9OgNG/jaPe+DUV+fuK18Z/CsfhXa2x5ZwdqlJLEtna5Pck2A7GOKASWsfc82K3JL3s9DIz9Ib+pOUeMKVmFsKBtJeJmRuBTP9zHFZv3V5YTNjrtTCSp7HFfvdBErwV1Wl/EVIiQoeY/3eXsv2JIDDjIMee+1IMILNMleLkMNuHcqKtKd5bKEC2ykZ5COxKm15UPiRfqxhCmnTeaKS7j6jDy8vSnD0TrwhKieeCrg6KT1TQ==
*/