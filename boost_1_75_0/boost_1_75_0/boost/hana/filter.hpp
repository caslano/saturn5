/*!
@file
Defines `boost::hana::filter`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FILTER_HPP
#define BOOST_HANA_FILTER_HPP

#include <boost/hana/fwd/filter.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/lift.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto filter_t::operator()(Xs&& xs, Pred&& pred) const {
        using M = typename hana::tag_of<Xs>::type;
        using Filter = BOOST_HANA_DISPATCH_IF(filter_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::filter(xs, pred) requires 'xs' to be a MonadPlus");
    #endif

        return Filter::apply(static_cast<Xs&&>(xs),
                             static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <typename Pred, typename M>
        struct lift_or_empty {
            template <typename X>
            static constexpr auto helper(X&& x, hana::true_)
            { return hana::lift<M>(static_cast<X&&>(x)); }

            template <typename X>
            static constexpr auto helper(X&&, hana::false_)
            { return hana::empty<M>(); }

            template <typename X>
            constexpr auto operator()(X&& x) const {
                constexpr bool cond = decltype(std::declval<Pred>()(x))::value;
                return helper(static_cast<X&&>(x), hana::bool_c<cond>);
            }
        };
    }

    template <typename M, bool condition>
    struct filter_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred const&) {
            return hana::chain(static_cast<Xs&&>(xs),
                detail::lift_or_empty<Pred, M>{}
            );
        }
    };

    namespace detail {
        template <bool ...b>
        struct filter_indices {
            static constexpr auto compute_indices() {
                constexpr bool bs[] = {b..., false}; // avoid empty array
                constexpr std::size_t N = detail::count(bs, bs + sizeof(bs), true);
                detail::array<std::size_t, N> indices{};
                std::size_t* keep = &indices[0];
                for (std::size_t i = 0; i < sizeof...(b); ++i)
                    if (bs[i])
                        *keep++ = i;
                return indices;
            }

            static constexpr auto cached_indices = compute_indices();
        };

        template <typename Pred>
        struct make_filter_indices {
            Pred const& pred;
            template <typename ...X>
            auto operator()(X&& ...x) const -> filter_indices<
                static_cast<bool>(detail::decay<
                    decltype(pred(static_cast<X&&>(x)))
                >::type::value)...
            > { return {}; }
        };
    }

    template <typename S>
    struct filter_impl<S, when<Sequence<S>::value>> {
        template <typename Indices, typename Xs, std::size_t ...i>
        static constexpr auto filter_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<Indices::cached_indices[i]>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred const& pred) {
            using Indices = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::make_filter_indices<Pred>{pred})
            );

            return filter_impl::filter_helper<Indices>(
                static_cast<Xs&&>(xs),
                std::make_index_sequence<Indices::cached_indices.size()>{}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FILTER_HPP

/* filter.hpp
Y4d+VBEIDKnq9z7csi2CQ5PqQ8EsilTsQtDZ13AFMiHFacKL/cJRrFqYa5h/dErpi0xYFD2tR+Opvp7pV5ZPdZ54OZ1b3PTrp7SOlX1aAi+C1ZOD8mXPJISwDKEfrFUQNrSXkE+xFzReXShLsBcUFBciZa5whWQSF+Xmg3JUX30MpsYKjvMl5wDFY4V6ohDBSaazQ4+0PBxB+sCQvE+8wKQ3r6J8Nan2uT0L/7S84pMzxF/X6vblcyHn7p1JzaNW5LLHd/e68zrf3VMnN8MxttiMC9Lp105iY8qi+z6+c8Uv+LpA0SDkkzuq9fPVDBAm1/xn8Jn9Pfa/RsDtsk7zOUl6joWvtRXq0df7FHaLnEPHEF+xIOgQZggpRBgil5f/huSw+LFaq+jS77oTWQOgDMM0BEYJ8jh1HwiKFltfKLy5vt04KAoXljd9AJbxOv6hiU97be2LOncCsOdeT/l4+ZH9MIiVtrP/YvapYsnJ5w+nhZirE1ZBS/sqvqFA6xbVVbegGO6nbFbnLj7GgBN666t6dOP3b9XzJ4q75K2VFwx5c0znJYBMFZDB0oIDCdmchXb/lYXO+Abai0mtlr1QdsTs9XmrORe8+JT6WxRAO/dPx8TcpS3kD+VYCVnFehTe4u0OtyaLyor+8fp/ui0be9Bxvv8r0x2QOIeJbZIiPD/UnhYTqF1KMztnNhVhRRv4MY/dvXhwMe0LWfmC
*/