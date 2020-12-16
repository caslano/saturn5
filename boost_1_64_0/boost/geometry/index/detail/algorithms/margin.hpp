// Boost.Geometry Index
//
// n-dimensional box's margin value (hypersurface), 2d perimeter, 3d surface, etc...
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MARGIN_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MARGIN_HPP

// WARNING! comparable_margin() will work only if the same Geometries are compared
// so it shouldn't be used in the case of Variants!

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename Box>
struct default_margin_result
{
    typedef typename select_most_precise<
        typename coordinate_type<Box>::type,
        long double
    >::type type;
};

//template <typename Box,
//          std::size_t CurrentDimension,
//          std::size_t EdgeDimension = dimension<Box>::value>
//struct margin_for_each_edge
//{
//    BOOST_STATIC_ASSERT(0 < CurrentDimension);
//    BOOST_STATIC_ASSERT(0 < EdgeDimension);
//
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return margin_for_each_edge<Box, CurrentDimension, EdgeDimension - 1>::apply(b) *
//            ( geometry::get<max_corner, EdgeDimension - 1>(b) - geometry::get<min_corner, EdgeDimension - 1>(b) );
//    }
//};
//
//template <typename Box, std::size_t CurrentDimension>
//struct margin_for_each_edge<Box, CurrentDimension, CurrentDimension>
//{
//    BOOST_STATIC_ASSERT(0 < CurrentDimension);
//
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return margin_for_each_edge<Box, CurrentDimension, CurrentDimension - 1>::apply(b);
//    }
//};
//
//template <typename Box, std::size_t CurrentDimension>
//struct margin_for_each_edge<Box, CurrentDimension, 1>
//{
//    BOOST_STATIC_ASSERT(0 < CurrentDimension);
//
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return geometry::get<max_corner, 0>(b) - geometry::get<min_corner, 0>(b);
//    }
//};
//
//template <typename Box>
//struct margin_for_each_edge<Box, 1, 1>
//{
//    static inline typename default_margin_result<Box>::type apply(Box const& /*b*/)
//    {
//        return 1;
//    }
//};
//
//template <typename Box,
//          std::size_t CurrentDimension = dimension<Box>::value>
//struct margin_for_each_dimension
//{
//    BOOST_STATIC_ASSERT(0 < CurrentDimension);
//
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return margin_for_each_dimension<Box, CurrentDimension - 1>::apply(b) +
//            margin_for_each_edge<Box, CurrentDimension>::apply(b);
//    }
//};
//
//template <typename Box>
//struct margin_for_each_dimension<Box, 1>
//{
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return margin_for_each_edge<Box, 1>::apply(b);
//    }
//};

// TODO - test if this definition of margin is ok for Dimension > 2
// Now it's sum of edges lengths
// maybe margin_for_each_dimension should be used to get more or less hypersurface?

template <typename Box,
          std::size_t CurrentDimension = dimension<Box>::value>
struct simple_margin_for_each_dimension
{
    BOOST_STATIC_ASSERT(0 < CurrentDimension);

    static inline typename default_margin_result<Box>::type apply(Box const& b)
    {
        return simple_margin_for_each_dimension<Box, CurrentDimension - 1>::apply(b) +
            geometry::get<max_corner, CurrentDimension - 1>(b) - geometry::get<min_corner, CurrentDimension - 1>(b);
    }
};

template <typename Box>
struct simple_margin_for_each_dimension<Box, 1>
{
    static inline typename default_margin_result<Box>::type apply(Box const& b)
    {
        return geometry::get<max_corner, 0>(b) - geometry::get<min_corner, 0>(b);
    }
};

namespace dispatch {

template <typename Geometry, typename Tag>
struct comparable_margin
{
    BOOST_MPL_ASSERT_MSG(false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY, (Geometry, Tag));
};

template <typename Geometry>
struct comparable_margin<Geometry, point_tag>
{
    typedef typename default_margin_result<Geometry>::type result_type;

    static inline result_type apply(Geometry const& ) { return 0; }
};

template <typename Box>
struct comparable_margin<Box, box_tag>
{
    typedef typename default_margin_result<Box>::type result_type;

    static inline result_type apply(Box const& g)
    {
        //return detail::margin_for_each_dimension<Box>::apply(g);
        return detail::simple_margin_for_each_dimension<Box>::apply(g);
    }
};

} // namespace dispatch

template <typename Geometry>
typename default_margin_result<Geometry>::type comparable_margin(Geometry const& g)
{
    return dispatch::comparable_margin<
        Geometry,
        typename tag<Geometry>::type
    >::apply(g);
}

//template <typename Box>
//typename default_margin_result<Box>::type margin(Box const& b)
//{
//    return 2 * detail::margin_for_each_dimension<Box>::apply(b);
//}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MARGIN_HPP

/* margin.hpp
o/sp0X1Kd7fmwrwk/RKHwfOIvX7H3S34q3e3PiL7P+nuVh3M3gbubtUT7VG6u7UE5m3r7paEm9doe7rW/5+5v7XX37z7W2+cZLa7x+R+X7K5XrbXqZ+tF+TL60J5UoTajwrdr6/HvU1g2jaubUBH8s9uoOzkhfaeNGeGTmVZ175mUp/HfeJE68yQKSs9zy+qeFzmnzOIdjjLbvGmmmdn9yLur/G5nn50rifR9ewsaKdZtK3daeWcUTPuQdD5H4771n2sG8Vr5tVX3Jbs5LgbRwTqakqA1TNrjY6yNoD9lzJ+UknbpjBvN3kH7SDZ30FayH0ecFsBl8k4rzUw2JXaAx7n4ZYX2Rd6hsBN6YP5vtHp5H8hlZHvc2hMh+wNjQE/p2/vJ95uco9/OLX9qcT7kDnGTrHkCp1zm0X+aaLb+CsjLPR8C3ke9QN9r6Y2wN87HzRfEs0+mkf9JZvCRDtMr/9JuOdQuFlyfm6FYYeEfZCnRh/5J0TszzDrYG6HuQPmTrbnw6yHuSuic1+xKTd1dT0XwHY5D6yUi2OvmwHN4zoxx7p/2S28XNTNpawsI5XqXC704/7uxHu+pwAuXFY4vOxGy0Y6sIJoU9S85LHYWeTX3zUvJ5B/mpSLIrKnyxnaDZzG+RGlq2YM55KOI9/kM/ycjgGrr3ak46IB+YMX9AtLSm06PtbNLPMj4CL9eBPS8TinYyvRAUt3HySs5+Fvf1+2VXfex3NJ2/fD0vbrsLS9+wTS1t6nrHzbJDSStBNjAjqWgu5WWlZWL+CmyZA1Dn6Y69fa7o4ybR95h6qK7JusfRjEj9K6ZqbVxwtPTzkPNIfsWzzXenxUz2/PNnjwYOfsCjnTnwksJ7r7cao/hft1K6xu9K1rUjktbXsxW8l/Ntq7TPxX8hKRo3yUM0ZlRPug5w+eeJqfjkGCrHoLZ/GMtbbYfp7wN6lymOYJ0GwyaBLLfNF9fAnoX+SczZ9TyRC9FWY96DcTffBFx1tYTBPzttCsCKehsHmsck9Ec9rYlKgeTj0PyE+UCcpPmeciv+BG+SXv6yA/4Cb5ofT1G/fL+ovoBOsMn8IeVhkKlNVUVmB3YUGZNTZp79SrwfRxyrnLjkQXqhvjVTpzzzp0/q/KuLZZhKGU3CEOo8+K4JymNbZpb7tDJOcVyM2UJwduWXJmTvm2UseOHzADv5XX46/m9CmW9MH4qQJF1pE2st/CtPmekzwt2A0afMjtNLhkUdwK3NMM/Or5u8vJvthTCk639GP9zfLtHjyGKJRvFyD8NHnzVNEryO3ipURX45lB43/2Z/3Q1ntHq4gG54jx/wL8UutxqE38E9E1fId5A9GMx9dOZTe8BEtuwyBfGtXpLSivxciT+4y61bKj4zy9RbMCNPcTTX/He0hW/duaHtl5Z65vjjI1RlOmCt3LlNS5ke/hj4EQKhl4BvA46mh+TypT9AwvvlJUVmWcbjLLxVvmvgKcpc4xfaasX4wme2+vD39fhWF9q/hXWVpdUyrjthuI7i3oi2xJNCtSTZqyBQEpY1cSzReeII/tAikmjX3c9kJP1i3F47atZB8N/85yR/Amv2nyMH/oYL0HHqF+GyvdEXekJ8VdSccjnI5TeCxxDkyCcca6l5qO0J1eMtejSUfuYz4k+mGcrhZ/qtUHQN5G3yaXeVW+U15pSw6+bxKX8t7FdCNsyFvQW+RlWeUdYbir7whPJdoxLKvFm0l7S8eQHsH3+c34xC6+WKDjvXemWw+6B4z64c900Fj28yLQb2/FGbIiziSrkkcJH5rEM70cZ6AHcd5pizO9QmwskTvzSMYBHxD9MO8AeZfWCqODlE+vrXyOF/92Uu7fI/sI70A=
*/