// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP

#include <cstddef>

#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace num_segments
{


struct range_count
{
    template <typename Range>
    static inline std::size_t apply(Range const& range)
    {
        std::size_t n = boost::size(range);
        if ( n <= 1 )
        {
            return 0;
        }

        return
            geometry::closure<Range>::value == open
            ?
            n
            :
            static_cast<std::size_t>(n - 1);
    }
};

}} // namespace detail::num_segments
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct num_segments
    : not_implemented<Tag>
{};

template <typename Geometry>
struct num_segments<Geometry, point_tag>
    : detail::counting::other_count<0>
{};

// the number of segments (1-dimensional faces) of the hypercube is
// given by the formula: d * 2^(d-1), where d is the dimension of the
// hypercube; see also:
//            http://en.wikipedia.org/wiki/Hypercube
template <typename Geometry>
struct num_segments<Geometry, box_tag>
    : detail::counting::other_count
        <
            geometry::dimension<Geometry>::value
            * (1 << (geometry::dimension<Geometry>::value - 1))
        >
{};

template <typename Geometry>
struct num_segments<Geometry, segment_tag>
    : detail::counting::other_count<1>
{};

template <typename Geometry>
struct num_segments<Geometry, linestring_tag>
    : detail::num_segments::range_count
{};

template <typename Geometry>
struct num_segments<Geometry, ring_tag>
    : detail::num_segments::range_count
{};

template <typename Geometry>
struct num_segments<Geometry, polygon_tag>
    : detail::counting::polygon_count<detail::num_segments::range_count>
{};

template <typename Geometry>
struct num_segments<Geometry, multi_point_tag>
    : detail::counting::other_count<0>
{};

template <typename Geometry>
struct num_segments<Geometry, multi_linestring_tag>
    : detail::counting::multi_count
        <
            num_segments< typename boost::range_value<Geometry>::type>
        >
{};

template <typename Geometry>
struct num_segments<Geometry, multi_polygon_tag>
    : detail::counting::multi_count
        <
            num_segments< typename boost::range_value<Geometry>::type>
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



namespace resolve_dynamic
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct num_segments
{
    static inline std::size_t apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::num_segments<Geometry>::apply(geometry);
    }
};


template <typename Geometry>
struct num_segments<Geometry, dynamic_geometry_tag>
{
    static inline std::size_t apply(Geometry const& geometry)
    {
        std::size_t result = 0;
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            result = num_segments<util::remove_cref_t<decltype(g)>>::apply(g);
        }, geometry);
        return result;
    }
};


template <typename Geometry>
struct num_segments<Geometry, geometry_collection_tag>
{
    static inline std::size_t apply(Geometry const& geometry)
    {
        std::size_t result = 0;
        detail::visit_breadth_first([&](auto const& g)
        {
            result += num_segments<util::remove_cref_t<decltype(g)>>::apply(g);
            return true;
        }, geometry);
        return result;
    }
};


} // namespace resolve_dynamic



/*!
\brief \brief_calc{number of segments}
\ingroup num_segments
\details \details_calc{num_segments, number of segments}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{number of segments}

\qbk{[include reference/algorithms/num_segments.qbk]}
*/
template <typename Geometry>
inline std::size_t num_segments(Geometry const& geometry)
{
    return resolve_dynamic::num_segments<Geometry>::apply(geometry);
}



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP

/* num_segments.hpp
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
*/