// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/within.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>


namespace boost { namespace geometry { namespace strategy
{

namespace within
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct within_coord
{
    template <typename Value1, typename Value2>
    static inline bool apply(Value1 const& value, Value2 const& min_value, Value2 const& max_value)
    {
        return value > min_value && value < max_value;
    }
};

struct covered_by_coord
{
    template <typename Value1, typename Value2>
    static inline bool apply(Value1 const& value, Value2 const& min_value, Value2 const& max_value)
    {
        return value >= min_value && value <= max_value;
    }
};

template <typename Geometry, std::size_t Dimension, typename CSTag>
struct within_range
    : within_coord
{};


template <typename Geometry, std::size_t Dimension, typename CSTag>
struct covered_by_range
    : covered_by_coord
{};


// NOTE: the result would be the same if instead of structs defined below
// the above xxx_range were used with the following arguments:
// (min_value + diff_min, min_value, max_value)
struct within_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const& diff_min, CalcT const& min_value, CalcT const& max_value)
    {
        CalcT const c0 = 0;
        return diff_min > c0
            && (min_value + diff_min < max_value
             /*|| max_value - diff_min > min_value*/);
    }
};

struct covered_by_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const& diff_min, CalcT const& min_value, CalcT const& max_value)
    {
        return min_value + diff_min <= max_value
            /*|| max_value - diff_min >= min_value*/;
    }
};


template <typename Geometry,
          typename CoordCheck,
          typename DiffCheck>
struct longitude_range
{
    template <typename Value1, typename Value2>
    static inline bool apply(Value1 const& value, Value2 const& min_value, Value2 const& max_value)
    {
        typedef typename select_most_precise
            <
                Value1, Value2
            >::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Geometry>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        if (CoordCheck::apply(value, min_value, max_value))
        {
            return true;
        }

        // min <= max <=> diff >= 0
        calc_t const diff_ing = max_value - min_value;

        // if containing covers the whole globe it contains all
        if (diff_ing >= constants::period())
        {
            return true;
        }

        // calculate positive longitude translation with min_value as origin
        calc_t const diff_min = math::longitude_distance_unsigned<units_t, calc_t>(min_value, value);

        return DiffCheck::template apply<calc_t>(diff_min, min_value, max_value);
    }
};


// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Geometry>
struct within_range<Geometry, 0, spherical_tag>
    : longitude_range<Geometry, within_coord, within_longitude_diff>
{};


template <typename Geometry>
struct covered_by_range<Geometry, 0, spherical_tag>
    : longitude_range<Geometry, covered_by_coord, covered_by_longitude_diff>
{};


template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag, // cartesian_tag or spherical_tag
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct relate_point_box_loop
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        if (! SubStrategy<Point, Dimension, CSTag>::apply(get<Dimension>(point),
                    get<min_corner, Dimension>(box),
                    get<max_corner, Dimension>(box))
            )
        {
            return false;
        }

        return relate_point_box_loop
            <
                SubStrategy,
                CSTag,
                Dimension + 1, DimensionCount
            >::apply(point, box);
    }
};


template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag,
    std::size_t DimensionCount
>
struct relate_point_box_loop<SubStrategy, CSTag, DimensionCount, DimensionCount>
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& , Box const& )
    {
        return true;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

struct cartesian_point_box
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return detail::relate_point_box_loop
            <
                detail::within_range,
                cartesian_tag,
                0, dimension<Point>::value
            >::apply(point, box);
    }
};

struct spherical_point_box
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return detail::relate_point_box_loop
            <
                detail::within_range,
                spherical_tag,
                0, dimension<Point>::value
            >::apply(point, box);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Point, typename Box>
struct default_strategy
    <
        Point, Box,
        point_tag, box_tag,
        pointlike_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef within::cartesian_point_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Point, typename Box>
struct default_strategy
    <
        Point, Box,
        point_tag, box_tag,
        pointlike_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef within::spherical_point_box type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

} // namespace within

namespace covered_by
{

struct cartesian_point_box
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return within::detail::relate_point_box_loop
            <
                within::detail::covered_by_range,
                cartesian_tag,
                0, dimension<Point>::value
            >::apply(point, box);
    }
};

struct spherical_point_box
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return within::detail::relate_point_box_loop
            <
                within::detail::covered_by_range,
                spherical_tag,
                0, dimension<Point>::value
            >::apply(point, box);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{


template <typename Point, typename Box>
struct default_strategy
    <
        Point, Box,
        point_tag, box_tag,
        pointlike_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef covered_by::cartesian_point_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Point, typename Box>
struct default_strategy
    <
        Point, Box,
        point_tag, box_tag,
        pointlike_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef covered_by::spherical_point_box type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


} // namespace covered_by


}}} // namespace boost::geometry::strategy


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_BOX_HPP

/* point_in_box.hpp
I53reRzpD6U9znGVcxhDM4fxvBsfM35kg2Ir/mSekeUrFjsGe/U8mWOPxJVmEtPK8r2jy2jE3aTB4clQxkzrc3zPJc5hjLTYZ5mEsT0zx5jM/myI6HOoN+cNzweI3ZabwnIfkOKyRwaUsBHfz1xulc7opB6XE/d3LG/Gc6vyRX/2CNaj4/xXjHk+TrR8q34QXc7UU2LLNz5vGFspLGd8xjNaPshYzi7djGk5JOtIjn/P81my1ru1YZ5LpbQskiWR/TZzntFtqcb8qmfBJPrBeKOZY5QuLhut99mfET80X/SPT80VXecSTH+G7pa8sc9EC62DnWDIgF7J3RIS/759ILKdXikbHf8x45kctTNfizY9kW309IfRbbQ02/NrRucP4wGE/TR/2E9rf5RleQcOTEkMwwdmLPffW6+Ojn+f+UbHvR6RsRgN66sva3RMg1XRZcwcq/TP0WcLJKb2HpiQUV+rZM4vOhZqxviKOz/KuTxWhuu87aPbz9+FOvtx9vIID7IJq/H3tmH1c1jvxtnWu0LMeIo5zDdmPY/dTmF/Dr9P6JMSedcw1uhYZTn3hOh9V40+OVqe8ceWZ2bZ9Q3TLY19bom+C0fb0/JM4jLT1N6aWXa9ElMzKlL/PgM0UEMzFvRXlN/ILM9t7J05ZrL3y/JeZWPGU46dT3g+QFi/FIc7hfwL9ah2zHaKTlsxh7ocW+d6D/TOoc04dp8ssS2UY7b2fUYoxzPDcakiV5im6KeZ5RhduC7q9MDk494PR2bdD3NYzzB+euw6ZWvfEgqGZ9OENv2qjDb9s8xlS0lMjRmzOKPkj7utzdpeVMm6PJH6EpfTMx9DHY+d1rE69njkO7z0/96RsrJBVvrH/phlz2yZu0fGCTfJLz5rvELW5Qnleez+l3NdqZ1ZR6Ozy7q8nQtFZ1LWwhULro4s+I6M5Q2PhXEY7ZbcP/2YdjzLm/Ec/03R98n8ebafM57r/2Dk39Hn4Wc+N/+e8FrW5+b7Mu2Y5+YPyXytQfrPAzJ/rp/+c2L4OeO5+p3DzxnP1b8q/JzxXP2WmT+fl7HtGXveFxc73mxMOVYsHF35U8IxrijPLuM8+/Oj5Ri2ecrgpKSByamJCb/m+Dbyn3R8i7QJ7Xbm3LbODutwZVj31hnPyY9OH/uMtejgvl0yRudOSuxxHHUi9nn5fvZy5vloTHk+Hga8TAhj5HfhYeVZe1cOy9LT54mU3gr0eMbq1WZn2/+H/pXz0BHHnIcqz1947l18tvPrF3dlnrem/3ztl7Hn2w3D+jYPA7+1CH0mmvIW09T+KmN9w1p2Ue4JPpPe8M95XlRGXbcUXuvha+TocubfY77h9azLWTV8YhubJ3rcGMW1kePG3szljBx/+zvT7tYrUfuWMOxXb5OM8ZIrp5djzDMjwj45IPuY/TmW/fboMsV1DWXfdH/GZ7Toz1W+zvkzW9f0/0e+14qu40Z65rCL5DmuY+/EbipNqHtD+bfGzb/gO++R7TkGI7Kt++ij5xRWL6x7Ds+0DfUu27M2Um7ok5SxbNG/7Xi0XEIdiG3HIn/fKsuxrseNCaGdj5bT2d/EluNdf84st9jndxaPrmx6XzN+zfTnDRzKm2187Rxaj+NoCyPl1+2HmPI7rrHCI/v4eZl1J3r9Iedx+2Pr+u7ioR7kDvWAkfUp+mP29clsgY6rDiz+6fjqwNF1OKbtyeGZmrHPlh9dIjrT1VJOlss6yz7lSPq8M45FPfonhees/8L+WTvLMSj2+Z/dstXP7unLVvToZwHldHRs8rg8//qxyf/VY5DnPKb4rx+b/L9lrPGcx3r/62ON5zym+K8fIzznMcv/+tjtOY9Z/uvHGv9rY6s=
*/