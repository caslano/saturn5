// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_SEGMENT_OR_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_SEGMENT_OR_BOX_HPP


#include <boost/geometry/algorithms/detail/disjoint/multirange_geometry.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/views/closeable_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


template
<
    typename SegmentOrBox,
    typename Tag = typename tag<SegmentOrBox>::type
>
struct disjoint_point_segment_or_box
    : not_implemented<Tag>
{};

template <typename Segment>
struct disjoint_point_segment_or_box<Segment, segment_tag>
{
    template <typename Point, typename Strategy>
    static inline bool apply(Point const& point, Segment const& segment, Strategy const& strategy)
    {
        return dispatch::disjoint
            <
                Point, Segment
            >::apply(point, segment,
                     strategy.template get_point_in_geometry_strategy<Point, Segment>());
    }
};

template <typename Box>
struct disjoint_point_segment_or_box<Box, box_tag>
{
    template <typename Point, typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& strategy)
    {
        return dispatch::disjoint
            <
                Point, Box
            >::apply(point, box,
                     strategy.get_disjoint_point_box_strategy());
    }
};


template
<
    typename Range,
    closure_selector Closure,
    typename SegmentOrBox
>
struct disjoint_range_segment_or_box
{
    template <typename Strategy>
    static inline bool apply(Range const& range,
                             SegmentOrBox const& segment_or_box,
                             Strategy const& strategy)
    {
        typedef typename closeable_view<Range const, Closure>::type view_type;

        typedef typename ::boost::range_value<view_type>::type point_type;
        typedef typename ::boost::range_iterator
            <
                view_type const
            >::type const_iterator;

        typedef typename ::boost::range_size<view_type>::type size_type;

        typedef typename geometry::model::referring_segment
            <
                point_type const
            > range_segment;

        view_type view(range);

        const size_type count = ::boost::size(view);

        if ( count == 0 )
        {
            return false;
        }
        else if ( count == 1 )
        {
            return disjoint_point_segment_or_box
                <
                    SegmentOrBox
                >::apply(geometry::range::front<view_type const>(view),
                         segment_or_box,
                         strategy);
        }
        else
        {
            const_iterator it0 = ::boost::begin(view);
            const_iterator it1 = ::boost::begin(view) + 1;
            const_iterator last = ::boost::end(view);

            for ( ; it1 != last ; ++it0, ++it1 )
            {
                range_segment rng_segment(*it0, *it1);
                if ( !dispatch::disjoint
                         <
                             range_segment, SegmentOrBox
                         >::apply(rng_segment, segment_or_box, strategy) )
                {
                    return false;
                }
            }
            return true;
        }
    }
};




template
<
    typename Linear,
    typename SegmentOrBox,
    typename Tag = typename tag<Linear>::type
>
struct disjoint_linear_segment_or_box
    : not_implemented<Linear, SegmentOrBox>
{};


template <typename Linestring, typename SegmentOrBox>
struct disjoint_linear_segment_or_box<Linestring, SegmentOrBox, linestring_tag>
    : disjoint_range_segment_or_box<Linestring, closed, SegmentOrBox>
{};


template <typename MultiLinestring, typename SegmentOrBox>
struct disjoint_linear_segment_or_box
    <
        MultiLinestring, SegmentOrBox, multi_linestring_tag
    > : multirange_constant_size_geometry<MultiLinestring, SegmentOrBox>
{};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linear, typename Segment>
struct disjoint<Linear, Segment, 2, linear_tag, segment_tag, false>
    : detail::disjoint::disjoint_linear_segment_or_box<Linear, Segment>
{};


template <typename Linear, typename Box, std::size_t DimensionCount>
struct disjoint<Linear, Box, DimensionCount, linear_tag, box_tag, false>
    : detail::disjoint::disjoint_linear_segment_or_box<Linear, Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_SEGMENT_OR_BOX_HPP

/* linear_segment_or_box.hpp
l8IJeNmmpDyCwdva4TLE5Xtg+5yeuBs+UlDveOW95gZv7paL1+HeafjoUr1h6QPi/b54OHReLMSvVAuq6SXFSVn2zlEPj0pyzRqwS+1aVRlf6RuFfInnhao9H4iJmPh/s24UFugRW7XR+21Tp8RDU3nQXT3qxY/rJkc2VsKFX+LhlfVRSE41T71NsVEw2VwOw4YhM8S0c36crM4OcL/GXn40zsq7zOsR73nMDWeTQnjpK7FzBP8+riZdywdsf2uVeJg/MRaun4yLip968rQQ/CovvwuInyvF9b5r4M3X7q+W333u4itxP22h3vWAOtzVM06Mu9Ru92pO4W894k34zncJzIEN7y3zDNTLxW9lfhgD4yrpv8RxcbW/wTy4GMkPXLrcGv5V04fG1OYz1Dz17GOc9PnZ4t/8Rl8t5geI89bmUFv/DTvvujwKFy/CTfHclDTciw9v+Ny4+KI9H3Q07nM/hZNqWU78rW0DPqqsd5HzKVtDqHqXelIFhpWMh4V82eJL/BdufFgA3pRnl4NyuQX88p088K11O7zzc+ddAnON63ExFG6OhTmZ8SH9zBtsd1WtEJJKwvkH5QB/JNFJmsv35EWOhT35nftc494hlus+qNbqVT573GeuN/ZD9sqjrsDoMurduNtCKKvWbVfztiaptduMiz/WiInmxr8apnesSAuoIbb00JvWipEr8JVkekZtYxGjTdTjQdfobwrRReBp0UN6ySd8Xo+mEOHEuWDGM7gS/vE07IiXjEK54vrxN2gG/DEqWxBX4uF+GDUHbt9DX0gRWzByQQsYOdDzC3D9rYPw36z6RT1ZnUSdgw+Fn4CrH8PF0vpo+POAmHtcTzRyTzw0k1eP6FF75xAbI0J4FD9tw1+z1O5B8/EJ8f+1zwc/RE/SP6SuVj8Gw7Vhcp++NFbuVyljnJv1pmzacTyc+AafvducgngSjxuWqM3DYVtt820N89Ts7U/Snb5O8CeYpg9JY6fUqfyxCkZsNMdL42HyHbAXhgykRzTUaw1+CVejHZxxXSxcBQcb1la/6+gT9FlHS/M9f+wVP1mXGyf8rzk6FpKryKV8OIvesVU1vRkffgHjynSD4XhGzfvE6PYo9Dsofp/DQZJhCg68Vl2KtcD5++r5Gov/teaoV6gtdlaUFGPsnOiZflPbh1fmT/k9YALeo3Y0UVMrzVeD0uAQ3lkDx2tKT+mmN+zbUYyUkavj3Pef8KdYvaYMzgO/3xCfBV9Rq52zhPHux9Vf7My/30Xh6c5siktWGaL/N68kGNFMrWrSFQ8riIf5/hn9+M0YcvJhNEmdVZemTHV/g2scqs/ufPR9L2BjHGv44NvZ8JW/Fo9x72uFeDhrEnu09HcPXLsvCiuull+P6IOG6HNG41O0lc/HhdCmVRQaw/RaHfCrOC5bQz02jpx3+11VutHjePocGt5w35sEb8zzcvXxCjY6S+zU6U3fyINb4/krv/He7UrGDXv3d1TT+eeDUsZ2QSw8j+fUSOVXvX7JhvqT7mzBBveWxgXEwoVLQrj7Jhqk+QxxzRvm0yjkS/6FUZjwgRrZPaYWqf89YmFiJ/m5UqzhkC0b4ebZzGMf7awxntTSOu/z8Ezc5c6H68iVGWLi00/lJHzpyS6z6R7T35IHcCBXU76Vn53pbbVw2fHy7q1DPivEv9XwSrk0KfFsuDfF+PlwQn50LA4Xzgohk2tdtQde/gDPx+ADznXTezQIsTK4CY1O7mT2u4P634DfdNiC9+92LfgR6WH7LaNx6e0fosud0S0mtug+fDDmWziDi4yCf0nfq+Xr1Ry8sI8xzbwksdldTOfBkyrSqRJa8SJzmxELd2RR61ryM+0s0wA=
*/