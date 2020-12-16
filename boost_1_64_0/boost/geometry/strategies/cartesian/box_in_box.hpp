// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2016, 2017, 2019.
// Modifications copyright (c) 2016-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
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


struct box_within_coord
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        return bing_min <= bed_min && bed_max <= bing_max // contained in containing
            && bed_min < bed_max;                         // interiors overlap
    }
};


struct box_covered_by_coord
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        return bed_min >= bing_min && bed_max <= bing_max;
    }
};


struct box_within_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const& diff_ed)
    {
        return diff_ed > CalcT(0);
    }
};

struct box_covered_by_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const&)
    {
        return true;
    }
};

template <typename Geometry,
          typename CoordCheck,
          typename InteriorCheck>
struct box_longitude_range
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        typedef typename select_most_precise
            <
                BoxContainedValue,
                BoxContainingValue
            >::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Geometry>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        if (CoordCheck::apply(bed_min, bed_max, bing_min, bing_max))
        {
            return true;
        }

        // min <= max <=> diff >= 0
        calc_t const diff_ed = bed_max - bed_min;
        calc_t const diff_ing = bing_max - bing_min;
        
        // if containing covers the whole globe it contains all
        if (diff_ing >= constants::period())
        {
            return true;
        }

        // if containing is smaller it cannot contain
        // and check interior (within vs covered_by)
        if (diff_ing < diff_ed || ! InteriorCheck::apply(diff_ed))
        {
            return false;
        }

        // calculate positive longitude translation with bing_min as origin
        calc_t const diff_min = math::longitude_distance_unsigned<units_t>(bing_min, bed_min);

        // max of contained translated into the containing origin must be lesser than max of containing
        return bing_min + diff_min + diff_ed <= bing_max
            /*|| bing_max - diff_min - diff_ed >= bing_min*/;
    }
};


template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct relate_box_box_loop
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& b_contained, Box2 const& b_containing)
    {
        assert_dimension_equal<Box1, Box2>();
        
        if (! SubStrategy<Box1, Dimension, CSTag>::apply(
                    get<min_corner, Dimension>(b_contained),
                    get<max_corner, Dimension>(b_contained),
                    get<min_corner, Dimension>(b_containing),
                    get<max_corner, Dimension>(b_containing)
                )
            )
        {
            return false;
        }

        return within::detail::relate_box_box_loop
            <
                SubStrategy, CSTag,
                Dimension + 1, DimensionCount
            >::apply(b_contained, b_containing);
    }
};

template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag,
    std::size_t DimensionCount
>
struct relate_box_box_loop<SubStrategy, CSTag, DimensionCount, DimensionCount>
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& , Box2 const& )
    {
        return true;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// for backward compatibility
template <typename Geometry, std::size_t Dimension, typename CSTag>
struct box_within_range
    : within::detail::box_within_coord
{};


template <typename Geometry, std::size_t Dimension, typename CSTag>
struct box_covered_by_range
    : within::detail::box_covered_by_coord
{};


// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Geometry>
struct box_within_range<Geometry, 0, spherical_tag>
    : within::detail::box_longitude_range
        <
            Geometry,
            within::detail::box_within_coord,
            within::detail::box_within_longitude_diff
        >
{};


template <typename Geometry>
struct box_covered_by_range<Geometry, 0, spherical_tag>
    : within::detail::box_longitude_range
        <
            Geometry,
            within::detail::box_covered_by_coord,
            within::detail::box_covered_by_longitude_diff
        >
{};


// for backward compatibility
template
<
    typename B1,
    typename B2,
    template <typename, std::size_t, typename> class SubStrategy = box_within_range
>
struct box_in_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        typedef typename tag_cast
            <
                typename geometry::cs_tag<Box1>::type,
                spherical_tag
            >::type cs_tag;

        return within::detail::relate_box_box_loop
            <
                SubStrategy, cs_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};


struct cartesian_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                box_within_range,
                cartesian_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};

struct spherical_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                box_within_range,
                spherical_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};


} // namespace within


namespace covered_by
{


struct cartesian_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                strategy::within::box_covered_by_range,
                cartesian_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};

struct spherical_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                strategy::within::box_covered_by_range,
                spherical_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};


}


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace within { namespace services
{

template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef cartesian_box_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef spherical_box_box type;
};


}} // namespace within::services

namespace covered_by { namespace services
{

template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef cartesian_box_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef spherical_box_box type;
};


}} // namespace covered_by::services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}} // namespace boost::geometry::strategy

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP

/* box_in_box.hpp
e87Dvxhw6jHj1GPFiceNWY/hpJOC1c3ghDMvTjdEcwYyrBI2UIbTTQWssBWrIIJV0AdfNJ2YgU3O4xxjwBnGjPOLFWcXN84tMZxZUrCWGZxX5mGvBpxTzDijWOG13DibxOA1U0U7+N+xgwUDvVzxBeopzIQRFecvKDNraT37SSo+xaf4FJ/iU3yKT/EpPv91z98BUEsDBBQAAAAIAEKxvEojQaLC9dsFAADQFwATAAAAYmluNjQvbGlic3NsTURkLnBkYuxdeXxU1RV+QxYCKiZhESNCiLKTmIQAAVHJMlkgmYRk2KPDZOYlGZnMDDOTAIoWl7pURG21trYureCG1rVqtaK2tVZrK1VrN2vduttWcKm1tva795773n3vTYLbH21/7/4Yvplzzj3n3HPX9969L62RUDKeiveki+uOq5szp7i1s6F4YVl5+WGji+o7NaR8TRsBOMOjaVUjNZ62eTQ3uclNbnKTm9zkJje5yU1ucpOb3PQ/lB55/wM3uclNbnKTm9zkJje5yU1ucpOb3PR/nqqztI+SXvrATW5yk5vc5CY3uclNbnKTm9zkJjf9z6VDnqzwVPN9/vzDE6Nnc8wyftvxTC2rcMR4xm+Pb9aTK1N6sj2pp/RYWtvP6B6T7ounJesA540wec2xYCgdGdQ1Rs8y6a3BLZH+gX6hK0uVHwxGI2Ftf4M2cnwOjiakyffAyk5vR6Cmzt+8qtm/NtDe4e30+uq8WtlJNaurhmAuXart/4ZRDn97oK6mpaW2pm45JJrbOphoU3Njk8bLk5nva+torWmR5cos09K2msqRmd/sW1XT0lw/rExd20qfX3vzwP5apdwjWLkziYtSZ2SxMo/WPPkJ5PfA79HQkg09h+LXbC1nvKZtH6FZUnckHkilmcqV4itUiHy5lK9Q8xSyCI7E7xx8mG9jtLx8XjcoUR5oTH5UBvlErlP+EJI/lOTHQH6Eqd+URcTHkOzhJDsBstkky2QKmcZckaeQ58nWCihPIeUZjTwekcfUDfo4khtPcpMhl6vozpE2+EfkFT0mVzuC8k60lNnMeyTZKqQyF5H8USR/L9rlYWgPwpf01oSu7cdvbjNPiwX76ffofNb8uzcnI2kd7YPTDgNtotad1INhjf3Ox+9irTsxkE5pkj9T6+7V6fdY/C7XQulkVOicgN/VWgj5uU6DtlQL66l0Mr5VE7RJoDVpoWA02h0MbQxwBQvQhkajYo4GT6Z23ob69XRfPCybkkkRLeoBlFf0s2VttYG22mXeOn/A5/UHOmr8XjR/n7+jrSXg9dXUtni1N6m/DSvbWrMmUFvjq1/dXO8XfTh7WPn6zrr2gL+mUfTDkcPK8g4baGipaexELNahT2ZTn5ySrw2XU+QR/fOgYqyv7swUl+a2jGHhMRlOrtOPeNS0tPm8gVVtLStbvTTmWPMMXdQ3RVmzqKxTRVnNnB+mqFzKWVKme3aWLGtdW2tza02jV3ADzXC5Za0on503r7K22d/hXbGyucNLY2i2M3+gpbm2o6ZD6Miz8zvhia/RV9Pq7Wxu9EGNaF/5djlfDWYQb8ALz9e2tzX7/GRvu+b02d+BYbfeW7uysb7GX6OR3BD+Y0Zq8HagAEYZOwKrvB2dzW0+tONl7FclbGXm8Tw5Vnqzj+h5nF7vbfH6vfUBVsRAi9fX6G9CGU3+Kj9rQI017RYJURdUaP/adi/vU3W1sv99wPM2t7R6/U1t9YFOVr2dmA5F32PF7mxe55XrAVFo5IB3TQGRp2NVjZw7bXxvk8nLs/FqobeutqWtbrnUbZZBxNOIlUlfUGXQs1V6Q0dba2Clr7XGBxP1ImZD8wMdXn9Nsy9Q095e39Y=
*/