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


namespace boost { namespace hana { namespace detail {
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
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_UNPACK_FLATTEN_HPP

/* unpack_flatten.hpp
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
*/