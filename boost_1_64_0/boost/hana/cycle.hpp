/*!
@file
Defines `boost::hana::cycle`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CYCLE_HPP
#define BOOST_HANA_CYCLE_HPP

#include <boost/hana/fwd/cycle.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto cycle_t::operator()(Xs&& xs, N const& n) const {
        using M = typename hana::tag_of<Xs>::type;
        using Cycle = BOOST_HANA_DISPATCH_IF(cycle_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::cycle(xs, n) requires 'xs' to be a MonadPlus");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::cycle(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::cycle(xs, n) requires 'n' to be non-negative");

        return Cycle::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    namespace detail {
        template <typename M, std::size_t n, bool = n % 2 == 0>
        struct cycle_helper;

        template <typename M>
        struct cycle_helper<M, 0, true> {
            template <typename Xs>
            static constexpr auto apply(Xs const&)
            { return hana::empty<M>(); }
        };

        template <typename M, std::size_t n>
        struct cycle_helper<M, n, true> {
            template <typename Xs>
            static constexpr auto apply(Xs const& xs)
            { return cycle_helper<M, n/2>::apply(hana::concat(xs, xs)); }
        };

        template <typename M, std::size_t n>
        struct cycle_helper<M, n, false> {
            template <typename Xs>
            static constexpr auto apply(Xs const& xs)
            { return hana::concat(xs, cycle_helper<M, n-1>::apply(xs)); }
        };
    }

    template <typename M, bool condition>
    struct cycle_impl<M, when<condition>> : default_ {
        template <typename Xs, typename N>
        static constexpr auto apply(Xs const& xs, N const&) {
            constexpr std::size_t n = N::value;
            return detail::cycle_helper<M, n>::apply(xs);
        }
    };

    namespace detail {
        template <std::size_t N, std::size_t Len>
        struct cycle_indices {
            static constexpr auto compute_value() {
                detail::array<std::size_t, N * Len> indices{};
                // Avoid (incorrect) Clang warning about remainder by zero
                // in the loop below.
                std::size_t len = Len;
                for (std::size_t i = 0; i < N * Len; ++i)
                    indices[i] = i % len;
                return indices;
            }

            static constexpr auto value = compute_value();
        };
    }

    template <typename S>
    struct cycle_impl<S, when<Sequence<S>::value>> {
        template <typename Indices, typename Xs, std::size_t ...i>
        static constexpr auto cycle_helper(Xs&& xs, std::index_sequence<i...>) {
            constexpr auto indices = Indices::value;
            (void)indices; // workaround GCC warning when sizeof...(i) == 0
            return hana::make<S>(hana::at_c<indices[i]>(xs)...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            using Indices = detail::cycle_indices<n, len>;
            return cycle_helper<Indices>(static_cast<Xs&&>(xs),
                                         std::make_index_sequence<n * len>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CYCLE_HPP

/* cycle.hpp
1g4pff1m77l4nrdjnwiaXzTvFjbaJyLEZZ+IWvC8K4Somi7ESkgZ/j6ShP7M1IhBYzWiH/abOJAC35hUjai4SojysTjXIAaM6aBxOE+QLnq8ELdDvkO/bpmAtiBOTMLfkLB0pIMYII9b8Y6JD84d5NsT+UXqhBgBicXZmgQph1RC6iGj9EKkQXKRdscUhA0IQ0yQBch/gYw3Ij/8XTkN7YXUQIYi3xFZOG6+r1gJ3uGDvBG30IT2QTJzoDMz4zsbmawnYzAYDAaDwWAw2hLtsf43FsDSrs8yt4X/f5QI1NZifbgmTq6Pcq1GXUbDShy/x9DvFfbfLXk2Xe40i1sSleaJcKybGvLIzXVP0m56hhcj5bsLwap/e/oKhRlY9AUTS7+FfYfkOrCC9AwZlpwci1l1oC7PmCmE2s8gXh2Zqc/TZWAwrIgbrh0h8zksj50hNCJH7WkQjVThSD+tuwBUJlZjXr7JJux7IISBfX6Wx5xGYS9xhQwjh+447vsYAdhMeap/dPCaME3RZ2SrtKNR3n2qvK4U9hLrVdhf1XGDOjYrT2c25tmMBpVGNrmHSjOTwp7KM6BZJ5a3WR17RrNt6qfy7N24TajXlVoD8gnEGvPlSHDs3F/DxURVr1cQXgN5FbIW4i2StWPxWxf8VoDwjZApxK9B1kGKIOshcyAbiF+HVEDegNggcyn8JmQjpD/qPk6209sxxPlWq9Fs09lPJKevCthmlOOHNoSC+6i2TxOd0I5eYpjSNcU3rWqSuia0VaOdpNodEpuUfM5AQXFnqDiBuLMTBO1pEU3+K2O8nHNK6apeU2VCTxBj11Ul09yNpKV4FH33MoJKfqZO6cgmNz15TxsyZPLZ+A9f4rTFojhPc3mkNhmFRjvyQ+6dMA6yHpsi7To2/NYEQm6OoTa+Ueds42BHu1c1xJ0vmuifxn2R7NIXaLvzvL1dQ6XR9TKA/I3WHFJtP/Gig2G1mIWzDVuoDXHN+BwNofKW0odFX1N9Daby6mtUeXQRdCtMzfMFqOcByLVyngdeLjqjfKlTqsRgXUfz25EuBBm/JdNp5t7rqOfURufAuwhvhVRC3oNsg2RCtkPmIM8d4PchH0A+hOyEfAT5GLILUkXnDsTjGALOufvKIcfYnC3Hxm0MwjoIhW40BiGko91CY0AX9Ua9gnzRFh/wp6jDbkh1C8fiPNINl1C5oVRuRxqL9J9VuXKiJ45Nvdp+Bsv5hP6NxDE2yCrVv75+voGajo4+Xk193JI6HAHnenvS+3rS43rSv3rSs7Zev5uo9MSvdJ87M37m2E0i4pGjH/6y7ClP+920v77Wk1454gzVruuyHj60oaq0snJ70PZNC1M86dc96+MvUO2qjat7etPNj53/0b6vD92x/MEiIawqPjZxd7fqzbfu9T8W9PzBXknQyw5X5RYujtrqs3mzOW7X9BW1i4KrcC9Q5RoSs74++oUpaPaGUZftvqPrR570zZ70363X93vSW3+v2hs/NOWpdYuTdvZd+2hgUXg3jO0xOceFgrqWbPHCWEHk9WIu+ALEv0x/DxOY5/T3mZDDCI/yomcaesaRv6GJYihYYjuigsE7wL3A74PjwB+C48Efg88HV4EvAX8KTgJXg1PAn4MngveAp4O/BM8C7wXfDf4aXAL+FrwE/D34UfAB8NPgQ+AXwIfBG8FHwO+ozZlr5m6j8CfgOvCX4F/AP4Prwb+CfXDi90ZbOoLjwJ3AA8CB4EHgIPBgcAj4ErAWfCm4C3gUOBJ8FbgbeAK4B3gyuCfYCI4CTwNHg1HHhvsi3X/Rn+rvMGFHF0qXIBz3JJRN6XzB/SjdSvI/fQncEfwKOEAeI+zHVwi6x4A=
*/