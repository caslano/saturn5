/*!
@file
Defines `boost::hana::all`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ALL_HPP
#define BOOST_HANA_ALL_HPP

#include <boost/hana/fwd/all.hpp>

#include <boost/hana/all_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto all_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using All = BOOST_HANA_DISPATCH_IF(all_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::all(xs) requires 'xs' to be a Searchable");
    #endif

        return All::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct all_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::all_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ALL_HPP

/* all.hpp
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
*/