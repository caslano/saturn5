// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/is_simple/failure_policy.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename Ring, typename CSTag>
struct is_simple_ring
{
    static inline bool apply(Ring const& ring)
    {
        simplicity_failure_policy policy;
        return ! boost::empty(ring)
            && ! detail::is_valid::has_duplicates
                    <
                        Ring, geometry::closure<Ring>::value, CSTag
                    >::apply(ring, policy);
    }
};


template <typename Polygon, typename CSTag>
class is_simple_polygon
{
private:
    template <typename InteriorRings>
    static inline
    bool are_simple_interior_rings(InteriorRings const& interior_rings)
    {
        return
            detail::check_iterator_range
                <
                    is_simple_ring
                        <
                            typename boost::range_value<InteriorRings>::type,
                            CSTag
                        >
                >::apply(boost::begin(interior_rings),
                         boost::end(interior_rings));
    }

public:
    static inline bool apply(Polygon const& polygon)
    {
        return
            is_simple_ring
                <
                    typename ring_type<Polygon>::type,
                    CSTag
                >::apply(exterior_ring(polygon))
            &&
            are_simple_interior_rings(geometry::interior_rings(polygon));
    }
};


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A Ring is a Polygon.
// A Polygon is always a simple geometric object provided that it is valid.
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Ring>
struct is_simple<Ring, ring_tag>
{
    template <typename Strategy>
    static inline bool apply(Ring const& ring, Strategy const&)
    {
        return detail::is_simple::is_simple_ring
            <
                Ring,
                typename Strategy::cs_tag
            >::apply(ring);
    }
};


// A Polygon is always a simple geometric object provided that it is valid.
//
// Reference (for validity of Polygons): OGC 06-103r4 (6.1.11.1)
template <typename Polygon>
struct is_simple<Polygon, polygon_tag>
{
    template <typename Strategy>
    static inline bool apply(Polygon const& polygon, Strategy const&)
    {
        return detail::is_simple::is_simple_polygon
            <
                Polygon,
                typename Strategy::cs_tag
            >::apply(polygon);
    }
};


// Not clear what the definition is.
// Right now we consider a MultiPolygon as simple if it is valid.
//
// Reference (for validity of MultiPolygons): OGC 06-103r4 (6.1.14)
template <typename MultiPolygon>
struct is_simple<MultiPolygon, multi_polygon_tag>
{
    template <typename Strategy>
    static inline bool apply(MultiPolygon const& multipolygon, Strategy const&)
    {
        return
            detail::check_iterator_range
                <
                    detail::is_simple::is_simple_polygon
                        <
                            typename boost::range_value<MultiPolygon>::type,
                            typename Strategy::cs_tag
                        >,
                    true // allow empty multi-polygon
                >::apply(boost::begin(multipolygon), boost::end(multipolygon));
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP

/* areal.hpp
Ohv2RBF2gw2bY8JaPINb3VnAjVen4oYws56qtb2G2qfcCFnmu4547vLEZKeYf7iJcRQQ3++8cdfzE8WxfPDm1C2eR5R8o77D0OT3+ocZTnVl+LbrrRGO+7sMRd4Xy5xGOSPJcW6XHCFJ5veOiMPS2tV3Utb0faaq7+55Ti761NH1I/3r6GTaghhf3X/cCCpzzLeTO5cGmHpmTOLyzNgvw7jBvrZfM2ZeVaTTbtE5pZiD9HmeXknDyFDimzL7/DXHTdEZP2FRFqcsNo8fntX67dIIR/a4H/udxynd+XG6wX38dzM/SOf3CLc+PzDW/59cONeBz/v9jEn9efwBxkX+WebfyD+PZP6DwlWZ/2JMlfkw41Jm231Rva7Nw73nUG2P3b+jOqKtGyYR6bP/l3lmayx2HWyCF412WMDYRuWgTkvYPza5u+yIjrdXd3Neo1zqWNxCeo36xKrgXIZM077chj61JO8vegxzUMa0iPhHucPP9we4lMc2/3jLWZWKgYT0QaC266hQq2r36HxY9aXncXsYWk03cvEZr6cGmCnyNMrUbn9aqKm+40fV/Owb6Jq2GjlsTogF4+v9Q8x8QPg96hgL3oJ4KuN2Ew9jTwOWbu3F9zGtVYEdCMyU06YLBn/7DgKGOVKli2ObfrrGUfbnPkPj+W21LPOZOg+Tt+LuVOaszJ7zPURg2rzxQoGzeHG/aIBDbIv3rghbgc+i9S9Xsq3IMwzdoS9DDk94fubIDAd9oLtFlOcumVMdK+ZSsNW7WzjvdDllnPdr1DHSUpEvxGu3TcH2tTb1NdVHeSLLohWYMvWtDu+JcdNVzhbfdJFt5xmbsBT9fEPtB/q8TNrdKn395cDSwLTJcfhRHB68YX20D6/u7Onl9nKM2l7CO9Oer3JowcPldY20e0QP1ggERtE4X+u6eR0FzaldfU416toepO+r+lzP+jT1h1e1uU84XmL17hT0fhpj6Wv35vnwsvBDNzJOO7aFXW0OsEbVoNIHPZFx2l1oCEL3I65/pTxvrySpgLTj9/evhhzAbX8vMVzQ7PJ2VY8ndUs/ETGTDl4XAYZbh5ARvuvsFIRZYmqtfj0hDE+kfZ8kMGSwXbuorlLHi79Sy5Oz5fF3kLffZ1dXFTV5v1Xl5Z083wszVvBYkp65HWvf90mgS6Uu7+G8iLWM8e7IP6XvfzfKhAU9eS6hOAsX4lfJ+d6JZlxyZzxve3NebVKsZZSa8oxo1qRLd2d3c79b5nNS5bnCM29K55F0wSvrPHK4BK+i82iZU+SvqvLi/eenNePV+PxkTeWkXl16B2HX7DxwuM9LYl+f97E6G/ZQ2zaMbl1rTw+p7Wm6W7z3nhR6zYfbYbsEhvBe4OjXdcyNeTqVdA1mEpZ91G7gY1NVnGRJYS/zpd1ybBvORZ4RYhPyvsYzgcE3U+OdRRjHa7OPwkcf20c0nT524Z73j5BQu4WktT3CkLvyVBQBLWRltB//CVImv2WKMq4eTLdrkLPQRhlXngo5ZtqqRyvjPgubzVuRU9I/Ojqc3oCRzt906fjWgeHBddsydwu9tttx1g4ep98HFeKI7tc+ZFzlPqizPT6wKb0nPb73KMSz9zVF8cPzoW+SeG7N5k2jA5tIhqYD5lg5vL6iphPeDfVWwdk6sAHNSp/rYjyc6zonjg8BvP/gbR4fHBnZgp0k/ZvW5kZQY/0b+D5mltWUC6Ge9/bmaYq5RvDmOt7wAPax5PT7o2KOvD/qvO4Yz9rDOz3HmOrAWt3WGJe29q5M3Oy5x+JcidudOJEtaJzQFt7dHXK4IKz/8wNOaBBIS5fHvKCNvldPK5U4P0rHTL9y//0+HxcnW0T4p70uqPxROlQ=
*/