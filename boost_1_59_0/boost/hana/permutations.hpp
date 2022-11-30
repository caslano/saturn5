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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_PERMUTATIONS_HPP

/* permutations.hpp
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
*/