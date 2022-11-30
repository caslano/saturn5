/*!
@file
Defines `boost::hana::is_subset`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_SUBSET_HPP
#define BOOST_HANA_IS_SUBSET_HPP

#include <boost/hana/fwd/is_subset.hpp>

#include <boost/hana/all_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/functional/partial.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto is_subset_t::operator()(Xs&& xs, Ys&& ys) const {
        using S1 = typename hana::tag_of<Xs>::type;
        using S2 = typename hana::tag_of<Ys>::type;
        using IsSubset = BOOST_HANA_DISPATCH_IF(
            decltype(is_subset_impl<S1, S2>{}),
            hana::Searchable<S1>::value &&
            hana::Searchable<S2>::value &&
            !is_default<is_subset_impl<S1, S2>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S1>::value,
        "hana::is_subset(xs, ys) requires 'xs' to be Searchable");

        static_assert(hana::Searchable<S2>::value,
        "hana::is_subset(xs, ys) requires 'ys' to be Searchable");

        static_assert(!is_default<is_subset_impl<S1, S2>>::value,
        "hana::is_subset(xs, ys) requires 'xs' and 'ys' to be embeddable "
        "in a common Searchable");
    #endif

        return IsSubset::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S1, typename S2, bool condition>
    struct is_subset_impl<S1, S2, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S, bool condition>
    struct is_subset_impl<S, S, when<condition>> {
        template <typename Xs, typename Ys>
        static constexpr decltype(auto) apply(Xs&& xs, Ys&& ys) {
            return hana::all_of(static_cast<Xs&&>(xs),
                    hana::partial(hana::contains, static_cast<Ys&&>(ys)));
        }
    };

    // Cross-type overload
    template <typename S1, typename S2>
    struct is_subset_impl<S1, S2, when<
        detail::has_nontrivial_common_embedding<Searchable, S1, S2>::value
    >> {
        using C = typename common<S1, S2>::type;
        template <typename Xs, typename Ys>
        static constexpr decltype(auto) apply(Xs&& xs, Ys&& ys) {
            return hana::is_subset(hana::to<C>(static_cast<Xs&&>(xs)),
                                   hana::to<C>(static_cast<Ys&&>(ys)));
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_IS_SUBSET_HPP

/* is_subset.hpp
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
*/