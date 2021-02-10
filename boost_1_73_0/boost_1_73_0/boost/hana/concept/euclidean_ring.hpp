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
K++GJeuMZQnLBXcY9nTYKlmEAX7y9BJervN5FIqlU3IDU8WLQZIywaMIxwK6kAvJNmczJR4Hu7E1cBxm+CGSWOBU18tkZXUEOeIoQZ7GMBHIATotEhCzw/J4wVPqTCvXUyiZkoD7baop+V2wJAZm2MZwxsazDTb3RAj6fjM+//n04py9GU6nw8n5W3Z6zIaTtzjY6/HkyGEc7AGm5x/WKRcwecrC1ToK+ULN+fX+Bp1vw9iP8gVnG6g8V/AsX/eXGx1oCBY8YBezkTu9mJ2fzDrVvus0jLNAdVYtezxN46S/PDBe+WkuskjgS2MIGGHhZR6Sly8FjxeB/eqKSO1OEbgLe96NVR5lYSi5Afnn4E+EiNy557+HMV2cqvNHh4HNxAKaZA/JmOuDbOPMhaYgvGSb8nMXOjd2E6AT2BhsU33BjvMkiRjO4a5htjAG6k+7nc5gkx2D9jx2Cfss1uOAUoFZBpKCNj9ZgMWmIPZUbt45F9nWysv8JQzDDi+mJ9ilz0BXIvOy0C/ewT5auzRK1x457dFSw8B+74awBp5mmqbXY9iN6dlx3JF7NhpN3ePh+GR05P5jNB0fjw+H5+PTCS7zE8rkOgTegFoR+57gTFqIOx3NLk7O3dPXOx3pI62RT1/vtlFMLk5O3LPh
*/