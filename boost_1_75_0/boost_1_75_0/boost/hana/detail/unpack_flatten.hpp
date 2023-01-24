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
qSV/loZCdLSi+5S0tFkxGrFPDZUM3O6xApBpbLmwyUSzSqR0msXoJJy7mQVRQiUCPCVecfT6joQSkFACEkpAQglAqPuQUG+x0mKk8jwEmHtnIbHSkVjfYeGJQ5HTEExbOw3BZsUJRtXo1wpQpytOp8odanbem4nD3GCua+OvsQZAWl2P8R0WvARZ7xgLYk50TAI+rXfMEB2zQOlJzqtfOYZdiUQFo8DcYFhYzZtxrT3fHDYvXOw1LSzkTc35M/TqBVyQc2bhLEQCpCFlOA19br5roDMwU7Njtr4sZnAEL5kGRD7iL54tFvX6OvhrAaU0itIsikImRScDUEMMAdF5AXpFrsRjXk3OnXmV4O3ZMm5bsN6JB1lNeSK9hFub4+bN+F678pZMstlc+x23t7xQqbm3FL2u3Gpr8eY2bNLXym7v3IZSecGpqsSGpoZTDdHBlnr3+QWnvNcQvlfmzwPy9wH/DDZRKP93wkfQjeh+CW0MA+JyrMQXGpzyWnhfV5ujQws86q3bG2V6yjYJ0tzxFbxTamrtruAQIfK9/s3zYYJaF6KbvRYPmg2X/0FNGfxFhwvGh6UP4BMKgIEQ6gwIyXUnvImMzHix1r0ar+KOAkABOYyXZj+AdACF4VEsipTnpni/z5qn3NfmvUcAKiwCpf42brfL4HGvLbcd9c7jdi8bJB+V2w5UJZIgOUA6F3O70VUiQLxXk0gxILEF
*/