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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IS_SUBSET_HPP

/* is_subset.hpp
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
*/