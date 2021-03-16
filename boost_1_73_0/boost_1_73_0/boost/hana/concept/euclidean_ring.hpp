/*!
@file
Defines `boost::hana::EuclideanRing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP
#define BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP

#include <boost/hana/fwd/concept/euclidean_ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/div.hpp>
#include <boost/hana/mod.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct EuclideanRing
        : hana::integral_constant<bool,
            !is_default<mod_impl<typename tag_of<R>::type,
                                 typename tag_of<R>::type>>::value &&
            !is_default<div_impl<typename tag_of<R>::type,
                                 typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP

/* euclidean_ring.hpp
ULXnY6bP+s9WyTWdVUYFXQc8SOm1qQSfwblBifUIcq5H0VAwCeb7ZqOKZrp2mBm2gzihrXW03ZWJEX3IRL/iUO2r9m+qVHEg+5DFyE4/SF/tuz2CS9b9bozglKinCk+czFvQZtqsRCQuViISLUpEAv24Fok20wSnuyY4XVf3ekfb4GheW31F0kbPbj04teDKHrPB5YL1KdXU0rCgvmlh08K5/5WlnsUu84RkWkE7PbhO2+lRtATzcJgp5qmumKc=
*/