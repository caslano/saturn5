/*!
@file
Defines `boost::hana::Sequence`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEQUENCE_HPP
#define BOOST_HANA_CONCEPT_SEQUENCE_HPP

#include <boost/hana/fwd/concept/sequence.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename S, typename Tag = typename hana::tag_of<S>::type>
        struct sequence_dispatch
            : hana::integral_constant<bool,
                hana::Sequence<Tag>::value
            >
        { };

        template <typename S>
        struct sequence_dispatch<S, S>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename S, bool condition>
    struct Sequence<S, when<condition>>
        : detail::sequence_dispatch<S>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEQUENCE_HPP

/* sequence.hpp
pF3pBCigvkD3fIpFigODog7RLPedJ8da0ilbNPkuMEUWZe/262kPRRZkI0N9WFeMuZiNn9+gK8YH8C/yD46OGv5FSPUnedkl5T5kqCZt2He70WhX63ih5B57Zuu945D5JXpx54kiBJfw01GbetKHlyOEwlUvVfqMwmQ/dZ37iUfozFZU+PtmP6sZjh9gbTCDxhEunhEJz8F0f7GBS1Pmw204Z4x3ak6NqGnkt9cbVrCuW2fY
*/