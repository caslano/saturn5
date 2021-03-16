/*!
@file
Defines `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_OF_HPP
#define BOOST_HANA_NONE_OF_HPP

#include <boost/hana/fwd/none_of.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto none_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using NoneOf = BOOST_HANA_DISPATCH_IF(none_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return NoneOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_of_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::not_(hana::any_of(static_cast<Xs&&>(xs),
                                           static_cast<Pred&&>(pred)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_OF_HPP

/* none_of.hpp
Nh0ffbvzK5jue/i+meCSwdR/pOwH6/j20PwM5u1P+D66g/rVJ8zr5c9Hd1GNe3Ge7+X76DvD9vsY63RA2derXzS4+8D8+VO+j64PtoDZrXJ6xwu9z5wAM/cQ3xeFsBrMO4f4Pnp7OQBm3mG+byjCs2B2H+b79iCcALP6s8C+98H8/TO+j07v62DePML30f2Kk2BuHeH7cEqyLkcxxxzl+6j/roDpeozv24gwEMyBY3wf1e9HMD2a+T5qbwyYs80=
*/