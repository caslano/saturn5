// Boost.Geometry Index
//
// boxes union/intersection area/volume
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_box_box.hpp>

#include <boost/geometry/index/detail/algorithms/content.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

// Util to distinguish between default and non-default index strategy
template <typename Box, typename Strategy>
inline bool disjoint_box_box(Box const& box1, Box const& box2, Strategy const&)
{
    return geometry::detail::disjoint::disjoint_box_box(box1, box2,
                typename Strategy::disjoint_box_box_strategy_type());
}

template <typename Box>
inline bool disjoint_box_box(Box const& box1, Box const& box2, default_strategy const& )
{
    typedef typename strategy::disjoint::services::default_strategy<Box, Box>::type strategy_type;
    return geometry::detail::disjoint::disjoint_box_box(box1, box2, strategy_type());
}

/**
 * \brief Compute the area, volume, ... of the intersection of b1 and b2
 */
template <typename Box, typename Strategy>
inline typename default_content_result<Box>::type intersection_content(Box const& box1, Box const& box2, Strategy const& strategy)
{
    bool const intersects = ! index::detail::disjoint_box_box(box1, box2, strategy);

    // NOTE: the code below may be inconsistent with the disjoint_box_box()
    // however intersection_box_box checks if the boxes intersect on the fly so it should be ok
    // but this also means that disjoint_box_box() is probably not needed

    if ( intersects )
    {
        Box box_intersection;
        bool const ok = geometry::detail::intersection::intersection_box_box
                            <
                                0, geometry::dimension<Box>::value
                            >::apply(box1, box2, 0, box_intersection, 0);
        if ( ok )
        {
            return index::detail::content(box_intersection);
        }
    }
    return 0;
}

template <typename Box>
inline typename default_content_result<Box>::type intersection_content(Box const& box1, Box const& box2)
{
    return intersection_content(box1, box2, default_strategy());
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP

/* intersection_content.hpp
08khtkVwnLdDtjxKnCyj8NNyB7cCpYVF9DXEVNyk1D588YmHnTxV8rQwtT8tWUY1cQunR7Nv7bmS0LUzSElIhv0fdlSP7qE4zOROpX7jGXOmZKyt7JPiQ+4uKJvP/k7TKsxsZTKWx/SFh7PDxeVENCHUF1msdr57+2Q7WQdFdgyJXsu1nWRPQPz+RRz1Ex5PQPJb5BVI9t2m2xf7VKo++N6kfuwTeCkz08lTGfw2eGh0piyLO1XGXrWLi/b9pMS+qVEvTP+Sdo8lxxKE4CmzpBB9J+PUjpKwKWtrq+AN04e5OVXkRLl2UT7qwfk4q8/02dP1SEoPgdwj9KCnTfMJfzsPJ7ajy9kHPK2YOovexsYMvms3V7QO88di1yF8eXgaeOR/Uvvh/D9x2X58PXze08Py1U7j2VwUPONzU/lWeMzcTar9rYntq9xFWUe42dOP4muj/m4pCl523jBf/T9PiY+hHGTUv2czyQ+3/nygd5iDT69Z6s79UQv2mUbxOLIlYQZCEWP+fZrmTivzhCpdo9d9nL5eJa/7x9Wedt0/ro6s3CbLvlRbwnQYMuOXnp5mqd3sefIagv/tcGQB2c26zhy3v0rpKyeFtaP20Nm+u+KjcbKOIVnnTxqTzNaSJWu9vPzxAz3suObrC1vDCqP3aG8kxQzbePE7a0ejvZaf7GkyfbzKv6k/48bBSVhLaanittyVCD0SoJepSIC/
*/