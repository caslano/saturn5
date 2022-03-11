// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_OF_BOXES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_OF_BOXES_HPP

#include <cstddef>

#include <algorithm>
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/max_interval_gap.hpp>
#include <boost/geometry/algorithms/detail/expand/indexed.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


template <typename T>
class longitude_interval
{
    typedef T const& reference_type;

public:
    typedef T value_type;
    typedef T difference_type;

    longitude_interval(T const& left, T const& right)
    {
        m_end[0] = left;
        m_end[1] = right;        
    }

    template <std::size_t Index>
    reference_type get() const
    {
        return m_end[Index];
    }

    difference_type length() const
    {
        return get<1>() - get<0>();
    }

private:
    T m_end[2];
};


template <typename Units>
struct envelope_range_of_longitudes
{
    template <std::size_t Index>
    struct longitude_less
    {
        template <typename Interval>
        inline bool operator()(Interval const& i1, Interval const& i2) const
        {
            return math::smaller(i1.template get<Index>(),
                                 i2.template get<Index>());
        }
    };

    template <typename RangeOfLongitudeIntervals, typename Longitude>
    static inline void apply(RangeOfLongitudeIntervals const& range,
                             Longitude& lon_min, Longitude& lon_max)
    {
        typedef typename math::detail::constants_on_spheroid
            <
                Longitude, Units
            > constants;

        Longitude const zero = 0;
        Longitude const period = constants::period();

        lon_min = lon_max = zero;

        // the range of longitude intervals can be empty if all input boxes
        // degenerate to the north or south pole (or combination of the two)
        // in this case the initialization values for lon_min and
        // lon_max are valid choices
        if (! boost::empty(range))
        {
            lon_min = std::min_element(boost::begin(range),
                                       boost::end(range),
                                       longitude_less<0>())->template get<0>();
            lon_max = std::max_element(boost::begin(range),
                                       boost::end(range),
                                       longitude_less<1>())->template get<1>();

            if (math::larger(lon_max - lon_min, constants::half_period()))
            {
                Longitude max_gap_left, max_gap_right;
                Longitude max_gap = geometry::maximum_gap(range,
                                                          max_gap_left,
                                                          max_gap_right);

                BOOST_GEOMETRY_ASSERT(! math::larger(lon_min, lon_max));
                BOOST_GEOMETRY_ASSERT
                    (! math::larger(lon_max, constants::max_longitude()));
                BOOST_GEOMETRY_ASSERT
                    (! math::smaller(lon_min, constants::min_longitude()));

                BOOST_GEOMETRY_ASSERT
                    (! math::larger(max_gap_left, max_gap_right));
                BOOST_GEOMETRY_ASSERT
                    (! math::larger(max_gap_right, constants::max_longitude()));
                BOOST_GEOMETRY_ASSERT
                    (! math::smaller(max_gap_left, constants::min_longitude()));

                if (math::larger(max_gap, zero))
                {
                    Longitude wrapped_gap = period + lon_min - lon_max;
                    if (math::larger(max_gap, wrapped_gap))
                    {
                        lon_min = max_gap_right;
                        lon_max = max_gap_left + period;
                    }
                }
            }
        }
    }
};


template <std::size_t Dimension, std::size_t DimensionCount>
struct envelope_range_of_boxes_by_expansion
{
    template <typename RangeOfBoxes, typename Box>
    static inline void apply(RangeOfBoxes const& range_of_boxes, Box& mbr)
    {
        typedef typename boost::range_value<RangeOfBoxes>::type box_type;

        typedef typename boost::range_iterator
            <
                RangeOfBoxes const
            >::type iterator_type;

        // first initialize MBR
        detail::indexed_point_view<Box, min_corner> mbr_min(mbr);
        detail::indexed_point_view<Box, max_corner> mbr_max(mbr);

        detail::indexed_point_view<box_type const, min_corner>
            first_box_min(range::front(range_of_boxes));

        detail::indexed_point_view<box_type const, max_corner>
            first_box_max(range::front(range_of_boxes));

        detail::conversion::point_to_point
            <
                detail::indexed_point_view<box_type const, min_corner>,
                detail::indexed_point_view<Box, min_corner>,
                Dimension,
                DimensionCount
            >::apply(first_box_min, mbr_min);

        detail::conversion::point_to_point
            <
                detail::indexed_point_view<box_type const, max_corner>,
                detail::indexed_point_view<Box, max_corner>,
                Dimension,
                DimensionCount
            >::apply(first_box_max, mbr_max);

        // now expand using the remaining boxes
        iterator_type it = boost::begin(range_of_boxes);
        for (++it; it != boost::end(range_of_boxes); ++it)
        {
            detail::expand::indexed_loop
                <
                    min_corner,
                    Dimension,
                    DimensionCount
                >::apply(mbr, *it);

            detail::expand::indexed_loop
                <
                    max_corner,
                    Dimension,
                    DimensionCount
                >::apply(mbr, *it);
        }
    }

};


struct envelope_range_of_boxes
{
    template <std::size_t Index>
    struct latitude_less
    {
        template <typename Box>
        inline bool operator()(Box const& box1, Box const& box2) const
        {
            return math::smaller(geometry::get<Index, 1>(box1),
                                 geometry::get<Index, 1>(box2));
        }
    };

    template <typename RangeOfBoxes, typename Box>
    static inline void apply(RangeOfBoxes const& range_of_boxes, Box& mbr)
    {
        // boxes in the range are assumed to be normalized already

        typedef typename boost::range_value<RangeOfBoxes>::type box_type;
        typedef typename coordinate_type<box_type>::type coordinate_type;
        typedef typename detail::cs_angular_units<box_type>::type units_type;
        typedef typename boost::range_iterator
            <
                RangeOfBoxes const
            >::type iterator_type;

        static const bool is_equatorial = ! boost::is_same
                                            <
                                                typename cs_tag<box_type>::type,
                                                spherical_polar_tag
                                            >::value;

        typedef math::detail::constants_on_spheroid
            <
                coordinate_type, units_type, is_equatorial
            > constants;

        typedef longitude_interval<coordinate_type> interval_type;
        typedef std::vector<interval_type> interval_range_type;

        BOOST_GEOMETRY_ASSERT(! boost::empty(range_of_boxes));

        iterator_type it_min = std::min_element(boost::begin(range_of_boxes),
                                                boost::end(range_of_boxes),
                                                latitude_less<min_corner>());
        iterator_type it_max = std::max_element(boost::begin(range_of_boxes),
                                                boost::end(range_of_boxes),
                                                latitude_less<max_corner>());

        coordinate_type const min_longitude = constants::min_longitude();
        coordinate_type const max_longitude = constants::max_longitude();
        coordinate_type const period = constants::period();

        interval_range_type intervals;
        for (iterator_type it = boost::begin(range_of_boxes);
             it != boost::end(range_of_boxes);
             ++it)
        {
            if (is_inverse_spheroidal_coordinates(*it))
            {
                continue;
            }

            coordinate_type lat_min = geometry::get<min_corner, 1>(*it);
            coordinate_type lat_max = geometry::get<max_corner, 1>(*it);
            if (math::equals(lat_min, constants::max_latitude())
                || math::equals(lat_max, constants::min_latitude()))
            {
                // if the box degenerates to the south or north pole
                // just ignore it
                continue;
            }                             

            coordinate_type lon_left = geometry::get<min_corner, 0>(*it);
            coordinate_type lon_right = geometry::get<max_corner, 0>(*it);

            if (math::larger(lon_right, max_longitude))
            {
                intervals.push_back(interval_type(lon_left, max_longitude));
                intervals.push_back
                    (interval_type(min_longitude, lon_right - period));
            }
            else
            {
                intervals.push_back(interval_type(lon_left, lon_right));
            }
        }

        coordinate_type lon_min = 0;
        coordinate_type lon_max = 0;
        envelope_range_of_longitudes
            <
                units_type
            >::apply(intervals, lon_min, lon_max);

        // do not convert units; conversion will be performed at a
        // higher level

        // assign now the min/max longitude/latitude values
        detail::indexed_point_view<Box, min_corner> mbr_min(mbr);
        detail::indexed_point_view<Box, max_corner> mbr_max(mbr);

        geometry::set<0>(mbr_min, lon_min);
        geometry::set<1>(mbr_min, geometry::get<min_corner, 1>(*it_min));
        geometry::set<0>(mbr_max, lon_max);
        geometry::set<1>(mbr_max, geometry::get<max_corner, 1>(*it_max));

        // what remains to be done is to compute the envelope range
        // for the remaining dimensions (if any)
        envelope_range_of_boxes_by_expansion
            <
                2, dimension<Box>::value
            >::apply(range_of_boxes, mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_OF_BOXES_HPP

/* range_of_boxes.hpp
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
*/