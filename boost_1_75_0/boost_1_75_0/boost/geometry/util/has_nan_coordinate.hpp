// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_NAN_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_NAN_COORDINATE_HPP

#include <cstddef>

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/math/special_functions/fpclassify.hpp>


namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct isnan
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return boost::math::isnan(t);
    }
};

template
<
    typename Point,
    typename Predicate,
    bool Enable,
    std::size_t I = 0,
    std::size_t N = geometry::dimension<Point>::value
>
struct has_coordinate_with_property
{
    static bool apply(Point const& point)
    {
        return Predicate::apply(geometry::get<I>(point))
            || has_coordinate_with_property
                <
                    Point, Predicate, Enable, I+1, N
                >::apply(point);
    }
};

template <typename Point, typename Predicate, std::size_t I, std::size_t N>
struct has_coordinate_with_property<Point, Predicate, false, I, N>
{
    static inline bool apply(Point const&)
    {
        return false;
    }
};

template <typename Point, typename Predicate, std::size_t N>
struct has_coordinate_with_property<Point, Predicate, true, N, N>
{
    static bool apply(Point const& )
    {
        return false;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_nan_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::isnan,
            boost::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_NAN_COORDINATE_HPP

/* has_nan_coordinate.hpp
3aXbXwMhJ1/WV52eOOPbFuHm6u7tqnFt4/DXpSLb5UXnwYigufVLtPzz0HtMV4lTwuMYj7/8Ftn+mn8ePBzchivOOgfn4hTd/CjBPge/iv2VgSBnPOuzv01ULO+GdpJI2fkm9o+LBcRJiOLPe0t+HX+DNvnmuCX6IhQdZTYNf+6pktToxTVWiBpLdUwR8xa57B43NgMQcjyNEBKcf95wS7j4vDeo15R6POy+CHzVISDTD2Jbp4qJCp1nTwfnhJMKCLVZ2at7pvAQ8AVazIUlgA/cfXnuT5L6nyTTKeq9urjKD/8Zpju5RECwm867nh/vy56SkWa/Lrwx7scaLtDymIg6Gjotz0QrXdWuCBWY932R7u1axq2Gv+WGJLpgcO1qXO5WQvV/68vkloAgZOnWBdMz9XX7rTat4T+Pbi6XjfM4Z28uhbslOQvMJVzf1z2IQWHAAZR6+EsqBPcIZUab1cvG8bo4AT1yQ9Xv9WZ/96HaJkakTWG1MHDlSDXAT8a4sDro2rjn5M0ApZ80Zz7xC1p8/+aMAMQeog+1hYnAvBsaesGUSfSbQX+4vXSv7wxh1M/R0otHT9BYKAqMCWYJS836sac5wGo7M8Ydtf5WmAZpkSbgsDSg0z2wkBzGDMc49TjPyvmjUXz1J7KYBPz2LCFHDsWntKooOuzzwvuhLfKpQ/ETdcgv5DOCRUefz45EtXsDoqPEUh/Ynd4B
*/