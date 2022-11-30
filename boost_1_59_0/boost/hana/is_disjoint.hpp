/*!
@file
Defines `boost::hana::is_disjoint`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_DISJOINT_HPP
#define BOOST_HANA_IS_DISJOINT_HPP

#include <boost/hana/fwd/is_disjoint.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/none_of.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto is_disjoint_t::operator()(Xs&& xs, Ys&& ys) const {
        using S1 = typename hana::tag_of<Xs>::type;
        using S2 = typename hana::tag_of<Ys>::type;
        using IsDisjoint = BOOST_HANA_DISPATCH_IF(
            decltype(is_disjoint_impl<S1, S2>{}),
            hana::Searchable<S1>::value &&
            hana::Searchable<S2>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S1>::value,
        "hana::is_disjoint(xs, ys) requires 'xs' to be Searchable");

        static_assert(hana::Searchable<S2>::value,
        "hana::is_disjoint(xs, ys) requires 'ys' to be Searchable");
    #endif

        return IsDisjoint::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    namespace detail {
        template <typename Ys>
        struct in_by_reference {
            Ys const& ys;
            template <typename X>
            constexpr auto operator()(X const& x) const
            { return hana::contains(ys, x); }
        };
    }

    template <typename S1, typename S2, bool condition>
    struct is_disjoint_impl<S1, S2, when<condition>> : default_ {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const& xs, Ys const& ys) {
            return hana::none_of(xs, detail::in_by_reference<Ys>{ys});
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_IS_DISJOINT_HPP

/* is_disjoint.hpp
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
*/