// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_RING_TYPE_HPP
#define BOOST_GEOMETRY_CORE_RING_TYPE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{


/*!
\brief Traits class to indicate ring-type  of a polygon's exterior ring/interior rings
\ingroup traits
\par Geometries:
    - polygon
\par Specializations should provide:
    - typedef XXX type ( e.g. ring<P> )
\tparam Geometry geometry
*/
template <typename Geometry>
struct ring_const_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Geometry>
struct ring_mutable_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag, typename Geometry>
struct ring_return_type
{};


template <typename LineString>
struct ring_return_type<linestring_tag, LineString>
{
    typedef LineString& type;
};


template <typename Ring>
struct ring_return_type<ring_tag, Ring>
{
    typedef Ring& type;
};


template <typename Polygon>
struct ring_return_type<polygon_tag, Polygon>
{
    typedef typename boost::remove_const<Polygon>::type nc_polygon_type;

    typedef typename boost::mpl::if_
        <
            boost::is_const<Polygon>,
            typename traits::ring_const_type<nc_polygon_type>::type,
            typename traits::ring_mutable_type<nc_polygon_type>::type
        >::type type;
};


template <typename MultiLinestring>
struct ring_return_type<multi_linestring_tag, MultiLinestring>
{
    typedef typename ring_return_type
        <
            linestring_tag,
            typename boost::mpl::if_
                <
                    boost::is_const<MultiLinestring>,
                    typename boost::range_value<MultiLinestring>::type const,
                    typename boost::range_value<MultiLinestring>::type
                >::type
        >::type type;
};


template <typename MultiPolygon>
struct ring_return_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename ring_return_type
        <
            polygon_tag,
            typename boost::mpl::if_
                <
                    boost::is_const<MultiPolygon>,
                    typename boost::range_value<MultiPolygon>::type const,
                    typename boost::range_value<MultiPolygon>::type
                >::type
        >::type type;
};


template <typename GeometryTag, typename Geometry>
struct ring_type
{};


template <typename Ring>
struct ring_type<ring_tag, Ring>
{
    typedef Ring type;
};


template <typename Polygon>
struct ring_type<polygon_tag, Polygon>
{
    typedef typename boost::remove_reference
        <
            typename ring_return_type<polygon_tag, Polygon>::type
        >::type type;
};


template <typename MultiLinestring>
struct ring_type<multi_linestring_tag, MultiLinestring>
{
    typedef typename boost::remove_reference
        <
            typename ring_return_type<multi_linestring_tag, MultiLinestring>::type
        >::type type;
};


template <typename MultiPolygon>
struct ring_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename boost::remove_reference
        <
            typename ring_return_type<multi_polygon_tag, MultiPolygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif


/*!
\brief \brief_meta{type, ring_type, \meta_geometry_type}
\details A polygon contains one exterior ring
    and zero or more interior rings (holes).
    This metafunction retrieves the type of the rings.
    Exterior ring and each of the interior rings all have the same ring_type.
\tparam Geometry A type fullfilling the Ring, Polygon or MultiPolygon concept.
\ingroup core

\qbk{[include reference/core/ring_type.qbk]}
*/
template <typename Geometry>
struct ring_type
{
    typedef typename core_dispatch::ring_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


template <typename Geometry>
struct ring_return_type
{
    typedef typename core_dispatch::ring_return_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_RING_TYPE_HPP

/* ring_type.hpp
pS3mjtfUcwfdvct2671XNKmZFp7iXVHB2e9M3biJ6t0gzHWYdCNl4eKihFaVerTC1dPsK5ik571Fd3F1y0LhqTLvPPpIvdweeNdXV4Uqw3EjvPMFO9zmgh32XrClKm7c9Z1DhKFpWV0VYmD0/VRCsexdiFnnvVHa2LOysqoooYJvHZyJkdLWFfbslZtV74qdb0wmnr2Yebfi6uTelbvl7uUpvqw8zGDozWIeCbWsmxbKKyr13kakqrrlyiR5xRd5X9+qQ0y4Eley5aBz/3JG8SU7Kc47afyYwd51corG140bf5Jb7V3jbUp1W77uvdpOy11Pr8rC0oKyijZ9Eys5g5i1TEE9sUvLKiLxtXJu6eVjJ8Vi6H4llXtQt8C+VZRLUWJ5aWU4wnz06OGeSol1oWIvr0hZ4dTi1q3db3k4JtTJYtq63KvptAIeDFTJV4f4KlkFCyvds6JVA8mMK1NJsT5J7HH2aJQwDO45FV/OnZrXvnLXE6/Jiq0kluSVhDwK2S2unS0qwtzTMBAeZd5HJuw9ns1LQ6tC731zz96EL5aJXyoLCguLQxIWFQ22J5OtWn3TlBIuxXIrVT35Iq5ojGIlSyhLj2liz+ZdtbFvziuLqmXeF5TT3H7YIg+BvEu5a46vsr9DS5Vnqdsh8RutnWHY+bJpa/vbrXP629rz267b3uM7r4xW/AR2vwI3P9EjTniaR1ni12M3Va+vxa2/Eid+75Uirh4FesydkkpmfkVRuLRgqvSqDhmOv5dt+XWZKRmqrLInuB7UaQxIVVlBuVTxqM/ej3B1SLdykndnnL2suDfrdr0U2wm2VPZjtEp9hxBfLrvhFrk3ToRTKiNlBeLb6vu3u9TlhZmI8UXuxd37i7hbY18iy4qLZHJI+WA5gG6BOwLx39DtJQjWp12zZjbmFYQvqSjMKylyW8VdZNwyjtcUHFu3TvhmkvBkwPupgFu809ZVzJDKac2lDEuV2zqx2H14l1DHvCmoiK/x/grxSx42uE3iFj0pL66qqnQTk+PXWudNOipwbN74CWPHneKsgEUzm5uUNM8deaIok8n7SUb8UwzR9nyyj59MkoRy97i6FYkbc58SuUXuzYV3oXsl9HqUIsVVPPUWIV+9Ckr5f7fIHQLvO3jvxy1SLCe2fXuqT0v7hkZq5UbHnVVuqZyCiUX2Gu6Wt5pdrF5VHueYFIfLphSUT5Fij6FIbMAN+5gWakq8sqehngQJhfHJt9h119t9COUWRdxp4PnowfOxk9cjp/gyzkDOjPjSFkM2g8PvCjnW3APptbywlEXdvRq5daHiiiJzaeWeeHJxCU9PRLk3EFy0ilicJbbLm+e1FMqRtZX9EMxdlppnitx56fPCHoX4rdsTVoLm5b61ziuYPLmqeLoOE9q2NLOPgNwhuCUJ9wwyreOuNXapDBT2zIEiKYoE3DMs7HU1cWtmxLWLu90Ku0+/RLoXDdH2rZpMICls9XhMytwtuE+hRCdcNShzD0eLYrljabnBtp4zybOXydVm+DwWdanZ5XJPkzafFFHfemhlFW/zYQ519pC790iej3Y8H+v80mcxrZ7DtPUMpq3nL62fvezsuUu49YIuRe5oeC/oO3scE2614no/mkmowqmq2J5prWvki5t08q5yO3rtHguujJB7hnhW8AhI6lovvTt7kLKzhygtH6C0enji/eAk7Lkah90Ft8WOJeY+oyxS2vK6krBQea9T7vc9jyc1O3tKs7MnNN5PZ9p4MtPGUxmvJzI7fxrT9pOYnT6FaeMJTPxVcEZBWUSPGtcw515aSqWp/WqASnyHIu4VisQ3KJw3GgZLl1alraRn1yGeXYe0kl5dPTvGi1adioY=
*/