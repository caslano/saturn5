/*!
@file
Defines `boost::hana::Applicative`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_APPLICATIVE_HPP
#define BOOST_HANA_CONCEPT_APPLICATIVE_HPP

#include <boost/hana/fwd/concept/applicative.hpp>

#include <boost/hana/ap.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename A>
    struct Applicative
        : hana::integral_constant<bool,
            !is_default<ap_impl<typename tag_of<A>::type>>::value &&
            !is_default<lift_impl<typename tag_of<A>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_APPLICATIVE_HPP

/* applicative.hpp
eQnATcTpkwovYIX7xDNpYo9SQl1jukP09yG6z+SIzKkY47rZTL6OKwklmHboI/4pLpRs8dvwS4fKNoHnbw6VHcnf4KaCoeJ0E++W+Ykf/I54ywvB12U8FL4OzHq7zFq1eM+g8bBQkj/PHm+BHfi97ng4Gag6WyT1i3YrphuKxAV73T6q2pQmuXIAZdTTHLzzZaHsGK4sp99CyvK93OmTAheP4Xi2luP/qaRCFYMtxx9Ai+rX
*/