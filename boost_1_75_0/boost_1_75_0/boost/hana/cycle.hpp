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
8KQyev/eX1C8M7qrihnNGmvkdWiTs0HLm/ICQPGpUjka0/wOJPEo4buujof2i5BWjkE6G/WsVEPtSBatP6mkVLmZz4iUlJPD9kMun++VGzqGv0jd/IUTpzTDrppdbFV4nhItdz2jraTIt+LT1xqw29sneYw9TyOkWZqbAZW33l6b7zSN/Xg0FrmFdh/cJlXTUy+4XAuMdn8kzONc2qnUGppCygXKNTLbJ/ychCrHfapBUpVf4zOpjRsoYn80A8T6rMWfaUYG6w8ArzdreZvy9Twhqa5Di04XXwlNofU90zw7sh5GWSNRWnOOjCBD+4XNn32BinIMX0bsIrDfcpj0RTEbCvJ3ewttP1BuSBgIdPujmaHBJ4JkRCzxd54+gEsTYKsBn09/17MFuG6ceU2kgB3TNE/quzN6riPnok6M02tsOw7n+uBY3DisOuBMYheOpoQmDbONz+VA3uFl1oezn8002/YJXpqXsNNNF6XC5iObZfGAK5Pw+idoKp1HFYjHa+Xh4qSZ2vMlCGa29KY2bBfdrbHppH2hsdtx7ai1+jALbwZywAfNEz7Qo7Ov9kPW0fsyyB6t711Uajs6moc8ORUbZOdQHID/6FV7XxSHA54oGveUsxPwfYA/jkpNB4PWoUNZ9yvAXdChXU4V3pXp5+18tcNjxXfMl9vX9VVqyGvHy6N7GnKAS0CsyKUHksGR9GbS+DaNA5gy9RNc
*/