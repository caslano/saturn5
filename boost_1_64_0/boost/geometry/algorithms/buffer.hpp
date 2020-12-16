// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_BUFFER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_BUFFER_HPP

#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/detail/buffer/buffer_box.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffer_inserter.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Input,
    typename Output,
    typename TagIn = typename tag<Input>::type,
    typename TagOut = typename tag<Output>::type
>
struct buffer: not_implemented<TagIn, TagOut>
{};


template <typename BoxIn, typename BoxOut>
struct buffer<BoxIn, BoxOut, box_tag, box_tag>
{
    template <typename Distance>
    static inline void apply(BoxIn const& box_in, Distance const& distance,
                Distance const& , BoxOut& box_out)
    {
        detail::buffer::buffer_box(box_in, distance, box_out);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant {

template <typename Geometry>
struct buffer
{
    template <typename Distance, typename GeometryOut>
    static inline void apply(Geometry const& geometry,
                             Distance const& distance,
                             Distance const& chord_length,
                             GeometryOut& out)
    {
        dispatch::buffer<Geometry, GeometryOut>::apply(geometry, distance, chord_length, out);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct buffer<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Distance, typename GeometryOut>
    struct visitor: boost::static_visitor<void>
    {
        Distance const& m_distance;
        Distance const& m_chord_length;
        GeometryOut& m_out;

        visitor(Distance const& distance,
                Distance const& chord_length,
                GeometryOut& out)
        : m_distance(distance),
          m_chord_length(chord_length),
          m_out(out)
        {}

        template <typename Geometry>
        void operator()(Geometry const& geometry) const
        {
            buffer<Geometry>::apply(geometry, m_distance, m_chord_length, m_out);
        }
    };

    template <typename Distance, typename GeometryOut>
    static inline void apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
        Distance const& distance,
        Distance const& chord_length,
        GeometryOut& out
    )
    {
        boost::apply_visitor(visitor<Distance, GeometryOut>(distance, chord_length, out), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{buffer}
\ingroup buffer
\details \details_calc{buffer, \det_buffer}.
\tparam Input \tparam_geometry
\tparam Output \tparam_geometry
\tparam Distance \tparam_numeric
\param geometry_in \param_geometry
\param geometry_out \param_geometry
\param distance The distance to be used for the buffer
\param chord_length (optional) The length of the chord's in the generated arcs around points or bends

\qbk{[include reference/algorithms/buffer.qbk]}
 */
template <typename Input, typename Output, typename Distance>
inline void buffer(Input const& geometry_in, Output& geometry_out,
            Distance const& distance, Distance const& chord_length = -1)
{
    concepts::check<Input const>();
    concepts::check<Output>();

    resolve_variant::buffer<Input>::apply(geometry_in, distance, chord_length, geometry_out);
}

/*!
\brief \brief_calc{buffer}
\ingroup buffer
\details \details_calc{return_buffer, \det_buffer}. \details_return{buffer}.
\tparam Input \tparam_geometry
\tparam Output \tparam_geometry
\tparam Distance \tparam_numeric
\param geometry \param_geometry
\param distance The distance to be used for the buffer
\param chord_length (optional) The length of the chord's in the generated arcs
    around points or bends (RESERVED, NOT YET USED)
\return \return_calc{buffer}
 */
template <typename Output, typename Input, typename Distance>
Output return_buffer(Input const& geometry, Distance const& distance, Distance const& chord_length = -1)
{
    concepts::check<Input const>();
    concepts::check<Output>();

    Output geometry_out;

    resolve_variant::buffer<Input>::apply(geometry, distance, chord_length, geometry_out);

    return geometry_out;
}

/*!
\brief \brief_calc{buffer}
\ingroup buffer
\details \details_calc{buffer, \det_buffer}.
\tparam GeometryIn \tparam_geometry
\tparam MultiPolygon \tparam_geometry{MultiPolygon}
\tparam DistanceStrategy A strategy defining distance (or radius)
\tparam SideStrategy A strategy defining creation along sides
\tparam JoinStrategy A strategy defining creation around convex corners
\tparam EndStrategy A strategy defining creation at linestring ends
\tparam PointStrategy A strategy defining creation around points
\param geometry_in \param_geometry
\param geometry_out output multi polygon (or std:: collection of polygons),
    will contain a buffered version of the input geometry
\param distance_strategy The distance strategy to be used
\param side_strategy The side strategy to be used
\param join_strategy The join strategy to be used
\param end_strategy The end strategy to be used
\param point_strategy The point strategy to be used

\qbk{distinguish,with strategies}
\qbk{[include reference/algorithms/buffer_with_strategies.qbk]}
 */
template
<
    typename GeometryIn,
    typename MultiPolygon,
    typename DistanceStrategy,
    typename SideStrategy,
    typename JoinStrategy,
    typename EndStrategy,
    typename PointStrategy
>
inline void buffer(GeometryIn const& geometry_in,
                MultiPolygon& geometry_out,
                DistanceStrategy const& distance_strategy,
                SideStrategy const& side_strategy,
                JoinStrategy const& join_strategy,
                EndStrategy const& end_strategy,
                PointStrategy const& point_strategy)
{
    typedef typename boost::range_value<MultiPolygon>::type polygon_type;
    concepts::check<GeometryIn const>();
    concepts::check<polygon_type>();

    typedef typename point_type<GeometryIn>::type point_type;
    typedef typename rescale_policy_type
        <
            point_type,
            typename geometry::cs_tag<point_type>::type
        >::type rescale_policy_type;

    geometry_out.clear();

    if (geometry::is_empty(geometry_in))
    {
        // Then output geometry is kept empty as well
        return;
    }

    model::box<point_type> box;
    geometry::envelope(geometry_in, box);
    geometry::buffer(box, box, distance_strategy.max_distance(join_strategy, end_strategy));

    typename strategy::intersection::services::default_strategy
        <
            typename cs_tag<GeometryIn>::type
        >::type intersection_strategy;

    rescale_policy_type rescale_policy
            = boost::geometry::get_rescale_policy<rescale_policy_type>(
                box, intersection_strategy);

    detail::buffer::buffer_inserter<polygon_type>(geometry_in, range::back_inserter(geometry_out),
                distance_strategy,
                side_strategy,
                join_strategy,
                end_strategy,
                point_strategy,
                intersection_strategy,
                rescale_policy);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_BUFFER_HPP

/* buffer.hpp
b7ahhU4R7hPDDn5BiwWzZOaevO4O5SLUDerw0wktFUzObMH20BK0LDDee3Hb0WFohULdktUPulJmYFbMnBoP1KBJp2qfJfyXZ2c0BRjP8/q334fQvMH4fls6OS9F8xdMV9WgFVoQGJ+DrGvPc2gRgj3csOoHWhwY7yG+1fDXaElgfH5XFi98jpYu2GC93dPR8sCMmNVv/Hk75Qlmz+zWkJIhaGWC7Zd2XkGZTdO+z+fWnvACzVew7ZGn6qAFgvE1Q/rcH4wWK5helYhV1Luw5tll246jZQm2+a40ivoDs2HWaPauJdQfmCOzET+Nzai/6QYSV2bJPc5+RFOCOTArXzgsg+YO5sLszp3mt9Diwaryn+nfXh9ofoJl79G7Qz2A2TE7sOj9L+oBjPdXeMT5C/UwQ7sus3hTAs0IjO/Xc/qIqdQDWHVm/67Wu009gPH+ljVYPYp6EKz7yGP+1AMYn+33ggXp1INwzuGFNhrqYSZ8hmV2w0Olg+YGZspsTebBA9QfmJxZu7SYq2gBYObMajUacQYtVLDdiRdj0eLArJh9tt3dEi0JzIiZa7EVzV0Nxq+zjP06eWh5YCbMonbpr6HMwPiMYjdWxesMLh7tazB7cqfoSotq6AqGny2KdSKiBzSMrlNpoz0DmT3SiZziqVqVW2kRwSow/NzxWGe0p3Obpx8rzbNBHrMnOhHBjvX3HKu08BhJ3N/eS3TGjOulTnmGJgdzZyazrOtcaaMi/Zk91QmeMOo6/h1ueEQcGH43+kwneHRIu+TzaOmVdWRfvh9e8qf3qFIw7O+5juekR5u+2dC78GwDSYGk8nNxqc6Q8LDAj+Zkc+g7nQqz9r17AS0QzIJZiXKbF9q4OfR9QYU5zqu5HC0azIBZN7/0iWjTBTsnKfqGNk+wYcr3W9FUYHJ2liKNbws0tWBpPU9MQssBs2T26N12WrMQTMas5tr1O9FKBWusnhCGVgZmzmzrlInf0eRz/87hBVyfz7qGvELzB5NWzEGpfAlW8S/MmuoqzfpNdHSlhXiqwHDur3RGh65ecfwKXhN5zF7DNRF7401GpU2Kksz7u+YbnaaNowrXfcefB18wrHurEx6R8GvtI7w+I8Ak8srrRaMTHPGupbu80oaEp6/5+33kV53I4MjB32pW2oQoTZKBJE630sp0/vHUizMb++cswZrkv7P9phMT+eaZzAWtTLCB4078QpOs17alOz0M0aSC/Zvy6y6aXDDNYx/aTyGYfZ/5n9BcBduwO02D5rae8qyw+Z3sh2JmQcy+63iF+1Rz+pN18OgkZj90RkV2804IoXdhZr8g1xXPBgaiSVP+XoO/wbx1PfaiKcCMmaWc39wOrWYK/b1phVUtmZmK5g1mxOocXr+2QVOCmTDLODjIFi0ArNigYrYVdv3m7DtoQ7bSvaDCNCZN+6CFgknZmqmb/vmFFi3U3Z2WvRttumA26TtS0OLBeC5m/Y7tREsCM2B1ds2+WaKlgvHej46rq0RLF+xV6+3P0bLB9NmaNY/JLqPlCGc5XeNgMM1W6OHOOOvBaIXCOWuedrRAKwYzZWt2/BwwDk0DZs7s/I2LUWjSbdpniW7SmfJUgPFrYrdq5TU0VzA+I8/uV/XRvMEsmfWo4miE5g/Ge+iW3PUqWgCYGasbdq3XELQg4ZyZmaqPaBFgfA4NGks2ocUJdbPe3KQZqcAsmFVbtUeDpgYzZtaiXd2VaFlgJsyWef2kGeWB8awVoz/RmsVgdZmNPbxDWmkR0Yrtf02i26RhVp8vx9G6baffA1WY34l+MrQAMBmr67V23FW0IDAzZo0zLhaiRYBJmd2pOqcK2nQwA7ZfjGGPfWjxQl2Lkqo=
*/