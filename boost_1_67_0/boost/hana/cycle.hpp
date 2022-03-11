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
+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
*/