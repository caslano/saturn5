/*!
@file
Defines `boost::hana::detail::operators::adl`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ADL_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ADL_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace operators {
    //! @ingroup group-details
    //! Enables [ADL](http://en.cppreference.com/w/cpp/language/adl) in the
    //! `hana::detail::operators` namespace.
    //!
    //! This is used by containers in Hana as a quick way to automatically
    //! define the operators associated to some concepts, in conjunction
    //! with the `detail::xxx_operators` family of metafunctions.
    //!
    //! Note that `adl` can be passed template arguments to make it unique
    //! amongst a set of derived classes. This allows a set of derived classes
    //! not to possess a common base class, which would disable the EBO when
    //! many of these derived classes are stored in a Hana container. If EBO
    //! is not a concern, `adl<>` can simply be used.
    template <typename ...>
    struct adl { };
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ADL_HPP

/* adl.hpp
JOU1GQfyoFEJY64px9rmQ1r1h36baJzmmGyT0YOLCSh2hYqbDOLrgFj8Op3zc0ktjuMPpJ5igSCeAWUpla6EGggy/PvD05FAHqVViSbZY1iaObT6oyFE7ncAAGsT1D7jq4uJfWL2RiemfWGMDeJRZHd7CZwK/f512CH451sO0BhM7KFxboqJnUDsRmlysSz1qa2eWLK1wVbbN06grklQVbqpyyipAPWPRHaJ4cNwsUxj3HuH8Rb7bbHwC5mpqKZi+uijH3rRbUJekii8dWIPZIM5pahfmLSzApx7tGrYzxbFHK2fOuRFh1wMjAmGd1gfM1wXErLPB3OMtLfPxqYxMcf2BHSVbf56afD0pyhtWbMONg8uF/YYzOsQ6GlxaWFnd8s4uvE9nlx7uT/100LNSKkSlTkc4V1mKdg24zPhlHPSsr2aYT1D7h4WyJ30LeMtKNq++Td+4suI/HUd+lynlxm8spjW97iICnJDy55cXZibjixWuumITY4U5edhSgE/QiXIgxJmVTSaHcmCKnkgUtELij5/wmUGk5KC4k9kqh8YqQ8hnO8EKI3Afg56JWJGlimWQlHesufyJFOfWZrcXWV+mbhVzvM0h7p68KS6FCxrrLqpYlh3eyV9JGEUVahOun+8RKbrw5MjFSfs
*/