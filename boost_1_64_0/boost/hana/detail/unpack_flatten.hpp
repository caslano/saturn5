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
cVns5FI4CpFeaA+g5wfHrzE2qmtrqbPn32M4vr467fGVrPnVs9L+6a5UfXSjlDlMwYO+Kdcorg+kw3B+P+SjA0P7zJue0OgP+PdnNZh7CVP2m8qFzEiENyM89B/haek+mavGRaEaF/NU34f3gvFGL+v3g4onLQjwpIUB/rNI8R/yM08fJtqR4GdtrT3ZuHbkZ57HaRmoybq5yaYtFXtbM/6WcfzdPM3xZ94OtW1uXlCxpch0dALJG6JnGnx7axwYpgss296H4Ox4Ql1Hk6HRKOSVP0D5RobNiMIDsJO50THYr2X3Do8eyI7bkuaJ1HPmBrNPDr+Va/lXNJobn+wdNG1YRx8OPy4XPhwe4pgP74dzfdl9o8MTIy6xCCPVpnxphKsKhvz++Wfi7P5TsR+7VcBvEvDbUvtX3nMHTPuH+oXY79yi9o2/4n7HwPWe7zcWF3GWF90hw1wbyZuI79YOiVcQ/Y57zJ+Jsv9B7X3vIu2fk/bdbr1hmX+oZBP3qnj9dtWfVPyEir8PMLmu3xVY1+8XPFSXCWlAV90vVfE/V/F/V2v4LdNYw/8JnI7/CE+dybpqeZHQLzV1AtgNaWRnlN4X4sqA5y0LFF9eqPxNLVI8cipeqtfyErWWL1HrhtwXzqqYHt/Mywcs3+KsFmEk2ponjRIIesDUPGcPTLkmDhjJY5wqCcZpNqTs/oYG+gFzPBJ+bYYPHIChGmDOr01hheSJmfrsnomBwfGBoWzfxOhkLs5BA5P78eVT2PY+RFrFFQl/m1OR8IgFAl4g4Isq1Bu8CGvfdIsrKPuv8He3Pb6BaX5RCpiM1/xmGWAmbxOnz5krAOPcFXkWRCsrPI8BTcrYlI/gcocjeIbmQ6uY91xVb4NbCZjkMWsQJk/1/OcYtkG1iAMsxdvWVfAswHSTK9yn85gbPYzhhY4uw2gzG1a0FrI9JS38jmltFPX/ucCR9T+e4VsCNg8Gpvnso1TdfuXWP/aDXP82I3zzjPir4XWR4K2ZaPo81ewTyVMVf0p4a0Mk9qhib9oTSR7aXtsgeGgn7kuQhzIekOSOo9LPLBb3qN29mhIBq03dbawVe9AnijuMdd1whffETEpvY9eE5fa3URjG4RWC9k7pG0/IHMoETmdK997U433iqbtaq6JD72hUksfXTJPHy33mNdCR16V46vh5I+l36wcHesciz2O5D3XhEvpbdf5UT6qQttXDe87KGny3BLgw9UDMd1aJ5fvDaAOXL/LxvslOFjSR3zB8l2UhlaV9+VhM+RAo6Mc8SL2f3bE8sd9+S6n97fjcachnGdrlMfivfeScLub7evrAMfW/tlTjzo22kZc9rkLfbTf1ok2CCNN+l/oq5QupLJ+seuq2NetJRqwnjYqvbkd4jtJ17WC5m/Bfy7jP1PjgBDsFr0X5U/YALYo/IazeBgn7hm53vJJ41YH3YTv8OqbiWY8uxG9AfBHLBf0U7VylLaqWVxZFPRW0A8tjI6t9lu925SC+LscTfbwdV5GKfzLbaL14o1r6Py5WvmguRNi1d3WUbt9e0PrIjGRTUo/fJfh7V1eav+NUnObvbW5t6Bc8O2d/ez62l2Hnw2IfwwDEPGwheVjfEfCw9ln59q2jY73xntPNERHmHBmPxN0mjnvze7/aA3WusL71BgDXY/YszpuzA2k+UhZOc4BphpimJp+ui3vmuPhJ0O8rf74iKXO3nLfiHYtaNX/GmPc48UfJhw/GfHYsl+u3/H0U4aJoz3njOcv/jd/+kqhvMNc7NDFCXj0BnLKotx/7cJ+mOhoZy030D4/2DvU7v5P3o3Ybjd3q+MSYgZkzQyH6fFLw9s2RSZHqMAmI61w3tR1C2AQ=
*/