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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_CYCLE_HPP

/* cycle.hpp
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
*/