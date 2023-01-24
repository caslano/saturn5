// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP

#include <boost/range.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template
<
    typename Geometry, 
    typename Tag = typename tag<Geometry>::type
>
struct inner_range_type
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Geometry>::type::value,
            typename boost::range_value<Geometry>::type,
            typename boost::range_value<Geometry>::type const
        >::type type;
};


template <typename Polygon>
struct inner_range_type<Polygon, polygon_tag>
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Polygon>::type::value,
            typename geometry::ring_type<Polygon>::type,
            typename geometry::ring_type<Polygon>::type const
        >::type type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP

/* inner_range_type.hpp
PU7L/P1o2t7ocHBpQ9Lh4thcyKguQJWN2VexkpknxEF0KzvNAt6CbI9UENvca3BWUtFfLQTxh9Bf0GfFrOb7f71iW+7M+dZjJlc14z1HMXXr/e2W6cw5qmK4kHI9eVt0Ck+to6k+7rHddCMBeU5VrumvqUYnWoQi2Aqshh6xa9WsqmXFQXh44nyUjZrcbuEJ9Li7uGmvLShNHWUy/vyXGhS/96U9ePxEiIcUZghe57q0LDsaM9R+yFr5kqgVm3tutwJIFco9r7rcIKnPdq0hAEf0zKGh3Y4a7hQngSQXkUHQPuH+Om3H7VIIMh4fJIFb3vNaoIueF1zO2X2hYk3R2nJ7+CfzMC8pz3AnLhE2s1p2xJ7Qks/rA0OvsO7RhTADD/2fmPPlIpZ8WQdCTUtBDt/wP7ustYj3Tt5Frqoo2I7exJNcNYI5v28i7oQCAFVFDfyNArtobvoGYXsTOvdQK/3h5FD1xn7YZgd7iMyF55HXpsfmRlXDDV03q64LxDVC0Rmsg7TfdnuP2vfUpPmm7N4xpqnF4lJirV/RUoB0+YiE31O2bxwj1Mtammhaf97mTHbCG1+QWIic/6b0h91nGIN/U7r4/6J0xr/FG+Tm6+MM8tCxB3mIOtuDUNmBbiyAdrQK6IGY3N1nd6Sb78ZpYaQLS8rl0FDB5VfExqTMQfKqOHqHVX97zhryxCp0QJcsJedimAQlHUcVfJ7e
*/