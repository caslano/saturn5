// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2013 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXTREME_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXTREME_POINTS_HPP


#include <cstddef>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/iterators/ever_circling_iterator.hpp>

#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace extreme_points
{

template <std::size_t Dimension>
struct compare
{
    template <typename Point>
    inline bool operator()(Point const& lhs, Point const& rhs)
    {
        return geometry::get<Dimension>(lhs) < geometry::get<Dimension>(rhs);
    }
};


template <std::size_t Dimension, typename PointType, typename CoordinateType>
inline void move_along_vector(PointType& point, PointType const& extreme, CoordinateType const& base_value)
{
    // Moves a point along the vector (point, extreme) in the direction of the extreme  point
    // This adapts the possibly uneven legs of the triangle (or trapezium-like shape)
    //      _____extreme            _____
    //     /     \                 /     \                                    .
    //    /base   \         =>    /       \ point                             .
    //             \ point                                                    .
    //
    // For so-called intruders, it can be used to adapt both legs to the level of "base"
    // For the base, it can be used to adapt both legs to the level of the max-value of the intruders
    // If there are 2 or more extreme values, use the one close to 'point' to have a correct vector

    CoordinateType const value = geometry::get<Dimension>(point);
    //if (geometry::math::equals(value, base_value))
    if (value >= base_value)
    {
        return;
    }

    PointType vector = point;
    subtract_point(vector, extreme);

    CoordinateType const diff = geometry::get<Dimension>(vector);

    // diff should never be zero
    // because of the way our triangle/trapezium is build.
    // We just return if it would be the case.
    if (geometry::math::equals(diff, 0))
    {
        return;
    }

    CoordinateType const base_diff = base_value - geometry::get<Dimension>(extreme);

    multiply_value(vector, base_diff);
    divide_value(vector, diff);

    // The real move:
    point = extreme;
    add_point(point, vector);
}


template <std::size_t Dimension, typename Range, typename CoordinateType>
inline void move_along_vector(Range& range, CoordinateType const& base_value)
{
    if (range.size() >= 3)
    {
        move_along_vector<Dimension>(range.front(), *(range.begin() + 1), base_value);
        move_along_vector<Dimension>(range.back(), *(range.rbegin() + 1), base_value);
    }
}


template<typename Ring, std::size_t Dimension>
struct extreme_points_on_ring
{

    typedef typename geometry::coordinate_type<Ring>::type coordinate_type;
    typedef typename boost::range_iterator<Ring const>::type range_iterator;
    typedef typename geometry::point_type<Ring>::type point_type;

    template <typename CirclingIterator, typename Points>
    static inline bool extend(CirclingIterator& it,
            std::size_t n,
            coordinate_type max_coordinate_value,
            Points& points, int direction)
    {
        std::size_t safe_index = 0;
        do
        {
            it += direction;

            points.push_back(*it);

            if (safe_index++ >= n)
            {
                // E.g.: ring is completely horizontal or vertical (= invalid, but we don't want to have an infinite loop)
                return false;
            }
        } while (geometry::math::equals(geometry::get<Dimension>(*it), max_coordinate_value));

        return true;
    }

    // Overload without adding to poinst
    template <typename CirclingIterator>
    static inline bool extend(CirclingIterator& it,
            std::size_t n,
            coordinate_type max_coordinate_value,
            int direction)
    {
        std::size_t safe_index = 0;
        do
        {
            it += direction;

            if (safe_index++ >= n)
            {
                // E.g.: ring is completely horizontal or vertical (= invalid, but we don't want to have an infinite loop)
                return false;
            }
        } while (geometry::math::equals(geometry::get<Dimension>(*it), max_coordinate_value));

        return true;
    }

    template <typename CirclingIterator>
    static inline bool extent_both_sides(Ring const& ring,
            point_type extreme,
            CirclingIterator& left,
            CirclingIterator& right)
    {
        std::size_t const n = boost::size(ring);
        coordinate_type const max_coordinate_value = geometry::get<Dimension>(extreme);

        if (! extend(left, n, max_coordinate_value, -1))
        {
            return false;
        }
        if (! extend(right, n, max_coordinate_value, +1))
        {
            return false;
        }

        return true;
    }

    template <typename Collection, typename CirclingIterator>
    static inline bool collect(Ring const& ring,
            point_type extreme,
            Collection& points,
            CirclingIterator& left,
            CirclingIterator& right)
    {
        std::size_t const n = boost::size(ring);
        coordinate_type const max_coordinate_value = geometry::get<Dimension>(extreme);

        // Collects first left, which is reversed (if more than one point) then adds the top itself, then right
        if (! extend(left, n, max_coordinate_value, points, -1))
        {
            return false;
        }
        std::reverse(points.begin(), points.end());
        points.push_back(extreme);
        if (! extend(right, n, max_coordinate_value, points, +1))
        {
            return false;
        }

        return true;
    }

    template <typename Extremes, typename Intruders, typename CirclingIterator, typename SideStrategy>
    static inline void get_intruders(Ring const& ring, CirclingIterator left, CirclingIterator right,
            Extremes const& extremes,
            Intruders& intruders,
            SideStrategy const& strategy)
    {
        if (boost::size(extremes) < 3)
        {
            return;
        }
        coordinate_type const min_value = geometry::get<Dimension>(*std::min_element(boost::begin(extremes), boost::end(extremes), compare<Dimension>()));

        // Also select left/right (if Dimension=1)
        coordinate_type const other_min = geometry::get<1 - Dimension>(*std::min_element(boost::begin(extremes), boost::end(extremes), compare<1 - Dimension>()));
        coordinate_type const other_max = geometry::get<1 - Dimension>(*std::max_element(boost::begin(extremes), boost::end(extremes), compare<1 - Dimension>()));

        std::size_t defensive_check_index = 0; // in case we skip over left/right check, collect modifies right too
        std::size_t const n = boost::size(ring);
        while (left != right && defensive_check_index < n)
        {
            coordinate_type const coordinate = geometry::get<Dimension>(*right);
            coordinate_type const other_coordinate = geometry::get<1 - Dimension>(*right);
            if (coordinate > min_value && other_coordinate > other_min && other_coordinate < other_max)
            {
                int const factor = geometry::point_order<Ring>::value == geometry::clockwise ? 1 : -1;
                int const first_side = strategy.apply(*right, extremes.front(), *(extremes.begin() + 1)) * factor;
                int const last_side = strategy.apply(*right, *(extremes.rbegin() + 1), extremes.back()) * factor;

                // If not lying left from any of the extemes side
                if (first_side != 1 && last_side != 1)
                {
                    //std::cout << "first " << first_side << " last " << last_side << std::endl;

                    // we start at this intrusion until it is handled, and don't affect our initial left iterator
                    CirclingIterator left_intrusion_it = right;
                    typename boost::range_value<Intruders>::type intruder;
                    collect(ring, *right, intruder, left_intrusion_it, right);

                    // Also moves these to base-level, makes sorting possible which can be done in case of self-tangencies
                    // (we might postpone this action, it is often not necessary. However it is not time-consuming)
                    move_along_vector<Dimension>(intruder, min_value);
                    intruders.push_back(intruder);
                    --right;
                }
            }
            ++right;
            defensive_check_index++;
        }
    }

    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline void get_intruders(Ring const& ring,
            Extremes const& extremes,
            Intruders& intruders,
            SideStrategy const& strategy)
    {
        std::size_t const n = boost::size(ring);
        if (n >= 3)
        {
            geometry::ever_circling_range_iterator<Ring const> left(ring);
            geometry::ever_circling_range_iterator<Ring const> right(ring);
            ++right;

            get_intruders(ring, left, right, extremes, intruders, strategy);
        }
    }

    template <typename Iterator, typename SideStrategy>
    static inline bool right_turn(Ring const& ring, Iterator it, SideStrategy const& strategy)
    {
        typename std::iterator_traits<Iterator>::difference_type const index
            = std::distance(boost::begin(ring), it);
        geometry::ever_circling_range_iterator<Ring const> left(ring);
        geometry::ever_circling_range_iterator<Ring const> right(ring);
        left += index;
        right += index;

        if (! extent_both_sides(ring, *it, left, right))
        {
            return false;
        }

        int const factor = geometry::point_order<Ring>::value == geometry::clockwise ? 1 : -1;
        int const first_side = strategy.apply(*(right - 1), *right, *left) * factor;
        int const last_side = strategy.apply(*left, *(left + 1), *right) * factor;

//std::cout << "Candidate at " << geometry::wkt(*it) << " first=" << first_side << " last=" << last_side << std::endl;

        // Turn should not be left (actually, it should be right because extent removes horizontal/collinear cases)
        return first_side != 1 && last_side != 1;
    }


    // Gets the extreme segments (top point plus neighbouring points), plus intruders, if any, on the same ring
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(Ring const& ring,
                             Extremes& extremes,
                             Intruders& intruders,
                             SideStrategy const& strategy)
    {
        std::size_t const n = boost::size(ring);
        if (n < 3)
        {
            return false;
        }

        // Get all maxima, usually one. In case of self-tangencies, or self-crossings,
        // the max might be is not valid. A valid max should make a right turn
        range_iterator max_it = boost::begin(ring);
        compare<Dimension> smaller;
        for (range_iterator it = max_it + 1; it != boost::end(ring); ++it)
        {
            if (smaller(*max_it, *it) && right_turn(ring, it, strategy))
            {
                max_it = it;
            }
        }

        if (max_it == boost::end(ring))
        {
            return false;
        }

        typename std::iterator_traits<range_iterator>::difference_type const
            index = std::distance(boost::begin(ring), max_it);
//std::cout << "Extreme point lies at " << index << " having " << geometry::wkt(*max_it) << std::endl;

        geometry::ever_circling_range_iterator<Ring const> left(ring);
        geometry::ever_circling_range_iterator<Ring const> right(ring);
        left += index;
        right += index;

        // Collect all points (often 3) in a temporary vector
        std::vector<point_type> points;
        points.reserve(3);
        if (! collect(ring, *max_it, points, left, right))
        {
            return false;
        }

//std::cout << "Built vector of " << points.size() << std::endl;

        coordinate_type const front_value = geometry::get<Dimension>(points.front());
        coordinate_type const back_value = geometry::get<Dimension>(points.back());
        coordinate_type const base_value = (std::max)(front_value, back_value);
        if (front_value < back_value)
        {
            move_along_vector<Dimension>(points.front(), *(points.begin() + 1), base_value);
        }
        else
        {
            move_along_vector<Dimension>(points.back(), *(points.rbegin() + 1), base_value);
        }

        std::copy(points.begin(), points.end(), std::back_inserter(extremes));

        get_intruders(ring, left, right, extremes, intruders, strategy);

        return true;
    }
};





}} // namespace detail::extreme_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    std::size_t Dimension,
    typename GeometryTag = typename tag<Geometry>::type
>
struct extreme_points
{};


template<typename Ring, std::size_t Dimension>
struct extreme_points<Ring, Dimension, ring_tag>
    : detail::extreme_points::extreme_points_on_ring<Ring, Dimension>
{};


template<typename Polygon, std::size_t Dimension>
struct extreme_points<Polygon, Dimension, polygon_tag>
{
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(Polygon const& polygon, Extremes& extremes, Intruders& intruders,
                             SideStrategy const& strategy)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;
        typedef detail::extreme_points::extreme_points_on_ring
            <
                ring_type, Dimension
            > ring_implementation;

        if (! ring_implementation::apply(geometry::exterior_ring(polygon),
                                         extremes, intruders, strategy))
        {
            return false;
        }

        // For a polygon, its interior rings can contain intruders
        typename interior_return_type<Polygon const>::type
            rings = interior_rings(polygon);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            ring_implementation::get_intruders(*it, extremes,  intruders, strategy);
        }

        return true;
    }
};

template<typename Box>
struct extreme_points<Box, 1, box_tag>
{
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(Box const& box, Extremes& extremes, Intruders& ,
                             SideStrategy const& )
    {
        extremes.resize(4);
        geometry::detail::assign_box_corners_oriented<false>(box, extremes);
        // ll,ul,ur,lr, contains too exactly the right info
        return true;
    }
};

template<typename Box>
struct extreme_points<Box, 0, box_tag>
{
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(Box const& box, Extremes& extremes, Intruders& ,
                             SideStrategy const& )
    {
        extremes.resize(4);
        geometry::detail::assign_box_corners_oriented<false>(box, extremes);
        // ll,ul,ur,lr, rotate one to start with UL and end with LL
        std::rotate(extremes.begin(), extremes.begin() + 1, extremes.end());
        return true;
    }
};

template<typename MultiPolygon, std::size_t Dimension>
struct extreme_points<MultiPolygon, Dimension, multi_polygon_tag>
{
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(MultiPolygon const& multi, Extremes& extremes,
                             Intruders& intruders, SideStrategy const& strategy)
    {
        // Get one for the very first polygon, that is (for the moment) enough.
        // It is not guaranteed the "extreme" then, but for the current purpose
        // (point_on_surface) it can just be this point.
        if (boost::size(multi) >= 1)
        {
            return extreme_points
                <
                    typename boost::range_value<MultiPolygon const>::type,
                    Dimension,
                    polygon_tag
                >::apply(*boost::begin(multi), extremes, intruders, strategy);
        }

        return false;
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Returns extreme points (for Edge=1 in dimension 1, so the top,
       for Edge=0 in dimension 0, the right side)
\note We could specify a strategy (less/greater) to get bottom/left side too. However, until now we don't need that.
 */
template
<
    std::size_t Edge,
    typename Geometry,
    typename Extremes,
    typename Intruders,
    typename SideStrategy
>
inline bool extreme_points(Geometry const& geometry,
                           Extremes& extremes,
                           Intruders& intruders,
                           SideStrategy const& strategy)
{
    concepts::check<Geometry const>();

    // Extremes is not required to follow a geometry concept (but it should support an output iterator),
    // but its elements should fulfil the point-concept
    concepts::check<typename boost::range_value<Extremes>::type>();

    // Intruders should contain collections which value type is point-concept
    // Extremes might be anything (supporting an output iterator), but its elements should fulfil the point-concept
    concepts::check
        <
            typename boost::range_value
                <
                    typename boost::range_value<Intruders>::type
                >::type
            const
        >();

    return dispatch::extreme_points
            <
                Geometry,
                Edge
            >::apply(geometry, extremes, intruders, strategy);
}


template
<
    std::size_t Edge,
    typename Geometry,
    typename Extremes,
    typename Intruders
>
inline bool extreme_points(Geometry const& geometry,
                           Extremes& extremes,
                           Intruders& intruders)
{
    typedef typename strategy::side::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type strategy_type;

    return geometry::extreme_points<Edge>(geometry,extremes, intruders, strategy_type());
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXTREME_POINTS_HPP

/* extreme_points.hpp
IZUGfp84toxIVCSUFpKljSpxSNTWy44o3iX9FctQKIYlwxUrkiiOJYMVy5UpliWjFSvXlgFY5GEFbU6UJZaX9FmEYVUGl+yMGsSdSRU1qrBqScvCLRiRzDIy4G5mBOGmRWJmhUZo5aGXCZvVaRRs2Y9/Y2UxjYd+NrcWEiBymzSpf5vJfnIyfl/JL3eXlyt8FTR+PTsydkuqfh87Pm7ll31lFH5ZeL5zFRc5j4MUa5nJoyUTF6q0lTWTVIcLNFUyL4o9Knsqci9qfz5RX31Dd36w3Tm7u0l2D2vdPm4pR/VOL0gr0jvEm+WrV0mu+E4vf7kyekrEfrtMbefmegNDflxfL30bdn+6QQ6NUntJUy7N/aasshuT1JXVGSuokJObEVVUwiIoRVhUChIsFERgy/Iiy/CoKP/dxHe+ptoGuN7ivzB2FHd3uljfepPDf31U4tKNPB/qvaDHy4h1OB2Nm9NJaExciNPji4bliYUF6WVd1sfQM4sOjJI8EqW8ZOAIvvaJY8nvwAhgBzBE9qAGUIJIM0Azx+FkLeb6oIKQtDUTgb0JJg4WkpDnEAv+0F5DBOgiFNuZC2OtxJIHSEFX1LsUPerw3MbykuHeXFyDPDGdG61eJBsOj2m2q45DUwmtDLVjxasDOtzomHZDmGZkGa6uWyuMYcJaXFbSPyGdFzix496zl3YuZ9qcPDDwNaYO1Oi2TzJzBTuFVbJZ9H8GPengIum7iBhpoRcVPEhMJ0a42nvwUGbLt0eOUtCz59uiu5YGNkMad751gEnLmG0Mz7vUMZ0jo9ORDQCGvyKuUgUuIsY6tmdGexltGwTnItIl7ukNtUNclyi5nwyNclyWh5githLyHkO7EvYcORSptyHc46c+JmU0Zo60aMCmz8edw4wGpTdiMAYTPKIzulMYTUy71zsqbk2tqfOt5MIaZC8e6LMuZMF2lgy0W8VzALvImF2so6VMGWonYkRAs5zS1oRLcaa66qAr27OcATFK2csoXHUZzUhnLSaAPAERuKF3phaiQ5R3YmxDf/OHbQ0fMAUbJXbrLOnALJAmXR9cqvavFpmvBhHCeAtwr533uNtpHzTTploHNSLJObeXg4CT7Jw7TFOzk9yLp3Kt9COGo3do0yPMiHHPHruU27EfWNPyVAaEID47nKfgN0WUJUnlHsyjC0drcyqH9PypOFzAxmYOcYuZtCbcpx/SqlHQZ2hgze+x7DIVcEVoJeAVwjEh1Q5+C5+UiJiGK1/VVpP+kj79E7P/EOH2BmwPplZBIxSKIGZXrIbNGWSkoiYZLRwaJ30hWShyhpDAo1PeOLxvbSJt2gEjEBpHLYExLxEa/GfgogXOHARYs8s6hR/+gcOrtwVuv88DkXST41EfTUV/Rjg7SA26goj7tEvVALwX0cGRQYuQPRohI3F64lzTseb8CgnbkO00dWbcGCRRf4ZCB3lC8LG04HKjpkRdwzR3bR3gSTLMnWTYGZYkettMl8Feh6rcBHvqvNjS5nzW/iRpgSVXeo9xOrzIEk1jZjnDZj+Dw+Me8CRonkUra/0Ek7aBWrSDJGdfsol2145klb5o+Yj19A8mC357ErGiGpY1UpXJC8yX1o8COBwJyIXBLP8dKYEMmSHp4Pfj5kfRlNMvMilHR9o8elZZ8zPkfaz6nb6sVi7CLzkL7u4x7tC6Tk5NvlxYYGcXF7i3YNbG8TzZHNlQvI4uThAvAfcJYT3zE+S4RE26MosD4jmCGtpDaCgCUuRXYGybeiUOrSCpWE16PLr2kPN3WNyy9OOHwopKAOUKlQyZfbxS5Y0lZ7hlCfJJGEt20JQNawtHeKVcliMm9keQ9F/tx9Sxy48iAFpBxkQmGpb03OT69N7QYQsTooRIcUKo4NS4L6Ea4qMBqTFnYDWoCtvHBEv3UMtLFNMaCbFSBDp7Xdgy0dK49V7Hi9tQWQImH8btWAPFaY0exwi9KeWMVbxs74UBt0yeg44HjAnRdB7BriFn63ivhiS3cMuZ3YmPDN2DrNPQArGwVKOMxs9o63/T+dVCsTHhHY5I+AOhqfFOR8akidOM7f0sAJUHsqkbO1mPrs2Ow1rtI48ahxlTq4Jvug9C6PZo4paJ3mX08Ls4bSbzdkZVVAdUCeUa6uPQL+GERCqmYSKy+KCjCVHjM+iBvlVSDJdGOsEfMDUWqpmeP+kiAY7CzQqo46QadnCMHHYy5pd7OEaiexlwIC0coVTJRYThCKd2xfCpnm0lZT5juLS/dsVRTay/doiquJwBUzzZyLMATiD2cKdGTIi4AlmDHP3Uvzpi6rC1rKd2xnHpog0cOnb1KhRbhStOcInV5JnF81/BEqwTNpyhloII4TV/EoUdjKsBdP6TRDUrqHLCaOJY/qLIR1LegDyrW+66OQzFOswb3J/bYzazoyUvxqmyYbCckKsrrCFfWpYmtwGqoMR9VqZWLsy4mOZ8EEEFjVQwAGJmgY+Q9Bkog0zfwS/nAQnnATL/fuWoAIDy8HYgfMIFgD3OKyAYW0MsCSH9o1HqP+AoT/delmaQOECVX+xchkbFzLxUhTCAES4/50Scq60swcEoC3s2gD8eDKQSN5t0nI8XIY9oTGqe6FEGLscsRFEtXiMgP65/ZshNSQDrzL/SK1opBMtcAPaVF9ovP2RXxUMAPrByPjcUffL85EGej66qHfATbNBtGoAMgR+XG1xLj9kxoxDbTBrFvzS7eXTGb5ZnBGI4TFS3Yq5+jVPlwpEUe7YjcupFvmYi4UK2cQp6nSi9Hel3UWxoHVnf4CzPScVMC8GMAOkdGdpjDUKlxr+ckWfuIw3QRI2jnQWGSmVQ0TfovPeX6nL4Q7A3zCa4kWn/Kt0KzqkSpkcXtplQ0/gwoI2eFkhXNosblVcXgIxuf4K/U2aODHpJIpAxOH1GBoMNszkRdITGn1HlTkXci/iWRTBb050LhwulQrhBt4tDTzaU8VgwM4wxGcJYnoxRqkZIJH5r1WAlmW1rE+73JE+eKV8hnHQbLUzkRO44mz+ZJXJnjqRAcmuZUipYSS93NpOkQDDIkEIjAC14oNhUMBgqj1/YF6J/Ja/gYv//EHZPPcLwUAKAv7Ft27Zt23rHtm3btm3btm3bntnZ/QN78aTpSXvRnCY9vWg6O11GVSAQZHBdRgf5TvtGV0k9u0Qo2Ihyd4FpdO6hFK/J39STpzEt7Y5wIc3unJKxqepbvLeGZHdG6uZExc0J74wGcS0B1nkykAzVX028mu1Hxpb/QN2Bs4Xp70GUu0++UCmdXM7G1z1voFjBRjlrQ8qh9i0iaB+2E8ecejzGgqRD8XQCjFwKwSJeQQfOieQPnQobvW5WIZUsUVzWYZdZDLFxIAfSZ0lCLkn9RIxGrAlLYh7U6DGowcIJnIPpnyElxktVMnnG2YHLchoZARXqWuJP9yiQkjz2r3kKYkmbCXsRjgVtKMSfsjCus6EvsfjfOCW7ERNljNcCNzJKapSTyn98VSFILfz5gNLOkKIJEWLRx9/lHZobThN40uhwzpKBuyppF04Kd0KykIK8kkGtxgUOlHsWQ4vilBYhghrEmUcV+JAWzt2yxwEvE9JiROlluhbCJM1+b1byVLDOyCDeE/GPU5AVKZnyHEUmAXua8WUJ0nbaDBWBSyKJB8EZd2DdCiY94YIyxIGbDwoItDQWit170ojqNKiYSZHYSrAwhBeHkUZ4ZhWz0uwxj43cxnl1oGeykTdguRD9FaUZXSLMoWcygYFuEXSqGeTQ+lXqZ1IAXUXITiK8uxLMI4jGjUmdHM/DaBTE8LCIUGASxQ4yv/jaKgAVnP5H+kASCuquCeNI8WOP/XIqTkzWIGzvgRnEVZwSqOniKCDSGIwiLI4I5Zto5gFCCfiVuJHE8ZDZFP9hqQRGX2hAmQq53IEhBDvcq797Kelb7Mug7cuy5jCuk+FuJVqSAjbcyHSl7kUuw8IHxGUE5pNDiP/nXhKiHPihM7FvaxFqcmJ4qlKiTg97X8pZ1YXnYEfcRAh3pei/3MxPECAjSDAhb68C07VxYgdgLQlvWcHPaMaDti2H3q1xb6O1mk7qbURQi5hqzlorBb+DjzT/j76NqZxTrRU6W7ZmoyWDBxdaT8KvMA7Wdsn67FT+sXXvyEDEcg97xy7SjknhJABUPKapaJMabTr38Gc0dxBi2CJBA+odB1lXvZPczrb5HMqoWbFeEWVPAws7L4gHYDi1D8z8rBvyiJku61OcF8e0G5LnBKYmStgUBfwYX1xPIWDVVDD0O7/DnD1w2c6Bz821KgsklfTmCi5A6r/mZCGUbjufAjtdSIXr6Qo+C24AXK3QqX04U5KLFNufrI5WIvBRnOAkHeBuC/u3Qo/CvSiSsrXIE+kVk3JmvkusCMppIeuEiSYiCLI8Qql8AVZSeAo2hI3FobfCC4N9KxErGO5pNBZU4xnriX29nbkk+SUVfG0K3PV6yGQlwwsRcosieEwEfBF/Zcn5dxr2Bvk4cQDtAhVYYd3JoYlceU0UrjVCgWkGlW4Rkm0uJEldYAezZcC5eggP2rE6AAgK6O/00B3hG7o6DfanLLQVii88L1BKNCqhmvkEqgKQC9+TiV/fkwzfJA6ScZBf5Z/ziS4+dDbwJKkSIn3Sw5GCAp2rxvmseORMXeX1EgU1ibIhk5mD3wvINT3fjKuR2u3O+u01Gyu2FqzN6OsRF8P/v/uDpEX+DlR4c4NqoQK33Di4x5JvSevsYnmrW1chBn8D6eTqWMilgMO9CXN+sL/TmR0c8XrFPrQ4fdEi6eTaiCpdSkjx0uHZodjq1qYBeTW7nXVjOz/1S6p5opmimZLmGxb1xcAE9h574bvtqektBeiBrecgJbq/Os3bzTs9rs3ykBmsAVLZgbFEGYuyRPnaDoJ7Y3Nzs7NAg6dnE+7znB7Zrrf9MSK2GKuUXXtTr8V1tWnkqMZTos7jvVUqXWJb4BGHhePdIR0tpUnv3v81LPCyiTYKXRgq3xoPxu0F2oZbJ0atjmyam4XdTW7ff/D+Mm4vMYk6NETTHIspsO2lZCpZBJxROmX9IZNtDsrGEXJsrJsjO/2VuZtUiH7KhvOg5630oK6d4F3mTS1U7fXyEehkaXqv3r4jWK192uNQXPwQ/ZjokWRaHd5RfdqGMXjr9nTTHKu7R0T47ogH2Xgak+tE5jrb83nyrKPm7GB3PBDDF557RML3sWhYm9RVfxWOp4uJxuRxVdfJxcO6H0PAsSsSM1ljvTvHVWa83DImBxvbRd9EePz4vAnHu+XqKJh2fZ/J93v1+V6a8LLdc5tOfr10zsPTOlJEe9d9e5x/o27RWk1FVZ7sSTGzGEJotlrTnZnJEteRDGm3XbK18jZMRkZGORhKF66RwW6FAetDAWunPpUgkoQ2I66Hx9ZKpeo6ESA4UO2zgm9Bj6JuZynQlwFgTRclIfm2fRlCRqfDyUzqgX5T6pGAti24MxB5cfZRgstaAdXeS9W+e7F/oyGwLW3j2mjgDuldZuOklqXqyMJNRBqbF8roS04Sq2Jjk3IH5KoMUuQ7P8fxb/e0W2/zoOc4WEWom9GjCpmr5gJRmfG75IztYuM75XkdLpa3w9Didg+tx90qlji1CHxccmcI1P61xDkUF2+91Wi1P+B58YIOL7Y55oiszXuM11Vp+c06EDaHr5l0SgczN/7D5vLow/aCZzWH2usgfV3XvTR393GmYvmzUNb73uHfdv/pbdj3079cDFu0yZbDBT8aq5e7UFZfpZ2eXgTGAqFPtoMvoAmh2OAi38bjMc+b4h4xQtiXrQzex1NPnMaEm9mO8/Q8hVmcjK/+7w+5wOSGcCyaWbqLNIbL0/VEuo/rtBUW+186vp4vN4HUTN7aq3TcZ91VgshVdd+3E4OLPLhNnLeYTAbP1espd9RttXBfoc0O2yuubtxfg+8ihkJa7xbyJiadt9EbrXRvHTJpPIHXPK8xmMzY1aa24r89HHldWIB0aKZXwdXe2S1XGpdU1D4fmUojLh7mWC0mViXm9fRwxN5Btxy6NT8+uuoe6q2srfgQ4A5lUJCIRq0h/Vr4wblaa7o5WJSa0qFZXm2t4UTpWm09LrOy3PKLUK1+zLoXe90xUU3VtFxdyFVelgrbravuvfZjMfq5ilIrY06bfTeI5tnZw8T3cV1d/5Pb8/xI4OJJ2kz74J81e8NLwb34nA2XqThL57vvT7LBhaV73cX1YzAwImQrh9nBo/xrf3qv4fjRxufp/rbNhqa70fEevKNyU4oLnelUIqWsVPcL1Mnpa4NN/W1wvemoSl0U6m6lea7EvPID0N302JQfqsTxcn+T2XH7we3z1kI3e+VJbnr3c/VjedqdjcBhLTHBtdGitTrDebQt5Mn6qD20ExNJ5ctFf3NU87Kdgx33km44F8pWysoj1fs6mArk4a3abnhVNt19iryVtUn/OXq74NPm+6ndKuaDvXv+mAGgFInL9yW50qDWs7n9Ljj4JgfpE07nNqy2Xe9yq2UdcY/R3HCjpxx1o4YyKOp+ENmZGYy5vwQTnECe70f1b0X+V5wtq9nBuzwKU78iLLac8FdacIu7PrQkKI8RylOBrf1ic3AUCjFAMDFkQcj9JVYQMBvX9XX2lPA1+G3x8mab+SjcVRWl0/sIz6XtKH9sWG/NZpOz82IONLe2KpHTl89lzi5SeeFuJwQi0xJs6tp+HP5TTrpo0XcsZeXGzMpr4WEznkJOGpz9YyEPgkrXncljKLgfz+t5h6xRrofFqPkwunT37WipicpTEo777hCh1jQj98t6jMFZMZd3IU9qhN0i+Vns6X68hVeX20Vdd8H9Zufoc8V0+eZc96mUd+edTauwGozr/alrBVOCQirxGukgIZVOoiNTlWL9HZiUkNZ8XvEzwf0lqdj+5cyISyOvWD3/eDL11yc4AbHw2p+hVYFRRmEwq9R1btkVLxm+26k8uzlWExHLtIP4nC+k4ChfWmvyUAXaMVvJ0NBMbbLW67sDCApD5lOpOxvwmElfQtFK0WsrYFgoXHk6UjZM60qx6IU3h6jA8MAebGWLG65n57AQjRq32cheWtugwfuqoD2/KXAhC2wilDqtF5+Ds9/Hc2y5G8cCrxef1Hx8geQx4Trxnm+yMPHgSqkQCXUoQ9FEb6RtZ+Nw1vZbDiDPyP1Uw3g0V6Nl/MXbbbAg3P02RLbNsD8+fNp9FKxL7dvR2sDjWmpJSokzl+7a/p/SdKol77gWwpK76GSWvhTn6F3r19OdI9OIJqzX4vH4eE9js44ctMSnW87txhcR2eq3x0cKWI/PQSdaSg6tdAT510/qLRLXT8d3pLeY63S218OWTiMj7Pmk7ibH3QPULteme7IWKPCNwOPUyzND9pdr9iJvNqS9S5lsPiHkEKAPzOXFXDHDlfwpJOy3UmtMBvfEc9560UnnWvbtwTqFhUzZZkbKvM217QN+396Flmtrzs9vVcdPxTJPWdLlkBkAy69tRLz9s8aNr7vwPFTB7zjCMInC91gPdNOHAs+id25Ve+fZylAFzciIT0t+8pdSsJYNr5zz49Ue90z8GkOWVCWb3ymmzat9RR6I6UftfyOGc4fhqvcxXMX2O7OmUb2+Fy+bt+u8BtbDx5NArVOenKWDszu9T5S6
*/