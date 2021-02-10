// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP

#include <cstddef>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

template <typename Box, std::size_t I>
struct has_valid_corners
{
    template <typename VisitPolicy>
    static inline bool apply(Box const& box, VisitPolicy& visitor)
    {
        if (math::equals(geometry::get<geometry::min_corner, I-1>(box),
                         geometry::get<geometry::max_corner, I-1>(box)))
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }
        else if (geometry::get<geometry::min_corner, I-1>(box)
                 >
                 geometry::get<geometry::max_corner, I-1>(box))
        {
            return visitor.template apply<failure_wrong_corner_order>();
        }
        return has_valid_corners<Box, I-1>::apply(box, visitor);
    }
};


template <typename Box>
struct has_valid_corners<Box, 0>
{
    template <typename VisitPolicy>
    static inline bool apply(Box const&, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        return visitor.template apply<no_failure>();
    }
};


template <typename Box>
struct is_valid_box
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Box const& box, VisitPolicy& visitor, Strategy const&)
    {
        return
            ! has_invalid_coordinate<Box>::apply(box, visitor)
            &&
            has_valid_corners<Box, dimension<Box>::value>::apply(box, visitor);
    }
};

}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A box is always simple
// A box is a Polygon, and it satisfies the conditions for Polygon validity.
//
// The only thing we have to check is whether the max corner lies in
// the upper-right quadrant as defined by the min corner
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Box>
struct is_valid<Box, box_tag>
    : detail::is_valid::is_valid_box<Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP

/* box.hpp
d+a9+eSddi8u3nRPC81Vqd+KsO/Z1WXvxCpyC8S6r1Jzel9NE6ogu6rXHFuRakN0jQkOjg2FZ4xCKavTbYIzkUj0qe7ST7WBQElj05FIem4VM/mhJYWOPpgYSzljaYNqjRk00FC1x0Gq7VABoqx3zFGhnTh1HCfXVWBW9JwbyLcdipR29gvMI1eSKTzhdr5ee9Z3+BzGsJnNqm8aOH93edXvlew/uegz6YNvDo41ZrGOFgmGXcGXpn1xFHbfJAzs38bjR6P47A5HVazTFQA6M2ht/0JGd8AZnAqCjRxj2tYcPfZ4AapxHC8jhUMWeVpE/kFem2Hyls4KIwIIsDo6Pxc1E2chgkVIKEggd4tsRAPd3y/wiZpAhQxtuBqq2PotDftTWEJexurvFRwI1B1NF9G9HO/LCEOBTNY2m0QRSZPTTFTloiD50UgWaQsChRG5Ryx/H8VLpiJWQ3CoyEsLH6D4+6Mpx8vsNk7f31x+4IikOyUTqZSfs8R332nTlsXx/Qh4D7qiOGhxojimuZ+oQI+eyzyQYMWgDsU6U5womLAlAoGofooSwIKZH3ic0p/hNNPihBI7PEFd2obLMlX54OEHTbJVYq+EbBaSqOcNhlfXZSbDlDbDtkhkwqbUb1ri4oJqo1KmDvJmUZsR
*/