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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SORT_HPP

/* sort.hpp
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
*/