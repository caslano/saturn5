// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP


#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template<typename Tag>
struct get_ring
{};

// A range of rings (multi-ring but that does not exist)
// gets the "void" tag and is dispatched here.
template<>
struct get_ring<void>
{
    template<typename Range>
    static inline typename boost::range_value<Range>::type const&
                apply(ring_identifier const& id, Range const& container)
    {
        return range::at(container, id.multi_index);
    }
};


template<>
struct get_ring<ring_tag>
{
    template<typename Ring>
    static inline Ring const& apply(ring_identifier const& , Ring const& ring)
    {
        return ring;
    }
};


template<>
struct get_ring<box_tag>
{
    template<typename Box>
    static inline Box const& apply(ring_identifier const& ,
                    Box const& box)
    {
        return box;
    }
};


template<>
struct get_ring<polygon_tag>
{
    template<typename Polygon>
    static inline typename ring_return_type<Polygon const>::type const apply(
                ring_identifier const& id,
                Polygon const& polygon)
    {
        BOOST_GEOMETRY_ASSERT
            (
                id.ring_index >= -1
                && id.ring_index < int(boost::size(interior_rings(polygon)))
            );
        return id.ring_index < 0
            ? exterior_ring(polygon)
            : range::at(interior_rings(polygon), id.ring_index);
    }
};


template<>
struct get_ring<multi_polygon_tag>
{
    template<typename MultiPolygon>
    static inline typename ring_type<MultiPolygon>::type const& apply(
                ring_identifier const& id,
                MultiPolygon const& multi_polygon)
    {
        BOOST_GEOMETRY_ASSERT
            (
                id.multi_index >= 0
                && id.multi_index < int(boost::size(multi_polygon))
            );
        return get_ring<polygon_tag>::apply(id,
                    range::at(multi_polygon, id.multi_index));
    }
};


template <typename Geometry>
inline std::size_t segment_count_on_ring(Geometry const& geometry,
                                         segment_identifier const& seg_id)
{
    typedef typename geometry::tag<Geometry>::type tag;
    ring_identifier const rid(0, seg_id.multi_index, seg_id.ring_index);
    // A closed polygon, a triangle of 4 points, including starting point,
    // contains 3 segments. So handle as if closed and subtract one.
    return geometry::num_points(detail::overlay::get_ring<tag>::apply(rid, geometry), true) - 1;
}

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP

/* get_ring.hpp
/XJYXBZtmgw3Z6YchZypcCOdFQWiqZHZvgrm2ocp9SFSXzwnwSgtFTi8PlHxfGOSR0RT9pd+ZXF61ppij8MotQ30b7L2moFK2kRLrsVfnv7JlJqaBk6vyEL9AZTdi6kGY5zqAIuwDl4DFTQagxvcWcShTac32ulFXPr2scMUc6mStF0Pcfem6oJhYcVccCZKNeKtp9tvLS++Tm91W2Wrq10TMhRJ2g3dOTfEudEKQweESRu7hOhHhL4MNQJuRLha15/QsZ23QElQ12q76UpdYSaV6tFQsGC+ZRI7r06+6+umCOP4187t/h1P6H6xvb9U3wfekH0te83DVF+pu/l1dVfordNTagrobozQXR6uLeA9QJnIBR+x8XtAHP097PTZTaShq691ZjugcOgOXWCYz+5XMP7kil5BI6M4E5vbubijLvBLpQGyrg6Y13bagExd3PaKqKvwCt3sFZKnvdmsiKvQr70VuG3pviJIMVlSXLMqQDFZi8yEv7sR9Fh/NcPFbWqsMqTs1y7NFOcYL1J3AtYuBpQ2xpI7AIC/XGsAMH3PlM+DtB2S9rBVIfW4XHvVofOr09dnXGDwdM5lI0opAaqBrOwMkr5Yko6qQ9oF0oKIoC8o6ZlIgv8N6of7TNWbeJ8pBK9cXxd2VtWF926sC7+2ri6cVlkXrq6XfuHaunC7irrw8ZJ66VfWhW9ZUxf2ltWFJ62ql/69evGldeFRxfXKV49+g/J6/K2ql/79eunrlfe1DfXyX1uPfr3yr6ysR79+/uvqlb+0Hv3ieuVfUy++pB79lfX4X12Pv7J6+RfXSx+Ub2j+96qwWbjGeAIL8crWCLmL+KeMCMMvnf96NXAVCgl/xPok0sZtpSGo1YbaOborkRe/QgvDioqeCb1XidM70CLCnRUZNsPZ3OQLngfDWhgm8KRsBL1scYWqDdYKnOmW3PPFSbTeDHN/LcNcVgfOUZeW4zh13YBf2v95JSCPKJQpdYsuj/k3nkke9aa2D7yiS+U8RT3hUo9g+uNuiUUbwdltdaef7DiSU45iYTP4PYIiC1z9Qtv9w8Th5JTcKxWMBNRbbaT1Me7PIMdpNv3OXvJpVDGj/QuROBfbhQvuNR9uOuuH5+1Ol8czfwrIww95tN3MOtaESKbcEBBJaD2Cayn6sDvbhpKHFmpOp6+jRgdQT+enQUoJiTbO0cfjTpufAe6ffmE945uX5RDSt9BgY7e7w8mtwrII7SSHXJXogq701CaMa2FXTTsPeCqNdi+mPTzbJnbc7BUmdgBhIcf2eo4njGsAdOviSrsM/Me6Wr+9DNC54v27E2QHWw3kT7uLPZC6DVV9sf3YPgwCEsY2rLOfokY7rC9tG1vj9M1jAqdPrYzmJv4zv+ouLB8MFRpgOcW63G5USg8kO0sPprpiKwGaALaVXjO8CdIbAW+89EZalzujANoAKqUHxbHBaJAzKYzuYnTFVuGCUpSkegBUS4iFGJ1yCbyCsvQKytIbSarSGw1iaJuu2FJnUklWeum4RtCOSVFFeVzvAzw+FvA0wBhGliudGTz9M1yUylvJEKsLrfr3PfXWQ/Sae+ZFvU2/VhhHHcxqqz34bPBMjJNnYmgnNvDUQ1eD1FLtrvQIgx5zsYhxkFSvdLm72eI5pCehq4OE3CsQkKolhCj3mKsT+LiKBHoESMeFSJeLmJ4kfbSTJL0KBASlXc/UIa1o64IBuTeL9hSgMlVQ6RWg/0anIP3hIqY36T+h078V9AW58XXo396WF8enpnLAqLoVDKkmai/cxlu+t7eVuux1c1mc57uINfo3XGf93U/w/MvzwfNa8xeKoyuyZp1ttY0vhcOp2qo6sKItDsGQT9c=
*/