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
g/3iavS2rv0W8/VzrKuncnlaTv79UaL4nonwpGrvMXDbwzTDGu2bU5UyAdmacV/BSpsnOG1y+QM5MNvxp15NGwy+a0KZpc8r5sltVl5ZfcKFC51vvz4Gefw/6eXB27I1fGlD1yeAT52vTGxGX6vcF3eRr1AvH/ZrSqpM6fTyFf6H5Vu9yDk2eyoH7iKf/v0JF/nA1+gYzXU9cpxV/xY7ZdoBmdaJTI2/iaGTbd0JyGaV/90sWxub/qedxlhWLxseNS5DRdKWf+ZpE3H+gV/O6j//k17f9ZrLTMYFfN5tDnCQca5PlQ/Tf6xASb1Uz7gcI9pp3kRaY5IzLhxGlq3vreC+1/LLoDBaw/4t2Yu9afh7DkxLOas1V85JZPxMZ6lRmnPBBzfYVpHbX0FThD6rPTB0nqakluqFfPMDom3DdrSEv7D+U/DEUw7PqMBbvzJvLSb626BzuyW7Wd97HC6zqf/eg/zthjRcAX5fzBLqc7t4LqDyMAXp+Ixfb37bhP2SZRHsZ1+4xLn+8rQxR/lFyUde3dCWL9A2qLcL/s1/b2VZI++tnGLF43KTeRTHo8A6i67GY5bLOiTTpdCcu3gJ8gbhnY/ESEzCe2WZ2NtLj5W9vVo+hxB+Bov3G4FRtFfQUspHjYzp0sgvW8Z0vcgeE9F987A0Ue9ZXWESTuL4nw3zrNH+g8oe/4qqitryslJOA+VcAtNOQt/R1XYWfMb8WbYxRDHRDPX0YX0C44XPb9sbn1k9v6qOeApt4Z4BHqYJpRm3BZcRTW6zywVkhZ1lVcYXJIvStuYtdbT7tLa5U02riqpZ1XJBz33cZfKdyHqBlYcblzrvB62BXHtUufh2k74cg7bZd4Os9BkUtPoeHoPxOmO9IgctybLCbNd1RuZpc0LyxCwL1e1kmDN5bcDv1cvDCwSaMs48COlkfNHwn8j10yqHA8k/g+04wUf2eGm7tkd0vghl1C1tl+vraUATF6ms+KeJC3gar69Br6O+gq/B+gr/xuvrLd7/fn215vjPLXe+4fecUR7VNAs93+fSxoM+orf7NGVRZCm80lk3RhiCRdllUXQI6GQBffPrhTWm/thFlnxXWfgCvkv65J+ATPKuwwrnW1R0x1Fk0rwv5iIPeCJ6h6qhe47HVmjeZTHOEqry1GAEp5OB6WIbbdsbKjMrfq2/9xlUZcDAE4uJ5firTw/QN9q2j2ssPRZdpR8nrQ6TZVapVgamS3Ed+9wX5T72eShKHfvs5vwNG1dFfE9d2hTlPBDJo9QT39XOvbznjbdwJM4u78q55AP4Tngv79arHbpyKB/80SKT8y05F3nAE9E9lIbk2b5SvxaVr8jD+gAjWIsCX4NrUcPhH74WBZ5G16JA8z9bi5L3Q64xA+7NH+gF86KxTuBMG96k1ucT6OWcSnKm4YejGKLTSPybnI/WWQaECTuFqeRtwm/krjf968Flrd5N/iIKQxcH5unZZBnt8hxZxf0WwksFpgFfykG+xKjylJfUKHvGzjEQ8yCkcZ4XzffubWMgLldM057m/ufDfibZf/CMRO/0PozMW8P04hwmuii6l5EJ+xCy/0JvLGyD+8dAvnNryeFY+7f2iyeS/4eeAeDDGF32i/vGGu4ttOv/98SQn2Ofugp+fyC/WzyX8zgW8ca/gOghqiT/5zx+8N+jhFFFYaTj1ytEMxO1sD27YXec3OagPTqPdKP5foM8v9baXz7LF4vvhO8j5DCdf5VFN8e4YhA9wRebqduHbsf0dassnUbBaxO709WQmJagdeg14vTYRrK11eoxSgfeS/4dzP0P/sbaVbxHkhgMyh5JE85csU4OZT8roI5d+f68/szQkuv046HVsWo=
*/