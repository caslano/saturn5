// Boost.Geometry Index
//
// n-dimensional box-linestring intersection
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_PATH_INTERSECTION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_PATH_INTERSECTION_HPP


#include <boost/geometry/index/detail/algorithms/segment_intersection.hpp>

#include <boost/geometry/strategies/default_length_result.hpp>


namespace boost { namespace geometry { namespace index { namespace detail {

namespace dispatch {

template <typename Indexable, typename Geometry, typename IndexableTag, typename GeometryTag>
struct path_intersection
{
    BOOST_MPL_ASSERT_MSG((false), NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_OR_INDEXABLE, (path_intersection));
};

// TODO: FP type must be used as a relative distance type!
// and default_distance_result can be some user-defined int type
// BUT! This code is experimental and probably won't be released at all
// since more flexible user-defined-nearest predicate should be added instead

template <typename Indexable, typename Segment>
struct path_intersection<Indexable, Segment, box_tag, segment_tag>
{
    typedef typename default_distance_result<typename point_type<Segment>::type>::type comparable_distance_type;

    static inline bool apply(Indexable const& b, Segment const& segment, comparable_distance_type & comparable_distance)
    {
        typedef typename point_type<Segment>::type point_type;
        point_type p1, p2;
        geometry::detail::assign_point_from_index<0>(segment, p1);
        geometry::detail::assign_point_from_index<1>(segment, p2);
        return index::detail::segment_intersection(b, p1, p2, comparable_distance);
    }
};

template <typename Indexable, typename Linestring>
struct path_intersection<Indexable, Linestring, box_tag, linestring_tag>
{
    typedef typename default_length_result<Linestring>::type comparable_distance_type;

    static inline bool apply(Indexable const& b, Linestring const& path, comparable_distance_type & comparable_distance)
    {
        typedef typename ::boost::range_value<Linestring>::type point_type;
        typedef typename ::boost::range_const_iterator<Linestring>::type const_iterator;        
        typedef typename ::boost::range_size<Linestring>::type size_type;
        
        const size_type count = ::boost::size(path);

        if ( count == 2 )
        {
            return index::detail::segment_intersection(b, *::boost::begin(path), *(::boost::begin(path)+1), comparable_distance);
        }
        else if ( 2 < count )
        {
            const_iterator it0 = ::boost::begin(path);
            const_iterator it1 = ::boost::begin(path) + 1;
            const_iterator last = ::boost::end(path);

            comparable_distance = 0;

            for ( ; it1 != last ; ++it0, ++it1 )
            {
                typename default_distance_result<point_type, point_type>::type
                    dist = geometry::distance(*it0, *it1);

                comparable_distance_type rel_dist;
                if ( index::detail::segment_intersection(b, *it0, *it1, rel_dist) )
                {
                    comparable_distance += dist * rel_dist;
                    return true;
                }
                else
                    comparable_distance += dist;
            }
        }

        return false;
    }
};

} // namespace dispatch

template <typename Indexable, typename SegmentOrLinestring>
struct default_path_intersection_distance_type
{
    typedef typename dispatch::path_intersection<
        Indexable, SegmentOrLinestring,
        typename tag<Indexable>::type,
        typename tag<SegmentOrLinestring>::type
    >::comparable_distance_type type;
};

template <typename Indexable, typename SegmentOrLinestring> inline
bool path_intersection(Indexable const& b,
                       SegmentOrLinestring const& path,
                       typename default_path_intersection_distance_type<Indexable, SegmentOrLinestring>::type & comparable_distance)
{
    // TODO check Indexable and Linestring concepts

    return dispatch::path_intersection<
            Indexable, SegmentOrLinestring,
            typename tag<Indexable>::type,
            typename tag<SegmentOrLinestring>::type
        >::apply(b, path, comparable_distance);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_PATH_INTERSECTION_HPP

/* path_intersection.hpp
fdBuxKm8RWhBZteVy3nUGqIvBH0irxFaYeJMuryjMlPOUy8mvyFodeIc7bBBuszwh2882mnRq9+M+0E5PEfoTnY17u04LxA3+DniptSPdT4zby7h8lgEk5CJsq7LGwDG53SISXc/K6nA4DkL7YS8U8PhtHWkFb1xTPSjqKwqZwQ5rfLJP47tOE1H9igpm97U5qWdvS0b08qM/33cHm+CGWicWyhQ418xu4oirrvjh3gy/R14Ra+DzE++Ibdo0FjjerOZkff3hO9a9NztuMxafGlyzhfrLZWl1hq18PzJ0veJf5gyFZUgBDPdVpP/TZ7WiGl3mP4wYz297Xkgbx7cRLRXOtqHHA7rbvKfihD8uNnWAr1tWpPmiS465HleIukhOuQRX7hTfJV8OpJs5tNGmE78zs1Lxp7uMMkn6TRpHKlvN5h+CI8p1DcWx4t/vpypXk32hXyfRXlDUe7uXgcauJO9XMLobeqepZ6Cx7Rc7m9kescb6twm30P+E2z85aWza+tE39bN5H++px3yIQ6+k5BCk2HugtkAszGl0XGw3Df7aJjcN3PV7YN0Cr0VKPN+dnO+4Yf1OTOvtvL4YDPf/SwYLnlVUVVR5zo+4Lxi+tZy1vt8sq/1+PC3RNUvruiCXEx01egdkiWNZoOunHXLXAKcE+HdlLDyq6wbH0MtoEEItx3DeSyXNyIUz2oZwbmO4Zg+TepkP7IPdIz1rfJ1OvmfrI75eEycT36nybc8YXobBo6IiujdVbcx4a9GyJiQ7LPYXpOmvikcTPWq9w25DARDaVM9R19HmYbvGEZwF7ChN1jz0kgO1ODQfeRPslCvRQ7zWayZ1XOL6qqNS370JKytvrNaE1k3s3gXNipXJsvFa2QcjrqWNyHdK2/dpPE96e0ZyMeRIl9NWWBuyUxu1dR5cajMjyb6Is8I6XutMDLd7s2wf7b0x2PJXoIe2Uv6Gzoj7Q7BkE6G7MRubu+y8H1nan9ejrDt0czBub1R7poo9c2T4SUYzPXN4O9p3AOTtAppCMcKDp91VdbamDZf/GStTfx6NVo3uJ3kc64lYedeZygyd8v08t013s813Iw2YpRDZkoEjcxMmyvjinPJjjtH0v/PlfFlGfklkwyZcuchpDbUPvboT7QFGJPHEu1dRGuoQ6zF2XicmofN0jMwnGhPaXLa5LAdYcOuhK3Ugz1ZZjrdCvADfw805pSr7emEi+4ltXPc9G8wbZr0k3eSfaXXqMvzqSEK0GM+dj0ZDxDNYq8yNuLwNpOf32vd5X19tNnvdkDbmyppb4hUxPsE/H4d0V1M6VwF+xVkr0OOxUu7gpyaWYrrTmgEZbz7HNGlsN36ns/GAw4aioKH7yJlE81v7DTlRUhm+xvLH1M83mG7xCM8DiV2vXPHiGedrB+tJZ7rMJpNtH2rBvKUVc1kvjn4VjTRPcF2+VboTj/arQVlsuBPdNXga0t0a+xhK3G9xAskmgfYrsSD9eTgWZc5fO+L03QH0cRKm/VUhG9PFDjmC3xGKIf7NUAW8CjMUmMt86xQOa0rqakztU8VXVI9Q68T5CWif03mlShvHEZ3aq+X5LBuQ+t+uPh3kXtiL5B9v6cTr0VfTjy0Dybz0WeJ5kNPT75PWSjhdHKOP1k/zB7yf8PUY8Hncl+NcE3MTS8f4sP6k0Jj/cvJjeVVxpWQJ0xX9cdId53+scNjJN3nY50E12rLSDVybV2REXAdWj3dugnzRTd5jKHTS7Yy15StP7fxJ1u6Tl7wOmQTqfRtGPN0a9aenKbcSvod18i4yqjoYzXpt6C6IiRo02Swt+kj25rf/IzHNgdYj2mh7ZsBLOni9nYJNgP1b9ER7UucPhY=
*/