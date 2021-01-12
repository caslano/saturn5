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
cfm/P/k1Jy9XkZS8eDZ/W7cYferQRg+P0V1q+1n9JzYMFQtfDH6SDpk7m+yQ8ZhskePnurBsiLIVRYSn51za4y6JxxMfQEXpxjYGzY2UveWQIuveQM/dY5p7+HP4c/hz+HP4c/hz+HP4c/hz+HP4c/hz+HP4c/hz+HP4c/hz+HP4c/hz+HP4c/hz+HP4c/hz+HP4c/hz+HP483/4/Cd/iBkqk95POYo/fe/gEHe5YbV7C+uW
*/