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
wGKBaOHvkOK3YQnqJ8sg8/YgWIZquPOx4/kOTrTqrWVb21XOWYzMxnj+Rb+nI7pslrnuFBBiCN2dA0FXXKhF2pdQ1XHw7XPr5bDrwKET0adh53IGF4XCqF6EivzlaZzooe7iuQPcJBPqxfYsNvw+PpbTwfdmLH1bHKRwE2wKoZgW2W9+cvOu7SjPBPhK6bL/0WABB/bSR2DUaZU9tGotm/hA9bfXLFxgFJiBCXv/1yNbtvEktFG2wjgj6BTKoeQbZkblgF6EG6Rk02JXH814Chf7XO8aw2uGxoAduN0SkZ1Qm/kJcpJqVWVzBLpawqw6+0odPzq7Eq9qXtBxUgSMHLDjIoaZ4RaKtpVFEBwAhUejYBV8MOfm1Bmj1M4FQrlKdKuW5QFuLvUs82Wk59HiEPe1v782TN60izC2sVVTqOPVI87SAsTohvRbJGHnE8kiORlKq2BKtl2iAdmQOjfmE/GnvqONsaMix4ibbVEDB0FQT2dGM+UY2Yx4mKwm7V4bhZ1DGEENzwC07wg8mWO1mS+RTEnubId23OikniMnqUixcFBmwKID8Uv9BNhg8F4kRpXtWvOs60y2vdFuR0utVuRSf3yrc7uLUupDQHXkzXu/yAPEglmB5GUWEY5k+NgVKPJXQFWc1obF90moUkas0cpF/Q1yW7WA1X6N9dY5A/HUw6ozMBuMkC0JGSoE9qAJVweA9tGgJpHqGXEu
*/