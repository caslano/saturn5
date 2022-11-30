/*!
@file
Defines `boost::hana::sort`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SORT_HPP
#define BOOST_HANA_SORT_HPP

#include <boost/hana/fwd/sort.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/length.hpp>
#include <boost/hana/less.hpp>

#include <utility> // std::declval, std::index_sequence


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Predicate>
    constexpr auto sort_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Sort = BOOST_HANA_DISPATCH_IF(sort_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::sort(xs, predicate) requires 'xs' to be a Sequence");
    #endif

        return Sort::apply(static_cast<Xs&&>(xs),
                           static_cast<Predicate&&>(pred));
    }

    template <typename Xs>
    constexpr auto sort_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Sort = BOOST_HANA_DISPATCH_IF(sort_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::sort(xs) requires 'xs' to be a Sequence");
    #endif

        return Sort::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    namespace detail {
        template <typename Xs, typename Pred>
        struct sort_predicate {
            template <std::size_t I, std::size_t J>
            using apply = decltype(std::declval<Pred>()(
                hana::at_c<I>(std::declval<Xs>()),
                hana::at_c<J>(std::declval<Xs>())
            ));
        };

        template <typename Left, typename Right>
        struct concat;

        template <std::size_t ...l, std::size_t ...r>
        struct concat<std::index_sequence<l...>, std::index_sequence<r...>> {
            using type = std::index_sequence<l..., r...>;
        };

        template <typename Pred, bool PickRight, typename Left, typename Right>
        struct merge;

        template <
            typename Pred,
            std::size_t l0,
            std::size_t l1,
            std::size_t ...l,
            std::size_t r0,
            std::size_t ...r>
        struct merge<
            Pred,
            false,
            std::index_sequence<l0, l1, l...>,
            std::index_sequence<r0, r...>
        > {
            using type = typename concat<
                std::index_sequence<l0>,
                typename merge<
                    Pred,
                    (bool)Pred::template apply<r0, l1>::value,
                    std::index_sequence<l1, l...>,
                    std::index_sequence<r0, r...>
                >::type
            >::type;
        };

        template <
            typename Pred,
            std::size_t l0,
            std::size_t r0,
            std::size_t ...r>
        struct merge<
            Pred,
            false,
            std::index_sequence<l0>,
            std::index_sequence<r0, r...>
        > {
            using type = std::index_sequence<l0, r0, r...>;
        };

        template <
            typename Pred,
            std::size_t l0,
            std::size_t ...l,
            std::size_t r0,
            std::size_t r1,
            std::size_t ...r>
        struct merge<
            Pred,
            true,
            std::index_sequence<l0, l...>,
            std::index_sequence<r0, r1, r...>
        > {
            using type = typename concat<
                std::index_sequence<r0>,
                typename merge<
                    Pred,
                    (bool)Pred::template apply<r1, l0>::value,
                    std::index_sequence<l0, l...>,
                    std::index_sequence<r1, r...>
                >::type
            >::type;
        };

        template <
            typename Pred,
            std::size_t l0,
            std::size_t ...l,
            std::size_t r0>
        struct merge<
            Pred,
            true,
            std::index_sequence<l0, l...>,
            std::index_sequence<r0>
        > {
            using type = std::index_sequence<r0, l0, l...>;
        };

        template <typename Pred, typename Left, typename Right>
        struct merge_helper;

        template <
            typename Pred,
            std::size_t l0,
            std::size_t ...l,
            std::size_t r0,
            std::size_t ...r>
        struct merge_helper<
            Pred,
            std::index_sequence<l0, l...>,
            std::index_sequence<r0, r...>
        > {
            using type = typename merge<
                Pred,
                (bool)Pred::template apply<r0, l0>::value,
                std::index_sequence<l0, l...>,
                std::index_sequence<r0, r...>
            >::type;
        };

        // split templated structure, Nr represents the number of elements
        // from Right to move to Left
        // There are two specializations:
        // The first handles the generic case (Nr > 0)
        // The second handles the stop condition (Nr == 0)
        // These two specializations are not strictly ordered as
        //   the first cannot match Nr==0 && empty Right
        //   the second cannot match Nr!=0
        // std::enable_if<Nr!=0> is therefore required to make sure these two
        // specializations will never both be candidates during an overload
        // resolution (otherwise ambiguity occurs for Nr==0 and non-empty Right)
        template <std::size_t Nr, typename Left, typename Right, typename=void>
        struct split;

        template <
            std::size_t Nr,
            std::size_t ...l,
            std::size_t ...r,
            std::size_t r0>
        struct split<
            Nr,
            std::index_sequence<l...>,
            std::index_sequence<r0, r...>,
            typename std::enable_if<Nr!=0>::type
        > {
            using sp = split<
                Nr-1,
                std::index_sequence<l..., r0>,
                std::index_sequence<r...>
            >;
            using left = typename sp::left;
            using right = typename sp::right;
        };

        template <std::size_t ...l, std::size_t ...r>
        struct split<0, std::index_sequence<l...>, std::index_sequence<r...>> {
            using left = std::index_sequence<l...>;
            using right = std::index_sequence<r...>;
        };

        template <typename Pred, typename Sequence>
        struct merge_sort_impl;

        template <typename Pred, std::size_t ...seq>
        struct merge_sort_impl<Pred, std::index_sequence<seq...>> {
            using sequence = std::index_sequence<seq...>;
            using sp = split<
                sequence::size() / 2,
                std::index_sequence<>,
                sequence
            >;
            using type = typename merge_helper<
                Pred,
                typename merge_sort_impl<Pred, typename sp::left>::type,
                typename merge_sort_impl<Pred, typename sp::right>::type
            >::type;
        };

        template <typename Pred, std::size_t x>
        struct merge_sort_impl<Pred, std::index_sequence<x>> {
            using type = std::index_sequence<x>;
        };

        template <typename Pred>
        struct merge_sort_impl<Pred, std::index_sequence<>> {
            using type = std::index_sequence<>;
        };
    } // end namespace detail

    template <typename S, bool condition>
    struct sort_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...i>
        static constexpr auto apply_impl(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(hana::at_c<i>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred const&) {
            constexpr std::size_t Len = decltype(hana::length(xs))::value;
            using Indices = typename detail::merge_sort_impl<
                detail::sort_predicate<Xs&&, Pred>,
                std::make_index_sequence<Len>
            >::type;

            return apply_impl(static_cast<Xs&&>(xs), Indices{});
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return sort_impl::apply(static_cast<Xs&&>(xs), hana::less); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_SORT_HPP

/* sort.hpp
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
*/