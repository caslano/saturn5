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
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
*/