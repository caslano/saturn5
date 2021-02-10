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
LDuMQtGsxX+2222OKecqoAzyGahZawAal1HwrXGCmpd3u47AFwLpdsJsiS3fkLboKRCw7WPcM+YOCfzR1AagB8Dkw2ZFhJsEsBewSIquZeKH18RPuavAgYD/5y8AxYRRAqEBlAX4S66TUPDVKIxU57j1gwAdipgGINI3MBeHkywceNAir4WJaHdZ+4HCC7nA9IDbUnoKbS11k9fJ7Jk5BEves8emcbKuLzdeICHmRt1RbNb1GV2YQ9v81Lcm6M5vMr8xmYz7by8npj0cjc+NtTMgFpL9y0SrVzOPJRfYgTve0ZKG/24CgdoCZkOGQifAvCtRr0N2cu3bfnySeRSDE/RtmI6FGOXfj345fbq/Zo53gVHocdkPlJRbSxq5fHrnUuolEGfe5aR5mhFmcTSSlCf680uqGr4WN1Xt6kqP9P7cFEurhGotcltleHvkecVQiR0RVCphD4GmPTq1z83z0fhqBeLlYe/xye0cdWXFXr8uL1POze077wl2Vhj3FmtuV9ayX/EExAaoYAoHgT3CdaP90ZS4lLYSMfcq8GsUoYYsCKzSmetFuba1ktvEoA3SyxY2i6PFaqmtldtHkdyNGb3KMcgzYjfUXYJtKqgFQdtFTBcOuOgQfI1Oyf4+uN//AA+b2XXJBAAYf4b0
*/