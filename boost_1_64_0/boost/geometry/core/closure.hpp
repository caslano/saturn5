// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_CLOSURE_HPP
#define BOOST_GEOMETRY_CORE_CLOSURE_HPP

#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>

namespace boost { namespace geometry
{


/*!
\brief Enumerates options for defining if polygons are open or closed
\ingroup enum
\details The enumeration closure_selector describes options for if a polygon is
    open or closed. In a closed polygon the very first point (per ring) should
    be equal to the very last point.
    The specific closing property of a polygon type is defined by the closure
    metafunction. The closure metafunction defines a value, which is one of the
    values enumerated in the closure_selector

\qbk{
[heading See also]
[link geometry.reference.core.closure The closure metafunction]
}
*/
enum closure_selector
{
    /// Rings are open: first point and last point are different, algorithms
    /// close them explicitly on the fly
    open = 0,
    /// Rings are closed: first point and last point must be the same
    closed = 1,
    /// (Not yet implemented): algorithms first figure out if ring must be
    /// closed on the fly
    closure_undertermined = -1
};

namespace traits
{

/*!
    \brief Traits class indicating if points within a
        ring or (multi)polygon are closed (last point == first point),
        open or not known.
    \ingroup traits
    \par Geometries:
        - ring
    \tparam G geometry
*/
template <typename G>
struct closure
{
    static const closure_selector value = closed;
};


} // namespace traits


#ifndef DOXYGEN_NO_DETAIL
namespace core_detail { namespace closure
{

struct closed
{
    static const closure_selector value = geometry::closed;
};


/// Metafunction to define the minimum size of a ring:
/// 3 for open rings, 4 for closed rings
template <closure_selector Closure>
struct minimum_ring_size {};

template <>
struct minimum_ring_size<geometry::closed> : boost::mpl::size_t<4> {};

template <>
struct minimum_ring_size<geometry::open> : boost::mpl::size_t<3> {};


}} // namespace detail::point_order
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct closure
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Box>
struct closure<point_tag, Box> : public core_detail::closure::closed {};

template <typename Box>
struct closure<box_tag, Box> : public core_detail::closure::closed {};

template <typename Box>
struct closure<segment_tag, Box> : public core_detail::closure::closed {};

template <typename LineString>
struct closure<linestring_tag, LineString>
    : public core_detail::closure::closed {};


template <typename Ring>
struct closure<ring_tag, Ring>
{
    static const closure_selector value
        = geometry::traits::closure<Ring>::value;
};

// Specialization for Polygon: the closure is the closure of its rings
template <typename Polygon>
struct closure<polygon_tag, Polygon>
{
    static const closure_selector value = core_dispatch::closure
        <
            ring_tag,
            typename ring_type<polygon_tag, Polygon>::type
        >::value ;
};

template <typename MultiPoint>
struct closure<multi_point_tag, MultiPoint>
    : public core_detail::closure::closed {};

template <typename MultiLinestring>
struct closure<multi_linestring_tag, MultiLinestring>
    : public core_detail::closure::closed {};

// Specialization for MultiPolygon: the closure is the closure of Polygon's rings
template <typename MultiPolygon>
struct closure<multi_polygon_tag, MultiPolygon>
{
    static const closure_selector value = core_dispatch::closure
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::value ;
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{value, closure (clockwise\, counterclockwise),
    \meta_geometry_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/closure.qbk]}
*/
template <typename Geometry>
struct closure
{
    static const closure_selector value = core_dispatch::closure
        <
            typename tag<Geometry>::type,
            typename util::bare_type<Geometry>::type
        >::value;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_CLOSURE_HPP

/* closure.hpp
RSXhXdEPENQrtd/K5oiDcrpT6Ooi8xyZB5wFqECwjMlzeKP08lx1816u5Y+f2iaaWZtl9XU8QuudaLyrP8p9EK/ws0gX9j39QW6VoilBHCX5xkFpkaVGM7hucDcjXaxKSplvfOoKPB80PjXHd1BM522tFMih6uXHRWqxwbmsY4eIlqt3WRu3DAitGP5kYXD5uMKit031Cbk6p3sG67wWKXEEer596J5JyaiQqZwhGkUUSOSXKT6fVBIIwfHz3vahSyjfTAxJck250HwUE3SgNsFVI7IyfxJ4O8G+ETP4I8Oslrr9dtyyK2Uk081yR5jyqLemNKpoJ07wzK8eb+V91YtmXPFByJw1vQbSljDvJKlrgTeSJCzrbrGWVSgD7ggMoVm9fJ0qDkY+WL18sI+MHcKng2w41+05w7X221YlP/NjEWmB3zGQnst4Vgs5/M5/7h5B68fRK+Li2eEGpHuuUSXfPzNo7ENT0VIdoK3Swn6kAv0Inyu86DFRqaEGQJoJCUWp417paQxfGgmvxq6ftwvrY77aS8Fi6rJvirm9jf68g6M/74tn8/N6Z+yXuvylLdSifGdoIQIPIFp+daENeiA8Siv/WTMOBuW7InGvkDVLqPh26qMcaquWWdP5QTJOqSKBFvxvJbp25dw8XMdVnAuWtWHNVskkwqEpsqacR6/rrg+9P5ko7/7vhdYVv8V7Dvdmi0XqdJqeufsgGemT+hr2xsENCRcg8Rb8cJFfYibat1VRXz6cLY+PoSPdf2leDvZ96WGbJdh3PfER4mribcQlxAXEEuJlRC9xDDGD2JvYhRhP3P8bwfeJbxJfINYS1xDvJ95JrCQuIs4hXkEsIuYRRxD7EVOJbYlfPiT4EXEX8SXiM8QniA8S7yIuJ95ALCVeRZxMPJ+YRRxE7EHsQLQQ9/xaMP1+5vMewenEq4gzibOIJcTvEucQ5xJLiWVEH3EBcSFxEXEx8QZiOfEm4hLizcRK4jLicuIK4kribcTbiXcSVxHvIt5NvIe4mngf8X7iA8QHiQ8RHyY+QnyUuIb4OPEJYg1xHXE9cQOxlriR+AxxE7GRuIX4HPEF4jbiS8Q/EV8h7iS+TnyT+BZxF/Ft4rvE94gm8X3iB8SPiLuJe4ifEfcS9xMPEL8kHiJa7hW0ER3EeGIisS0xidiBmEzsROxC7EpMJZ5O7EHsRUwj9iamE/sRBxAHEc8iDiVmEIcTRxDPJWYRRxJHEccQc4l5xHzi+UQ3cRzRS5xALCJOJE4mXkKcQryMOJV4BXE68SriTOIsYgnxu8Q5xLnEUmIZ0UdcQFxIXERcTLyBWE68ibiEeDOxkriMuJy4griSeBvxduKdxFXEu4h3E+8hribeR7yf+ADxQeJDxIeJjxAfJa4hPk58glhDXEdcT9xArCVuJD5D3ERsJG4hPkc891ds/3x+ifgn4ivEncTXiW8S3yLuIr5NfJf4HtEkvk/8gPgRcTdxD/Ez4l7ifuIB4pfEQ0TLakEb0UGMJyYS2xKTiB2IycROxC7ErsRU4unEHsRexDRib2I6sR9xAHEQ8SziUGIGcThxBPFcYhZxJHEUcQwxl5hHzCeeT3QTxxG9xAnEIuJE4mTiJcQpxMuIU4lXEKcTryLOJM4ilhC/S5xDnEssJZYRfcQFxIXERcTFxBuI5cSbiEuINxMricuIy4kriCuJtxFvJ95JXEW8i3g38R7iauJ9xPuJDxAfJD5EfJj4CPFR4hri48QniDXEdcT1xA3EWuJG4jPETcRG4hbic8QXiNuILxH/RHyFuJP4OvFN4lvEXcS3ie8S3yOaxPeJHxA/Iu4m7iF+RtxL3E88QPySeIho+bmgjeggxhM=
*/