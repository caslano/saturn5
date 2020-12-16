// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_UNIQUE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_UNIQUE_HPP

#include <algorithm>

#include <boost/range.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/policies/compare.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace unique
{


struct range_unique
{
    template <typename Range, typename ComparePolicy>
    static inline void apply(Range& range, ComparePolicy const& policy)
    {
        typename boost::range_iterator<Range>::type it
            = std::unique
                (
                    boost::begin(range),
                    boost::end(range),
                    policy
                );

        traits::resize<Range>::apply(range, it - boost::begin(range));
    }
};


struct polygon_unique
{
    template <typename Polygon, typename ComparePolicy>
    static inline void apply(Polygon& polygon, ComparePolicy const& policy)
    {
        range_unique::apply(exterior_ring(polygon), policy);

        typename interior_return_type<Polygon>::type
            rings = interior_rings(polygon);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            range_unique::apply(*it, policy);
        }
    }
};


template <typename Policy>
struct multi_unique
{
    template <typename MultiGeometry, typename ComparePolicy>
    static inline void apply(MultiGeometry& multi, ComparePolicy const& compare)
    {
        for (typename boost::range_iterator<MultiGeometry>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, compare);
        }
    }
};


}} // namespace detail::unique
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct unique
{
    template <typename ComparePolicy>
    static inline void apply(Geometry&, ComparePolicy const& )
    {}
};


template <typename Ring>
struct unique<Ring, ring_tag>
    : detail::unique::range_unique
{};


template <typename LineString>
struct unique<LineString, linestring_tag>
    : detail::unique::range_unique
{};


template <typename Polygon>
struct unique<Polygon, polygon_tag>
    : detail::unique::polygon_unique
{};


// For points, unique is not applicable and does nothing
// (Note that it is not "spatially unique" but that it removes duplicate coordinates,
//  like std::unique does). Spatially unique is "dissolve" which can (or will be)
//  possible for multi-points as well, removing points at the same location.


template <typename MultiLineString>
struct unique<MultiLineString, multi_linestring_tag>
    : detail::unique::multi_unique<detail::unique::range_unique>
{};


template <typename MultiPolygon>
struct unique<MultiPolygon, multi_polygon_tag>
    : detail::unique::multi_unique<detail::unique::polygon_unique>
{};


} // namespace dispatch
#endif


/*!
\brief \brief_calc{minimal set}
\ingroup unique
\details \details_calc{unique,minimal set (where duplicate consecutive points are removed)}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be made unique

\qbk{[include reference/algorithms/unique.qbk]}
*/
template <typename Geometry>
inline void unique(Geometry& geometry)
{
    concepts::check<Geometry>();

    // Default strategy is the default point-comparison policy
    typedef geometry::equal_to
        <
            typename geometry::point_type<Geometry>::type
        > policy;


    dispatch::unique<Geometry>::apply(geometry, policy());
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_UNIQUE_HPP

/* unique.hpp
7lsVfil2GyQ30KLdFMfhtjgq/ygxJiy31I2vOxnf1BRfxYQNHQDt44D2nWpoz5dSRqz0DPya9WRqdAA5YTmwoz+oLKVwddxJrgHJdeF64dWPW+lulfLh+NDdfSktcJOYYpBTm+HkI95E38bX30wuxTeTJydW33SutHk8uXQ3OVO7D8B/i3bXuRP+2yh/Dlq8m1bkK5ivZGVP6x3pWHzYfNG18cYbKkD0At86/+5i8u84U0vgeBOqG+8Tt0D+ShN3gx/pd3eTZ+rG097Rvd7m7d3rbTwm1bHxmO7OLbtVlHXcSVZ7UnhrD5+f2zfccM32jg1S643ZtLt9TEenCrHuFwpz70R69sF7Mj37Unr2037xPMHUUjbjgCfmeZz4efZxv/1mbdKJA5Q8NsQU27WrJTWmpvPsgcq9y/MDCBBTSiKZH6Td/fxAOvQQvszPoGPcg5n5efaasmHtQro3ULb0EBVOIGR+RXonPNQxv95bE97mer8D0sddlf52YQBJp21HpZ8dehxsnbjs2UNWR2vcO9KljFfowCB6D6biRTwA/2EvxyKHrFUoUBx7AbugaM+EkjGIugMrvTCCp9K0P74tKdbOYzAvv6v6akJU2MPwfQVRFeuDlxODl4dbvFyjVm86x2y+3lgo3ubabgzzDfyIyrUJKF8cqXVjmDwFs2MZEryYssknvrZq+4VvUcn3rWXblbscABaRDMYnv4XyoJxardyPVnIITGSR3xm1W5DBTJVUPov8qG3FMRYfZmXazrb6eXDjzTvHbtje1dW5lsJa75TfjtN8Us9H03MbeEByx5VdqraMybZF76F+X1q+r03lzYkqzdj2feOuzjGbbrphqmPT7rHrjVlHruYo7qJUebiPiv/17b5cNhOEKgn60di/kyP6YS/Gkc2MFstWwP1UshWnkb+V6obv4aB9UtEoHsvJju+MRHxnJuI7i+I7e8RyDFNConjwGIU/f02eltN1tM7Mq3iqJ9lIXq9JdYrzaupbnWPHprQfVS+Lwk84R3HJMlPGM4/EosyMyv8LVJiqYocyTJf/F9bEIydR9RTKYIuOwHqnsnjOOFwVz1zWe1RnuliFueYuIdV5L1HvW5T9rPgmsoWXSrvlYAunpDAvU2FUkec13ZfbdI+Q55erKyOXuvS4LVcaOzOhFQZUfKPOjSydtx0k1vD7akWj9rgc0X2NoVvnpXTQB7HJABQdtoMKq66NMzgbo2U/PXRXjobNTffxLfrX6DGs2fWkxzdQ+tZvXMYzbPW4LTeZusgwdmMks2F/07Zf2YFxSCa3yrDH1zbttkR94vYWeeu0hlSfuIPSeif5jeqP8+hBEX0MLMrSyG1i47ZuvrfPtNmgYxvncoEX2vZyWnKTPu3ytAXlc74kVSt2mxGdfQNeydQfJwRxd1u6MGcDez7EBiPvR7xaq7273WLmcB+1PtnhOOiy5D/yuOH//cTH7YmPD6g06BlFXqqiZvPZZcjE5luxJ5Wp+qliemdTT5d1bvO9kEnJHdUr6V4PcY2hutiDNfk8Jc9qI4A2eZVqTyGfUQwb7qNKR90ytEGdXab34bhMQPkQ8+FRSw8fS+jh4y24E3r4BOnhk1beMPQ0mTciO/O0ZWfWJzvzTF07kwhJpXmYb1LnbBr/gc5FdD5n0TmG6Hy+Lp3JwBShw3009vrWRPn9IskA9QalwS+RDF42/iDHBOZVwpxJmNcI87r2V8uTf1AXinjyZh2evDWy7DqGF575qOKYG2maSFp8hDfnhLqcnrxF3tptipr6zUTiHbzXzScN6gWSP+8RfyZEnACocOeldHyA39nhPmGSFnoO7TYgQvgI7jPD/wTSQrcYjPyFzbDyFVo=
*/