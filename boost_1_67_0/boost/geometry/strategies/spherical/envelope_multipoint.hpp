// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_MULTIPOINT_HPP

#include <cstddef>
#include <algorithm>
#include <utility>
#include <vector>

#include <boost/algorithm/minmax_element.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/geometries/helper_geometry.hpp>

#include <boost/geometry/algorithms/detail/envelope/box.hpp>
#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>
#include <boost/geometry/algorithms/detail/envelope/range.hpp>
#include <boost/geometry/algorithms/detail/expand/point.hpp>

#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/envelope_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_point.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

class spherical_multipoint
{
private:
    template <std::size_t Dim>
    struct coordinate_less
    {
        template <typename Point>
        inline bool operator()(Point const& point1, Point const& point2) const
        {
            return math::smaller(geometry::get<Dim>(point1),
                                 geometry::get<Dim>(point2));
        }
    };

    template <typename Constants, typename MultiPoint, typename OutputIterator>
    static inline void analyze_point_coordinates(MultiPoint const& multipoint,
                                                 bool& has_south_pole,
                                                 bool& has_north_pole,
                                                 OutputIterator oit)
    {
        typedef typename boost::range_value<MultiPoint>::type point_type;
        typedef typename boost::range_iterator
            <
                MultiPoint const
            >::type iterator_type;

        // analyze point coordinates:
        // (1) normalize point coordinates
        // (2) check if any point is the north or the south pole
        // (3) put all non-pole points in a container
        //
        // notice that at this point in the algorithm, we have at
        // least two points on the spheroid
        has_south_pole = false;
        has_north_pole = false;

        for (iterator_type it = boost::begin(multipoint);
             it != boost::end(multipoint);
             ++it)
        {
            point_type point;
            normalize::spherical_point::apply(*it, point);

            if (math::equals(geometry::get<1>(point),
                             Constants::min_latitude()))
            {
                has_south_pole = true;
            }
            else if (math::equals(geometry::get<1>(point),
                                  Constants::max_latitude()))
            {
                has_north_pole = true;
            }
            else
            {
                *oit++ = point;
            }
        }
    }

    template <typename SortedRange, typename Value>
    static inline Value maximum_gap(SortedRange const& sorted_range,
                                    Value& max_gap_left,
                                    Value& max_gap_right)
    {
        typedef typename boost::range_iterator
            <
                SortedRange const
            >::type iterator_type;

        iterator_type it1 = boost::begin(sorted_range), it2 = it1;
        ++it2;
        max_gap_left = geometry::get<0>(*it1);
        max_gap_right = geometry::get<0>(*it2);

        Value max_gap = max_gap_right - max_gap_left;
        for (++it1, ++it2; it2 != boost::end(sorted_range); ++it1, ++it2)
        {
            Value gap = geometry::get<0>(*it2) - geometry::get<0>(*it1);
            if (math::larger(gap, max_gap))
            {
                max_gap_left = geometry::get<0>(*it1);
                max_gap_right = geometry::get<0>(*it2);
                max_gap = gap;
            }
        }

        return max_gap;
    }

    template
    <
        typename Constants,
        typename PointRange,
        typename LongitudeLess,
        typename CoordinateType
    >
    static inline void get_min_max_longitudes(PointRange& range,
                                              LongitudeLess const& lon_less,
                                              CoordinateType& lon_min,
                                              CoordinateType& lon_max)
    {
        typedef typename boost::range_iterator
            <
                PointRange const
            >::type iterator_type;

        // compute min and max longitude values
        std::pair<iterator_type, iterator_type> min_max_longitudes
            = boost::minmax_element(boost::begin(range),
                                    boost::end(range),
                                    lon_less);

        lon_min = geometry::get<0>(*min_max_longitudes.first);
        lon_max = geometry::get<0>(*min_max_longitudes.second);

        // if the longitude span is "large" compute the true maximum gap
        if (math::larger(lon_max - lon_min, Constants::half_period()))
        {
            std::sort(boost::begin(range), boost::end(range), lon_less);

            CoordinateType max_gap_left = 0, max_gap_right = 0;
            CoordinateType max_gap
                = maximum_gap(range, max_gap_left, max_gap_right);

            CoordinateType complement_gap
                = Constants::period() + lon_min - lon_max;

            if (math::larger(max_gap, complement_gap))
            {
                lon_min = max_gap_right;
                lon_max = max_gap_left + Constants::period();
            }
        }
    }

    template
    <
        typename Constants,
        typename Iterator,
        typename LatitudeLess,
        typename CoordinateType
    >
    static inline void get_min_max_latitudes(Iterator const first,
                                             Iterator const last,
                                             LatitudeLess const& lat_less,
                                             bool has_south_pole,
                                             bool has_north_pole,
                                             CoordinateType& lat_min,
                                             CoordinateType& lat_max)
    {
        if (has_south_pole && has_north_pole)
        {
            lat_min = Constants::min_latitude();
            lat_max = Constants::max_latitude();
        }
        else if (has_south_pole)
        {
            lat_min = Constants::min_latitude();
            lat_max
                = geometry::get<1>(*std::max_element(first, last, lat_less));
        }
        else if (has_north_pole)
        {
            lat_min
                = geometry::get<1>(*std::min_element(first, last, lat_less));
            lat_max = Constants::max_latitude();
        }
        else
        {
            std::pair<Iterator, Iterator> min_max_latitudes
                = boost::minmax_element(first, last, lat_less);

            lat_min = geometry::get<1>(*min_max_latitudes.first);
            lat_max = geometry::get<1>(*min_max_latitudes.second);
        }
    }

public:
    template <typename MultiPoint, typename Box>
    static inline void apply(MultiPoint const& multipoint, Box& mbr)
    {
        typedef typename point_type<MultiPoint>::type point_type;
        typedef typename coordinate_type<MultiPoint>::type coordinate_type;
        typedef typename boost::range_iterator
            <
                MultiPoint const
            >::type iterator_type;

        typedef math::detail::constants_on_spheroid
            <
                coordinate_type,
                typename geometry::detail::cs_angular_units<MultiPoint>::type
            > constants;

        if (boost::empty(multipoint))
        {
            geometry::detail::envelope::initialize<Box, 0, dimension<Box>::value>::apply(mbr);
            return;
        }

        geometry::detail::envelope::initialize<Box, 0, 2>::apply(mbr);

        if (boost::size(multipoint) == 1)
        {
            return dispatch::envelope
                <
                    typename boost::range_value<MultiPoint>::type
                >::apply(range::front(multipoint), mbr, strategy::envelope::spherical_point());
        }

        // analyze the points and put the non-pole ones in the
        // points vector
        std::vector<point_type> points;
        bool has_north_pole = false, has_south_pole = false;

        analyze_point_coordinates<constants>(multipoint,
                                             has_south_pole, has_north_pole,
                                             std::back_inserter(points));

        coordinate_type lon_min, lat_min, lon_max, lat_max;
        if (points.size() == 1)
        {
            // we have one non-pole point and at least one pole point
            lon_min = geometry::get<0>(range::front(points));
            lon_max = geometry::get<0>(range::front(points));
            lat_min = has_south_pole
                ? constants::min_latitude()
                : constants::max_latitude();
            lat_max = has_north_pole
                ? constants::max_latitude()
                : constants::min_latitude();
        }
        else if (points.empty())
        {
            // all points are pole points
            BOOST_GEOMETRY_ASSERT(has_south_pole || has_north_pole);
            lon_min = coordinate_type(0);
            lon_max = coordinate_type(0);
            lat_min = has_south_pole
                ? constants::min_latitude()
                : constants::max_latitude();
            lat_max = (has_north_pole)
                ? constants::max_latitude()
                : constants::min_latitude();
        }
        else
        {
            get_min_max_longitudes<constants>(points,
                                              coordinate_less<0>(),
                                              lon_min,
                                              lon_max);

            get_min_max_latitudes<constants>(points.begin(),
                                             points.end(),
                                             coordinate_less<1>(),
                                             has_south_pole,
                                             has_north_pole,
                                             lat_min,
                                             lat_max);
        }

        typedef typename helper_geometry
            <
                Box,
                coordinate_type,
                typename geometry::detail::cs_angular_units<MultiPoint>::type
            >::type helper_box_type;

        helper_box_type helper_mbr;

        geometry::set<min_corner, 0>(helper_mbr, lon_min);
        geometry::set<min_corner, 1>(helper_mbr, lat_min);
        geometry::set<max_corner, 0>(helper_mbr, lon_max);
        geometry::set<max_corner, 1>(helper_mbr, lat_max);

        // now transform to output MBR (per index)
        geometry::detail::envelope::envelope_indexed_box_on_spheroid<min_corner, 2>::apply(helper_mbr, mbr);
        geometry::detail::envelope::envelope_indexed_box_on_spheroid<max_corner, 2>::apply(helper_mbr, mbr);

        // compute envelope for higher coordinates
        iterator_type it = boost::begin(multipoint);
        geometry::detail::envelope::envelope_one_point<2, dimension<Box>::value>::apply(*it, mbr);

        for (++it; it != boost::end(multipoint); ++it)
        {
            strategy::expand::detail::point_loop
                <
                    2, dimension<Box>::value
                >::apply(mbr, *it);
        }
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<multi_point_tag, spherical_equatorial_tag, CalculationType>
{
    typedef strategy::envelope::spherical_multipoint type;
};

template <typename CalculationType>
struct default_strategy<multi_point_tag, spherical_polar_tag, CalculationType>
{
    typedef strategy::envelope::spherical_multipoint type;
};

template <typename CalculationType>
struct default_strategy<multi_point_tag, geographic_tag, CalculationType>
{
    typedef strategy::envelope::spherical_multipoint type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_MULTIPOINT_HPP

/* envelope_multipoint.hpp
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
*/