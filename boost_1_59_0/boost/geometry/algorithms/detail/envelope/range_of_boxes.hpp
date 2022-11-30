// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_OF_BOXES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_OF_BOXES_HPP

#include <algorithm>
#include <cstddef>
#include <type_traits>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

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

        static const bool is_equatorial = ! std::is_same
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