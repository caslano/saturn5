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
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
*/