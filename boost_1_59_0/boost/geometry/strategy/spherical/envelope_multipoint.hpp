// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_MULTIPOINT_HPP

#include <cstddef>
#include <algorithm>
#include <utility>
#include <vector>

#include <boost/algorithm/minmax_element.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

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

#include <boost/geometry/strategy/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategy/spherical/envelope_box.hpp>
#include <boost/geometry/strategy/spherical/envelope_point.hpp>


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
            spherical_point::apply(range::front(multipoint), mbr);
            return;
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

#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_MULTIPOINT_HPP

/* envelope_multipoint.hpp
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
*/