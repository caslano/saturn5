// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP
#define BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
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
\brief Traits class indicating interior container type of a polygon
\details defines inner container type, so the container containing
        the interior rings
\ingroup traits
\par Geometries:
    - polygon
\par Specializations should provide:
    - typedef X type ( e.g. std::vector&lt;myring&lt;P&gt;&gt; )
\tparam Geometry geometry
*/
template <typename Geometry>
struct interior_const_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Geometry>
struct interior_mutable_type
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
struct interior_return_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Polygon>
struct interior_return_type<polygon_tag, Polygon>
{
    typedef typename boost::remove_const<Polygon>::type nc_polygon_type;

    typedef typename boost::mpl::if_
        <
            boost::is_const<Polygon>,
            typename traits::interior_const_type<nc_polygon_type>::type,
            typename traits::interior_mutable_type<nc_polygon_type>::type
        >::type type;
};




template <typename GeometryTag, typename Geometry>
struct interior_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Polygon>
struct interior_type<polygon_tag, Polygon>
{
    typedef typename boost::remove_reference
        <
            typename interior_return_type<polygon_tag, Polygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif


/*!
\brief \brief_meta{type, interior_type (container type
    of inner rings), \meta_geometry_type}
\details Interior rings should be organized as a container
    (std::vector, std::deque, boost::array) with
    Boost.Range support. This metafunction defines the type
    of the container.
\tparam Geometry A type fullfilling the Polygon or MultiPolygon concept.
\ingroup core

\qbk{[include reference/core/interior_type.qbk]}
*/
template <typename Geometry>
struct interior_type
{
    typedef typename core_dispatch::interior_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};

template <typename Geometry>
struct interior_return_type
{
    typedef typename core_dispatch::interior_return_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP

/* interior_type.hpp
Mz/r3Mh3ssGG0oFnpKMjrkwQ5VWPbts2uXFiO0u0864s0nb3rm5PHF0BevA+vN2IHopjY1K+nkbzU1tXEBlIbljAk3V36ODhDMbO2927uXtQIRQQvaagRrdHlWSUlGj0WpS89rJdkiDJJN83Cfo+5IO61T3hwder9+dvVneH4Xd21fvj19K9sY81Ry79Hc+3r1Z8vspy/JPhH9ug3t+1hu7+hy43rxIN/37NYq4G6y3PWMXatZxF6r/vQOb4wfvTV+aPPrB/0enIw4iN+ZUqbePw46qRUSnr9WfyVh+s+QbA9dKhbkOtfG/ZJo8A7byrnGSmX513b+nKXTv99x/K3P3YwXtg2+uJoe219L+Ky3k1212G7evCOnW/Fd8fzvbS5vWvdzTR+0p+Px96d9iuvwj+5u9QvoD53E7a3X8wfee/nP56a/rU4KdFM9Bd+CRtq0gA1o5EWpqclJNwUknPL6xmvl9KYLzF+fmy8fwV4/my8fxV4/lreC7x89eN528Yz9/E83l+/pbx/G08z/Lzd4zn7ybogZ6/Zzx/nNJV1yeM508az58ynl/i6OdPkzzq+ozx/FmSR12vdPTz50gedX2eZOA4SR3nNUkd53VJHaclpeIkqNDwf7NYj5Lowv+uVLIp2ew0J5qTTU5ToimZclKJVDLpoFCSCSeRSCR/+ctf/erXvxbGlWLWB5jna/Avyb/5n+Lf/G/i3/Jvxn07kL+UZYP7r2S54C4ZNjOfKvN5saP43Jrjf4XjX6b4wfQP0JOWg8rfkKdEZqflOk90LB/pkmRkOYkYpqnlZX2x3PROOJaf4qeFlOv//4rz22ajhV/aqBufVtHr/r7LFm+ihDopj340Lcbs2XlXeeKsUJzm5VZ/Tw1FW0x/qC5/Xg40+S9GLxMVuegWHjHM/qxZfcf+5811+xmH9t/6AfKekH4ZoeOnTaLju00mjvx0J8ITgXsicHQt4fe4610zP64h96VlBO+gu7qW9IOfN64b143rxnXj+q9cWP459cYfP+PBT9lVvOeTnvSOB/76oc95Kf3ujXW+i75kxK3fzrMVuUvDx83cfu9O9cmLneW8/OZ23ouBfgMiHD+8q5Tz98nchYK61oob143rxnXjunH9uy6n3RHth3DvahZduWWiay/uva0lwh1qFofwvgbwNb3NCrYmJdZIGL3XoFuTkPgeZ1NabMq1ik1DLWJT78r59lmF34LJiJary0XT3rS40IN5E4ShXzcJwiGEYY3wOYD9h9MIL9N8TFgwr1vbxNYcwlCr2Lq3RWzt7VpYN985t3q2Q+cRPNcMch5vkRK3qDaLlb2JHpsOurenRJdzZ5EsJQamNmDs5QglQ0dKdFy9vUhf3icuYILipwh3WWD58GNJ6b0HCLbrIPLqwaU+r9xBdHz8jiKduxPhfohQIjzlywoL8iFYNE05WoQ8AvwFZBJIQyANATmicVMqblR21mNUDwS/mb6beKveboZ36H9Nubkk9bbPs8mVCbFyMNGDO+m8Hh+Wh+8x8jG/LU0J0YTy7HgQfuMW4cpvOM9ypB2Bazqf/tZpcesry8VNq2mqG01DoMF+kLsi3OK3Wv8aFuLD8nXfBO/lRI+Xd6vtUVyDdnNabM61iM1Dy8XmvXgeNG22lXSp6ZZw39IitqCObEEd2bIXz4OdC6vnOa0NzWLDYPtC69zy2WUDzT2U36PN4mi1XbRcWSmaQDePg4X3msBe09+xPuTMGXACcYQVLyIwkmUE9+5m0Y3634363z3YNk/xqQyXi4uYk3lSEXWcaAgu/QHBPoZwSfOPwMjGwUMgfpAPxY/AnJukxU2qCCjzm8CubtK7ap51L8trITWfGCbazrQ=
*/