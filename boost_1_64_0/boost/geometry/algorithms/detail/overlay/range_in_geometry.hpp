// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RANGE_IN_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RANGE_IN_GEOMETRY_HPP


#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/iterators/point_iterator.hpp>

#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct points_range
{
    typedef geometry::point_iterator<Geometry const> iterator_type;

    explicit points_range(Geometry const& geometry)
        : m_geometry(geometry)
    {}

    iterator_type begin() const
    {
        return geometry::points_begin(m_geometry);
    }

    iterator_type end() const
    {
        return geometry::points_end(m_geometry);
    }

    Geometry const& m_geometry;
};
// Specialized because point_iterator doesn't support boxes
template <typename Box>
struct points_range<Box, box_tag>
{
    typedef typename geometry::point_type<Box>::type point_type;
    typedef const point_type * iterator_type;

    explicit points_range(Box const& box)
    {
        detail::assign_box_corners(box,
            m_corners[0], m_corners[1], m_corners[2], m_corners[3]);
    }

    iterator_type begin() const
    {
        return m_corners;
    }

    iterator_type end() const
    {
        return m_corners + 4;
    }

    point_type m_corners[4];
};

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct point_in_geometry_helper
{
    template <typename Point, typename Strategy>
    static inline int apply(Point const& point, Geometry const& geometry,
                            Strategy const& strategy)
    {
        return detail::within::point_in_geometry(point, geometry, strategy);
    }
};
// Specialized because point_in_geometry doesn't support Boxes
template <typename Box>
struct point_in_geometry_helper<Box, box_tag>
{
    template <typename Point, typename Strategy>
    static inline int apply(Point const& point, Box const& box,
                            Strategy const&)
    {
        return geometry::covered_by(point, box) ? 1 : -1;
    }
};

// This function returns
// when it finds a point of geometry1 inside or outside geometry2
template <typename Geometry1, typename Geometry2, typename Strategy>
static inline int range_in_geometry(Geometry1 const& geometry1,
                                    Geometry2 const& geometry2,
                                    Strategy const& strategy,
                                    bool skip_first = false)
{
    int result = 0;
    points_range<Geometry1> points(geometry1);
    typedef typename points_range<Geometry1>::iterator_type iterator_type;
    iterator_type const end = points.end();
    iterator_type it = points.begin();
    if (it == end)
    {
        return result;
    }
    else if (skip_first)
    {
        ++it;
    }

    typename Strategy::template point_in_geometry_strategy
        <
            Geometry1, Geometry2
        >::type const in_strategy
        = strategy.template get_point_in_geometry_strategy<Geometry1, Geometry2>();

    for ( ; it != end; ++it)
    {
        result = point_in_geometry_helper<Geometry2>::apply(*it, geometry2, in_strategy);
        if (result != 0)
        {
            return result;
        }
    }
    // all points contained entirely by the boundary
    return result;
}

// This function returns if first_point1 is inside or outside geometry2 or
// when it finds a point of geometry1 inside or outside geometry2
template <typename Point1, typename Geometry1, typename Geometry2, typename Strategy>
inline int range_in_geometry(Point1 const& first_point1,
                             Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
{
    // check a point on border of geometry1 first
    int result = point_in_geometry_helper<Geometry2>::apply(first_point1, geometry2,
                    strategy.template get_point_in_geometry_strategy<Point1, Geometry2>());
    if (result == 0)
    {
        // if a point is on boundary of geometry2
        // check points of geometry1 until point inside/outside is found
        // NOTE: skip first point because it should be already tested above
        result = range_in_geometry(geometry1, geometry2, strategy, true);
    }    
    return result;
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RANGE_IN_GEOMETRY_HPP

/* range_in_geometry.hpp
sqlFfLqrtJkCNrdaqfrbB31iSVqwJMvi7x48iBtY3iAL3tkjzV6+3pAqS4BqDz+bMgig7Hf99EuCzEtuTTUYx8XUI6h+BM0gW+BceXJ+mxXQblk6ykh3B+YsvJCn6iZ+jwgetCw5sy04acd+hSFKlkz1qMNHUEgktdjDZyHp1xj4/6RH8VN5d4m+gph+o5TGGuW0sE3qFdPULLvQ8051Vp5jSpyDUMeYu0hsp57lnELJ9U5xVZ6FmVqvsfGDkJGY2Qsa1MweoijGpiQioY9TTZWEJwAvLsc/Q4lK5G7hfHQuYsF+glp0uBTVjFFMUYDepSnQP2oJupNWM1pxsX6MuGJN5H66X4BbPzvJeYBDgtBfkp6CBRNTsxBN501WwF9b/gSjQXKKyWeNUVXRRdJef6zStf5PonV3yTseLdfNTvoZz0xEpy4OBs/VmuSsLeYL1Ia9sF47S6K9u1I/pBmuPit0GVYbAbzrkn6sVaYSt8ckOoDhJ5RGjdZjcDvHSKAQRXpFxheVijTciloLgYwj4ehUeKEMECPlfsG4FKMnonv5oQg/NtkpqNeKD1W9vty6ya45j1xBoFE5f0Mrc6mKzsEb26Uzj8guz5tu4g35L5AZOJ4nRl8felTXnYTg3oIPUCpqroU9b4DqoTMbSr+H0MQha9+JVoPIOAH/sRP6eU2MkD0W/PuT4NtSw79fwn95AuBbV+B/eRXgh07ucoPVoHAc5fz/0cR5a7Yzxfl/UnhaivDDj6hw0Y0rNWNtR2ZS4dOvgi5mqlqVitcAkuI+QIp7mOvFpYru/wRHti7xqqsyaiV/eWRc47qXugdJXY1cg5WBCZZ85BKTB3hCinntErOzeO9ZhXRfn8mbz5ZJ942Sdp/hErf18PGUV2vCYKYe5jrC13zhkxsNFixvjhtH+0eAW+g/jf+ygntN/i7BqCUAwcye7yNGZBYch6I4hbwQjr/R4SsSr0XG4yvLivDzgnuz/cP5b0Bwr9PfqzTKjPmtRWJz5BRE2mtBpBPg2E6HA461dKTDUQH48jrLcCGGgyoFmn0Dwkc9RKORF6F65t4hr1MweZYYebv5ALzk7eYowSvMzVlFYmtkGL7W8WswHEOZ7T5w5NDRE44gMXaG4xP6mIvEttJDShi1UrLGzjFyhc6+cba9rJDOiNHv4b9zghGTf1AwggtSgods9nKjEndfCnANWco9j26Hcnvotij36XQ3qwI56P7YQMBO/yj+O700ImspE/kgvVn+GxVzDWOuUu4n6H5Ouc+g+wnl7kY3zVQgLYDcONnvhssGaLl4O/A+Be9svLvi7YSgWxFSZbEKroHDTMcc2o8wwzETjsvpM4XjjY7xSIQ8+fP4NkEVjG/oafbi2yYbtpoNa52gN6z1O3rDWjWzaljrJjhi5yvBI9k3elDqPUb/mfzXL7jHBHJmj8V/YfCILVCMPuljy02HYwgdk+DoRUchHB3o4PI4jI7c4B6nfzD/OUr3ADiLeIQVGDgBUd4xq3xkXHrELPORUQMfH8hHJyUlwN+l2HGeT1jvHGeFP0gOHw5Mc7xzX/fJS8qy8zk2MFi8lCJXIylpBC7bexPsj+O3Er+X8avDbzt+m/F7D7+P8TMYpfVjs009FlvLx2o7+pNm++c+/wRLzP+djy7/82CSkuw6pRbwMLtFm/hu4cpEj/vpOzxh3Jxb5c43+bEBq5JWI4LNtkV7sAGjcR8z3tgtuIR7raXmqPxDXN1EmyTC5QyZhGtkS6t02GohioQmzs/CmFu/k5jrcqsUPya/q46+muh7LNqr0Ps3eZYDdVVq1C3Lk01+w67U5el8vOURLkdNK/g9jgK/w/HCZ31Z2U403/seJos=
*/