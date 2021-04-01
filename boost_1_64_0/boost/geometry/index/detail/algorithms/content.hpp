// Boost.Geometry Index
//
// n-dimensional content (hypervolume) - 2d area, 3d volume, ...
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename Indexable>
struct default_content_result
{
    typedef typename select_most_precise<
        typename coordinate_type<Indexable>::type,
        long double
    >::type type;
};

namespace dispatch {

template <typename Box,
          std::size_t CurrentDimension = dimension<Box>::value>
struct content_box
{
    BOOST_STATIC_ASSERT(0 < CurrentDimension);

    static inline typename detail::default_content_result<Box>::type apply(Box const& b)
    {
        return content_box<Box, CurrentDimension - 1>::apply(b) *
            ( get<max_corner, CurrentDimension - 1>(b) - get<min_corner, CurrentDimension - 1>(b) );
    }
};

template <typename Box>
struct content_box<Box, 1>
{
    static inline typename detail::default_content_result<Box>::type apply(Box const& b)
    {
        return get<max_corner, 0>(b) - get<min_corner, 0>(b);
    }
};

template <typename Indexable, typename Tag>
struct content
{
    BOOST_MPL_ASSERT_MSG(false, NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_AND_TAG, (Indexable, Tag));
};

template <typename Indexable>
struct content<Indexable, point_tag>
{
    static typename detail::default_content_result<Indexable>::type apply(Indexable const&)
    {
        return 0;
    }
};

template <typename Indexable>
struct content<Indexable, box_tag>
{
    static typename default_content_result<Indexable>::type apply(Indexable const& b)
    {
        return dispatch::content_box<Indexable>::apply(b);
    }
};

} // namespace dispatch

template <typename Indexable>
typename default_content_result<Indexable>::type content(Indexable const& b)
{
    return dispatch::content
            <
                Indexable,
                typename tag<Indexable>::type
            >::apply(b);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP

/* content.hpp
E/boc0Y0kc3HpI7irqPusPTiEhhpBYIJ00JXmr5+NiLyyNy0JiXt/QX1J8AqqkQ0XDaiWr9AM0HqyT3slBoAUcSjRd876lJuvuWHxIyrlXlFTDi76P1Ksl+AvfAX3q4kAlKHIew44JEM5WsyoP8CqE7ScA556WOnNgu9w7gt05lUHbmGfIPOy2NNhvRJFHsmARLtaPGbsVToQmV5mPczxgZV0vHWRmaIZuE+a2zThRgysRpDuzL3w6g0QthbyJQB5YXDkO5jR8Ww6C6IKKzw9WsAO0rUHz/ci9Hg0hj0wUoY0muL+ftttqJJgjd2HgCc2ftaxauZ5GS98455pj5c883oEJ1rgpdd9/Q0esiPyrI2RmluaUjP8d1z/1wgcvZqELY0i2SSJrT60jkz8+uAH49LmmWKoJGJX1xmn1aF+fhYjrUPRUI67lBCobGpzyT+2/BZLKRvc6pBwhFSiGZo2+NOIr31v86XxbwLoqhoqYR7E/Pg5/M733+qaLdZcoZD+kP3rfGCRqYVTt19BZgOk1VDNwSmTh3g5Oom5S0iDUCy7cGjIoNyC1n9Vg==
*/