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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FILTER_HPP

/* filter.hpp
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
*/