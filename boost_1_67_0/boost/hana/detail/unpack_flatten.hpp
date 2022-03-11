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
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
*/