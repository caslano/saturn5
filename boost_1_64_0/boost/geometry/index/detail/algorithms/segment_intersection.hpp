// Boost.Geometry Index
//
// n-dimensional box-segment intersection
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SEGMENT_INTERSECTION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SEGMENT_INTERSECTION_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

//template <typename Indexable, typename Point>
//struct default_relative_distance_type
//{
//    typedef typename select_most_precise<
//        typename select_most_precise<
//        typename coordinate_type<Indexable>::type,
//        typename coordinate_type<Point>::type
//        >::type,
//        float // TODO - use bigger type, calculated from the size of coordinate types
//    >::type type;
//
//
//    BOOST_MPL_ASSERT_MSG((!::boost::is_unsigned<type>::value),
//        THIS_TYPE_SHOULDNT_BE_UNSIGNED, (type));
//};

namespace dispatch {

template <typename Box, typename Point, size_t I>
struct box_segment_intersection_dim
{
    BOOST_STATIC_ASSERT(0 <= dimension<Box>::value);
    BOOST_STATIC_ASSERT(0 <= dimension<Point>::value);
    BOOST_STATIC_ASSERT(I < size_t(dimension<Box>::value));
    BOOST_STATIC_ASSERT(I < size_t(dimension<Point>::value));
    BOOST_STATIC_ASSERT(dimension<Point>::value == dimension<Box>::value);

    // WARNING! - RelativeDistance must be IEEE float for this to work

    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        RelativeDistance ray_d = geometry::get<I>(p1) - geometry::get<I>(p0);
        RelativeDistance tn = ( geometry::get<min_corner, I>(b) - geometry::get<I>(p0) ) / ray_d;
        RelativeDistance tf = ( geometry::get<max_corner, I>(b) - geometry::get<I>(p0) ) / ray_d;
        if ( tf < tn )
            ::std::swap(tn, tf);

        if ( t_near < tn )
            t_near = tn;
        if ( tf < t_far )
            t_far = tf;

        return 0 <= t_far && t_near <= t_far;
    }
};

template <typename Box, typename Point, size_t CurrentDimension>
struct box_segment_intersection
{
    BOOST_STATIC_ASSERT(0 < CurrentDimension);

    typedef box_segment_intersection_dim<Box, Point, CurrentDimension - 1> for_dim;

    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        return box_segment_intersection<Box, Point, CurrentDimension - 1>::apply(b, p0, p1, t_near, t_far)
            && for_dim::apply(b, p0, p1, t_near, t_far);
    }
};

template <typename Box, typename Point>
struct box_segment_intersection<Box, Point, 1>
{
    typedef box_segment_intersection_dim<Box, Point, 0> for_dim;

    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        return for_dim::apply(b, p0, p1, t_near, t_far);
    }
};

template <typename Indexable, typename Point, typename Tag>
struct segment_intersection
{
    BOOST_MPL_ASSERT_MSG((false), NOT_IMPLEMENTED_FOR_THIS_GEOMETRY, (segment_intersection));
};

template <typename Indexable, typename Point>
struct segment_intersection<Indexable, Point, point_tag>
{
    BOOST_MPL_ASSERT_MSG((false), SEGMENT_POINT_INTERSECTION_UNAVAILABLE, (segment_intersection));
};

template <typename Indexable, typename Point>
struct segment_intersection<Indexable, Point, box_tag>
{
    typedef dispatch::box_segment_intersection<Indexable, Point, dimension<Indexable>::value> impl;

    template <typename RelativeDistance>
    static inline bool apply(Indexable const& b, Point const& p0, Point const& p1, RelativeDistance & relative_distance)
    {

// TODO: this ASSERT CHECK is wrong for user-defined CoordinateTypes!

        static const bool check = !::boost::is_integral<RelativeDistance>::value;
        BOOST_MPL_ASSERT_MSG(check, RELATIVE_DISTANCE_MUST_BE_FLOATING_POINT_TYPE, (RelativeDistance));

        RelativeDistance t_near = -(::std::numeric_limits<RelativeDistance>::max)();
        RelativeDistance t_far = (::std::numeric_limits<RelativeDistance>::max)();

        return impl::apply(b, p0, p1, t_near, t_far) &&
               (t_near <= 1) &&
               ( relative_distance = 0 < t_near ? t_near : 0, true );
    }
};

} // namespace dispatch

template <typename Indexable, typename Point, typename RelativeDistance> inline
bool segment_intersection(Indexable const& b,
                          Point const& p0,
                          Point const& p1,
                          RelativeDistance & relative_distance)
{
    // TODO check Indexable and Point concepts

    return dispatch::segment_intersection<
            Indexable, Point,
            typename tag<Indexable>::type
        >::apply(b, p0, p1, relative_distance);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SEGMENT_INTERSECTION_HPP

/* segment_intersection.hpp
b5abPlf2z4CddYWQfa9jfSHTmLeRXymteXvaeD3PwSzF930JwaeNcY21F7IPZf91mCmp6C8ieIunYR2plrzQIWZ8H263pJj2tHGmfWi6mo4H25vp+CagHfBpoFG+AuMkHalfo5TUv4XItD2k3/sj2Td4HW0At5txE1gPIfdFSbBbunCG5sqcVvraruMN/28QV+seJnSJzKe5veTlHKKZ7riraemk2UAyrfNGoV7y/V/84zt91v4P0Sz1PuZ5mt0s2bpjbSKW7z04dfX8hb7dQmR5juxjtWGQbheU3fp2vHfRIni1Y8+Cafojb24zaGLrPCEa9zNC75D8rdiO0SZ9N5fCzOQwL0SYdxhhpgQ/8EW3dui1OBV2n1EeuE1+C/g2zH4YP8w7MAdgBsG8yzTvRah/BulA6wFY6HO0J0YZ9ZA/vQFIZbSHdZ4kzyt7q0ls+uKbO4k+WFdRaZ5tOxlumKdMgZ3TwKLJivisBMKAPBwGZNo7QeqNso/Xv4MpUyFMGuNpSNd6lgnXzeWcbEs521QnZeQo0Q1mOS2+TMm7k8827F7lneKY1EZ1SITaCDnLVKfIfYTlzmSGDJh2uZD/7JDclaXGuqTrPXmmTdHeTYes7J/Z6LkC3qN23K/1q3dmSf4jsBcj8E0Q2O+NPdL6+8qJ5Rftb9n1usBvl7VCeU433B+9Yd7veq3aPuuD1j9t+bZbh/5IA3LP9JWOffXcQ5U9TrrpmiWLN+Ms9rlxhvulqTc988y8nPP23H7JI/Xdf3Uqyh6F/9CZE44cP+3Uv//+Hx+8ONM78xWUoxjDfV777nnbWq954IfFj6589ZqvJ6HdjjbcJz668Zz3f7l37Feb/7C25T0n3YZ17ljD/ejRljdvPPn6FUP+GqzNHPAhBsRoi+B+z/RLpx2Ku/6uKzam1e/e8Fvoc4cz3A8Pn9hmfrfrVz2VNeT6FvU/417jKJL/tcv+/tIv395wZPG17Vs/tOpXkP135J7z9JJVxztNe/LqReMeuOov9++G3k0KPz//rimfvvZj1qS3Lmsz6U9tdqEOUfjr30ge/Ovos386q0vyky93+eAl9FMUrzPzyo5efuHsntELZicu+UfZ35EO5P7mbz96aXhZxZ+XfXPpjAc7bopFukUZ7nc9GPd416HX/zDgtoR7pk/5498wV25huE+59zfvd27/+tGDz68Jxl76MdL5lBTDfch33bpOObrk6i1nXZB1KP7apeh3Ug33531pTxT17//sGbE9B89rNwrlcAK5X/yXy9b738i8e9zygxfNPTbtz7Q2C/ftex9648fcsy57vqDm1Rf6P3s9ygmlf13ONd8uO/ePF/y6x/l/8vdv8TGO7CYY7tE7UkpnzOt9+x/vefD8nzvuxljwEpJn05/vGnllTPTPw2cO3Fz14cASnCMg9+MHnkm4+Yplq896+2hJxa9OqkedJ3kOrcq7pfdzVceXfb3+seXr2+NN2dcoHQJ7Kq/69nDXl/5+44g2vT4ahHdXctMM97ZvzEyce/H4K99rcVWgc/fCOzBWIPe7bpo1aVvMl+8+eWeXX/64ZuWd6Dsp/NHnzMz5aNqRXi0CbeqXDjiGcAaS/M++Nu2LTXNzD/5y47qR+zs9hHswbei7K+6+5fVPXszPX/bi5EUV1204hFkW0W/9aHqHm4s3t/x14m5v5tG7H0M9b2243/HAH59+7a/zjl2Wuj29Z8J3Z+OOPMkTdWdFx85XHB2ccywnJeORGfvNOcc+fAP/SN9wPcoT1JDR2GURsDX8vjfSClgC+4+23z/YfqPfkt93yG9T51K3KHOd5X7b742235ttvzfZfvdON8OZ7DH1EASN9UwP6RKQ39c=
*/