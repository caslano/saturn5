// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_TAG_HPP
#define BOOST_GEOMETRY_CORE_TAG_HPP


#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>


namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class to attach a tag to a geometry
\details All geometries should implement a traits::tag<G>::type metafunction to indicate their
    own geometry type.
\ingroup traits
\par Geometries:
    - all geometries
\par Specializations should provide:
    - typedef XXX_tag type; (point_tag, box_tag, ...)
\tparam Geometry geometry
*/
template <typename Geometry, typename Enable = void>
struct tag
{
    typedef void type;
};

} // namespace traits



/*!
\brief \brief_meta{type, tag, \meta_geometry_type}
\details With Boost.Geometry, tags are the driving force of the tag dispatching
    mechanism. The tag metafunction is therefore used in every free function.
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/tag.qbk]}
*/
template <typename Geometry>
struct tag
{
    typedef typename traits::tag
        <
            typename geometry::util::bare_type<Geometry>::type
        >::type type;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_TAG_HPP

/* tag.hpp
nIU/LD8D7YvOwN0f/wB/XVwJ8MlUToYvt0FNxRew/JkIqNlsh9rPP4LaT3Kh9CULbI2LGOUpf+i4yTDtsAu6rPgG+s3MhxEHz8OoI5ch9eBlGLLvMsSWXYRn9lyEJ3ZcAOvWC/C/TVWgcVSB7PPzEIa6uB910fGTs/C7ZWehHeoilMqw4nVOBgr7NkJN6Rqo2boUzuX0ArTN6cL6T86cCjOOupHneUgpWg+j1u2B1yqrYdyxyzD88GUYduAyDMQ6ec55CXpjnTyGcphonWy4AEpPnaw+762TEKyTfyw5AbBqeoMM+zcDzEqA+eNTVjS2/5defR3erXRz+l15Aga/VwAzvroEU76qhldRjjFHL0P6l1gn+7k66V96CaJ2Yp1suwhdMY/ui/Pwb9RFp0/PQejqc/AX1AXd1/mvpSjD6hmsfLC/DNHvFYOsW39Q/rfbr4Xlp7+WCx+edMNj2y+CBZ9r+OJVMGnHfnj722qYfqqa7bHMPF4No1AXKVgng/ddghiUoy/WSU/UhQXr5L9YJ2qsky6oi39hnfyNr5POxV8BrHkTus/dAAFv7YUHojNo+c8Lyx8x6U3IP1UDfWgd70R+S/fC8PylMOcHF8w+7YI3v3XBNNQFVyfVfJ1cEtfJdq5ODBuqQIF18iCrk3NwH9rnH5djnRT9AAEznfC711bAg0+K98GOnPI2FH5bA3FoZ/3R3nvvrIKMOYXw
*/