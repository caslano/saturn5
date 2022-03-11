/*!
@file
Defines `boost::hana::permutations`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PERMUTATIONS_HPP
#define BOOST_HANA_PERMUTATIONS_HPP

#include <boost/hana/fwd/permutations.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto permutations_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Permutations = BOOST_HANA_DISPATCH_IF(permutations_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::permutations(xs) requires 'xs' to be a Sequence");
    #endif

        return Permutations::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    namespace detail {
        template <std::size_t N>
        struct permutation_indices {
            static constexpr auto value =
                detail::array<std::size_t, N>{}.iota(0).permutations();
        };
    }

    template <typename S, bool condition>
    struct permutations_impl<S, when<condition>> : default_ {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto
        nth_permutation(Xs const& xs, std::index_sequence<i...>) {
            constexpr auto indices = detail::permutation_indices<sizeof...(i)>::value;
            (void)indices; // workaround GCC warning when sizeof...(i) == 0
            return hana::make<S>(hana::at_c<indices[n][i]>(xs)...);
        }

        template <std::size_t N, typename Xs, std::size_t ...n>
        static constexpr auto
        permutations_helper(Xs const& xs, std::index_sequence<n...>) {
            return hana::make<S>(nth_permutation<n>(xs, std::make_index_sequence<N>{})...);
        }

        template <typename Xs>
        static constexpr auto apply(Xs const& xs) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            constexpr std::size_t total_perms = detail::factorial(N);
            return permutations_helper<N>(xs, std::make_index_sequence<total_perms>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PERMUTATIONS_HPP

/* permutations.hpp
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
*/