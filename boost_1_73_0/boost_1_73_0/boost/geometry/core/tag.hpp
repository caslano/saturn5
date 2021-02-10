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
AjUELW7lSFbIE2joWcOvZrrEEaTkZQjJGMKAKsB9nErvmEW8cuqjXYJTfW9vy5YCM+jlS/UzHpFYnFSjce8qdoR1NBtUf/VKrUF9LPZs7+vEYuszFXs+pVTkZwtm2nCiDDlOpGjm2rCSDfW8Ph52QGGDs8rsQPYH4+yCVkWe6jDXaB/WKrQkn4R1+aNMxXxEnhIx2d/IxpXdSUriwQ06qFabag1113Ux5YFMn9e/spvh8zOyT7ftLIzk/LM++krGdR0hR/z6ppMe5BEqcQlagZZPiJ2c8MDN+dbBwem746OPb985ZAn0mgT970rYHty15w4wdnL161RONEXXykWL3KiH7ulT0bP57QqZXiD3RObVBC8srvxzaz+Vebiaj/GnQhzfMlfrkH4++XDUPunsHB3+1j4+2T86PGGWNwYD+h9xp3wcDBQ7A3aS+DJMcxk/CiIqc2yvV80gu0Fz2LC3pgg2SSLN7g+Ry67LQDt50onDHE1DAaapjA5ggIntW4RSUGF8heXWegArtZT7R3mzZe3qaY2gqEsLpe+l3WOWOrxm/o/xNyB2rAMj0PPrxAmPyU4yHOFpKL1oyQEYx7keAI3FhnqiFtG7yi0vqbWGWoFlZkvDagNBu3l0GRbB8JajCRBBXcEMrcAZ4K5j
*/